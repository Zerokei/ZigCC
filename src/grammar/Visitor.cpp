#include <cstdint>
#include <string>
#include <vector>

#include "grammar/Visitor.h"

Scope &Visitor::currentScope()
{
    return this->scopes.back();
}

std::any Visitor::visitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx)
{
    visitDeclarationseq(ctx->declarationseq());
    return nullptr;
}

std::any Visitor::visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx)
{
    
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

}

std::any Visitor::visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx)
{

}

std::any Visitor::visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx)
{

}

std::any Visitor::visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx)
{

}

std::any Visitor::visitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx)
{

}

std::any Visitor::visitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx)
{

}

std::any Visitor::visitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx)
{

}

std::any Visitor::visitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx)
{

}

std::any Visitor::visitAndExpression(ZigCCParser::AndExpressionContext *ctx)
{

}

std::any Visitor::visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx)
{

}

std::any Visitor::visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx)
{

}

std::any Visitor::visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx)
{

}

std::any Visitor::visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx)
{

}

std::any Visitor::visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx)
{

}

std::any Visitor::visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx)
{
    if (auto AssignmentOperator = ctx->assignmentOperator()) {
        std::string AssignOp = std::any_cast<std::string>(visitAssignmentOperator(AssignmentOperator));
        if (AssignOp == "=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            builder.CreateStore(rhs, alloca);
            return rhs;
        } else if (AssignOp == "*=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            auto value = builder.CreateLoad(alloca);
            auto result = builder.CreateMul(value, rhs, "multmp");
            builder.CreateStore(result, alloca);
            return result;
        } else if (AssignOp == "/=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            auto value = builder.CreateLoad(alloca);
            auto result = builder.CreateSDiv(value, rhs, "divtmp");
            builder.CreateStore(result, alloca);
            return result;
        } else if (AssignOp == "%=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            auto value = builder.CreateLoad(alloca);
            auto result = builder.CreateSRem(value, rhs, "modtmp");
            builder.CreateStore(result, alloca);
            return result;
        } else if (AssignOp == "+=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            auto value = builder.CreateLoad(alloca);
            auto result = builder.CreateAdd(value, rhs, "addtmp");
            builder.CreateStore(result, alloca);
            return result;
        } else if (AssignOp == "-=") {
            auto lhs = std::any_cast<std::string>(visitLogicalOrExpression(ctx->logicalOrExpression()));
            auto rhs = std::any_cast<llvm::Value*>(visitInitializerClause(ctx->initializerClause()));
            auto alloca = this->currentScope().getVariable(lhs);
            auto value = builder.CreateLoad(alloca);
            auto result = builder.CreateSub(value, rhs, "subtmp");
            builder.CreateStore(result, alloca);
            return result;
        } else if (AssignOp == ">>=") {
            
    } else if (auto ConditionalExpression = ctx->conditionalExpression()) {
        return visitConditionalExpression(ConditionalExpression);
    } else if (auto LogicalOrExpression = ctx->logicalOrExpression()) {
        return visitLogicalOrExpression(LogicalOrExpression);
    } else if (auto ThrowExpression = ctx->throwExpression()) {
        return visitThrowExpression(ThrowExpression);
    } else if (auto InitializerClause = ctx->initializerClause()) {
        return visitInitializerClause(InitializerClause);
    }
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

}

std::any Visitor::visitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx)
{

}

std::any Visitor::visitStatement(ZigCCParser::StatementContext *ctx)
{

}

std::any Visitor::visitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx)
{

}

std::any Visitor::visitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx)
{

}

std::any Visitor::visitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx)
{

}

std::any Visitor::visitStatementSeq(ZigCCParser::StatementSeqContext *ctx)
{

}

std::any Visitor::visitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx)
{

}

std::any Visitor::visitCondition(ZigCCParser::ConditionContext *ctx)
{

}

std::any Visitor::visitIterationStatement(ZigCCParser::IterationStatementContext *ctx)
{

}

std::any Visitor::visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx)
{

}

std::any Visitor::visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx)
{

}

std::any Visitor::visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx)
{

}

std::any Visitor::visitJumpStatement(ZigCCParser::JumpStatementContext *ctx)
{

}

std::any Visitor::visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx)
{

}

std::any Visitor::visitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx)
{
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
    // 目前没有想到一行中有两种类型的情况，所以暂时不考虑
    // 当前只考虑 int x, y = 0; int x = y = 0; 这种情况，enum 以及 class 等复杂类型之后再作处理（添加分支处理（？））
    // 还有强制类型转换可以做（感觉应该不难）
    llvm::Type* type = std::any_cast<llvm::Type*>(visitDeclSpecifierSeq(ctx->declSpecifierSeq()));
    std::vector<std::string> names;
    std::vector<llvm::Value*> values;
    for (auto decl : ctx->initDeclaratorList()->initDeclarator()) {
        // visitDeclarator 函数返回变量名
        auto name = std::any_cast<std::string>(visitDeclarator(decl->declarator()));
        names.push_back(name);
        // 如果进行了初始化，则将初始化的值存入 values 中
        if (auto Initializer = decl->initializer()) {
            auto value = std::any_cast<llvm::Value*>(visitInitializer(Initializer));
            values.push_back(value);
        } else { // 否则存入 nullptr
            values.push_back(nullptr);
        }
    }
    for (int i = 0; i < names.size(); i++) {
        // CreateAlloca 函数将类型为 type 的变量 name 加入栈帧，对齐方式 nullptr（可能 struct 类型有用？）
        auto alloca = builder.CreateAlloca(type, nullptr, names[i]);
        // 当进行了初始化时，CreateStore 函数将赋值的表达式存入上一步开辟的地址空间 alloca 中
        if (values[i] != nullptr)
            builder.CreateStore(values[i], alloca);
        this->currentScope().setVariable(names[i], alloca);
    }
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
        
    } else if (auto Typedef = ctx->Typedef()) {
        
    } else if (auto Constexpr = ctx->Constexpr()) {
        
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
        return llvm::Type::getInt8Ty(*llvm_context);
    } else if (ctx->Char16() != nullptr) {
        return llvm::Type::getInt16Ty(*llvm_context);
    } else if (ctx->Char32() != nullptr) {
        return llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Wchar() != nullptr) {
        return llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Bool() != nullptr) {
        return llvm::Type::getInt1Ty(*llvm_context);
    } else if (ctx->Int() != nullptr) {
        return llvm::Type::getInt32Ty(*llvm_context);
    } else if (ctx->Float() != nullptr) {
        return llvm::Type::getFloatTy(*llvm_context);
    } else if (ctx->Double() != nullptr) {
        return llvm::Type::getDoubleTy(*llvm_context);
    } else if (ctx->Void() != nullptr) {
        return llvm::Type::getVoidTy(*llvm_context);
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

}

std::any Visitor::visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx)
{

}

std::any Visitor::visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx)
{

}

std::any Visitor::visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx)
{

}

std::any Visitor::visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx)
{

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

}