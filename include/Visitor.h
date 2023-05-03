#pragma once

#include "SyntaxModel/SyntaxModel.h"
#include "antlr4-runtime.h"
#include "grammar/ZigCCParserBaseVisitor.h"
#include "utils.h"

using namespace antlrcpptest;

class Visitor : public ZigCCParserBaseVisitor {
public:
    virtual std::any visitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx) override;
    virtual std::any visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx) override;
    virtual std::any visitIdExpression(ZigCCParser::IdExpressionContext *ctx) override;
    virtual std::any visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx) override;
    virtual std::any visitQualifiedId(ZigCCParser::QualifiedIdContext *ctx) override;
    virtual std::any visitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx) override;
    virtual std::any visitLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx) override;
    virtual std::any visitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx) override;
    virtual std::any visitLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx) override;
    virtual std::any visitCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx) override;
    virtual std::any visitCaptureList(ZigCCParser::CaptureListContext *ctx) override;
    virtual std::any visitCapture(ZigCCParser::CaptureContext *ctx) override;
    virtual std::any visitSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx) override;
    virtual std::any visitInitcapture(ZigCCParser::InitcaptureContext *ctx) override;
    virtual std::any visitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx) override;
    virtual std::any visitPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx) override;
    virtual std::any visitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx) override;
    virtual std::any visitExpressionList(ZigCCParser::ExpressionListContext *ctx) override;
    virtual std::any visitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx) override;
    virtual std::any visitUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx) override;
    virtual std::any visitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx) override;
    virtual std::any visitNewExpression(ZigCCParser::NewExpressionContext *ctx) override;
    virtual std::any visitNewPlacement(ZigCCParser::NewPlacementContext *ctx) override;
    virtual std::any visitNewTypeId(ZigCCParser::NewTypeIdContext *ctx) override;
    virtual std::any visitNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx) override;
    virtual std::any visitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx) override;
    virtual std::any visitNewInitializer(ZigCCParser::NewInitializerContext *ctx) override;
    virtual std::any visitDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx) override;
    virtual std::any visitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx) override;
    virtual std::any visitCastExpression(ZigCCParser::CastExpressionContext *ctx) override;
    virtual std::any visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx) override;
    virtual std::any visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx) override;
    virtual std::any visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx) override;
    virtual std::any visitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx) override;
    virtual std::any visitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx) override;
    virtual std::any visitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx) override;
    virtual std::any visitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx) override;
    virtual std::any visitAndExpression(ZigCCParser::AndExpressionContext *ctx) override;
    virtual std::any visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx) override;
    virtual std::any visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx) override;
    virtual std::any visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx) override;
    virtual std::any visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx) override;
    virtual std::any visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx) override;
    virtual std::any visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx) override;
    virtual std::any visitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx) override;
    virtual std::any visitExpression(ZigCCParser::ExpressionContext *ctx) override;
    virtual std::any visitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx) override;
    virtual std::any visitStatement(ZigCCParser::StatementContext *ctx) override;
    virtual std::any visitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx) override;
    virtual std::any visitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx) override;
    virtual std::any visitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx) override;
    virtual std::any visitStatementSeq(ZigCCParser::StatementSeqContext *ctx) override;
    virtual std::any visitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx) override;
    virtual std::any visitCondition(ZigCCParser::ConditionContext *ctx) override;
    virtual std::any visitIterationStatement(ZigCCParser::IterationStatementContext *ctx) override;
    virtual std::any visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx) override;
    virtual std::any visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx) override;
    virtual std::any visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx) override;
    virtual std::any visitJumpStatement(ZigCCParser::JumpStatementContext *ctx) override;
    virtual std::any visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx) override;
    virtual std::any visitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx) override;
    virtual std::any visitDeclaration(ZigCCParser::DeclarationContext *ctx) override;
    virtual std::any visitBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx) override;
    virtual std::any visitAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx) override;
    virtual std::any visitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx) override;
    virtual std::any visitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx) override;
    virtual std::any visitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx) override;
    virtual std::any visitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx) override;
    virtual std::any visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx) override;
    virtual std::any visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx) override;
    virtual std::any visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx) override;
    virtual std::any visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx) override;
    virtual std::any visitTypedefName(ZigCCParser::TypedefNameContext *ctx) override;
    virtual std::any visitTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx) override;
    virtual std::any visitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx) override;
    virtual std::any visitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx) override;
    virtual std::any visitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx) override;
    virtual std::any visitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx) override;
    virtual std::any visitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx) override;
    virtual std::any visitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx) override;
    virtual std::any visitTheTypeName(ZigCCParser::TheTypeNameContext *ctx) override;
    virtual std::any visitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx) override;
    virtual std::any visitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx) override;
    virtual std::any visitEnumName(ZigCCParser::EnumNameContext *ctx) override;
    virtual std::any visitEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx) override;
    virtual std::any visitEnumHead(ZigCCParser::EnumHeadContext *ctx) override;
    virtual std::any visitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx) override;
    virtual std::any visitEnumkey(ZigCCParser::EnumkeyContext *ctx) override;
    virtual std::any visitEnumbase(ZigCCParser::EnumbaseContext *ctx) override;
    virtual std::any visitEnumeratorList(ZigCCParser::EnumeratorListContext *ctx) override;
    virtual std::any visitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx) override;
    virtual std::any visitEnumerator(ZigCCParser::EnumeratorContext *ctx) override;
    virtual std::any visitNamespaceName(ZigCCParser::NamespaceNameContext *ctx) override;
    virtual std::any visitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx) override;
    virtual std::any visitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx) override;
    virtual std::any visitNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx) override;
    virtual std::any visitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx) override;
    virtual std::any visitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx) override;
    virtual std::any visitUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx) override;
    virtual std::any visitUsingDirective(ZigCCParser::UsingDirectiveContext *ctx) override;
    virtual std::any visitAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx) override;
    virtual std::any visitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx) override;
    virtual std::any visitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx) override;
    virtual std::any visitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx) override;
    virtual std::any visitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx) override;
    virtual std::any visitAttributeList(ZigCCParser::AttributeListContext *ctx) override;
    virtual std::any visitAttribute(ZigCCParser::AttributeContext *ctx) override;
    virtual std::any visitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx) override;
    virtual std::any visitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx) override;
    virtual std::any visitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx) override;
    virtual std::any visitBalancedtoken(ZigCCParser::BalancedtokenContext *ctx) override;
    virtual std::any visitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx) override;
    virtual std::any visitInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx) override;
    virtual std::any visitDeclarator(ZigCCParser::DeclaratorContext *ctx) override;
    virtual std::any visitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx) override;
    virtual std::any visitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx) override;
    virtual std::any visitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx) override;
    virtual std::any visitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx) override;
    virtual std::any visitPointerOperator(ZigCCParser::PointerOperatorContext *ctx) override;
    virtual std::any visitCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx) override;
    virtual std::any visitCvQualifier(ZigCCParser::CvQualifierContext *ctx) override;
    virtual std::any visitRefqualifier(ZigCCParser::RefqualifierContext *ctx) override;
    virtual std::any visitDeclaratorid(ZigCCParser::DeclaratoridContext *ctx) override;
    virtual std::any visitTheTypeId(ZigCCParser::TheTypeIdContext *ctx) override;
    virtual std::any visitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx) override;
    virtual std::any visitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx) override;
    virtual std::any visitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx) override;
    virtual std::any visitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx) override;
    virtual std::any visitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx) override;
    virtual std::any visitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx) override;
    virtual std::any visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx) override;
    virtual std::any visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx) override;
    virtual std::any visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx) override;
    virtual std::any visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx) override;
    virtual std::any visitInitializer(ZigCCParser::InitializerContext *ctx) override;
    virtual std::any visitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx) override;
    virtual std::any visitInitializerClause(ZigCCParser::InitializerClauseContext *ctx) override;
    virtual std::any visitInitializerList(ZigCCParser::InitializerListContext *ctx) override;
    virtual std::any visitBracedInitList(ZigCCParser::BracedInitListContext *ctx) override;
    virtual std::any visitClassName(ZigCCParser::ClassNameContext *ctx) override;
    virtual std::any visitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx) override;
    virtual std::any visitClassHead(ZigCCParser::ClassHeadContext *ctx) override;
    virtual std::any visitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx) override;
    virtual std::any visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx) override;
    virtual std::any visitClassKey(ZigCCParser::ClassKeyContext *ctx) override;
    virtual std::any visitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx) override;
    virtual std::any visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx) override;
    virtual std::any visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx) override;
    virtual std::any visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx) override;
    virtual std::any visitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx) override;
    virtual std::any visitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx) override;
    virtual std::any visitPureSpecifier(ZigCCParser::PureSpecifierContext *ctx) override;
    virtual std::any visitBaseClause(ZigCCParser::BaseClauseContext *ctx) override;
    virtual std::any visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx) override;
    virtual std::any visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx) override;
    virtual std::any visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx) override;
    virtual std::any visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx) override;
    virtual std::any visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx) override;
    virtual std::any visitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx) override;
    virtual std::any visitConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx) override;
    virtual std::any visitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx) override;
    virtual std::any visitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx) override;
    virtual std::any visitMemInitializerList(ZigCCParser::MemInitializerListContext *ctx) override;
    virtual std::any visitMemInitializer(ZigCCParser::MemInitializerContext *ctx) override;
    virtual std::any visitMeminitializerid(ZigCCParser::MeminitializeridContext *ctx) override;
    virtual std::any visitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx) override;
    virtual std::any visitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx) override;
    virtual std::any visitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx) override;
    virtual std::any visitTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx) override;
    virtual std::any visitTemplateParameter(ZigCCParser::TemplateParameterContext *ctx) override;
    virtual std::any visitTypeParameter(ZigCCParser::TypeParameterContext *ctx) override;
    virtual std::any visitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx) override;
    virtual std::any visitTemplateId(ZigCCParser::TemplateIdContext *ctx) override;
    virtual std::any visitTemplateName(ZigCCParser::TemplateNameContext *ctx) override;
    virtual std::any visitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx) override;
    virtual std::any visitTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx) override;
    virtual std::any visitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx) override;
    virtual std::any visitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx) override;
    virtual std::any visitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx) override;
    virtual std::any visitTryBlock(ZigCCParser::TryBlockContext *ctx) override;
    virtual std::any visitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx) override;
    virtual std::any visitHandlerSeq(ZigCCParser::HandlerSeqContext *ctx) override;
    virtual std::any visitHandler(ZigCCParser::HandlerContext *ctx) override;
    virtual std::any visitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx) override;
    virtual std::any visitThrowExpression(ZigCCParser::ThrowExpressionContext *ctx) override;
    virtual std::any visitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx) override;
    virtual std::any visitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx) override;
    virtual std::any visitTypeIdList(ZigCCParser::TypeIdListContext *ctx) override;
    virtual std::any visitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx) override;
    virtual std::any visitTheOperator(ZigCCParser::TheOperatorContext *ctx) override;
    virtual std::any visitLiteral(ZigCCParser::LiteralContext *ctx) override;

private:
    template <typename CTX>
    antlrcpp::Any visitBinaryOp(CTX* ctx, SyntaxModel::BinaryOp::Op op)
    {
        const auto& exprs = ctx->expression();
        auto left_expr = visit_single<SyntaxModel::Expression>(exprs[0]);
        auto right_expr = visit_single<SyntaxModel::Expression>(exprs[1]);
        return static_cast<SyntaxModel::Expression*>(new SyntaxModel::BinaryOp(ctx->getSourceInterval(), left_expr, right_expr, op));
    }

    template <class CTX>
    inline antlrcpp::Any visitUnaryAffectation(SyntaxModel::Affectation::Op op, CTX* ctx)
    {
        // array_indexing is nullptr if we don't affect to an array element
        auto var_name = SyntaxModel::Identifier(ctx->IDENTIFIER());
        auto array_index = visit_single<SyntaxModel::Expression>(ctx->expression());
        return static_cast<SyntaxModel::Expression*>(new SyntaxModel::Affectation(ctx->getSourceInterval(), op, var_name, array_index));
    }

    template <class CTX>
    inline antlrcpp::Any visitBinaryAffectation(SyntaxModel::Affectation::Op op, CTX* ctx)
    {
        // array_indexing is nullptr if we don't affect to an array element
        auto var_name = SyntaxModel::Identifier(ctx->IDENTIFIER());
        auto expressions = ctx->expression();
        auto array_index = (expressions.size() > 1) ? visit_single<SyntaxModel::Expression>(ctx->expression(0)) : nullptr;
        auto value = visit_single<SyntaxModel::Expression>(expressions.back());
        return static_cast<SyntaxModel::Expression*>(new SyntaxModel::Affectation(ctx->getSourceInterval(), op, var_name, array_index, value));
    }

    template <class T, class CTX>
    inline T* visit_single(CTX* context)
    {
        if (context != nullptr)
            return static_cast<T*>(visit(context));
        return nullptr;
    }

    template <class T, class CTX>
    inline std::list<const T*> visit_all(const std::vector<CTX*>& contexts)
    {
        std::list<const T*> syntax_nodes;
        for (auto* ctx : contexts) {
            if (ctx != nullptr) {
                auto visited = visit(ctx);
                if (visited.isNotNull())
                    syntax_nodes.push_back(static_cast<T*>(visited));
            }
        }
        return syntax_nodes;
    }

    static inline const std::list<const SyntaxModel::Definition::size_constant*> parseArraySizes(const std::vector<antlr4::tree::TerminalNode*>& integers);
    static inline std::vector<utils::TerminalInfo> make_all_terminals(const std::vector<antlr4::tree::TerminalNode*>& contexts);
};
