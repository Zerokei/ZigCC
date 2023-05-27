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
    // TODO: 暂时只考虑了有一个 literal 的情况
    if (ctx->LeftParen() != nullptr && ctx->RightParen() != nullptr) {
        return visitExpression(ctx->expression());
    }
    if (ctx->literal(0) != nullptr) {
        return visitLiteral(ctx->literal(0));
    } else if (ctx->idExpression() != nullptr) {
        return visitIdExpression(ctx->idExpression());
    } else if (ctx->lambdaExpression() != nullptr) {
        return visitLambdaExpression(ctx->lambdaExpression());
    }
    return nullptr;
}

std::any Visitor::visitIdExpression(ZigCCParser::IdExpressionContext *ctx)
{
    if (auto UnqualifiedId = ctx->unqualifiedId()) {
        return visitUnqualifiedId(UnqualifiedId);
    } else if (auto QualifiedId = ctx->qualifiedId()) {
        return visitQualifiedId(QualifiedId);
    }
    return nullptr;
}

std::any Visitor::visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx)
{
    if (auto Identifier = ctx->Identifier()) {
        return std::string(Identifier->getText());
    } else if (ctx->Tilde() != nullptr) {
        if (auto ClassName = ctx->className()) {
            return "~" + std::any_cast<std::string>(visitClassName(ClassName));
        }
    }
    return nullptr;
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
    } else if(ctx->LeftParen() && ctx->RightParen()) {
        auto _function_call_postfixExpression = ctx->postfixExpression();
        std::string fun_name = std::any_cast<std::string>(visitPostfixExpression(_function_call_postfixExpression));
        auto function = this->module->getFunction(fun_name);
        if(nullptr == function) {
            std::cout << "Error: Function " << fun_name << " not declared." << std::endl;
            return nullptr;
        }
        auto function_type = function->getFunctionType();

        std::vector<llvm::Value *> param_values;
        std::vector<llvm::Type *> param_types;
        if(auto _function_call_expressionList = ctx->expressionList()) {
            param_values = std::any_cast<std::vector<llvm::Value *> >(visitExpressionList(_function_call_expressionList));
        }
        for(const auto &value: param_values) {
            param_types.push_back(value->getType());
        }

        // 根据函数，获得函数要求的参数类型
        llvm::ArrayRef<llvm::Type *> _array_need_param_types = function_type->params();
        std::vector<llvm::Type *> need_param_types(_array_need_param_types.begin(), _array_need_param_types.end());

        if (need_param_types.size() == param_types.size() || function_type->isVarArg() && need_param_types.size() <= param_types.size()) {
            // TODO: 类型检查与匹配，如果无法 cast 应报错
            auto call = builder.CreateCall(function_type, function, param_values);
            return static_cast<llvm::Value *>(call);
        } else {
            std::cout << "Error: Wrong number of parameters when calling " + fun_name + "." << std::endl;
            return nullptr;
        }
        
    } else if (ctx->Dot() != nullptr) { // a.x
        std::string objname = "";
        if (auto PostfixExpression = ctx->postfixExpression()) {
            if (auto PrimaryExpression = PostfixExpression->primaryExpression()) {
                if (auto ID = PrimaryExpression->idExpression()) {
                    if (auto UnqualifiedId = ID->unqualifiedId()) {
                        if (auto Identifier = UnqualifiedId->Identifier()) {
                            objname = Identifier->getText();
                        }
                    }
                }
            }
        }
        
        std::string classname = "";
        llvm::Value* object_alloc = nullptr;
        for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
            for (auto object : it->objects) {
                if (std::get<0>(object) == objname) {
                    classname = std::get<1>(object).first;
                    object_alloc = std::get<1>(object).second;
                    break;
                }
            }
        }
        if (classname == "") {
            std::cout << "Error: Use . after a none object name '" << objname << "'" << std::endl;
            return nullptr;
        }

        std::string membername;
        if (auto ID = ctx->idExpression()) {
            if (auto UnqualifiedId = ID->unqualifiedId()) {
                if (auto Identifier = UnqualifiedId->Identifier()) {
                    membername = Identifier->getText();
                }
            }
        }

        size_t member_index = -1;
        llvm::Function* func = nullptr;
        for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
            for (auto thisclass : it->classes) {
                if (std::get<0>(thisclass) == classname) {
                    auto classinfo = std::get<1>(thisclass);
                    for (int i = 0; i < classinfo->variables.size(); i++) {
                        if (classinfo->variables[i].first == membername) {
                            member_index = i;
                            break;
                        }
                    }
                    if (classinfo->functions.find(classname + "_" + membername) != classinfo->functions.end()) {
                        func = module->getFunction(classname + "_" + membername);
                    }
                    // TODO: 我们不考虑主动调用构造函数和析构函数的情况，只考虑调用成员函数
                }
            }
        }
        if (member_index == -1 && func == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << classname << "." << membername << "'" << std::endl;
            return nullptr;
        } else if (member_index != -1) {
            std::vector<llvm::Value*> Indices;
			Indices.push_back(builder.getInt32(0));
			Indices.push_back(builder.getInt32(member_index));
			return builder.CreateGEP(object_alloc->getType()->getNonOpaquePointerElementType(), object_alloc, Indices);
        } else if (func != nullptr) {

        }
    } else if (ctx->Arrow() != nullptr) { // a->x
        // this
    } else if (ctx->LeftBracket() && ctx->RightBracket()) {
        std::vector<llvm::Value*> Indices;
        auto TempExpr = ctx;
        while (TempExpr->LeftBracket() != nullptr) {
            if (TempExpr->expression() != nullptr) {
                // 检查下标是否是整数类型
                llvm::Value* array_size = std::any_cast<llvm::Value*>(visitExpression(TempExpr->expression()));
                if (array_size != nullptr && !array_size->getType()->isIntegerTy()) {
                    std::cout << "Error: Array size must be an integer." << std::endl;
                    return nullptr;
                }
                Indices.insert(Indices.begin(), array_size);
            } else {
                std::cout << "Error: Array size must be an integer." << std::endl;
            }
            TempExpr = TempExpr->postfixExpression();
        }

        std::string arrayname = "";
        if (auto PostfixExpression = ctx->postfixExpression()) {
            if (auto PrimaryExpression = PostfixExpression->primaryExpression()) {
                if (auto ID = PrimaryExpression->idExpression()) {
                    if (auto UnqualifiedId = ID->unqualifiedId()) {
                        if (auto Identifier = UnqualifiedId->Identifier()) {
                            arrayname = Identifier->getText();
                        }
                    }
                }
            }
        }
        llvm::Value* array_alloc = getVariable(arrayname);
        if (array_alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << arrayname << "'" << std::endl;
            return nullptr;
        }
        Indices.insert(Indices.begin(), llvm::ConstantInt::get(llvm::Type::getInt32Ty(*llvm_context), 0));

        llvm::Value* array = builder.CreateLoad(array_alloc->getType()->getNonOpaquePointerElementType(), array_alloc);
        if (array->getType()->isArrayTy()) {
            llvm::Type* element_type = array->getType()->getArrayElementType();
            auto GEP = builder.CreateInBoundsGEP(array_alloc->getType()->getNonOpaquePointerElementType(), array_alloc, Indices);
            return (llvm::Value*)builder.CreateLoad(element_type, GEP);
        } else if (array->getType()->isPointerTy()) {
            llvm::Type* element_type = array->getType()->getNonOpaquePointerElementType();
            auto GEP = builder.CreateGEP(element_type, array, Indices[1]); // 暂时只考虑一维数组
            return (llvm::Value*)builder.CreateLoad(element_type, GEP);
        } else {
            std::cout << "Error: Array type error." << std::endl;
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
    if(auto InitializerList = ctx->initializerList()) {
        return visitInitializerList(InitializerList);
    }
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

            // 如果出现 &a[0] 这种情况
            std::vector<llvm::Value*> Indices;
            std::string arrayname = "";
            if (auto UnaryExpr = ctx->unaryExpression()) {
                if (auto PostfixExpr = UnaryExpr->postfixExpression()) {
                    while (PostfixExpr->LeftBracket() != nullptr) {
                        if (PostfixExpr->expression() != nullptr) {
                            // 检查下标是否是整数类型
                            llvm::Value* array_size = std::any_cast<llvm::Value*>(visitExpression(PostfixExpr->expression()));
                            if (array_size != nullptr && !array_size->getType()->isIntegerTy()) {
                                std::cout << "Error: Array size must be an integer." << std::endl;
                                return nullptr;
                            }
                            Indices.insert(Indices.begin(), array_size);
                        } else {
                            std::cout << "Error: Array size must be an integer." << std::endl;
                        }
                        PostfixExpr = PostfixExpr->postfixExpression();
                    }
                    if (auto PrimaryExpression = PostfixExpr->primaryExpression()) {
                        if (auto ID = PrimaryExpression->idExpression()) {
                            if (auto UnqualifiedId = ID->unqualifiedId()) {
                                if (auto Identifier = UnqualifiedId->Identifier()) {
                                    arrayname = Identifier->getText();
                                }
                            }
                        }
                    }
                }
            }
            if (arrayname != "") {
                llvm::Value* array_alloc = getVariable(arrayname);
                if (array_alloc == nullptr) {
                    std::cout << "Error: Use of undeclared identifier '" << arrayname << "'" << std::endl;
                    return nullptr;
                }
                Indices.insert(Indices.begin(), llvm::ConstantInt::get(llvm::Type::getInt32Ty(*llvm_context), 0));

                llvm::Value* array = builder.CreateLoad(array_alloc->getType()->getNonOpaquePointerElementType(), array_alloc);
                if (array->getType()->isArrayTy()) {
                    llvm::Type* element_type = array->getType()->getArrayElementType();
                    operand_alloc = builder.CreateInBoundsGEP(array_alloc->getType()->getNonOpaquePointerElementType(), array_alloc, Indices);
                    operand = (llvm::Value*)builder.CreateLoad(element_type, operand_alloc);
                } else if (array->getType()->isPointerTy()) {
                    llvm::Type* element_type = array->getType()->getNonOpaquePointerElementType();
                    operand_alloc = builder.CreateGEP(element_type, array, Indices[1]); // 暂时只考虑一维数组
                    operand = (llvm::Value*)builder.CreateLoad(element_type, operand_alloc);
                } else {
                    std::cout << "Error: Array type error." << std::endl;
                    return nullptr;
                }
            }
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
                return (llvm::Value*)builder.CreateLoad(operand->getType()->getNonOpaquePointerElementType(), operand);
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
    } else if (auto NewExpression = ctx->newExpression()) {
        return visitNewExpression(NewExpression);
    } else if (auto DeleteExpression = ctx->deleteExpression()) {
        return visitDeleteExpression(DeleteExpression);
    }
    return nullptr;
}

std::any Visitor::visitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx)
{

}

std::any Visitor::visitNewExpression(ZigCCParser::NewExpressionContext *ctx)
{
    // 支持 new 基本类型和对象
    if (ctx->New() != nullptr) {
        if (ctx->newTypeId()->typeSpecifierSeq()->typeSpecifier(0)->trailingTypeSpecifier()->simpleTypeSpecifier()->theTypeName() != nullptr) {
            // 是 new 对象
            std::string classname = ctx->newTypeId()->typeSpecifierSeq()->typeSpecifier(0)->trailingTypeSpecifier()->simpleTypeSpecifier()->theTypeName()->className()->Identifier()->getText();
            for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
                for (auto thisclass : it->classes) {
                    if (std::get<0>(thisclass) == classname) {
                        
                    }
                }
            }
        } else {
            // 是 new 基本类型
            auto type = visitTypeSpecifierSeq(ctx->newTypeId()->typeSpecifierSeq());
            if (type.type() == typeid(llvm::Type*)) {
                auto type_alloc = std::any_cast<llvm::Type*>(type);
                return builder.CreateAlloca(type_alloc);
            }
        }
    }
    return nullptr;
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
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(pointerMemberExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (pointerMemberExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(pointerMemberExpression_0);
    }
    for (size_t i = 1; i < ctx->pointerMemberExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto pointerMemberExpression_i = visitPointerMemberExpression(ctx->pointerMemberExpression(i));
        if (pointerMemberExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(pointerMemberExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(pointerMemberExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (pointerMemberExpression_i.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(pointerMemberExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto multiplicativeExpression_0 = visitMultiplicativeExpression(ctx->multiplicativeExpression(0));
    if (multiplicativeExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(multiplicativeExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(multiplicativeExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (multiplicativeExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(multiplicativeExpression_0);
    }
    for (size_t i = 1; i < ctx->multiplicativeExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto multiplicativeExpression_i = visitMultiplicativeExpression(ctx->multiplicativeExpression(i));
        if (multiplicativeExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(multiplicativeExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(multiplicativeExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (multiplicativeExpression_i.type() == typeid(llvm::Value*)) {
            operand = std::any_cast<llvm::Value*>(multiplicativeExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto additiveExpression_0 = visitAdditiveExpression(ctx->additiveExpression(0));
    if (additiveExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(additiveExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(additiveExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (additiveExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(additiveExpression_0);
    }
    for (size_t i = 1; i < ctx->additiveExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto additiveExpression_i = visitAdditiveExpression(ctx->additiveExpression(i));
        if (additiveExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(additiveExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(additiveExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (additiveExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(additiveExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto shiftExpression_0 = visitShiftExpression(ctx->shiftExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (shiftExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(shiftExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(shiftExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (shiftExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(shiftExpression_0);
    }
    for (size_t i = 1; i < ctx->shiftExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto shiftExpression_i = visitShiftExpression(ctx->shiftExpression(i));
        if (shiftExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(shiftExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(shiftExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (shiftExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(shiftExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto relationalExpression_0 = visitRelationalExpression(ctx->relationalExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (relationalExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(relationalExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(relationalExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (relationalExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(relationalExpression_0);
    }
    for (size_t i = 1; i < ctx->relationalExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto relationalExpression_i = visitRelationalExpression(ctx->relationalExpression(i));
        if (relationalExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(relationalExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(relationalExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (relationalExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(relationalExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto equalityExpression_0 = visitEqualityExpression(ctx->equalityExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (equalityExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(equalityExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(equalityExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (equalityExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(equalityExpression_0);
    }
    for (size_t i = 1; i < ctx->equalityExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto equalityExpression_i = visitEqualityExpression(ctx->equalityExpression(i));
        if (equalityExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(equalityExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(equalityExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (equalityExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(equalityExpression_i);
        }
        // 类型检查与转化
        result = this->CreateBitwiseAND(result, operand);
    }
    return result;
}

std::any Visitor::visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx)
{
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    auto andExpression_0 = visitAndExpression(ctx->andExpression(0));
    if (andExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(andExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(andExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (andExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(andExpression_0);
    }
    for (size_t i = 1; i < ctx->andExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto andExpression_i = visitAndExpression(ctx->andExpression(i));
        if (andExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(andExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(andExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (andExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(andExpression_i);
        }
        // 类型检查与转化
        result = this->CreateBitwiseXOR(result, operand);
    }
    return result;
}

std::any Visitor::visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx)
{
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto exclusiveOrExpression_0 = visitExclusiveOrExpression(ctx->exclusiveOrExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (exclusiveOrExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(exclusiveOrExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(exclusiveOrExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (exclusiveOrExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(exclusiveOrExpression_0);
    }
    for (size_t i = 1; i < ctx->exclusiveOrExpression().size(); i++) {
        llvm::Value* operand = nullptr;
        auto exclusiveOrExpression_i = visitExclusiveOrExpression(ctx->exclusiveOrExpression(i));
        if (exclusiveOrExpression_i.type() == typeid(std::string)) {
            std::string name = std::any_cast<std::string>(exclusiveOrExpression_i);
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(exclusiveOrExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (exclusiveOrExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(exclusiveOrExpression_i);
        }
        // 类型检查与转化
        result = this->CreateBitwiseOR(result, operand);
    }
    return result;
}

std::any Visitor::visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx)
{
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto inclusiveOrExpression_0 = visitInclusiveOrExpression(ctx->inclusiveOrExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (inclusiveOrExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(inclusiveOrExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(inclusiveOrExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (inclusiveOrExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(inclusiveOrExpression_0);
    }
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
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(inclusiveOrExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (inclusiveOrExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(inclusiveOrExpression_i);
        }
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
    llvm::Value* alloc = nullptr;
    llvm::Value* result = nullptr;
    auto logicalAndExpression_0 = visitLogicalAndExpression(ctx->logicalAndExpression(0));
    // 判断返回的是变量名 string 还是表达式 llvm::Value
    if (logicalAndExpression_0.type() == typeid(std::string)) {
        std::string name = std::any_cast<std::string>(logicalAndExpression_0);
        alloc = this->getVariable(name);
        if (alloc == nullptr) {
            std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(logicalAndExpression_0) << "'" << std::endl;
            return nullptr;
        }
        result = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
    } else if (logicalAndExpression_0.type() == typeid(llvm::Value *)) {
        result = std::any_cast<llvm::Value*>(logicalAndExpression_0);
    }
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
            alloc = this->getVariable(name);
            if (alloc == nullptr) {
                std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(logicalAndExpression_i) << "'" << std::endl;
                return nullptr;
            }
            operand = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
        } else if (logicalAndExpression_i.type() == typeid(llvm::Value *)) {
            operand = std::any_cast<llvm::Value*>(logicalAndExpression_i);
        }
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
            return nullptr;
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
    if (auto Expression = ctx->expression()) {
        visitExpression(Expression);
    }
    return nullptr;
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

        // 创建新的作用域管理 IF 块中的局部变量
        scopes.push_back(Scope(function));

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

        // 退出当前作用域
        scopes.pop_back();
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
    if (ctx->Do() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: Do statement not within a function." << std::endl;
            return nullptr;
        }

        // 创建新的作用域用来管理 DO-WHILE 块中的局部变量
        scopes.push_back(Scope(function));

        llvm::BasicBlock* DoLoopBB = llvm::BasicBlock::Create(*llvm_context, "DoLoop");
		llvm::BasicBlock* DoCondBB = llvm::BasicBlock::Create(*llvm_context, "DoCond");
		llvm::BasicBlock* DoEndBB = llvm::BasicBlock::Create(*llvm_context, "DoEnd");
        //Create an unconditional branch, jump to "DoLoop" block.
		builder.CreateBr(DoLoopBB);

		//Generate code in the "DoLoop" block
        DoLoopBB->insertInto(function);
		builder.SetInsertPoint(DoLoopBB);

        auto prev_cond_done_BB_pair = this->cond_done_BB_pair;

        std::pair<llvm::BasicBlock *, llvm::BasicBlock *> do_BB_pair(DoCondBB, DoEndBB);
        this->cond_done_BB_pair = &do_BB_pair;

		if (ctx->statement() != nullptr) {
			// TODO: 还需要处理 break 和 continue 语句
			visitStatement(ctx->statement());
		}
        this->cond_done_BB_pair = prev_cond_done_BB_pair;
		TerminateBlockByBr(DoCondBB);
		
        //Evaluate the loop condition (cast the type to i1 if necessary).
		//Since we don't allow variable declarations in if-condition (because we only allow expressions there),
		//we don't need to push a symbol table
        DoCondBB->insertInto(function);
		builder.SetInsertPoint(DoCondBB);
		llvm::Value* Condition = std::any_cast<llvm::Value*>(visitExpression(ctx->expression()));
		if (!(Condition = Cast2I1(Condition))) {
            scopes.pop_back();
			throw std::logic_error("The condition value of do-statement must be either an integer, or a floating-point number, or a pointer.");
            // NOTE: Must pop scope
			return nullptr;
		}
		builder.CreateCondBr(Condition, DoLoopBB, DoEndBB);
		
        // Finish "DoEnd" block
        DoEndBB->insertInto(function);
		builder.SetInsertPoint(DoEndBB);

        scopes.pop_back();
		return nullptr;
    } else if (ctx->While() != nullptr) {
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
			return nullptr;
		}

        // 创建新的作用域，管理 WHILE 块内的局部变量
        scopes.push_back(Scope(function));

		builder.CreateCondBr(Condition, WhileLoopBB, WhileEndBB);
		
        //Generate code in the "WhileLoop" block
        WhileLoopBB->insertInto(function);
		builder.SetInsertPoint(WhileLoopBB);

        auto prev_cond_done_BB_pair = this->cond_done_BB_pair;

        std::pair<llvm::BasicBlock *, llvm::BasicBlock *> while_BB_pair(WhileCondBB, WhileEndBB);
        this->cond_done_BB_pair = &while_BB_pair;
		if (ctx->statement() != nullptr) {
            // TODO: 还需要处理 break 和 continue 语句
			visitStatement(ctx->statement());
		}
        this->cond_done_BB_pair = prev_cond_done_BB_pair;
		TerminateBlockByBr(WhileCondBB);

		//Finish "WhileEnd" block
        WhileEndBB->insertInto(function);
		builder.SetInsertPoint(WhileEndBB);

        scopes.pop_back();
		return nullptr;
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
        
        // 创建作用域用来管理 FOR 块中的局部变量
        scopes.push_back(Scope(function));

        if (auto ForInitStatement = ctx->forInitStatement()) {
            visitForInitStatement(ForInitStatement);
        } else if (auto ForRangeDeclaration = ctx->forRangeDeclaration()) {
            // TODO: for (auto i : v)
            visitForRangeDeclaration(ForRangeDeclaration);
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
                scopes.pop_back();
				throw std::logic_error("The condition value of for-statement must be either an integer, or a floating-point number, or a pointer.");
				return nullptr;
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

        auto prev_cond_done_BB_pair = this->cond_done_BB_pair;

        std::pair<llvm::BasicBlock *, llvm::BasicBlock *> for_BB_pair(ForTailBB, ForEndBB);
        this->cond_done_BB_pair = &for_BB_pair;
		if (ctx->statement() != nullptr) {
            // TODO: 还需要处理 break 和 continue 语句
            visitStatement(ctx->statement());
        }

        this->cond_done_BB_pair = prev_cond_done_BB_pair;

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
		return nullptr;
    }
}

std::any Visitor::visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx)
{
    if (auto ExpressionStatement = ctx->expressionStatement()) {
        visitExpressionStatement(ExpressionStatement);
    } else if (auto SimpleDeclaration = ctx->simpleDeclaration()) {
        visitSimpleDeclaration(SimpleDeclaration);
    }

    return nullptr;
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
        // Second with WHILE_DONE & FOR_DONE
        if(nullptr == this->cond_done_BB_pair) {
            std::cout << "Error: Using break out of loop-body." << std::endl;
            return nullptr;
        }
        builder.CreateBr(cond_done_BB_pair->second);
        return nullptr;
    } else if (ctx->Continue() != nullptr) {
        // Firtst with WHILE_COND & FOR_TAIL
        if(nullptr == cond_done_BB_pair) {
            std::cout << "Error: Using break out of loop-body." << std::endl;
            return nullptr;
        }
        builder.CreateBr(cond_done_BB_pair->first);
        return nullptr;
    } else if (ctx->Return() != nullptr) {
        llvm::Function* function = currentScope().currentFunction;
        if (function == nullptr) {
            std::cout << "Error: Return statement not within a function" << std::endl;
            return nullptr;
        }
        if (ctx->expression() != nullptr) {
            llvm::Value* alloc;
            llvm::Value* value;
            auto RetExpr = visitExpression(ctx->expression());
            if (RetExpr.type() == typeid(std::string)) {
                std::cout << "Ret value is a string" << std::endl;
                std::string name = std::any_cast<std::string>(RetExpr);
                alloc = this->getVariable(name);
                if (alloc == nullptr) {
                    std::cout << "Error: Use of undeclared identifier '" << std::any_cast<std::string>(RetExpr) << "'" << std::endl;
                    return nullptr;
                }
                value = builder.CreateLoad(alloc->getType()->getNonOpaquePointerElementType(), alloc);
            } else if (RetExpr.type() == typeid(llvm::Value *)) {
                value = std::any_cast<llvm::Value*>(RetExpr);
            }
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
        return nullptr;
    } else if (ctx->Goto() != nullptr) {

    } else if (ctx->Identifier() != nullptr) {

    }
}

std::any Visitor::visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx)
{
    if (auto BlockDeclaration = ctx->blockDeclaration()) {
        visitBlockDeclaration(BlockDeclaration);
    }
    return nullptr;
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
    
    // 判断空语句
    if (!ctx->declSpecifierSeq() && !ctx->initDeclaratorList() && !ctx->attributeSpecifierSeq()) {
        return nullptr;
    }

    llvm::Type* type = nullptr;
    std::string temp_name;
    if (auto DeclSpecifierSeq = ctx->declSpecifierSeq()) {
        auto VisitDeclSpecifierSeq = visitDeclSpecifierSeq(DeclSpecifierSeq);
        if (VisitDeclSpecifierSeq.type() == typeid(llvm::Type *)) {
            type = std::any_cast<llvm::Type*>(VisitDeclSpecifierSeq);
        } else if(VisitDeclSpecifierSeq.type() == typeid(std::string)) {
            temp_name = std::any_cast<std::string>(VisitDeclSpecifierSeq);
        }
    }
    // 判断是否是对象的定义
    ClassType* classinfo = nullptr;
    for (auto scope = scopes.rbegin(); scope != scopes.rend(); scope++) {
        auto classes = scope->classes;
        for (auto thisclass : classes) {
            if (std::get<0>(thisclass) == temp_name) {
                classinfo = std::get<1>(thisclass);
                type = std::get<2>(thisclass);
                break;
            }
        }
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

        antlr4::tree::TerminalNode *L_paren = nullptr;

        // 判断是否进行函数调用，函数调用**一定**发生在函数内部
        if (nullptr != currentScope().currentFunction) {
            auto _L_paren_noPointerDeclarator = decl->declarator()->pointerDeclarator()->noPointerDeclarator();
            auto _L_paren_initializer = decl->initializer();
            if (_L_paren_noPointerDeclarator) {
                std::string fun_name;
                llvm::Function *callee;
                llvm::FunctionType *callee_type;
                std::vector<std::string> param_names;
                std::vector<llvm::Value *> param_values;
                std::vector<llvm::Type *> param_types;
                if(L_paren = _L_paren_noPointerDeclarator->LeftParen()) {
                    // 单参数
                    fun_name = temp_name;
                    auto PointerDeclarator =  _L_paren_noPointerDeclarator->pointerDeclarator();
                    std::string param_name = std::any_cast<std::string>(visitPointerDeclarator(PointerDeclarator));
                    param_names.push_back(param_name);
                } else if(auto _L_paren_parametersAndQualifiers = _L_paren_noPointerDeclarator->parametersAndQualifiers()) {
                    if (L_paren = _L_paren_parametersAndQualifiers->LeftParen()) {
                        // 无参数或多参数
                        fun_name = std::any_cast<std::string>(visitNoPointerDeclarator(_L_paren_noPointerDeclarator));
                        auto ParametersAndQualifiers = visitParametersAndQualifiers(_L_paren_parametersAndQualifiers);
                        if (_L_paren_parametersAndQualifiers->parameterDeclarationClause()) {
                            param_names = std::any_cast< std::vector<std::string> >(ParametersAndQualifiers);
                        }
                    }
                } else if(_L_paren_initializer && _L_paren_initializer->LeftParen()) {
                    // 函数调用中有式子
                    fun_name = std::any_cast<std::string>(visitDeclarator(decl->declarator()));
                    auto temp_values = std::any_cast<std::vector<llvm::Value *> >(visitInitializer(_L_paren_initializer));
                    param_values = temp_values;
                } else {
                    goto _ZIGCC_DECL_NOT_FUNCTION_CALL;
                }

                callee = module->getFunction(fun_name);
                if(nullptr == callee) {
                    std::cout << "Error: Function " << fun_name << " not declared." << std::endl;
                    return nullptr;
                }
                callee_type = callee->getFunctionType();
                
                // 根据参数名，获得对应参数 type & value
                if(0 == param_values.size()) {
                    for (const auto& name: param_names) {
                        llvm::Value *value = getVariable(name);
                        value = builder.CreateLoad(value->getType()->getNonOpaquePointerElementType(), value);
                        if (nullptr == value) {
                            std::cout << "Error: Undefined variable " + name + "." << std::endl;
                            return nullptr;
                        }
                        param_types.push_back(value->getType());
                        param_values.push_back(value);
                    }
                } else {
                    // 通过式子值获得参数类型
                    for(const auto &value: param_values) {
                        llvm::Type *temp_type = value->getType();
                        if(value)
                        param_types.push_back(temp_type);
                    }
                }
                

                // 根据函数，获得函数要求的参数类型
                llvm::ArrayRef<llvm::Type *> _array_need_param_types = callee_type->params();
                std::vector<llvm::Type *> need_param_types(_array_need_param_types.begin(), _array_need_param_types.end());

                if (need_param_types.size() == param_types.size() || callee_type->isVarArg() && need_param_types.size() <= param_types.size()) {
                    // TODO: 类型检查与匹配，如果无法 cast 应报错
                    builder.CreateCall(callee_type, callee, param_values);
                    continue;
                } else {
                    std::cout << "Error: Wrong number of parameters when calling " + fun_name + "." << std::endl;
                    return nullptr;
                }          
            }
        }
        
_ZIGCC_DECL_NOT_FUNCTION_CALL:

        // 判断是不是函数声明，NOTE: !!!!函数声明一定在全局进行!!!!
        if (nullptr == currentScope().currentFunction)
        if (auto _L_paren_noPointerDeclarator = decl->declarator()->pointerDeclarator()->noPointerDeclarator()) {
            if (auto _function_decl_noPointerDeclarator = _L_paren_noPointerDeclarator->noPointerDeclarator()) 
            if (auto _function_decl_parametersAndQualifiers = _L_paren_noPointerDeclarator->parametersAndQualifiers()) {
                // 管理变长参数
                bool has_ellipsis = false;
                if (auto _function_decl_paramDeclClause = _function_decl_parametersAndQualifiers->parameterDeclarationClause()) 
                if (_function_decl_paramDeclClause->Ellipsis()) {
                     has_ellipsis = true;
                }

                // 如果没有指定函数返回值类型，默认为 int32
                if (nullptr == type) {
                    type = (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
                }
                
                std::string fun_name = std::any_cast<std::string>(visitNoPointerDeclarator(_function_decl_noPointerDeclarator));
                
                if (nullptr != module->getFunction(fun_name)) {
                    // 在函数定义后声明
                    std::cout << "Warning: Function " << fun_name << " with declaration after its defination." << std::endl;
                    continue;
                }
                
                std::vector< std::pair<std::string, llvm::Type *> > params;
                params = std::any_cast< std::vector< std::pair<std::string, llvm::Type *> > >
                            (visitParametersAndQualifiers(_function_decl_parametersAndQualifiers));

                // 因为是函数声明，我们只在乎参数类型，并不在乎形参名
                std::vector<llvm::Type *> param_types;
                for (const auto &param : params) {
                    param_types.push_back(param.second);
                }

                llvm::FunctionType *function_type;
                function_type = llvm::FunctionType::get(type, 
                                                        llvm::ArrayRef<llvm::Type *>(param_types),
                                                        has_ellipsis);
                llvm::Function *function;
                function = llvm::Function::Create(function_type,
                                                    llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                    fun_name,
                                                    this->module.get());

                continue;
            }
        }

        // 判断是否有数组，创建数组类型（TODO: int a[][5] 这类的实现）
        auto NoPointerDeclarator = decl->declarator()->pointerDeclarator()->noPointerDeclarator();
        if (NoPointerDeclarator != nullptr) { // NOTE: Maybe NULL
            while (NoPointerDeclarator->LeftBracket() != nullptr) {
                if (NoPointerDeclarator->constantExpression() != nullptr) {
                    // 检查下标是否是整数类型
                    llvm::Value* array_size = std::any_cast<llvm::Value*>(visitConstantExpression(NoPointerDeclarator->constantExpression()));
                    if (array_size != nullptr && !array_size->getType()->isIntegerTy()) {
                        std::cout << "Error: Array size must be an integer." << std::endl;
                        return nullptr;
                    }
                    array_cnt.insert(array_cnt.begin(), array_size);
                } else {
                    array_cnt.insert(array_cnt.begin(), nullptr);
                }
                NoPointerDeclarator = NoPointerDeclarator->noPointerDeclarator();
            }
        }

        std::string name;
        if (array_cnt.size() > 0) {
            if (type != nullptr) {
                for (int i = array_cnt.size() - 1; i >= 0; i--) {
                    if (array_cnt[i] != nullptr) {
                        type = llvm::ArrayType::get(type, static_cast<llvm::ConstantInt*>(array_cnt[i])->getSExtValue());
                    } else {
                        type = llvm::ArrayType::get(type, 0);
                    }
                }
            }
            name = std::any_cast<std::string>(visitNoPointerDeclarator(NoPointerDeclarator));
        } else {
            name = std::any_cast<std::string>(visitDeclarator(decl->declarator()));
        }

        // 如果进行了初始化，则将初始化的值存入 values 中
        // TODO: 数组初始化
        llvm::Value* alloca = nullptr;
        llvm::Value* value = nullptr;

        // 首先进行对象的初始化
        if (classinfo != nullptr) {
            if (decl->initializer() == nullptr) { // Point p; 会调用 Point 的默认构造函数

            } else if (decl->initializer()->braceOrEqualInitializer() != nullptr) { // Point p2 = p1; 会调用 Point 的拷贝构造函数

            } else { // Point p(1, 2); 会调用 Point 的对应的构造函数

            }
        }

        if (auto Initializer = decl->initializer()) {
            auto AssignExpr = visitInitializer(Initializer);
            if (AssignExpr.type() == typeid(std::string)) {
                std::string var_name = std::any_cast<std::string>(AssignExpr);
                alloca = getVariable(var_name);
                if (alloca == nullptr) {
                    std::cout << "Error: Variable " + var_name + " is not defined before." << std::endl;
                    return nullptr;
                }
                value = builder.CreateLoad(alloca->getType()->getNonOpaquePointerElementType(), alloca);
            } else if (AssignExpr.type() == typeid(llvm::Value*)) {
                value = std::any_cast<llvm::Value*>(AssignExpr);
            }
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
                // 数组下标转换（TODO: 判断数组下标是否都存在）
                if (array_cnt.size() > 0) {
                    array_cnt.insert(array_cnt.begin(), llvm::ConstantInt::get(llvm::Type::getInt32Ty(*llvm_context), 0));
                    llvm::Value* array = builder.CreateLoad(var_alloc->getType()->getNonOpaquePointerElementType(), var_alloc);
                    if (array->getType()->isArrayTy()) {
                        var_alloc = builder.CreateInBoundsGEP(var_alloc->getType()->getNonOpaquePointerElementType(), var_alloc, array_cnt);
                    } else if (array->getType()->isPointerTy()) {
                        llvm::Type* element_type = array->getType()->getNonOpaquePointerElementType();
                        var_alloc = builder.CreateGEP(element_type, array, array_cnt[1]); // 暂时只考虑一维数组
                    } else {
                        std::cout << "Error: Array type error." << std::endl;
                        return nullptr;
                    }                    
                }
                // 指针解引用转换
                for (int i = 0; i < pointer_cnt; i++) {
                    var_alloc = builder.CreateLoad(var_alloc->getType()->getNonOpaquePointerElementType(), var_alloc);
                }
                // 类型检查与赋值
                // NOTE: 可能全局变量不能如此赋值！
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
            llvm::Constant* Initializer = (llvm::Constant*)std::get<1>(var);
            if (Initializer == nullptr) {
                Initializer = llvm::UndefValue::get(type);
            }
            auto alloca = new llvm::GlobalVariable(*module, type, false, llvm::Function::ExternalLinkage, 
                                                    Initializer, std::get<0>(var));
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

std::any Visitor::visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx)
{
    if (auto StorageClassSpecifier = ctx->storageClassSpecifier()) {
        return visitStorageClassSpecifier(StorageClassSpecifier);
    } else if (auto TypeSpecifier = ctx->typeSpecifier()) {
        return visitTypeSpecifier(TypeSpecifier);
    } else if (auto FunctionSpecifier = ctx->functionSpecifier()) {
        return visitFunctionSpecifier(FunctionSpecifier);
    } else if (auto Friend = ctx->Friend()) {
        return std::string("Friend");
    } else if (auto Typedef = ctx->Typedef()) {
        return std::string("Typedef");
    } else if (auto Constexpr = ctx->Constexpr()) {
        return std::string("Constexpr");
    }
}

std::any Visitor::visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx)
{
    // 目前只考虑只有一个或两个 declSpecifier 的情况
    auto DeclSpecifier = ctx->declSpecifier();
    if (DeclSpecifier.size() == 1) {
        return visitDeclSpecifier(DeclSpecifier[0]);
    } else if (DeclSpecifier.size() == 2) {
        // 例如 virtual inline const static 出现在第一个位置，第二个是位置普通类型
        // 可以扩展为支持更多，但目前没有必要
        auto DeclSpecifier1 = visitDeclSpecifier(DeclSpecifier[0]);
        auto DeclSpecifier2 = visitDeclSpecifier(DeclSpecifier[1]);
        return std::make_pair(DeclSpecifier1, DeclSpecifier2);
    }
    // TODO: attributeSpecifierSeq()
}

std::any Visitor::visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx)
{
    if (ctx->Register() != nullptr) {
        return std::string("Register");
    } else if (ctx->Static() != nullptr) {
        return std::string("Static");
    } else if (ctx->Thread_local() != nullptr) {
        return std::string("Thread_local");
    } else if (ctx->Extern() != nullptr) {
        return std::string("Extern");
    } else if (ctx->Mutable() != nullptr) {
        return std::string("Mutable");
    }
    return nullptr;
}

std::any Visitor::visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx)
{
    if (ctx->Inline() != nullptr) {
        return std::string("Inline");
    } else if (ctx->Virtual() != nullptr) {
        return std::string("Virtual");
    } else if (ctx->Explicit() != nullptr) {
        return std::string("Explicit");
    }
    return nullptr;
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
    return nullptr;
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
        if (auto TheTypeName = ctx->theTypeName()) {
            return visitTheTypeName(TheTypeName);
        }
        // TODO: "error: unknown type specifier"
        return nullptr;
    }
}

std::any Visitor::visitTheTypeName(ZigCCParser::TheTypeNameContext *ctx)
{
    if (auto ClassName = ctx->className()) {
        return visitClassName(ClassName);
    } else if (auto EnumName = ctx->enumName()) {
        return visitEnumName(EnumName);
    } else if (auto TypedefName = ctx->typedefName()) {
        return visitTypedefName(TypedefName);
    } else if (auto SimpleTemplateId = ctx->simpleTemplateId()) {
        return visitSimpleTemplateId(SimpleTemplateId);
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
    if(!ctx) return std::vector< std::pair< std::string, llvm::Type* > >();
    if (auto parameterDeclarationList = ctx->parameterDeclarationList()) {
        return visitParameterDeclarationList(parameterDeclarationList);
    }
}

std::any Visitor::visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx)
{
    auto param_list = ctx->parameterDeclaration();
    
    if(nullptr == ctx->parameterDeclaration(0)->declarator() && ctx->parameterDeclaration(0)->declSpecifierSeq()->declSpecifier(0)->typeSpecifier()->trailingTypeSpecifier()->simpleTypeSpecifier()->theTypeName()) {
         // Return className
        std::vector<std::string> param_names;
        for(const auto &param_dec_ctx : param_list) {
            if(auto _param_decl_typeSpecifier = param_dec_ctx->declSpecifierSeq()->declSpecifier(0)->typeSpecifier())
            if(auto _param_decl_simpleTypeSpecifier = _param_decl_typeSpecifier->trailingTypeSpecifier()->simpleTypeSpecifier())
            if(auto _param_decl_className = _param_decl_simpleTypeSpecifier->theTypeName()->className()) {
                std::string name = std::any_cast<std::string>(visitClassName(_param_decl_className));
                param_names.push_back(name);
            }
        }
        return param_names;
    } else {
        // Visit param with type & name(name may be empty)
        std::vector< std::pair< std::string, llvm::Type* > > params;

        for(const auto& param_dec_ctx: param_list) {
            auto dec_specifier = param_dec_ctx->declSpecifierSeq();
            llvm::Type *type = std::any_cast<llvm::Type *>(visitDeclSpecifierSeq(dec_specifier));
            
            // 分析指针类型
            size_t pointer_cnt = 0;
            if(auto _pointer_without_name_abstract = param_dec_ctx->abstractDeclarator())
            if(auto _poin_pointer_without_name_abstractDecl = _pointer_without_name_abstract->pointerAbstractDeclarator()) {
                pointer_cnt = _poin_pointer_without_name_abstractDecl->pointerOperator().size();
            }

            if(0 == pointer_cnt)
            if(auto _param_dec_ctx_declarator = param_dec_ctx->declarator())
            if(auto _param_dec_ctx_pointerDeclarator = _param_dec_ctx_declarator->pointerDeclarator())
            if(auto _param_dec_ctx_pointerOperator_size = _param_dec_ctx_pointerDeclarator->pointerOperator().size()) {
                pointer_cnt = _param_dec_ctx_pointerOperator_size;
            }

            if(nullptr != type)
            for(size_t i = 0; i < pointer_cnt; ++i) {
                type = llvm::PointerType::get(type, 0);
            }

            // 分析数组维度
            std::vector<llvm::Value *> array_cnt;
            std::string name;

            if(auto _param_dec_ctx_array_declarator = param_dec_ctx->declarator())
            if(auto _param_dec_ctx_array_pointerDeclarator = _param_dec_ctx_array_declarator->pointerDeclarator()) {
                if(auto _param_dec_ctx_array_noPointerDeclarator = _param_dec_ctx_array_pointerDeclarator->noPointerDeclarator()) {
                    while(nullptr != _param_dec_ctx_array_noPointerDeclarator->LeftBracket()) {
                        if(auto _param_dec_ctx_array_constantExpression = _param_dec_ctx_array_noPointerDeclarator->constantExpression()) {
                            llvm::Value *array_size = std::any_cast<llvm::Value *>(visitConstantExpression(_param_dec_ctx_array_constantExpression));
                            if(nullptr != array_size && !array_size->getType()->isIntegerTy()) {
                                std::cout << "Error: Array size must be an integer." << std::endl;
                                return nullptr;
                            }
                            array_cnt.insert(array_cnt.begin(), array_size);
                        } else {
                            array_cnt.insert(array_cnt.begin(), nullptr);
                        }
                        _param_dec_ctx_array_noPointerDeclarator = _param_dec_ctx_array_noPointerDeclarator->noPointerDeclarator();
                    }
                    name = std::any_cast<std::string>(visitNoPointerDeclarator(_param_dec_ctx_array_noPointerDeclarator));
                } 
            }

            if(array_cnt.size() > 0) {
                for(int i = array_cnt.size() - 1; i >= 0; --i) {
                    if(nullptr != array_cnt[i]) {
                        type = llvm::ArrayType::get(type, static_cast<llvm::ConstantInt *>(array_cnt[i])->getSExtValue());
                    } else {
                        type = llvm::ArrayType::get(type, 0);
                    }
                }
            }

            auto declarator = param_dec_ctx->declarator();
            if(declarator && name == "") {
                name = std::any_cast<std::string>(visitDeclarator(declarator));
            } 

            params.push_back(std::pair< std::string, llvm::Type * >(name, type));
        }

        return params;
    }
    
}

std::any Visitor::visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx)
{

}

std::any Visitor::visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx)
{
    llvm::Type *type = nullptr;
    if (auto declSpecifierSeq = ctx->declSpecifierSeq()) {
        auto DeclSpecifierSeq = visitDeclSpecifierSeq(declSpecifierSeq);
        if (DeclSpecifierSeq.type() == typeid(llvm::Type *)) {
            type = std::any_cast<llvm::Type *>(DeclSpecifierSeq);
        } else if (DeclSpecifierSeq.type() == typeid(std::pair<std::string, llvm::Type*>)) {
            auto pair = std::any_cast<std::pair<std::string, llvm::Type*>>(DeclSpecifierSeq);
            type = std::any_cast<llvm::Type *>(pair.second);
        }
    }

    if(nullptr != type) {
        // 判断返回值类型是不是指针
        if(auto _type_pointerDeclarator = ctx->declarator()->pointerDeclarator()) {
            size_t pointer_cnt = 0;
            pointer_cnt = _type_pointerDeclarator->pointerOperator().size();
            for(size_t i = 0; i < pointer_cnt; ++i) {
                type = llvm::PointerType::get(type, 0);
            }
        }
    } else {
        // 默认返回值类型 int32
        type = (llvm::Type *)llvm::Type::getInt32Ty(*llvm_context);
    }

    auto declarator = ctx->declarator();
    std::string fun_name = std::any_cast<std::string>(visitDeclarator(declarator));

    // 判断当前处理函数是否已经声明
    llvm::Function *function_decl = module->getFunction(fun_name);
    llvm::FunctionType *function_decl_type = nullptr;
    if(nullptr != function_decl) {
        function_decl_type = function_decl->getFunctionType();
    }
    
    // 获得参数列表
    std::vector< std::pair<std::string, llvm::Type *> > params;
    auto parametersAndQualifiers = ctx->declarator()->pointerDeclarator()->noPointerDeclarator()->parametersAndQualifiers();
    // auto ParametersAndQualifiers = visitParametersAndQualifiers(parametersAndQualifiers);
    params = std::any_cast<std::vector< std::pair<std::string, llvm::Type *> > >
        (visitParametersAndQualifiers(parametersAndQualifiers));

    // 判断是否为可变长参数
    bool has_ellipsis = false;
    if(auto _parameterDeclarationClause = parametersAndQualifiers->parameterDeclarationClause()) 
    if(_parameterDeclarationClause->Ellipsis()) {
        has_ellipsis = true;
    }


    std::vector<llvm::Type *> param_types;
    for (const auto& param: params) {
        param_types.push_back(param.second);
    }

    llvm::FunctionType *function_type;
    llvm::Function *function;
    if(nullptr != function_decl) {
        // 如果函数之前已经声明过，需要检查现在定义的函数参数列表和声明的是否相同
        llvm::ArrayRef<llvm::Type *> _arrayref_param_types_decl = function_decl_type->params();
        std::vector<llvm::Type *> param_types_decl(_arrayref_param_types_decl.begin(), _arrayref_param_types_decl.end());
        if(param_types_decl.size() != param_types.size()) {
            std::cout << "Error: Conflicts between parameters of function " << fun_name << " declared in function definition and declaration." << std::endl;
            return nullptr;
        }
        for(size_t i = 0; i < param_types_decl.size(); ++i) {
            if(false == TypeCheck(param_types_decl[i], param_types[i])) {
                std::cout << "Error: Conflicts between parameters of function " << fun_name << " declared in function definition and declaration." << std::endl;
                return nullptr;
            }
        }
        function = function_decl;
        function_type = function_decl->getFunctionType();
    } else {
        // 直接定义，添加 Function
        function_type = llvm::FunctionType::get(type, 
                                    llvm::ArrayRef<llvm::Type *>(param_types),
                                    has_ellipsis);
        
        function = llvm::Function::Create(function_type,
                                        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                        fun_name,
                                        this->module.get());
    }

    

    auto block = llvm::BasicBlock::Create(*llvm_context, llvm::Twine(std::string("entry_")+fun_name), function);
    builder.SetInsertPoint(block);

    Scope fun_scope = Scope(function);
    // 添加参数列表中的参数到 var_list 中
    // NOTE: 参数列表中的参数，认为是先前没有声明过的局部变量
    //      （不需要检查 scope 中是否已经有同名变量）
    auto fun_arg_iter = function->arg_begin();
    for (const auto& param: params) {
        std::string param_name = param.first;
        llvm::Type *param_type = param.second;
        auto alloca = this->builder.CreateAlloca(param_type, nullptr, param_name);
        builder.CreateStore(fun_arg_iter, alloca);
        fun_arg_iter++;
        // NOTE: 初步实现的是不做初始化参数
        fun_scope.setVariable(param_name, alloca);
        if(fun_arg_iter == function->arg_end()) {
            break;
        }
    }

    // 加入到 scopes 作为接下来 body 中的作用域
    this->scopes.push_back(fun_scope);

    // BODY
    auto functionBody = ctx->functionBody();
    visitFunctionBody(functionBody);

    // 创建一个空返回（如果能在 body 中处理最好，如果没有返回指令的话自动添加一个 void ret）
    // NOTE: 这个想法可能有问题，有待检查
    // llvm::BasicBlock *external_ret_block = llvm::BasicBlock::Create(*llvm_context, llvm::Twine(std::string("external_ret_")+fun_name), function);
    // builder.SetInsertPoint(external_ret_block);
    // builder.CreateRetVoid();

    // 抛出当前 scope，开始分析全局 / 下一个函数体
    this->scopes.pop_back();

    // NOTE: What to return?
    return function;
}

std::any Visitor::visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx)
{
    if (auto compoundStatement = ctx->compoundStatement()) {
        visitCompoundStatement(compoundStatement);
    }
    llvm::Function *function = currentScope().currentFunction;
    if(!builder.GetInsertBlock()->getTerminator()) {
        llvm::Type *retType = function->getReturnType();
        if(retType->isVoidTy()) {
            builder.CreateRetVoid();
        } else {
            std::cout << "Warning: Function " + function->getName().str() + " has NO return statment." << std::endl;
            builder.CreateRet(llvm::UndefValue::get(retType));
        }
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
    std::vector<llvm::Value *> res;
    auto InitializerClause = ctx->initializerClause();
    if(0 != InitializerClause.size()) {
        for(const auto &clause : InitializerClause) {
            auto temp_value = std::any_cast<llvm::Value *>(visitInitializerClause(clause));
            res.push_back(temp_value);
        }
    }
    return res;
}

std::any Visitor::visitBracedInitList(ZigCCParser::BracedInitListContext *ctx)
{

}

std::any Visitor::visitClassName(ZigCCParser::ClassNameContext *ctx)
{
    if (ctx->Identifier() != nullptr) {
        return ctx->Identifier()->getText();
    }
    return std::string("");
}

std::any Visitor::visitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx)
{
    // TODO: 目前强制最标准的 class/struct/union 定义，不支持匿名定义等
    ClassType* classinfo = new ClassType();
    std::string classtype, classname, baseclass, heritance_access;
    std::vector<llvm::Type*> member_types;

    if (ctx->classHead() != nullptr) {
        std::tuple<std::string, std::string, std::string, std::string> ret = std::any_cast< std::tuple<std::string, std::string, std::string, std::string> >(visitClassHead(ctx->classHead()));
        classtype = std::get<0>(ret);
        classname = std::get<1>(ret);
        baseclass = std::get<2>(ret);
        heritance_access = std::get<3>(ret);

        classinfo->ParentClass = baseclass;
        auto classtuple = std::make_tuple(classname, classinfo, nullptr);
        scopes.back().classes.push_back(classtuple);

        if (auto MemberSpecification = ctx->memberSpecification()) {
            member_types = std::any_cast< std::vector<llvm::Type*> >(visitMemberSpecification(MemberSpecification));
        }

        if (classtype == "class") {
            auto newclass = llvm::StructType::create(*llvm_context, "class." + classname);
            newclass->setBody(member_types);
            scopes.back().classes.pop_back();
            scopes.back().classes.push_back(std::make_tuple(classname, classinfo, newclass));
        } else if (classtype == "struct") {
            auto newstruct = llvm::StructType::create(*llvm_context, "struct." + classname);
            newstruct->setBody(member_types);
            scopes.back().classes.pop_back();
            scopes.back().classes.push_back(std::make_tuple(classname, classinfo, newstruct));
        } else if (classtype == "union") {
            auto newunion = llvm::StructType::create(*llvm_context, "union." + classname);
            llvm::Type* MaxSizeType = nullptr;
            for (auto member_type : member_types) {
                if (MaxSizeType == nullptr) {
                    MaxSizeType = member_type;
                } else if (DL->getTypeAllocSize(member_type) > DL->getTypeAllocSize(MaxSizeType)) {
                    MaxSizeType = member_type;
                }
            }
            newunion->setBody(MaxSizeType);
            scopes.back().classes.pop_back();
            scopes.back().classes.push_back(std::make_tuple(classname, classinfo, newunion));
        }
    }
    return nullptr;
}

std::any Visitor::visitClassHead(ZigCCParser::ClassHeadContext *ctx)
{
    std::string classname = std::any_cast<std::string>(visitClassHeadName(ctx->classHeadName()));
    if (ctx->Union() != nullptr) {
        return std::make_tuple(std::string("union"), classname, std::string(""), std::string(""));
    }
    std::string classtype = std::any_cast<std::string>(visitClassKey(ctx->classKey()));
    auto baseclass = std::string("");
    auto heritance_access = std::string("");
    if (auto baseClause = ctx->baseClause()) {
        auto pair = std::any_cast< std::pair<std::string, std::string> >(visitBaseClause(baseClause));
        baseclass = pair.first;
        heritance_access = pair.second;
    }
    return std::make_tuple(classtype, classname, baseclass, heritance_access);
}

std::any Visitor::visitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx)
{
    if (auto className = ctx->className()) {
        return visitClassName(className);
    } else if (auto nestedNameSpecifier = ctx->nestedNameSpecifier()) {
        return visitNestedNameSpecifier(nestedNameSpecifier);
    }
    return nullptr;
}

std::any Visitor::visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx)
{

}

std::any Visitor::visitClassKey(ZigCCParser::ClassKeyContext *ctx)
{
    if (ctx->Class() != nullptr) {
        return std::string("class");
    } else if (ctx->Struct() != nullptr) {
        return std::string("struct");
    }
    return std::string("");
}

std::any Visitor::visitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx)
{
    // 由于自动生成语法树的问题，此处只能强制要求 class 的每个变量前都要规定 private/protected/public
    // 强制要求 struct 和 union 都是 public，不允许加限制
    std::string classname = std::get<0>(scopes.back().classes.back());
    ClassType* classinfo = std::get<1>(scopes.back().classes.back());

    auto MemberDecl = ctx->memberdeclaration(0);
    size_t accessnum = ctx->accessSpecifier().size();

    llvm::Function *destructor = nullptr;
    llvm::Function *defaultConstructor = nullptr;
    llvm::Function *copyConstructor = nullptr;
    llvm::Function *moveConstructor = nullptr;
    std::vector< std::pair<std::string, Access> > variables;
    std::unordered_map<std::string, Access> functions;
    std::unordered_map<std::string, Access> constructors;
    std::vector<std::string> VTable;

    std::vector<llvm::Type*> member_types;

    if (MemberDecl != nullptr) {
        for (int i = 0; i < ctx->memberdeclaration().size(); i++) {
            Access access = Access::Public;
            if (accessnum > 0) {
                std::string access = std::any_cast<std::string>(visitAccessSpecifier(ctx->accessSpecifier(i)));
                if (access == "private") {
                    access = Access::Private;
                } else if (access == "protected") {
                    access = Access::Protected;
                } else if (access == "public") {
                    access = Access::Public;
                }
            }
            auto Member = visitMemberdeclaration(ctx->memberdeclaration(i));
            if (Member.type() == typeid(std::pair<llvm::Function*, std::string>)) {
                std::pair<llvm::Function*, std::string> pair = std::any_cast<std::pair<llvm::Function*, std::string>>(Member);
                functions[pair.first->getName().str()] = access;
                if (pair.second == "dtor") {
                    destructor = pair.first;
                } else if (pair.second == "default") {
                    defaultConstructor = pair.first;
                } else if (pair.second == "copy") {
                    copyConstructor = pair.first;
                } else if (pair.second == "ctor") {
                    constructors[pair.first->getName().str()] = access;
                } else if (pair.second == "virtual") {
                    VTable.push_back(pair.first->getName().str());
                }
            } else if (Member.type() == typeid(std::pair< llvm::Type*, std::vector<std::string> >)) {
                std::pair< llvm::Type*, std::vector<std::string> > pair = std::any_cast<std::pair< llvm::Type*, std::vector<std::string> >>(Member);
                for (auto name : pair.second) {
                    variables.push_back(std::make_pair(name, access));
                }
                for (int i = 0; i < pair.second.size(); i++) {
                    member_types.push_back(pair.first);
                }
            }
        }
    }
    if (destructor == nullptr) {
        
    }
    if (defaultConstructor == nullptr && copyConstructor == nullptr && moveConstructor == nullptr && constructors.size() == 0) {
        // 不能有其他构造函数，否则默认构造函数将会被遮蔽，不会自动生成

    }
    if (copyConstructor == nullptr) {
        
    }
    if (moveConstructor == nullptr) {
        // TODO: move constructor
    }
    classinfo->destructor = destructor;
    classinfo->defaultConstructor = defaultConstructor;
    classinfo->copyConstructor = copyConstructor;
    classinfo->moveConstructor = moveConstructor;
    classinfo->variables = variables;
    classinfo->functions = functions;
    classinfo->constructors = constructors;
    classinfo->VTable = VTable;

    return member_types;
}

std::any Visitor::visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx)
{
    // 由于时间有限，目前实现的类只能在类内定义函数而不能声明函数
    static int i = 3; // 重载的构造函数的下标
    std::string classname = std::get<0>(scopes.back().classes.back());
    if (auto FunctionDefinition = ctx->functionDefinition()) {
        llvm::Function* function = std::any_cast<llvm::Function*>(visitFunctionDefinition(FunctionDefinition));
        std::string func_name = function->getName().str();
        std::string func_attr = std::string("");

        if (func_name == classname) { // 判断构造函数和析构函数
            if (FunctionDefinition->declSpecifierSeq() != nullptr) {
                std::cout << "Error: Constructor cannot have return type" << std::endl;
            }
            if (function->arg_size() == 0) {
                func_name = classname + "_ctor" + std::to_string(0);
                func_attr = std::string("default");
            } else if (function->arg_size() == 1) { // 此处实现耍流氓，我认为构造函数为拷贝构造函数当且仅当只有一个参数
                func_name = classname + "_ctor" + std::to_string(1);
                func_attr = std::string("copy");
            } else {
                func_name = classname + "_ctor" + std::to_string(i++);
                func_attr = std::string("ctor");
            }
            function->setName(func_name);
        } else if (func_name == "~" + classname) {
            if (FunctionDefinition->declSpecifierSeq() != nullptr) {
                std::cout << "Error: Destructor cannot have return type" << std::endl;
            }
            func_name = classname + "_dtor";
            function->setName(func_name);
            func_attr = std::string("dtor");
        } else {
            func_name = classname + "_" + func_name;
            function->setName(func_name);
            func_attr = std::string("method");
            auto declSpecifierSeq = FunctionDefinition->declSpecifierSeq();
            auto DeclSpecifierSeq = visitDeclSpecifierSeq(declSpecifierSeq);
            if (DeclSpecifierSeq.type() == typeid(std::pair<std::string, llvm::Type*>)) {
                auto pair = std::any_cast<std::pair<std::string, llvm::Type*>>(DeclSpecifierSeq);
                if (pair.first == "virtual") {
                    func_attr = std::string("virtual");
                } else if (pair.first == "static") {
                    func_attr = std::string("static");
                } else if (pair.first == "inline") {
                    func_attr = std::string("inline");
                }
            }
        }
        return std::make_pair(function, func_attr);
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
    } else if (auto decl = ctx->declSpecifierSeq()) {
        std::pair< llvm::Type*, std::vector<std::string> > ret;

        llvm::Type* type = nullptr;
        std::string temp_name;
        auto VisitDeclSpecifierSeq = visitDeclSpecifierSeq(decl);
        if (VisitDeclSpecifierSeq.type() == typeid(llvm::Type *)) {
            type = std::any_cast<llvm::Type*>(VisitDeclSpecifierSeq);
        } else if(VisitDeclSpecifierSeq.type() == typeid(std::string)) {
            temp_name = std::any_cast<std::string>(VisitDeclSpecifierSeq);
        }
        // TODO: 函数声明，暂时只允许在类内定义函数
        for (auto MemberDeclarator : ctx->memberDeclaratorList()->memberDeclarator()) {
            // TODO: 有漏洞！一行只允许一个类型，int *x, y 未实现
            int pointer_cnt = 0;
            std::vector<llvm::Value*> array_cnt;

            pointer_cnt = MemberDeclarator->declarator()->pointerDeclarator()->pointerOperator().size();
            if (type != nullptr && pointer_cnt > 0) {
                for (int i = 0; i < pointer_cnt; i++) {
                    type = llvm::PointerType::get(type, 0);
                }
            }

            auto NoPointerDeclarator = MemberDeclarator->declarator()->pointerDeclarator()->noPointerDeclarator();
            if (NoPointerDeclarator != nullptr) { // NOTE: Maybe NULL
                while (NoPointerDeclarator->LeftBracket() != nullptr) {
                    if (NoPointerDeclarator->constantExpression() != nullptr) {
                        // 检查下标是否是整数类型
                        llvm::Value* array_size = std::any_cast<llvm::Value*>(visitConstantExpression(NoPointerDeclarator->constantExpression()));
                        if (array_size != nullptr && !array_size->getType()->isIntegerTy()) {
                            std::cout << "Error: Array size must be an integer." << std::endl;
                            return nullptr;
                        }
                        array_cnt.insert(array_cnt.begin(), array_size);
                    } else {
                        array_cnt.insert(array_cnt.begin(), nullptr);
                    }
                    NoPointerDeclarator = NoPointerDeclarator->noPointerDeclarator();
                }
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
            }
            name = std::any_cast<std::string>(visitNoPointerDeclarator(NoPointerDeclarator));
            if (name == classname) {
                std::cout << "Error: Variable name cannot be the same as class name." << std::endl;
                return nullptr;
            }
            ret.second.push_back(name);
        }
        ret.first = type;
        return ret;
    }
    return nullptr;
}

std::any Visitor::visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx)
{
    // 该函数在上层被略过
    return nullptr;
}

std::any Visitor::visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx)
{
    // 该函数在上层被略过
    return nullptr;
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
    // 暂时只考虑单继承以及 public 继承
    if (auto baseSpecifierList = ctx->baseSpecifierList()) {
        return visitBaseSpecifierList(baseSpecifierList);
    }
    return nullptr;
}

std::any Visitor::visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx)
{
    if (auto BaseSpecifier = ctx->baseSpecifier(0)) {
        return visitBaseSpecifier(BaseSpecifier);
    }
    return nullptr;
}

std::any Visitor::visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx)
{
    Access access = Access::Private;
    if (auto accessSpecifier = ctx->accessSpecifier()) {
        std::string access = std::any_cast<std::string>(visitAccessSpecifier(accessSpecifier));
        if (access == "private") {
            access = Access::Private;
        } else if (access == "protected") {
            access = Access::Protected;
        } else if (access == "public") {
            access = Access::Public;
        }
    }

    std::string baseclassname = std::string("");
    if (auto baseTypeSpecifier = ctx->baseTypeSpecifier()) {
        baseclassname = std::any_cast<std::string>(visitBaseTypeSpecifier(baseTypeSpecifier));
    }

    // TODO: attribute
    return std::make_pair(baseclassname, access);
}

std::any Visitor::visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx)
{
    if (auto nestedNameSpecifier = ctx->nestedNameSpecifier()) {
        return visitNestedNameSpecifier(nestedNameSpecifier);
    } else if (auto ClassName = ctx->className()) {
        return visitClassName(ClassName);
    } else if (auto decltypeSpecifier = ctx->decltypeSpecifier()) {
        return visitDecltypeSpecifier(decltypeSpecifier);
    }
}

std::any Visitor::visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx)
{
    if (auto ClassorDeclType = ctx->classOrDeclType()) {
        return visitClassOrDeclType(ClassorDeclType);
    }
    return nullptr;
}

std::any Visitor::visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx)
{
    if (ctx->Private() != nullptr) {
        return std::string("private");
    } else if (ctx->Protected() != nullptr) {
        return std::string("protected");
    } else if (ctx->Public() != nullptr) {
        return std::string("public");
    }
    return std::string("");
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
        std::string temp = ctx->StringLiteral()->getText();
        temp.erase(std::remove(temp.begin(), temp.end(), '\"'), temp.end());
        std::string::size_type pos = 0;
        while((pos = temp.find("\\n")) != std::string::npos) {
            temp.replace(pos, 2, "\n");
        }
        return (llvm::Value *)builder.CreateGlobalStringPtr(temp);
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