#include <cstdint>
#include <string>
#include <vector>
#include <utility>

#include "grammar/Visitor.h"
#include "exceptions/NotImplementedException.h"

Scope &Visitor::currentScope()
{
    return this->scopes.back();
}

llvm::Value *Visitor::getVariable(const std::string &name)
{
    for (auto it = this->scopes.rbegin(); it != this->scopes.rend(); it++) {
        auto variable = it->getVariable(name);
        if (variable) {
            return variable;
        }
    }
    return nullptr;
}

//Create an unconditional branch if the current block doesn't have a terminator.
//This function is safer than builder.CreateBr(llvm::BasicBlock* BB),
//because if the current block already has a terminator, it does nothing.
//For example, when generating if-statement, we create three blocks: ThenBB, ElseBB, MergeBB.
//At the end of ThenBB and ElseBB, an unconditional branch to MergeBB needs to be created respectively,
//UNLESS ThenBB or ElseBB is already terminated.
//e.g.
//	if (i) break;
//	else continue;
llvm::BranchInst* Visitor::TerminateBlockByBr(llvm::BasicBlock* BB)
{
	//If not terminated, jump to the target block
	if (!builder.GetInsertBlock()->getTerminator())
		return builder.CreateBr(BB);
	else
		return nullptr;
}

bool Visitor::TypeCheck(llvm::Type* LHS, llvm::Type* RHS)
{
    if (LHS == RHS)
        return true;
    else if (LHS->isIntegerTy() && RHS->isIntegerTy())
        return true;
    else if (LHS->isFloatingPointTy() && RHS->isFloatingPointTy())
        return true;
    else if (LHS->isPointerTy() && RHS->isPointerTy())
        return true;
    else if (LHS->isPointerTy() && RHS->isIntegerTy())
        return true;
    else if (LHS->isIntegerTy() && RHS->isPointerTy())
        return true;
    else if (LHS->isIntegerTy() && RHS->isFloatingPointTy())
        return true;
    else if (LHS->isFloatingPointTy() && RHS->isIntegerTy())
        return true;
    else return false;
}

// Cast a integer, or a floating-point number, or a pointer to i1 integer.
// Return NULL if failed.
// This function is very useful when generating a condition value for "if", "while", "for" statements.
llvm::Value* Visitor::Cast2I1(llvm::Value* Value) {
	if (Value->getType() == builder.getInt1Ty())
		return Value;
	else if (Value->getType()->isIntegerTy())
		return builder.CreateICmpNE(Value, llvm::ConstantInt::get((llvm::IntegerType*)Value->getType(), 0, true));
	else if (Value->getType()->isFloatingPointTy())
		return builder.CreateFCmpONE(Value, llvm::ConstantFP::get(Value->getType(), 0.0));
	else if (Value->getType()->isPointerTy())
		return builder.CreateICmpNE(builder.CreatePtrToInt(Value, builder.getInt64Ty()), builder.getInt64(0));
	else {
		throw std::logic_error("Cannot cast to bool type.");
		return nullptr;
	}
}

// Type casting
// Supported:
// 1. Int -> Int, FP, Pointer
// 2. FP -> Int, FP
// 3. Pointer -> Int, Pointer
//Other types are not supported, and will return NULL.
llvm::Value* Visitor::TypeCasting(llvm::Value* Value, llvm::Type* Type) {
	if (Value->getType() == Type) {
		return Value;
	}
	else if (Type == builder.getInt1Ty()) {	//Int1 (bool) is special.
		return Cast2I1(Value);
	}
	else if (Value->getType()->isIntegerTy() && Type->isIntegerTy()) {
		return builder.CreateIntCast(Value, Type, !Value->getType()->isIntegerTy(1));
	}
	else if (Value->getType()->isIntegerTy() && Type->isFloatingPointTy()) {
		return Value->getType()->isIntegerTy(1) ?
			builder.CreateUIToFP(Value, Type) : builder.CreateSIToFP(Value, Type);
	}
	else if (Value->getType()->isIntegerTy() && Type->isPointerTy()) {
		return builder.CreateIntToPtr(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isIntegerTy()) {
		return builder.CreateFPToSI(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isFloatingPointTy()) {
		return builder.CreateFPCast(Value, Type);
	}
	else if (Value->getType()->isPointerTy() && Type->isIntegerTy()) {
		return builder.CreatePtrToInt(Value, Type);
	}
	else if (Value->getType()->isPointerTy() && Type->isPointerTy()) {
		return builder.CreatePointerCast(Value, Type);
	}
	else {
		return nullptr;
	}
}

//Upgrade the type, given another type.
//1. int1
//2. int8
//3. int16
//4. int32
//5. int64
//6. float
//7. double
//Return NULL if failed.
//For example,
//	TypeUpgrading(int16, int32) -> int32
//	TypeUpgrading(int32, double) -> double
//	TypeUpgrading(int64, float) -> float
llvm::Value* Visitor::TypeUpgrading(llvm::Value* Value, llvm::Type* Type) {
	if (Value->getType()->isIntegerTy() && Type->isIntegerTy()) {
		size_t Bit1 = ((llvm::IntegerType*)Value->getType())->getBitWidth();
		size_t Bit2 = ((llvm::IntegerType*)Type)->getBitWidth();
		if (Bit1 < Bit2)
			return builder.CreateIntCast(Value, Type, Bit1 != 1);
		else return Value;
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isFloatingPointTy()) {
		if (Value->getType()->isFloatTy() && Type->isDoubleTy())
			return builder.CreateFPCast(Value, Type);
		else return Value;
	}
	else if (Value->getType()->isIntegerTy() && Type->isFloatingPointTy()) {
		return Value->getType()->isIntegerTy(1) ?
			builder.CreateUIToFP(Value, Type) : builder.CreateSIToFP(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isIntegerTy()) {
		return Value;
	}
	else return nullptr;
}

//Upgrade two types at the same time.
//1. int1
//2. int8
//3. int16
//4. int32
//5. int64
//6. float
//7. double
//Return false if failed.
//For example,
//	TypeUpgrading(int16, int32) -> int32
//	TypeUpgrading(int32, double) -> double
//	TypeUpgrading(int64, float) -> float
bool Visitor::TypeUpgrading(llvm::Value*& Value1, llvm::Value*& Value2) {
	if (Value1->getType()->isIntegerTy() && Value2->getType()->isIntegerTy()) {
		size_t Bit1 = ((llvm::IntegerType*)Value1->getType())->getBitWidth();
		size_t Bit2 = ((llvm::IntegerType*)Value2->getType())->getBitWidth();
		if (Bit1 < Bit2)
			Value1 = builder.CreateIntCast(Value1, Value2->getType(), Bit1 != 1);
		else if (Bit1 > Bit2)
			Value2 = builder.CreateIntCast(Value2, Value1->getType(), Bit2 != 1);
		return true;
	}
	else if (Value1->getType()->isFloatingPointTy() && Value2->getType()->isFloatingPointTy()) {
		if (Value1->getType()->isFloatTy() && Value2->getType()->isDoubleTy())
			Value1 = builder.CreateFPCast(Value1, builder.getDoubleTy());
		else if (Value1->getType()->isDoubleTy() && Value2->getType()->isFloatTy())
			Value2 = builder.CreateFPCast(Value2, builder.getDoubleTy());
		return true;
	}
	else if (Value1->getType()->isIntegerTy() && Value2->getType()->isFloatingPointTy()) {
		Value1 = Value1->getType()->isIntegerTy(1) ?
			builder.CreateUIToFP(Value1, Value2->getType()) : builder.CreateSIToFP(Value1, Value2->getType());
		return true;
	}
	else if (Value1->getType()->isFloatingPointTy() && Value2->getType()->isIntegerTy()) {
		Value2 = Value2->getType()->isIntegerTy(1) ?
			builder.CreateUIToFP(Value2, Value1->getType()) : builder.CreateSIToFP(Value2, Value1->getType());
		return true;
	}
	else return false;
}

//Create an equal-comparison instruction. This function will automatically do type casting
//if the two input values are not of the same type.
llvm::Value* Visitor::CreateCmpEQ(llvm::Value* LHS, llvm::Value* RHS) {
	//Arithmatic compare
	if (TypeUpgrading(LHS, RHS)) {
		if (LHS->getType()->isIntegerTy())
			return builder.CreateICmpEQ(LHS, RHS);
		else
			return builder.CreateFCmpOEQ(LHS, RHS);
	}
	//Pointer compare
	if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
		return builder.CreateICmpEQ(
			builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
			builder.CreatePtrToInt(RHS, builder.getInt64Ty())
		);
	}
	else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
		return builder.CreateICmpEQ(
			builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
			TypeUpgrading(RHS, builder.getInt64Ty())
		);
	}
	else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
		return builder.CreateICmpEQ(
			TypeUpgrading(LHS, builder.getInt64Ty()),
			builder.CreatePtrToInt(RHS, builder.getInt64Ty())
		);
	}
	throw std::domain_error("Comparison \"==\" using unsupported type combination.");
	return nullptr;
}

llvm::Value* Visitor::CreateCmpNEQ(llvm::Value* LHS, llvm::Value* RHS)
{
    if (TypeUpgrading(LHS, RHS)) {
        if (LHS->getType()->isIntegerTy())
            return builder.CreateICmpNE(LHS, RHS);
        else
            return builder.CreateFCmpONE(LHS, RHS);
    }
    //Pointer compare
    if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
        return builder.CreateICmpNE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
        return builder.CreateICmpNE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            TypeUpgrading(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
        return builder.CreateICmpNE(
            TypeUpgrading(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    throw std::domain_error("Comparison \"!=\" using unsupported type combination.");
    return nullptr;
}

llvm::Value* Visitor::CreateCmpGT(llvm::Value* LHS, llvm::Value* RHS)
{
    //Arithmatic compare
    if (TypeUpgrading(LHS, RHS)) {
        if (LHS->getType()->isIntegerTy())
            return builder.CreateICmpSGT(LHS, RHS);
        else
            return builder.CreateFCmpOGT(LHS, RHS);
    }
    //Pointer compare
    if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
        return builder.CreateICmpUGT(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
        return builder.CreateICmpUGT(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            TypeUpgrading(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
        return builder.CreateICmpUGT(
            TypeUpgrading(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    throw std::domain_error("Comparison \">\" using unsupported type combination.");
    return nullptr;
}

llvm::Value* Visitor::CreateCmpGE(llvm::Value* LHS, llvm::Value* RHS)
{
    //Arithmatic compare
    if (TypeUpgrading(LHS, RHS)) {
        if (LHS->getType()->isIntegerTy())
            return builder.CreateICmpSGE(LHS, RHS);
        else
            return builder.CreateFCmpOGE(LHS, RHS);
    }
    //Pointer compare
    if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
        return builder.CreateICmpUGE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
        return builder.CreateICmpUGE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            TypeUpgrading(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
        return builder.CreateICmpUGE(
            TypeUpgrading(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    throw std::domain_error("Comparison \">=\" using unsupported type combination.");
    return nullptr;
}

llvm::Value* Visitor::CreateCmpLT(llvm::Value* LHS, llvm::Value* RHS)
{
    //Arithmatic compare
    if (TypeUpgrading(LHS, RHS)) {
        if (LHS->getType()->isIntegerTy())
            return builder.CreateICmpSLT(LHS, RHS);
        else
            return builder.CreateFCmpOLT(LHS, RHS);
    }
    //Pointer compare
    if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
        return builder.CreateICmpULT(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
        return builder.CreateICmpULT(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            TypeUpgrading(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
        return builder.CreateICmpULT(
            TypeUpgrading(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    throw std::domain_error("Comparison \"<\" using unsupported type combination.");
    return nullptr;
}

llvm::Value* Visitor::CreateCmpLE(llvm::Value* LHS, llvm::Value* RHS)
{
    //Arithmatic compare
    if (TypeUpgrading(LHS, RHS)) {
        if (LHS->getType()->isIntegerTy())
            return builder.CreateICmpSLE(LHS, RHS);
        else
            return builder.CreateFCmpOLE(LHS, RHS);
    }
    //Pointer compare
    if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType()) {
        return builder.CreateICmpULE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
        return builder.CreateICmpULE(
            builder.CreatePtrToInt(LHS, builder.getInt64Ty()),
            TypeUpgrading(RHS, builder.getInt64Ty())
        );
    }
    else if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
        return builder.CreateICmpULE(
            TypeUpgrading(LHS, builder.getInt64Ty()),
            builder.CreatePtrToInt(RHS, builder.getInt64Ty())
        );
    }
    throw std::domain_error("Comparison \"<=\" using unsupported type combination.");
    return nullptr;
}

//Create an addition instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int + Int -> Int			(TypeUpgrading)
//2. Int + FP -> FP				(TypeUpgrading)
//3. Int + Pointer -> Pointer
//4. FP + Int -> FP				(TypeUpgrading)
//2. FP + FP -> FP				(TypeUpgrading)
//3. Pointer + Int -> Pointer
llvm::Value* Visitor::CreateAdd(llvm::Value* LHS, llvm::Value* RHS) {
	if (TypeUpgrading(LHS, RHS)) {
		if (LHS->getType()->isIntegerTy())
			return builder.CreateAdd(LHS, RHS);
		else
			return builder.CreateFAdd(LHS, RHS);
	}
	if (LHS->getType()->isIntegerTy() && RHS->getType()->isPointerTy()) {
		auto TMP = LHS;
		LHS = RHS;
		RHS = TMP;
	}
	if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
		return builder.CreateGEP(LHS->getType()->getNonOpaquePointerElementType(), LHS, RHS);
	}
	throw std::logic_error("Addition using unsupported type combination.");
	return nullptr;
}

//Create a subtraction instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int - Int -> Int			(TypeUpgrading)
//2. Int - FP -> FP				(TypeUpgrading)
//3. FP - Int -> FP				(TypeUpgrading)
//4. FP - FP -> FP				(TypeUpgrading)
//5. Pointer - Int -> Pointer
//6. Pointer - Pointer -> Int64
llvm::Value* Visitor::CreateSub(llvm::Value* LHS, llvm::Value* RHS) {
	if (TypeUpgrading(LHS, RHS)) {
		if (LHS->getType()->isIntegerTy())
			return builder.CreateSub(LHS, RHS);
		else
			return builder.CreateFSub(LHS, RHS);
	}
	if (LHS->getType()->isPointerTy() && RHS->getType()->isIntegerTy()) {
		return builder.CreateGEP(LHS->getType()->getNonOpaquePointerElementType(), LHS, builder.CreateNeg(RHS));
	}
	if (LHS->getType()->isPointerTy() && LHS->getType() == RHS->getType())
		return builder.CreatePtrDiff(LHS->getType()->getNonOpaquePointerElementType(), LHS, RHS);
	throw std::logic_error("Subtraction using unsupported type combination.");
	return nullptr;
}

//Create a multiplication instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int * Int -> Int			(TypeUpgrading)
//2. Int * FP -> FP				(TypeUpgrading)
//3. FP * Int -> FP				(TypeUpgrading)
//4. FP * FP -> FP				(TypeUpgrading)
llvm::Value* Visitor::CreateMul(llvm::Value* LHS, llvm::Value* RHS) {
	if (TypeUpgrading(LHS, RHS)) {
		if (LHS->getType()->isIntegerTy())
			return builder.CreateMul(LHS, RHS);
		else
			return builder.CreateFMul(LHS, RHS);
	}
	else {
		throw std::logic_error("Multiplication operator \"*\" must only be applied to integers or floating-point numbers.");
		return nullptr;
	}
}

//Create a division instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int / Int -> Int			(TypeUpgrading)
//2. Int / FP -> FP				(TypeUpgrading)
//3. FP / Int -> FP				(TypeUpgrading)
//4. FP / FP -> FP				(TypeUpgrading)
llvm::Value* Visitor::CreateDiv(llvm::Value* LHS, llvm::Value* RHS) {
	if (TypeUpgrading(LHS, RHS)) {
		if (LHS->getType()->isIntegerTy())
			return builder.CreateSDiv(LHS, RHS);
		else
			return builder.CreateFDiv(LHS, RHS);
	}
	else {
		throw std::logic_error("Division operator \"/\" must only be applied to integers or floating-point numbers.");
		return nullptr;
	}
}

//Create a modulo instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int % Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateMod(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Modulo operator \"%\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateSRem(LHS, RHS);
}

//Create a shl instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int << Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateShl(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Left shifting operator \"<<\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateShl(LHS, RHS);
}

//Create a shr instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int >> Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateShr(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Left shifting operator \"<<\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateAShr(LHS, RHS);
}

//Create a bitwise AND instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int & Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateBitwiseAND(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Bitwise AND operator \"&\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateAnd(LHS, RHS);
}

//Create a bitwise OR instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int | Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateBitwiseOR(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Bitwise OR operator \"|\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateOr(LHS, RHS);
}

//Create a bitwise XOR instruction. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int ^ Int -> Int			(TypeUpgrading)
llvm::Value* Visitor::CreateBitwiseXOR(llvm::Value* LHS, llvm::Value* RHS) {
	if (!(LHS->getType()->isIntegerTy() && RHS->getType()->isIntegerTy())) {
		throw std::domain_error("Bitwise XOR operator \"^\" must be applied to 2 integers.");
		return nullptr;
	}
	TypeUpgrading(LHS, RHS);
	return builder.CreateXor(LHS, RHS);
}

//Create an assignment. This function will automatically do type casting
//if the two input values are not of the same type.
//Supported:
//1. Int = FP
//2. Int = Int
//3. Int = Pointer
//4. FP = Int
//5. FP = FP
//6. Pointer = Int
//7. Pointer = Pointer
//8. Exactly the same type assignment
//The "pLHS" argument should be a pointer pointing to the variable (the left-value in C)
llvm::Value* Visitor::CreateAssignment(llvm::Value* pLHS, llvm::Value* RHS) {
	RHS = TypeCasting(RHS, pLHS->getType()->getNonOpaquePointerElementType());
	if (RHS == nullptr) {
		throw std::domain_error("Assignment with values that cannot be cast to the target type.");
		return nullptr;
	}
	builder.CreateStore(RHS, pLHS);
	return pLHS;
}

//Create a load instruction.
//This is different to builder.CreateLoad.
//If the argument is a pointer to an array, this function will
//return a pointer to its first element, instead of loading an array.
//This compiles with the C standard. For example:
//int a[10];
//int * b = a;	//When used as a right value, "a" is an integer pointer instead of an array. 
llvm::Value* Visitor::CreateLoad(llvm::Value* pLHS) {
	//For array types, return the pointer to its first element
	if (pLHS->getType()->getNonOpaquePointerElementType()->isArrayTy())
		return builder.CreatePointerCast(pLHS, pLHS->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());
	else
		return builder.CreateLoad(pLHS->getType()->getNonOpaquePointerElementType(), pLHS);
}

std::any Visitor::visitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx)
{
    visitDeclarationseq(ctx->declarationseq());
    return nullptr;
}

std::any Visitor::visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx)
{
    for (auto Literal : ctx->literal())
        return visitLiteral(Literal);
}

std::any Visitor::visitIdExpression(ZigCCParser::IdExpressionContext *ctx)
{
    if (auto UnqualifiedId = ctx->unqualifiedId()) {
        return visitUnqualifiedId(UnqualifiedId);
    } else if (auto QualifiedId = ctx->qualifiedId()) {
        return visitQualifiedId(QualifiedId);
    }
}

std::any Visitor::visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx)
{
    if (auto Identifier = ctx->Identifier()) {
        return std::string(Identifier->getText());
    } else if (auto OperatorFunctionId = ctx->operatorFunctionId()) {
        return visitOperatorFunctionId(OperatorFunctionId);
    } else if (auto ConversionFunctionId = ctx->conversionFunctionId()) {
        return visitConversionFunctionId(ConversionFunctionId);
    } else if (auto LiteralOperatorId = ctx->literalOperatorId()) {
        return visitLiteralOperatorId(LiteralOperatorId);
    } else if (auto TemplateId = ctx->templateId()) {
        return visitTemplateId(TemplateId);
    }
}

std::any Visitor::visitQualifiedId(ZigCCParser::QualifiedIdContext *ctx)
{

}

std::any Visitor::visitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx)
{

}

std::any Visitor::visitLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx)
{

}

std::any Visitor::visitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx)
{

}

std::any Visitor::visitLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx)
{

}

std::any Visitor::visitCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx)
{

}

std::any Visitor::visitCaptureList(ZigCCParser::CaptureListContext *ctx)
{

}

std::any Visitor::visitCapture(ZigCCParser::CaptureContext *ctx)
{

}

std::any Visitor::visitSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx)
{

}

std::any Visitor::visitInitcapture(ZigCCParser::InitcaptureContext *ctx)
{

}

std::any Visitor::visitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx)
{

}

std::any Visitor::visitPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx)
{
    if (ctx->PlusPlus() != nullptr) { // i++
        llvm::Value* operand_alloc = nullptr;
        llvm::Value* operand = nullptr;
        auto PostfixExpression = visitPostfixExpression(ctx->postfixExpression());
        if (PostfixExpression.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(PostfixExpression);
            operand_alloc = this->getVariable(name);
            if (operand_alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(PostfixExpression) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(operand_alloc->getType()->getNonOpaquePointerElementType(), operand_alloc);
        } else if (PostfixExpression.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(PostfixExpression);
        }
        llvm::Value* ret = operand;
        
        // 类型检查
        if (operand->getType()->isIntegerTy() ||
            operand->getType()->isFloatingPointTy() ||
            operand->getType()->isPointerTy()) {
            llvm::Value* result = builder.CreateAdd(operand, builder.getInt1(1));
            builder.CreateStore(result, operand_alloc);
            return ret;
        } else {
            std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(PostfixExpression) << "'" << std::endl;
            return nullptr;
        }
    } else if (ctx->MinusMinus() != nullptr) { // i--
        llvm::Value* operand_alloc = nullptr;
        llvm::Value* operand = nullptr;
        auto PostfixExpression = visitPostfixExpression(ctx->postfixExpression());
        if (PostfixExpression.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(PostfixExpression);
            operand_alloc = this->getVariable(name);
            if (operand_alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(PostfixExpression) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(operand_alloc->getType()->getNonOpaquePointerElementType(), operand_alloc);
        } else if (PostfixExpression.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(PostfixExpression);
        }
        llvm::Value* ret = operand;
        // 类型检查
        if (operand->getType()->isIntegerTy() ||
            operand->getType()->isFloatingPointTy() ||
            operand->getType()->isPointerTy()) {
            llvm::Value* result = builder.CreateSub(operand, builder.getInt1(1));
            builder.CreateStore(result, operand_alloc);
            return ret;
        } else {
            std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(PostfixExpression) << "'" << std::endl;
            return nullptr;
        }
    } else if (auto PrimaryExpression = ctx->primaryExpression()) {
        return visitPrimaryExpression(PrimaryExpression);
    }
}

std::any Visitor::visitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx)
{

}

std::any Visitor::visitExpressionList(ZigCCParser::ExpressionListContext *ctx)
{

}

std::any Visitor::visitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx)
{

}

std::any Visitor::visitUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx)
{
    if (ctx->unaryExpression() != nullptr) { // 表明有单目运算符计算需求
        llvm::Value* operand_alloc = nullptr;
        llvm::Value* operand = nullptr;
        auto UnaryExpression = visitUnaryExpression(ctx->unaryExpression());
        if (UnaryExpression.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(UnaryExpression);
            operand_alloc = this->getVariable(name);
            if (operand_alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(UnaryExpression) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(operand_alloc->getType()->getNonOpaquePointerElementType(), operand_alloc);
        } else if (UnaryExpression.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(UnaryExpression);
        }
        if (ctx->PlusPlus() != nullptr) { // ++i
            // 类型检查
            if (operand->getType()->isIntegerTy() ||
                operand->getType()->isFloatingPointTy() ||
                operand->getType()->isPointerTy()) {
                operand = builder.CreateAdd(operand, builder.getInt1(1));
                builder.CreateStore(operand, operand_alloc);
                return operand;
            } else {
                std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(UnaryExpression) << "'" << std::endl;
                return nullptr;
            }
        } else if (ctx->MinusMinus() != nullptr) { // --i
            // 类型检查
            if (operand->getType()->isIntegerTy() ||
                operand->getType()->isFloatingPointTy() ||
                operand->getType()->isPointerTy()) {
                operand = builder.CreateSub(operand, builder.getInt1(1));
                builder.CreateStore(operand, operand_alloc);
                return operand;
            } else {
                std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(UnaryExpression) << "'" << std::endl;
                return nullptr;
            }
        } else if (ctx->Sizeof() != nullptr) { // sizeof
            return DL->getTypeAllocSize(operand->getType());
        } else if (auto UnaryOp = ctx->unaryOperator()) {
            if (UnaryOp->Or() != nullptr) {
                // TODO: 这是啥情况，没看懂 |x 是什么意思
                return nullptr;
            } else if (UnaryOp->And() != nullptr) {
                return operand_alloc;
            } else if (UnaryOp->Star() != nullptr) {
                return builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
            } else if (UnaryOp->Plus() != nullptr) {
                return operand;
            } else if (UnaryOp->Minus() != nullptr) {
                // 类型检查
                if (operand->getType()->isIntegerTy()) {
                    return builder.CreateNeg(operand);
                } else if (operand->getType()->isFloatingPointTy()) {
                    return builder.CreateFNeg(operand);
                } else {
                    std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(UnaryExpression) << "'" << std::endl;
                    return nullptr;
                }
            } else if (UnaryOp->Tilde() != nullptr) {
                // 类型检查
                if (operand->getType()->isIntegerTy()) {
                    return builder.CreateNot(operand);
                } else {
                    std::cout << "Error: Invalid argument type '" << std::any_cast<std::string>(UnaryExpression) << "'" << std::endl;
                    return nullptr;
                }
            } else if (UnaryOp->Not() != nullptr) {
                return builder.CreateICmpEQ(Cast2I1(operand), builder.getInt1(false));
            }
        }
    } else if (auto PostfixExpression = ctx->postfixExpression()) {
        return visitPostfixExpression(PostfixExpression);
    }
}

std::any Visitor::visitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx)
{

}

std::any Visitor::visitNewExpression(ZigCCParser::NewExpressionContext *ctx)
{

}

std::any Visitor::visitNewPlacement(ZigCCParser::NewPlacementContext *ctx)
{

}

std::any Visitor::visitNewTypeId(ZigCCParser::NewTypeIdContext *ctx)
{

}

std::any Visitor::visitNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx)
{

}

std::any Visitor::visitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx)
{

}

std::any Visitor::visitNewInitializer(ZigCCParser::NewInitializerContext *ctx)
{

}

std::any Visitor::visitDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx)
{

}

std::any Visitor::visitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx)
{

}

std::any Visitor::visitCastExpression(ZigCCParser::CastExpressionContext *ctx)
{
    if (auto UnaryExpression = ctx->unaryExpression()) {
        return visitUnaryExpression(UnaryExpression);
    }
}

std::any Visitor::visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx)
{
    for (auto CastExpression : ctx->castExpression())
        return visitCastExpression(CastExpression);
}

std::any Visitor::visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx)
{
    // 此处 * 是作为乘号的情况，作为解引用是一元运算符
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto pointerMemberExpression_0 = visitPointerMemberExpression(ctx->pointerMemberExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (pointerMemberExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(pointerMemberExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(pointerMemberExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (pointerMemberExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(pointerMemberExpression_0);
    }
    if (ctx->pointerMemberExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->pointerMemberExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto pointerMemberExpression_i = visitPointerMemberExpression(ctx->pointerMemberExpression(i));
        if (pointerMemberExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(pointerMemberExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(pointerMemberExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (pointerMemberExpression_i.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(pointerMemberExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型捡查与转化
        if (ctx->Star(i - 1)) {
            result = this->CreateMul(result, operand);
        } else if (ctx->Div(i - 1)) {
            result = this->CreateDiv(result, operand);
        } else if (ctx->Mod(i - 1)) {
            result = this->CreateMod(result, operand);
        }
    }
    return result;
}

std::any Visitor::visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto multiplicativeExpression_0 = visitMultiplicativeExpression(ctx->multiplicativeExpression(0));
    if (multiplicativeExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(multiplicativeExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(multiplicativeExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (multiplicativeExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(multiplicativeExpression_0);
    }
    if (ctx->multiplicativeExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->multiplicativeExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto multiplicativeExpression_i = visitMultiplicativeExpression(ctx->multiplicativeExpression(i));
        if (multiplicativeExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(multiplicativeExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(multiplicativeExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (multiplicativeExpression_i.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(multiplicativeExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        if (ctx->Plus(i - 1)) {
            result = this->CreateAdd(result, operand);
        } else {
            result = this->CreateSub(result, operand);
        }
    }
    return result;
}

std::any Visitor::visitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto additiveExpression_0 = visitAdditiveExpression(ctx->additiveExpression(0));
    if (additiveExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(additiveExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(additiveExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (additiveExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(additiveExpression_0);
    }
    if (ctx->additiveExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->additiveExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto additiveExpression_i = visitAdditiveExpression(ctx->additiveExpression(i));
        if (additiveExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(additiveExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(additiveExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (additiveExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(additiveExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        // TODO: 算术右移和逻辑右移
        if (std::any_cast<std::string>(ctx->shiftOperator()) == ">>") {
            result = this->CreateShr(result, operand);
        } else if (std::any_cast<std::string>(ctx->shiftOperator()) == "<<") {
            result = this->CreateShl(result, operand);
        }
    }
    return result;
}

std::any Visitor::visitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx)
{
    // TODO: 暂时只考虑 << >> 这两种情况
    std::string result = "";
    if (ctx->Greater(0) != nullptr) {
        result = ">>";
    } else if (ctx->Less(0) != nullptr) {
        result = "<<";
    } else {
        std::cout << "Error: Unknown shift operator" << std::endl;
    }
    return result;
}

std::any Visitor::visitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    auto shiftExpression_0 = visitShiftExpression(ctx->shiftExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (shiftExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(shiftExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(shiftExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (shiftExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(shiftExpression_0);
    }
    if (ctx->shiftExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->shiftExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto shiftExpression_i = visitShiftExpression(ctx->shiftExpression(i));
        if (shiftExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(shiftExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(shiftExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (shiftExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(shiftExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        if (ctx->Less(i - 1)) {
            result = this->CreateCmpLT(result, operand);
        } else if (ctx->Greater(i - 1)) {
            result = this->CreateCmpGT(result, operand);
        } else if (ctx->LessEqual(i - 1)) {
            result = this->CreateCmpLE(result, operand);
        } else if (ctx->GreaterEqual(i - 1)) {
            result = this->CreateCmpGE(result, operand);
        }
    }
    return result;
}

std::any Visitor::visitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    auto relationalExpression_0 = visitRelationalExpression(ctx->relationalExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (relationalExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(relationalExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(relationalExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (relationalExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(relationalExpression_0);
    }
    if (ctx->relationalExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->relationalExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto relationalExpression_i = visitRelationalExpression(ctx->relationalExpression(i));
        if (relationalExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(relationalExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(relationalExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (relationalExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(relationalExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        if (ctx->Equal(i - 1)) {
            result = this->CreateCmpEQ(result, operand);
        } else if (ctx->NotEqual(i - 1)) {
            result = this->CreateCmpNEQ(result, operand);
        }
    }
    return result;
}

std::any Visitor::visitAndExpression(ZigCCParser::AndExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    auto equalityExpression_0 = visitEqualityExpression(ctx->equalityExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (equalityExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(equalityExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(equalityExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (equalityExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(equalityExpression_0);
    }
    if (ctx->equalityExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->equalityExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto equalityExpression_i = visitEqualityExpression(ctx->equalityExpression(i));
        if (equalityExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(equalityExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(equalityExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (equalityExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(equalityExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        result = this->CreateBitwiseAND(result, operand);
    }
    return result;
}

std::any Visitor::visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto andExpression_0 = visitAndExpression(ctx->andExpression(0));
    if (andExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(andExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(andExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (andExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(andExpression_0);
    }
    if (ctx->andExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->andExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto andExpression_i = visitAndExpression(ctx->andExpression(i));
        if (andExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(andExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(andExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (andExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(andExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        result = this->CreateBitwiseXOR(result, operand);
    }
    return result;
}

std::any Visitor::visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx)
{
   llvm::Value* result = nullptr;
   auto exclusiveOrExpression_0 = visitExclusiveOrExpression(ctx->exclusiveOrExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (exclusiveOrExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(exclusiveOrExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(exclusiveOrExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (exclusiveOrExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(exclusiveOrExpression_0);
    }
    if (ctx->exclusiveOrExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    for (size_t i = 1; i < ctx->exclusiveOrExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto exclusiveOrExpression_i = visitExclusiveOrExpression(ctx->exclusiveOrExpression(i));
        if (exclusiveOrExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(exclusiveOrExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(exclusiveOrExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (exclusiveOrExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(exclusiveOrExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        result = this->CreateBitwiseOR(result, operand);
    }
    return result;
}

std::any Visitor::visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    auto inclusiveOrExpression_0 = visitInclusiveOrExpression(ctx->inclusiveOrExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (inclusiveOrExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(inclusiveOrExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(inclusiveOrExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (inclusiveOrExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(inclusiveOrExpression_0);
    }
    if (ctx->inclusiveOrExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    // （需要做逻辑运算的情况下）判断得到的表达式是否能转化为 bool 类型
    if (ctx->inclusiveOrExpression().size() > 1) {
        result = Cast2I1(result);
        if (result == nullptr) {
            throw std::domain_error("Logic AND operator \"&&\" must be applied to 2 expressions that can be cast to boolean.");
            return nullptr;
        }
    }
    for (size_t i = 1; i < ctx->inclusiveOrExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto inclusiveOrExpression_i = visitInclusiveOrExpression(ctx->inclusiveOrExpression(i));
        if (inclusiveOrExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(inclusiveOrExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(inclusiveOrExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (inclusiveOrExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(inclusiveOrExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        operand = Cast2I1(operand);
        if (operand == nullptr) {
            throw std::domain_error("Logic AND operator \"&&\" must be applied to 2 expressions that can be cast to boolean.");
            return nullptr;
        }
        result = builder.CreateLogicalAnd(result, operand);
    }
    return result;
}

std::any Visitor::visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx)
{
    llvm::Value* result = nullptr;
    auto logicalAndExpression_0 = visitLogicalAndExpression(ctx->logicalAndExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (logicalAndExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(logicalAndExpression_0);
        result = this->getVariable(name);
        if (result == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(logicalAndExpression_0) << "'" << std::endl;
            return nullptr;
        }
    } else if (logicalAndExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(logicalAndExpression_0);
    }
    if (ctx->logicalAndExpression().size() == 1) {
        return result;
    }
    result = builder.CreateLoad(result->getType()->getNonOpaquePointerElementType(), result);
    // （需要做逻辑运算的情况下）判断得到的表达式是否能转化为 bool 类型
    if (ctx->logicalAndExpression().size() > 1) {
        result = Cast2I1(result);
        if (result == nullptr) {
            throw std::domain_error("Logic OR operator \"||\" must be applied to 2 expressions that can be cast to boolean.");
            return nullptr;
        }
    }
    for (size_t i = 1; i < ctx->logicalAndExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto logicalAndExpression_i = visitLogicalAndExpression(ctx->logicalAndExpression(i));
        if (logicalAndExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(logicalAndExpression_i);
            operand = this->getVariable(name);
            if (operand == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(logicalAndExpression_i) << "'" << std::endl;
                return nullptr;
            }
        } else if (logicalAndExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(logicalAndExpression_i);
        }
        operand = builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
        // 类型检查与转化
        operand = Cast2I1(operand);
        if (operand == nullptr) {
            throw std::domain_error("Logic OR operator \"||\" must be applied to 2 expressions that can be cast to boolean.");
            return nullptr;
        }
        result = builder.CreateLogicalOr(result, operand);
    }
    return result;
}

std::any Visitor::visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx)
{
    if (auto LogicalOrExpression = ctx->logicalOrExpression()) {
        return visitLogicalOrExpression(LogicalOrExpression);
    } else if (auto Expression = ctx->expression()) {
        return visitExpression(Expression);
    } else if (auto AssignmentExpression = ctx->assignmentExpression()) {
        return visitAssignmentExpression(AssignmentExpression);
    } // TODO: 还有 ?: 运算符要考虑
}

std::any Visitor::visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx)
{
    // TODO: 加入类型检查和类型转换
    if (auto AssignmentOperator = ctx->assignmentOperator()) {
        std::string AssignOp = std::any_cast<std::string>(visitAssignmentOperator(AssignmentOperator));
        auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
        // 判断该变量是否是之前处理过的
        llvm::Value* alloca;
        if (this->currentScope().getVariable(lhs) == nullptr) {
            std::cout << "error: use of undeclared identifier '" << lhs << "'" << std::endl;
            // TODO: Exception
        } else {
            alloca = this->currentScope().getVariable(lhs);
        }
        auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
        auto value = builder.CreateLoad(alloca->getType(), alloca);
        // 判断赋值号右边的变量是否初始化过（有待改进，不知道是哪个变量）
        if (value == nullptr) {
            std::cout << "error: use of uninitialized variable" << std::endl;
        }
        if (AssignOp == "=") {
            builder.CreateStore(rhs, alloca);
            return rhs;
        } else {
            llvm::Value* result;
            if (AssignOp == "*=") {
                auto result = builder.CreateMul(value, rhs, "multmp");
            } else if (AssignOp == "/=") {
                auto result = builder.CreateSDiv(value, rhs, "divtmp");
            } else if (AssignOp == "%=") {
                auto result = builder.CreateSRem(value, rhs, "modtmp");
            } else if (AssignOp == "+=") {
                auto result = builder.CreateAdd(value, rhs, "addtmp");
            } else if (AssignOp == "-=") {
                auto result = builder.CreateSub(value, rhs, "subtmp");
            } else if (AssignOp == ">>=") {
                auto result = builder.CreateAShr(value, rhs, "shrtmp");
            } else if (AssignOp == "<<=") {
                auto result = builder.CreateShl(value, rhs, "shltmp");
            } else if (AssignOp == "&=") {
                auto result = builder.CreateAnd(value, rhs, "andtmp");
            } else if (AssignOp == "^=") {
                auto result = builder.CreateXor(value, rhs, "xortmp");
            } else if (AssignOp == "|=") {
                auto result = builder.CreateOr(value, rhs, "ortmp");
            }
            builder.CreateStore(result, alloca);
            return result;
        }
    } else if (auto ConditionalExpression = ctx->conditionalExpression()) {
        return visitConditionalExpression(ConditionalExpression);
    } else if (auto LogicalOrExpression = ctx->logicalOrExpression()) {
        return visitLogicalOrExpression(LogicalOrExpression);
    } else if (auto ThrowExpression = ctx->throwExpression()) {
        return visitThrowExpression(ThrowExpression);
    } else if (auto InitializerClause = ctx->initializerClause()) {
        return visitInitializerClause(InitializerClause);
    } // TODO: 其他情况有待完善
}

std::any Visitor::visitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx)
{
    if (ctx->Assign() != nullptr) {
        return std::string("=");
    } else if (ctx->StarAssign() != nullptr) {
        return std::string("*=");
    } else if (ctx->DivAssign() != nullptr) {
        return std::string("/=");
    } else if (ctx->ModAssign() != nullptr) {
        return std::string("%=");
    } else if (ctx->PlusAssign() != nullptr) {
        return std::string("+=");
    } else if (ctx->MinusAssign() != nullptr) {
        return std::string("-=");
    } else if (ctx->RightShiftAssign() != nullptr) {
        return std::string(">>=");
    } else if (ctx->LeftShiftAssign() != nullptr) {
        return std::string("<<=");
    } else if (ctx->AndAssign() != nullptr) {
        return std::string("&=");
    } else if (ctx->XorAssign() != nullptr) {
        return std::string("^=");
    } else if (ctx->OrAssign() != nullptr) {
        return std::string("|=");
    }
}

std::any Visitor::visitExpression(ZigCCParser::ExpressionContext *ctx)
{
    // TODO: 暂时只实现了只有单个赋值的情况
    for (auto AssignmentExpression : ctx->assignmentExpression())
        return visitAssignmentExpression(AssignmentExpression);
}

std::any Visitor::visitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx)
{
    if (auto ConditionalExpression = ctx->conditionalExpression()) {
        auto ConstExpr = visitConditionalExpression(ConditionalExpression);
        if (ConstExpr.type() == typeid(llvm::Value*)) {
            return ConstExpr;
        } else {
            std::cout << "Error: Constant expression must be a constant expression." << std::endl;
            return nullptr;
        }
    }
    return nullptr;
}

std::any Visitor::visitStatement(ZigCCParser::StatementContext *ctx)
{
    if (auto LabeledStatement = ctx->labeledStatement()) {
        visitLabeledStatement(LabeledStatement);
    } else if (auto ExpressionStatement = ctx->expressionStatement()) {
        visitExpressionStatement(ExpressionStatement);
    } else if (auto CompoundStatement = ctx->compoundStatement()) {
        visitCompoundStatement(CompoundStatement);
    } else if (auto SelectionStatement = ctx->selectionStatement()) {
        visitSelectionStatement(SelectionStatement);
    } else if (auto IterationStatement = ctx->iterationStatement()) {
        visitIterationStatement(IterationStatement);
    } else if (auto JumpStatement = ctx->jumpStatement()) {
        visitJumpStatement(JumpStatement);
    } else if (auto DeclarationStatement = ctx->declarationStatement()) {
        visitDeclarationStatement(DeclarationStatement);
    } else if (auto TryBlock = ctx->tryBlock()) {
        visitTryBlock(TryBlock);
    } else if (auto AttributeSpecifierSeq = ctx->attributeSpecifierSeq()) {
        visitAttributeSpecifierSeq(AttributeSpecifierSeq);
    }
    return nullptr;
}

std::any Visitor::visitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx)
{

}

std::any Visitor::visitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx)
{

}

std::any Visitor::visitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx)
{
    if (auto statementSeq = ctx->statementSeq()) {
        visitStatementSeq(statementSeq);
    }
    return nullptr;
}

std::any Visitor::visitStatementSeq(ZigCCParser::StatementSeqContext *ctx)
{
    auto statement = ctx->statement();
    for(const auto& statement_ctx: statement) {
        visitStatement(statement_ctx);
    }

    return nullptr;
}

std::any Visitor::visitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx)
{
    if (ctx->If() != nullptr) {
        llvm::Value* condition = std::any_cast<llvm::Value*>(visitCondition(ctx->condition()));
        if (condition == nullptr) {
            std::cout << "Error: Condition is not a valid expression." << std::endl;
            return nullptr;
        }
        // 判断 condition 是否可以转化为 bool 类型
        condition = Cast2I1(condition);
        if (condition == nullptr) {
            std::cout << "Error: Condition is not a valid expression." << std::endl;
            return nullptr;
        }
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: If statement not within a function." << std::endl;
            return nullptr;
        }
        // llvm::LLVMContext &block_ctx = builder.getContext();
        llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(*llvm_context);
        llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(*llvm_context);
        llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*llvm_context);
        thenBlock->insertInto(function);
        
        // Create a branch instruction corresponding to this if statement
        builder.CreateCondBr(condition, thenBlock, elseBlock);
        // Generate code in the "Then" block
        builder.SetInsertPoint(thenBlock);
        if (ctx->statement(0) != nullptr) {
            visitStatement(ctx->statement(0));
        }
        TerminateBlockByBr(mergeBlock);

        // Generate code in the "Else" block
        elseBlock->insertInto(function);
        builder.SetInsertPoint(elseBlock);
        if (ctx->Else() != nullptr) {
            visitStatement(ctx->statement(1));
        }
        TerminateBlockByBr(mergeBlock);

        // Finish "Merge" block
        if (mergeBlock->hasNPredecessorsOrMore(1)) {
            mergeBlock->insertInto(function);
			builder.SetInsertPoint(mergeBlock);
		}
    } else if (ctx->Switch() != nullptr) {
        // TODO: 注意 switch 语句的条件不允许赋值，这和 if 语句不同，并且也不一定需要是 bool 类型
        llvm::Value* condition = std::any_cast<llvm::Value*>(visitCondition(ctx->condition()));
        if (condition == nullptr) {
            std::cout << "Error: Condition is not a valid expression." << std::endl;
            return nullptr;
        }
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: Switch statement not within a function." << std::endl;
            return nullptr;
        }
        // TODO: 未完成
    }
    return nullptr;
}

std::any Visitor::visitCondition(ZigCCParser::ConditionContext *ctx)
{
    if (auto Expression = ctx->expression()) {
        return visitExpression(Expression);
    }
}

std::any Visitor::visitIterationStatement(ZigCCParser::IterationStatementContext *ctx)
{
    if (ctx->While() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: While statement not within a function." << std::endl;
            return nullptr;
        }
        
        //Create "WhileCond", "WhileLoop" and "WhileEnd"
		llvm::BasicBlock* WhileCondBB = llvm::BasicBlock::Create(*llvm_context, "WhileCond");
		llvm::BasicBlock* WhileLoopBB = llvm::BasicBlock::Create(*llvm_context, "WhileLoop");
		llvm::BasicBlock* WhileEndBB = llvm::BasicBlock::Create(*llvm_context, "WhileEnd");
        //Create an unconditional branch, jump to "WhileCond" block.
		builder.CreateBr(WhileCondBB);

		//Evaluate the loop condition (cast the type to i1 if necessary).
		//Since we don't allow variable declarations in if-condition (because we only allow expressions there),
		//we don't need to push a symbol table
		WhileCondBB->insertInto(function);
		builder.SetInsertPoint(WhileCondBB);
		llvm::Value* Condition = std::any_cast<llvm::Value*>(visitCondition(ctx->condition()));
		if (!(Condition = Cast2I1(Condition))) {
			throw std::logic_error("The condition value of while-statement must be either an integer, or a floating-point number, or a pointer.");
			return NULL;
		}
		builder.CreateCondBr(Condition, WhileLoopBB, WhileEndBB);
		
        //Generate code in the "WhileLoop" block
        WhileLoopBB->insertInto(function);
		builder.SetInsertPoint(WhileLoopBB);
		if (ctx->statement() != nullptr) {
            // TODO: 还需要处理 break 和 continue 语句
			visitStatement(ctx->statement());
		}
		TerminateBlockByBr(WhileCondBB);

		//Finish "WhileEnd" block
        WhileEndBB->insertInto(function);
		builder.SetInsertPoint(WhileEndBB);
		return NULL;
    } else if (ctx->Do() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: Do statement not within a function." << std::endl;
            return nullptr;
        }
        llvm::BasicBlock* DoLoopBB = llvm::BasicBlock::Create(*llvm_context, "DoLoop");
		llvm::BasicBlock* DoCondBB = llvm::BasicBlock::Create(*llvm_context, "DoCond");
		llvm::BasicBlock* DoEndBB = llvm::BasicBlock::Create(*llvm_context, "DoEnd");
        //Create an unconditional branch, jump to "DoLoop" block.
		builder.CreateBr(DoLoopBB);

		//Generate code in the "DoLoop" block
        DoLoopBB->insertInto(function);
		builder.SetInsertPoint(DoLoopBB);
		if (ctx->statement() != nullptr) {
			// TODO: 还需要处理 break 和 continue 语句
			visitStatement(ctx->statement());
		}
		TerminateBlockByBr(DoCondBB);
		
        //Evaluate the loop condition (cast the type to i1 if necessary).
		//Since we don't allow variable declarations in if-condition (because we only allow expressions there),
		//we don't need to push a symbol table
        DoCondBB->insertInto(function);
		builder.SetInsertPoint(DoCondBB);
		llvm::Value* Condition = std::any_cast<llvm::Value*>(visitExpression(ctx->expression()));
		if (!(Condition = Cast2I1(Condition))) {
			throw std::logic_error("The condition value of do-statement must be either an integer, or a floating-point number, or a pointer.");
			return NULL;
		}
		builder.CreateCondBr(Condition, DoLoopBB, DoEndBB);
		
        // Finish "DoEnd" block
        DoEndBB->insertInto(function);
		builder.SetInsertPoint(DoEndBB);
		return NULL;
    } else if (ctx->For() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: For statement not within a function." << std::endl;
            return nullptr;
        }
        llvm::BasicBlock* ForCondBB = llvm::BasicBlock::Create(*llvm_context, "ForCond");
		llvm::BasicBlock* ForLoopBB = llvm::BasicBlock::Create(*llvm_context, "ForLoop");
		llvm::BasicBlock* ForTailBB = llvm::BasicBlock::Create(*llvm_context, "ForTail");
		llvm::BasicBlock* ForEndBB = llvm::BasicBlock::Create(*llvm_context, "ForEnd");
        
        Scope for_scope(currentScope().currentFunction);
        scopes.push_back(for_scope);
        if (ctx->forInitStatement() != nullptr) {
            visitForInitStatement(ctx->forInitStatement());
        } else if (ctx->forRangeDeclaration() != nullptr) {
            // TODO: for (auto i : v)
            visitForRangeDeclaration(ctx->forRangeDeclaration());
            visitForRangeInitializer(ctx->forRangeInitializer());
        }
		TerminateBlockByBr(ForCondBB);

		// Generate code in the "ForCond" block
        ForCondBB->insertInto(function);
		builder.SetInsertPoint(ForCondBB);
		if (ctx->condition() != nullptr) {
			// If it has a loop condition, evaluate it (cast the type to i1 if necessary).
			llvm::Value* Condition = std::any_cast<llvm::Value*>(visitCondition(ctx->condition()));
			if (!(Condition = Cast2I1(Condition))) {
				throw std::logic_error("The condition value of for-statement must be either an integer, or a floating-point number, or a pointer.");
				return NULL;
			}
			builder.CreateCondBr(Condition, ForLoopBB, ForEndBB);
		}
		else {
			// Otherwise, it is an unconditional loop condition (always returns true)
			builder.CreateBr(ForLoopBB);
		}

		// Generate code in the "ForLoop" block
        ForLoopBB->insertInto(function);
		builder.SetInsertPoint(ForLoopBB);
		if (ctx->statement() != nullptr) {
            // TODO: 还需要处理 break 和 continue 语句
            visitStatement(ctx->statement());
        }

		// If not terminated, jump to "ForTail"
		TerminateBlockByBr(ForTailBB);
		// Generate code in the "ForTail" block
        ForTailBB->insertInto(function);
		builder.SetInsertPoint(ForTailBB);
		if (ctx->expression() != nullptr) {
			visitExpression(ctx->expression());
        }
		builder.CreateBr(ForCondBB);
        
		//Finish "ForEnd" block
        ForEndBB->insertInto(function);
		builder.SetInsertPoint(ForEndBB);
        if (ctx->forInitStatement() != nullptr) {
            scopes.pop_back();
        }
		return NULL;
    }
}

std::any Visitor::visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx)
{
    if (auto ExpressionStatement = ctx->expressionStatement()) {
        visitExpressionStatement(ExpressionStatement);
    } else if (auto SimpleDeclaration = ctx->simpleDeclaration()) {
        visitSimpleDeclaration(SimpleDeclaration);
    }
}

std::any Visitor::visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx)
{

}

std::any Visitor::visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx)
{

}

std::any Visitor::visitJumpStatement(ZigCCParser::JumpStatementContext *ctx)
{
    if (ctx->Break() != nullptr) {

    } else if (ctx->Continue() != nullptr) {

    } else if (ctx->Return() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: Return statement not within a function" << std::endl;
            return nullptr;
        }
        if (ctx->expression() != nullptr) {
            llvm::Value* value = std::any_cast<llvm::Value*>(visitExpression(ctx->expression()));
            if (!TypeCheck(value->getType(), function->getReturnType())) {
                std::cout << "Error: Return type mismatch." << std::endl;
                return nullptr;
            }
            builder.CreateRet(value);
        } else {
            if (function->getReturnType() != builder.getVoidTy()) {
                std::cout << "Error: Expected an expression after return statement." << std::endl;
                return nullptr;
            }
            builder.CreateRetVoid();
        }
    } else if (ctx->Goto() != nullptr) {

    } else if (ctx->Identifier() != nullptr) {

    }
}

std::any Visitor::visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx)
{
    if (auto BlockDeclaration = ctx->blockDeclaration()) {
        visitBlockDeclaration(BlockDeclaration);
    }
}

std::any Visitor::visitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx)
{
    // 建立全局变量所在的 scope（有且仅有一个），其 currentFunction = nullptr
    // 此后 scopes[0] 就是全局的 scope 的代名词，所有这里面的变量都是可以在局部使用的，同时需要注意被覆盖的可能
    scopes.push_back(Scope());
    for (auto decl : ctx->declaration())
        visitDeclaration(decl);
    return nullptr;
}

std::any Visitor::visitDeclaration(ZigCCParser::DeclarationContext *ctx)
{
    if (auto BlockDeclaration = ctx->blockDeclaration()) {
        visitBlockDeclaration(BlockDeclaration);
    } else if (auto FunctionDefinition = ctx->functionDefinition()) {
        visitFunctionDefinition(FunctionDefinition);
    } else if (auto TemplateDeclaration = ctx->templateDeclaration()) {
        visitTemplateDeclaration(TemplateDeclaration);
    } else if (auto ExplicitInstantiation = ctx->explicitInstantiation()) {
        visitExplicitInstantiation(ExplicitInstantiation);
    } else if (auto ExplicitSpecialization = ctx->explicitSpecialization()) {
        visitExplicitSpecialization(ExplicitSpecialization);
    } else if (auto LinkageSpecification = ctx->linkageSpecification()) {
        visitLinkageSpecification(LinkageSpecification);
    } else if (auto NamespaceDefinition = ctx->namespaceDefinition()) {
        visitNamespaceDefinition(NamespaceDefinition);
    } else if (auto EmptyDeclaration = ctx->emptyDeclaration()) {
        visitEmptyDeclaration(EmptyDeclaration);
    } else if (auto AttributeDeclaration = ctx->attributeDeclaration()) {
        visitAttributeDeclaration(AttributeDeclaration);
    }
    return nullptr;
}

std::any Visitor::visitBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx)
{
    if (auto SimpleDeclaration = ctx->simpleDeclaration()) {
        visitSimpleDeclaration(SimpleDeclaration);
    } else if (auto AsmDefinition = ctx->asmDefinition()) {
        visitAsmDefinition(AsmDefinition);
    } else if (auto NamespaceAliasDefinition = ctx->namespaceAliasDefinition()) {
        visitNamespaceAliasDefinition(NamespaceAliasDefinition);
    } else if (auto UsingDeclaration = ctx->usingDeclaration()) {
        visitUsingDeclaration(UsingDeclaration);
    } else if (auto UsingDirective = ctx->usingDirective()) {
        visitUsingDirective(UsingDirective);
    } else if (auto StaticAssertDeclaration = ctx->staticAssertDeclaration()) {
        visitStaticAssertDeclaration(StaticAssertDeclaration);
    } else if (auto AliasDeclaration = ctx->aliasDeclaration()) {
        visitAliasDeclaration(AliasDeclaration);
    } else if (auto OpaqueEnumDeclaration = ctx->opaqueEnumDeclaration()) {
        visitOpaqueEnumDeclaration(OpaqueEnumDeclaration);
    }
    return nullptr;
}

std::any Visitor::visitAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx)
{

}

std::any Visitor::visitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx)
{
    // TODO: attributeSpecifierSeq()
    /* 事实上，我们在 ZigCCParser.h 中每个 context 类中的函数，有的是并列关系，即表示
       几种不同的类型，需要做 if-else 分类处理，有的是合作关系，如本函数对应的 context，
       观察语法树，我们这一函数将会实现类似于 int x, y = 0; 这类表达式的分离，即我们需要
       利用这一类型的函数将其分解成类型和变量名（有的函数负责提取类型，有的函数负责提取变量名，
       因此我们称这些函数是合作关系，在语法树上体现出分叉的特点），并在栈帧中开辟空间存储，
       分解的过程需要使用更底层的 visitor 函数返回需要的类型/变量名
    */
    // TODO: 目前暂未考虑一行中有两种类型的情况（const int 之类的）
    // 当前只考虑 int x, y = 0; int x = y = 0; 这种情况，enum 以及 class 等复杂类型之后再作处理（添加分支处理（？））
    // 还有强制类型转换可以做（感觉应该不难）
    llvm::Type* type = nullptr;
    if (auto DeclSpecifierSeq = ctx->declSpecifierSeq()) {
        type = std::any_cast<llvm::Type*>(visitDeclSpecifierSeq(DeclSpecifierSeq));
    }
    std::vector< std::pair<std::string, llvm::Value*> > vars;
    int pointer_cnt = 0;
    std::vector<llvm::Value*> array_cnt;
    for (auto decl : ctx->initDeclaratorList()->initDeclarator()) {
        // 我们先处理指针，再处理数组，因此默认 int *a[] 为指针数组
        // TODO: 数组指针需特判是否为 int (*a)[]
        // 首先判断是否有 * 运算符，创建指针类型
        pointer_cnt = decl->declarator()->pointerDeclarator()->pointerOperator().size();
        if (type != nullptr && pointer_cnt > 0) {
            for (int i = 0; i < pointer_cnt; i++) {
                type = llvm::PointerType::get(type, 0);
            }
        }
        // 判断是否有数组，创建数组类型（TODO: int a[][5] 这类的实现）
        auto NoPointerDeclarator = decl->declarator()->noPointerDeclarator();
        while (NoPointerDeclarator->LeftBracket() != nullptr) {
            if (NoPointerDeclarator->constantExpression() != nullptr) {
                // 检查下标是否是整数类型
                llvm::Value* array_size = std::any_cast<llvm::Value*>(visitConstantExpression(NoPointerDeclarator->constantExpression()));
                if (array_size != nullptr && !array_size->getType()->isIntegerTy()) {
                    std::cout << "Error: Array size must be an integer." << std::endl;
                    return nullptr;
                }
                array_cnt.push_back(array_size);
            } else {
                array_cnt.push_back(nullptr);
            }
            NoPointerDeclarator = NoPointerDeclarator->noPointerDeclarator();
        }
        
        std::string name;
        if (array_cnt.size() > 0) {
            for (int i = array_cnt.size() - 1; i >= 0; i--) {
                if (array_cnt[i] != nullptr) {
                    type = llvm::ArrayType::get(type, static_cast<llvm::ConstantInt*>(array_cnt[i])->getSExtValue());
                } else {
                    type = llvm::ArrayType::get(type, 0);
                }
            }
            name = std::any_cast<std::string>(visitNoPointerDeclarator(NoPointerDeclarator));
        } else { // visitDeclarator 函数返回变量名
            name = std::any_cast<std::string>(visitDeclarator(decl->declarator()));
        }
        // 如果进行了初始化，则将初始化的值存入 values 中
        // TODO: 数组初始化
        llvm::Value* value = nullptr;
        if (auto Initializer = decl->initializer()) {
            value = std::any_cast<llvm::Value*>(visitInitializer(Initializer));
        }
        vars.push_back(std::make_pair(name, value));
    }
    if (currentScope().currentFunction != nullptr) { // 局部变量的情况
        if (type == nullptr) { // 没有 type，说明此时是赋值
            for (auto var : vars) {
                // 因此需要判断当前变量是否已经定义过
                llvm::Value* var_alloc = getVariable(var.first);
                if (var_alloc == nullptr) {
                    std::cout << "Error: Variable " + var.first + " is not defined before." << std::endl;
                    return nullptr;
                }
                // 数组下标转换
                for (int i = array_cnt.size() - 1; i >= 0; i--) {
                    var_alloc = builder.CreateLoad(var_alloc->getType()->getNonOpaquePointerElementType(), var_alloc);
                    var_alloc = builder.CreateAdd(var_alloc, array_cnt[i]);
                }
                // 指针解引用转换
                for (int i = 0; i < pointer_cnt; i++) {
                    var_alloc = builder.CreateLoad(var_alloc->getType()->getNonOpaquePointerElementType(), var_alloc);
                }
                // 类型检查与赋值
                this->CreateAssignment(var_alloc, var.second);
            }
        }
        else {
            for (auto var : vars) {
                // TODO: 数组初始化
                // 类型检查
                if (std::get<1>(var) != nullptr && !TypeCheck(var.second->getType(), type)) {
                    std::cout << "Error: Type mismatch" << std::endl;
                    return nullptr;
                }
                // CreateAlloca 函数将类型为 type 的变量 name 加入栈帧，对齐方式 nullptr（可能 struct 类型有用？）
                auto alloca = builder.CreateAlloca(type, nullptr, std::get<0>(var));
                // 当进行了初始化时，CreateStore 函数将赋值的表达式存入上一步开辟的地址空间 alloca 中
                if (std::get<1>(var) != nullptr) {
                    builder.CreateStore(var.second, alloca);
                }
                this->currentScope().setVariable(std::get<0>(var), alloca);
            }
        }
    } else { // 全局变量的情况
        if (type == nullptr) { // 注意全局变量不允许出现在全局 scope 中赋值
            std::cout << "Error: Expected type specifier" << std::endl;
            return nullptr;
        }
        for (auto var : vars) {
            // TODO: 数组初始化
            // 类型检查
            if (var.second != nullptr && !TypeCheck(var.second->getType(), type)) {
                std::cout << "Error: Type mismatch" << std::endl;
                return nullptr;
            }
            // 先不考虑 const 的情况
            auto alloca = new llvm::GlobalVariable(*module, type, false, llvm::Function::ExternalLinkage, 
                                                    (llvm::Constant *)var.second, std::get<0>(var));
            if (!this->currentScope().setVariable(std::get<0>(var), alloca)) {
                std::cout << "Error: Redefinition of '" << std::get<0>(var) << "'" << std::endl;
                alloca->eraseFromParent();
            }
        }
    }
    return nullptr;
}

std::any Visitor::visitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx)
{

}

std::any Visitor::visitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx)
{

}

std::any Visitor::visitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx)
{

}

[[deprecated("Terminal not implemented")]]
std::any Visitor::visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx)
{
    if (auto StorageClassSpecifier = ctx->storageClassSpecifier()) {
        return visitStorageClassSpecifier(StorageClassSpecifier);
    } else if (auto TypeSpecifier = ctx->typeSpecifier()) {
        return visitTypeSpecifier(TypeSpecifier);
    } else if (auto FunctionSpecifier = ctx->functionSpecifier()) {
        return visitFunctionSpecifier(FunctionSpecifier);
    } else if (auto Friend = ctx->Friend()) {
        return "";
    } else if (auto Typedef = ctx->Typedef()) {
        return "";
    } else if (auto Constexpr = ctx->Constexpr()) {
        return "";
    }
}

std::any Visitor::visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx)
{
    // 显然是不能这么写代码的，但是目前只考虑只有一个 declSpecifier 的情况
    for (auto decl : ctx->declSpecifier())
        return visitDeclSpecifier(decl);
    // TODO: attributeSpecifierSeq()
}

std::any Visitor::visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx)
{

}

std::any Visitor::visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx)
{

}

std::any Visitor::visitTypedefName(ZigCCParser::TypedefNameContext *ctx)
{

}

std::any Visitor::visitTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx)
{
    if (auto TrailingTypeSpecifier = ctx->trailingTypeSpecifier()) {
	    return visitTrailingTypeSpecifier(TrailingTypeSpecifier);
    } else if (auto ClassSpecifier = ctx->classSpecifier()) {
        return visitClassSpecifier(ClassSpecifier);
    } else if (auto EnumSpecifier = ctx->enumSpecifier()) {
        return visitEnumSpecifier(EnumSpecifier);
    }
}

std::any Visitor::visitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx)
{
    if (auto SimpleTypeSpecifier = ctx->simpleTypeSpecifier()) {
        return visitSimpleTypeSpecifier(SimpleTypeSpecifier);
    } else if (auto ElaboratedTypeSpecifier = ctx->elaboratedTypeSpecifier()) {
        return visitElaboratedTypeSpecifier(ElaboratedTypeSpecifier);
    } else if (auto TypeNameSpecifier = ctx->typeNameSpecifier()) {
        return visitTypeNameSpecifier(TypeNameSpecifier);
    } else if (auto CvQualifier = ctx->cvQualifier()) {
        return visitCvQualifier(CvQualifier);
    }
}

std::any Visitor::visitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx)
{

}

std::any Visitor::visitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx)
{

}

std::any Visitor::visitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx)
{

}

std::any Visitor::visitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx)
{

}

std::any Visitor::visitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx)
{
    // TODO: 除了基本类型之外的函数
    if (ctx->Char() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt8Ty(*llvm_context);
    } else if (ctx->Char16() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt16Ty(*llvm_context);
    } else if (ctx->Char32() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Wchar() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Bool() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt1Ty(*llvm_context);
    } else if (ctx->Int() != nullptr) {
        return (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Float() != nullptr) {
        return (llvm::Type *)llvm::Type::getFloatTy(*llvm_context);
    } else if (ctx->Double() != nullptr) {
        return (llvm::Type *)llvm::Type::getDoubleTy(*llvm_context);
    } else if (ctx->Void() != nullptr) {
        return (llvm::Type *)llvm::Type::getVoidTy(*llvm_context);
    } else if (ctx->Auto() != nullptr) {
        // TODO: auto
    } else {
        // TODO: "error: unknown type specifier"
        return nullptr;
    }
}

std::any Visitor::visitTheTypeName(ZigCCParser::TheTypeNameContext *ctx)
{
    if (auto ClassName = ctx->className()) {
        visitClassName(ClassName);
    } else if (auto EnumName = ctx->enumName()) {
        visitEnumName(EnumName);
    } else if (auto TypedefName = ctx->typedefName()) {
        visitTypedefName(TypedefName);
    } else if (auto SimpleTemplateId = ctx->simpleTemplateId()) {
        visitSimpleTemplateId(SimpleTemplateId);
    }
}

std::any Visitor::visitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx)
{

}

std::any Visitor::visitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx)
{

}

std::any Visitor::visitEnumName(ZigCCParser::EnumNameContext *ctx)
{

}

std::any Visitor::visitEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx)
{

}

std::any Visitor::visitEnumHead(ZigCCParser::EnumHeadContext *ctx)
{

}

std::any Visitor::visitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx)
{

}

std::any Visitor::visitEnumkey(ZigCCParser::EnumkeyContext *ctx)
{

}

std::any Visitor::visitEnumbase(ZigCCParser::EnumbaseContext *ctx)
{

}

std::any Visitor::visitEnumeratorList(ZigCCParser::EnumeratorListContext *ctx)
{

}

std::any Visitor::visitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx)
{

}

std::any Visitor::visitEnumerator(ZigCCParser::EnumeratorContext *ctx)
{

}

std::any Visitor::visitNamespaceName(ZigCCParser::NamespaceNameContext *ctx)
{

}

std::any Visitor::visitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx)
{

}

std::any Visitor::visitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx)
{

}

std::any Visitor::visitNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx)
{

}

std::any Visitor::visitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx)
{

}

std::any Visitor::visitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx)
{

}

std::any Visitor::visitUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx)
{

}

std::any Visitor::visitUsingDirective(ZigCCParser::UsingDirectiveContext *ctx)
{

}

std::any Visitor::visitAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx)
{

}

std::any Visitor::visitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx)
{

}

std::any Visitor::visitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx)
{

}

std::any Visitor::visitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx)
{

}

std::any Visitor::visitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx)
{

}

std::any Visitor::visitAttributeList(ZigCCParser::AttributeListContext *ctx)
{

}

std::any Visitor::visitAttribute(ZigCCParser::AttributeContext *ctx)
{

}

std::any Visitor::visitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx)
{

}

std::any Visitor::visitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx)
{

}

std::any Visitor::visitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx)
{

}

std::any Visitor::visitBalancedtoken(ZigCCParser::BalancedtokenContext *ctx)
{

}

std::any Visitor::visitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx)
{

}

std::any Visitor::visitInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx)
{

}

std::any Visitor::visitDeclarator(ZigCCParser::DeclaratorContext *ctx)
{
    if (auto PointerDeclarator = ctx->pointerDeclarator()) {
        return visitPointerDeclarator(PointerDeclarator);
    } else if (auto NoPointerDeclarator = ctx->noPointerDeclarator()) {
        return visitNoPointerDeclarator(NoPointerDeclarator);
    } else if (auto ParametersAndQualifiers = ctx->parametersAndQualifiers()) {
        return visitParametersAndQualifiers(ParametersAndQualifiers);
    } else if (auto TrailingReturnType = ctx->trailingReturnType()) {
        return visitTrailingReturnType(TrailingReturnType);
    }
}

// TODO: 指针数组与数组指针
std::any Visitor::visitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx)
{
    if (auto NoPointerOperator = ctx->noPointerDeclarator()) {
        return visitNoPointerDeclarator(NoPointerOperator);
    }
    // TODO: 其他情况
    return nullptr;
}

std::any Visitor::visitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx)
{
    if (auto Declaratorid = ctx->declaratorid()) {
        return visitDeclaratorid(Declaratorid);
    } else if (auto NoPointerDeclarator = ctx->noPointerDeclarator()) {
        return visitNoPointerDeclarator(NoPointerDeclarator);
    } else if (auto ParametersAndQualifiers = ctx->parametersAndQualifiers()) {
        return visitParametersAndQualifiers(ParametersAndQualifiers);
    }
    // TODO: 其他情况
    return nullptr;
}

std::any Visitor::visitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx)
{
    if (auto parameterDeclarationClause = ctx->parameterDeclarationClause()) {
        return visitParameterDeclarationClause(parameterDeclarationClause);
    }
}

std::any Visitor::visitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx)
{

}

std::any Visitor::visitPointerOperator(ZigCCParser::PointerOperatorContext *ctx)
{

}

std::any Visitor::visitCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx)
{

}

std::any Visitor::visitCvQualifier(ZigCCParser::CvQualifierContext *ctx)
{

}

std::any Visitor::visitRefqualifier(ZigCCParser::RefqualifierContext *ctx)
{

}

std::any Visitor::visitDeclaratorid(ZigCCParser::DeclaratoridContext *ctx)
{
    if (auto IdExpression = ctx->idExpression()) {
        return visitIdExpression(IdExpression);
    }
    // TODO: 其他情况（省略号）
    return nullptr;
}

std::any Visitor::visitTheTypeId(ZigCCParser::TheTypeIdContext *ctx)
{

}

std::any Visitor::visitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx)
{

}

std::any Visitor::visitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx)
{

}

std::any Visitor::visitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx)
{

}

std::any Visitor::visitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx)
{

}

std::any Visitor::visitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx)
{

}

std::any Visitor::visitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx)
{
    if (auto parameterDeclarationList = ctx->parameterDeclarationList()) {
        return visitParameterDeclarationList(parameterDeclarationList);
    }
}

std::any Visitor::visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx)
{
    auto param_list = ctx->parameterDeclaration();
    std::vector< std::pair< std::string, llvm::Type* > > params;

    for(const auto& param_dec_ctx: param_list) {
        auto dec_specifier = param_dec_ctx->declSpecifierSeq();
        llvm::Type *type = std::any_cast<llvm::Type *>(visitDeclSpecifierSeq(dec_specifier));
        auto declarator = param_dec_ctx->declarator();
        std::string name= std::any_cast<std::string>(visitDeclarator(declarator));
        params.push_back(std::pair< std::string, llvm::Type * >(name, type));
    }

    return params;
}

std::any Visitor::visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx)
{

}

std::any Visitor::visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx)
{
    // 默认返回值类型 int32
    llvm::Type *type = (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
    if (auto declSpecifierSeq = ctx->declSpecifierSeq()) {
        type = std::any_cast<llvm::Type *>(visitDeclSpecifierSeq(declSpecifierSeq));
    }

    auto declarator = ctx->declarator();
    std::string fun_name = std::any_cast<std::string>(visitDeclarator(declarator));
    
    // 获得参数列表
    std::vector< std::pair<std::string, llvm::Type *> > params;
    auto parametersAndQualifiers = ctx->declarator()->pointerDeclarator()->noPointerDeclarator()->parametersAndQualifiers();
    params = std::any_cast<std::vector< std::pair<std::string, llvm::Type *> > >
            (visitParametersAndQualifiers(parametersAndQualifiers));
    std::vector<llvm::Type *> param_types;
    for (const auto& param: params) {
        param_types.push_back(param.second);
    }

    // 添加 Function
    llvm::FunctionType *function_type;
    function_type = llvm::FunctionType::get(type, 
                                   llvm::ArrayRef<llvm::Type *>(param_types),
                                   false);
    llvm::Function *function;
    function = llvm::Function::Create(function_type,
                                      llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                      fun_name,
                                      this->module.get());
    
    // 加入到 scopes 作为接下来 body 中的作用域
    Scope fun_scope = Scope(function);
    this->scopes.push_back(fun_scope);

    auto block = llvm::BasicBlock::Create(builder.getContext(), llvm::Twine(std::string("entry_")+fun_name), function);
    builder.SetInsertPoint(block);

    // 添加参数列表中的参数到 var_list 中
    // NOTE: 参数列表中的参数，认为是先前没有声明过的局部变量
    //      （不需要检查 scope 中是否已经有同名变量）
    for (const auto& param: params) {
        std::string param_name = param.first;
        llvm::Type *param_type = param.second;
        auto alloca = this->builder.CreateAlloca(param_type, nullptr, param_name);
        // NOTE: 初步实现的是不做初始化参数
        fun_scope.setVariable(param_name, alloca);
    }

    // BODY
    auto functionBody = ctx->functionBody();
    visitFunctionBody(functionBody);

    // 创建一个空返回（如果能在 body 中处理最好，如果没有返回指令的话自动添加一个 void ret）
    // NOTE: 这个想法可能有问题，有待检查
    llvm::BasicBlock *external_ret_block = llvm::BasicBlock::Create(*llvm_context, llvm::Twine(std::string("external_ret_")+fun_name), function);
    builder.SetInsertPoint(external_ret_block);
    builder.CreateRetVoid();

    // 抛出当前 scope，开始分析全局 / 下一个函数体
    this->scopes.pop_back();

    // NOTE: What to return?
    return nullptr;
}

std::any Visitor::visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx)
{
    if (auto compoundStatement = ctx->compoundStatement()) {
        visitCompoundStatement(compoundStatement);
    }
    return nullptr;
}

std::any Visitor::visitInitializer(ZigCCParser::InitializerContext *ctx)
{
    if (auto BraceOrEqualInitializer = ctx->braceOrEqualInitializer()) {
        return visitBraceOrEqualInitializer(BraceOrEqualInitializer);
    } else if (auto ExpressionList = ctx->expressionList()) {
        return visitExpressionList(ExpressionList);
    }
    // TODO: 还有左右括号的情况
}

std::any Visitor::visitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx)
{
    // 等于号赋值或初始化列表
    if (auto InitializerClause = ctx->initializerClause()) {
        return visitInitializerClause(InitializerClause);
    } else if (auto BracedInitList = ctx->bracedInitList()) {
        return visitBracedInitList(BracedInitList);
    }
}

std::any Visitor::visitInitializerClause(ZigCCParser::InitializerClauseContext *ctx)
{
    if (auto AssignmentExpression = ctx->assignmentExpression()) {
        return visitAssignmentExpression(AssignmentExpression);
    } else if (auto BracedInitList = ctx->bracedInitList()) {
        return visitBracedInitList(BracedInitList);
    }
}

std::any Visitor::visitInitializerList(ZigCCParser::InitializerListContext *ctx)
{

}

std::any Visitor::visitBracedInitList(ZigCCParser::BracedInitListContext *ctx)
{

}

std::any Visitor::visitClassName(ZigCCParser::ClassNameContext *ctx)
{

}

std::any Visitor::visitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx)
{

}

std::any Visitor::visitClassHead(ZigCCParser::ClassHeadContext *ctx)
{

}

std::any Visitor::visitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx)
{

}

std::any Visitor::visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx)
{

}

std::any Visitor::visitClassKey(ZigCCParser::ClassKeyContext *ctx)
{

}

std::any Visitor::visitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx)
{

}

[[deprecated("First rule not implemented")]]
std::any Visitor::visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx)
{
    if(1) {
        
    } else if (auto FunctionDefinition = ctx->functionDefinition()) {
        visitFunctionDefinition(FunctionDefinition);
    } else if (auto UsingDeclaration = ctx->usingDeclaration()) {
        visitUsingDeclaration(UsingDeclaration);
    } else if (auto StaticAssertDeclaration = ctx->staticAssertDeclaration()) {
        visitStaticAssertDeclaration(StaticAssertDeclaration);
    } else if (auto TemplateDeclaration = ctx->templateDeclaration()) {
        visitTemplateDeclaration(TemplateDeclaration);
    } else if (auto AliasDeclaration = ctx->aliasDeclaration()) {
        visitAliasDeclaration(AliasDeclaration);
    } else if (auto EmptyDeclaration = ctx->emptyDeclaration()) {
        visitEmptyDeclaration(EmptyDeclaration);
    }
}

std::any Visitor::visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx)
{

}

std::any Visitor::visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx)
{

}

std::any Visitor::visitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx)
{

}

std::any Visitor::visitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx)
{

}

std::any Visitor::visitPureSpecifier(ZigCCParser::PureSpecifierContext *ctx)
{

}

std::any Visitor::visitBaseClause(ZigCCParser::BaseClauseContext *ctx)
{

}

std::any Visitor::visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx)
{

}

std::any Visitor::visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx)
{

}

std::any Visitor::visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx)
{

}

std::any Visitor::visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx)
{

}

std::any Visitor::visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx)
{

}

std::any Visitor::visitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx)
{

}

std::any Visitor::visitConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx)
{

}

std::any Visitor::visitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx)
{

}

std::any Visitor::visitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx)
{

}

std::any Visitor::visitMemInitializerList(ZigCCParser::MemInitializerListContext *ctx)
{

}

std::any Visitor::visitMemInitializer(ZigCCParser::MemInitializerContext *ctx)
{

}

std::any Visitor::visitMeminitializerid(ZigCCParser::MeminitializeridContext *ctx)
{

}

std::any Visitor::visitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx)
{

}

std::any Visitor::visitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx)
{

}

std::any Visitor::visitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx)
{

}

std::any Visitor::visitTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx)
{

}

std::any Visitor::visitTemplateParameter(ZigCCParser::TemplateParameterContext *ctx)
{

}

std::any Visitor::visitTypeParameter(ZigCCParser::TypeParameterContext *ctx)
{

}

std::any Visitor::visitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx)
{

}

std::any Visitor::visitTemplateId(ZigCCParser::TemplateIdContext *ctx)
{

}

std::any Visitor::visitTemplateName(ZigCCParser::TemplateNameContext *ctx)
{

}

std::any Visitor::visitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx)
{

}

std::any Visitor::visitTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx)
{

}

std::any Visitor::visitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx)
{

}

std::any Visitor::visitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx)
{

}

std::any Visitor::visitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx)
{

}

std::any Visitor::visitTryBlock(ZigCCParser::TryBlockContext *ctx)
{

}

std::any Visitor::visitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx)
{

}

std::any Visitor::visitHandlerSeq(ZigCCParser::HandlerSeqContext *ctx)
{

}

std::any Visitor::visitHandler(ZigCCParser::HandlerContext *ctx)
{

}

std::any Visitor::visitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx)
{

}

std::any Visitor::visitThrowExpression(ZigCCParser::ThrowExpressionContext *ctx)
{

}

std::any Visitor::visitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx)
{

}

std::any Visitor::visitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx)
{

}

std::any Visitor::visitTypeIdList(ZigCCParser::TypeIdListContext *ctx)
{

}

std::any Visitor::visitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx)
{

}

std::any Visitor::visitTheOperator(ZigCCParser::TheOperatorContext *ctx)
{

}

std::any Visitor::visitLiteral(ZigCCParser::LiteralContext *ctx)
{
    if (ctx->IntegerLiteral() != nullptr) {
        return (llvm::Value *)llvm::ConstantInt::get(llvm::Type::getInt32Ty(*llvm_context), std::stoi(ctx->IntegerLiteral()->getText()));
    } else if (ctx->CharacterLiteral() != nullptr) {
        return (llvm::Value *)llvm::ConstantInt::get(llvm::Type::getInt8Ty(*llvm_context), ctx->CharacterLiteral()->getText()[1]);
    } else if (ctx->FloatingLiteral() != nullptr) {
        return (llvm::Value *)llvm::ConstantFP::get(llvm::Type::getFloatTy(*llvm_context), std::stof(ctx->FloatingLiteral()->getText()));
    } else if (ctx->StringLiteral() != nullptr) {
        return (llvm::Value *)builder.CreateGlobalStringPtr(ctx->StringLiteral()->getText());
    } else if (ctx->BooleanLiteral() != nullptr) {
        return (llvm::Value *)llvm::ConstantInt::get(llvm::Type::getInt1Ty(*llvm_context), ctx->BooleanLiteral()->getText() == "true");
    } else if (ctx->PointerLiteral() != nullptr) {
        // TODO: 不一定是 i8 也不一定是 NULL
        return (llvm::Value *)llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*llvm_context));
    } else if (ctx->UserDefinedLiteral() != nullptr) {
        // TODO: UserDefinedLiteral
        return nullptr;
    }
}