#include <cstdint>
#include <string>
#include <vector>

#include "SyntaxModel/SyntaxModel.h"
#include "Visitor.h"

namespace SM = SyntaxModel;
using PT = SM::PrimitiveType;

std::any visitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx)
{
    
}

std::any visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx)
{
    
}

std::any visitIdExpression(ZigCCParser::IdExpressionContext *ctx)
{

}

std::any visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx)
{

}

std::any visitQualifiedId(ZigCCParser::QualifiedIdContext *ctx)
{

}

std::any visitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx)
{

}

std::any visitLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx)
{

}

std::any visitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx)
{

}

std::any visitLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx)
{

}

std::any visitCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx)
{

}

std::any visitCaptureList(ZigCCParser::CaptureListContext *ctx)
{

}

std::any visitCapture(ZigCCParser::CaptureContext *ctx)
{

}

std::any visitSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx)
{

}

std::any visitInitcapture(ZigCCParser::InitcaptureContext *ctx)
{

}

std::any visitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx)
{

}

std::any visitPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx)
{

}

std::any visitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx)
{

}

std::any visitExpressionList(ZigCCParser::ExpressionListContext *ctx)
{

}

std::any visitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx)
{

}

std::any visitUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx)
{

}

std::any visitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx)
{

}

std::any visitNewExpression(ZigCCParser::NewExpressionContext *ctx)
{

}

std::any visitNewPlacement(ZigCCParser::NewPlacementContext *ctx)
{

}

std::any visitNewTypeId(ZigCCParser::NewTypeIdContext *ctx)
{

}

std::any visitNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx)
{

}

std::any visitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx)
{

}

std::any visitNewInitializer(ZigCCParser::NewInitializerContext *ctx)
{

}

std::any visitDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx)
{

}

std::any visitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx)
{

}

std::any visitCastExpression(ZigCCParser::CastExpressionContext *ctx)
{

}

std::any visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx)
{

}

std::any visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx)
{

}

std::any visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx)
{

}

std::any visitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx)
{

}

std::any visitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx)
{

}

std::any visitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx)
{

}

std::any visitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx)
{

}

std::any visitAndExpression(ZigCCParser::AndExpressionContext *ctx)
{

}

std::any visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx)
{

}

std::any visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx)
{

}

std::any visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx)
{

}

std::any visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx)
{

}

std::any visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx)
{

}

std::any visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx)
{

}

std::any visitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx)
{

}

std::any visitExpression(ZigCCParser::ExpressionContext *ctx)
{

}

std::any visitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx)
{

}

std::any visitStatement(ZigCCParser::StatementContext *ctx)
{

}

std::any visitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx)
{

}

std::any visitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx)
{

}

std::any visitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx)
{

}

std::any visitStatementSeq(ZigCCParser::StatementSeqContext *ctx)
{

}

std::any visitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx)
{

}

std::any visitCondition(ZigCCParser::ConditionContext *ctx)
{

}

std::any visitIterationStatement(ZigCCParser::IterationStatementContext *ctx)
{

}

std::any visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx)
{

}

std::any visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx)
{

}

std::any visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx)
{

}

std::any visitJumpStatement(ZigCCParser::JumpStatementContext *ctx)
{

}

std::any visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx)
{

}

std::any visitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx)
{

}

std::any visitDeclaration(ZigCCParser::DeclarationContext *ctx)
{

}

std::any visitBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx)
{

}

std::any visitAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx)
{

}

std::any visitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx)
{

}

std::any visitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx)
{

}

std::any visitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx)
{

}

std::any visitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx)
{

}

std::any visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx)
{

}

std::any visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx)
{

}

std::any visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx)
{

}

std::any visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx)
{

}

std::any visitTypedefName(ZigCCParser::TypedefNameContext *ctx)
{

}

std::any visitTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx)
{

}

std::any visitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx)
{

}

std::any visitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx)
{

}

std::any visitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx)
{

}

std::any visitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx)
{

}

std::any visitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx)
{

}

std::any visitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx)
{

}

std::any visitTheTypeName(ZigCCParser::TheTypeNameContext *ctx)
{

}

std::any visitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx)
{

}

std::any visitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx)
{

}

std::any visitEnumName(ZigCCParser::EnumNameContext *ctx)
{

}

std::any visitEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx)
{

}

std::any visitEnumHead(ZigCCParser::EnumHeadContext *ctx)
{

}

std::any visitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx)
{

}

std::any visitEnumkey(ZigCCParser::EnumkeyContext *ctx)
{

}

std::any visitEnumbase(ZigCCParser::EnumbaseContext *ctx)
{

}

std::any visitEnumeratorList(ZigCCParser::EnumeratorListContext *ctx)
{

}

std::any visitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx)
{

}

std::any visitEnumerator(ZigCCParser::EnumeratorContext *ctx)
{

}

std::any visitNamespaceName(ZigCCParser::NamespaceNameContext *ctx)
{

}

std::any visitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx)
{

}

std::any visitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx)
{

}

std::any visitNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx)
{

}

std::any visitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx)
{

}

std::any visitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx)
{

}

std::any visitUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx)
{

}

std::any visitUsingDirective(ZigCCParser::UsingDirectiveContext *ctx)
{

}

std::any visitAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx)
{

}

std::any visitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx)
{

}

std::any visitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx)
{

}

std::any visitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx)
{

}

std::any visitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx)
{

}

std::any visitAttributeList(ZigCCParser::AttributeListContext *ctx)
{

}

std::any visitAttribute(ZigCCParser::AttributeContext *ctx)
{

}

std::any visitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx)
{

}

std::any visitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx)
{

}

std::any visitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx)
{

}

std::any visitBalancedtoken(ZigCCParser::BalancedtokenContext *ctx)
{

}

std::any visitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx)
{

}

std::any visitInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx)
{

}

std::any visitDeclarator(ZigCCParser::DeclaratorContext *ctx)
{

}

std::any visitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx)
{

}

std::any visitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx)
{

}

std::any visitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx)
{

}

std::any visitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx)
{

}

std::any visitPointerOperator(ZigCCParser::PointerOperatorContext *ctx)
{

}

std::any visitCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx)
{

}

std::any visitCvQualifier(ZigCCParser::CvQualifierContext *ctx)
{

}

std::any visitRefqualifier(ZigCCParser::RefqualifierContext *ctx)
{

}

std::any visitDeclaratorid(ZigCCParser::DeclaratoridContext *ctx)
{

}

std::any visitTheTypeId(ZigCCParser::TheTypeIdContext *ctx)
{

}

std::any visitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx)
{

}

std::any visitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx)
{

}

std::any visitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx)
{

}

std::any visitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx)
{

}

std::any visitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx)
{

}

std::any visitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx)
{

}

std::any visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx)
{

}

std::any visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx)
{

}

std::any visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx)
{

}

std::any visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx)
{

}

std::any visitInitializer(ZigCCParser::InitializerContext *ctx)
{

}

std::any visitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx)
{

}

std::any visitInitializerClause(ZigCCParser::InitializerClauseContext *ctx)
{

}

std::any visitInitializerList(ZigCCParser::InitializerListContext *ctx)
{

}

std::any visitBracedInitList(ZigCCParser::BracedInitListContext *ctx)
{

}

std::any visitClassName(ZigCCParser::ClassNameContext *ctx)
{

}

std::any visitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx)
{

}

std::any visitClassHead(ZigCCParser::ClassHeadContext *ctx)
{

}

std::any visitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx)
{

}

std::any visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx)
{

}

std::any visitClassKey(ZigCCParser::ClassKeyContext *ctx)
{

}

std::any visitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx)
{

}

std::any visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx)
{

}

std::any visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx)
{

}

std::any visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx)
{

}

std::any visitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx)
{

}

std::any visitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx)
{

}

std::any visitPureSpecifier(ZigCCParser::PureSpecifierContext *ctx)
{

}

std::any visitBaseClause(ZigCCParser::BaseClauseContext *ctx)
{

}

std::any visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx)
{

}

std::any visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx)
{

}

std::any visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx)
{

}

std::any visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx)
{

}

std::any visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx)
{

}

std::any visitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx)
{

}

std::any visitConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx)
{

}

std::any visitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx)
{

}

std::any visitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx)
{

}

std::any visitMemInitializerList(ZigCCParser::MemInitializerListContext *ctx)
{

}

std::any visitMemInitializer(ZigCCParser::MemInitializerContext *ctx)
{

}

std::any visitMeminitializerid(ZigCCParser::MeminitializeridContext *ctx)
{

}

std::any visitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx)
{

}

std::any visitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx)
{

}

std::any visitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx)
{

}

std::any visitTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx)
{

}

std::any visitTemplateParameter(ZigCCParser::TemplateParameterContext *ctx)
{

}

std::any visitTypeParameter(ZigCCParser::TypeParameterContext *ctx)
{

}

std::any visitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx)
{

}

std::any visitTemplateId(ZigCCParser::TemplateIdContext *ctx)
{

}

std::any visitTemplateName(ZigCCParser::TemplateNameContext *ctx)
{

}

std::any visitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx)
{

}

std::any visitTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx)
{

}

std::any visitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx)
{

}

std::any visitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx)
{

}

std::any visitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx)
{

}

std::any visitTryBlock(ZigCCParser::TryBlockContext *ctx)
{

}

std::any visitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx)
{

}

std::any visitHandlerSeq(ZigCCParser::HandlerSeqContext *ctx)
{

}

std::any visitHandler(ZigCCParser::HandlerContext *ctx)
{

}

std::any visitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx)
{

}

std::any visitThrowExpression(ZigCCParser::ThrowExpressionContext *ctx)
{

}

std::any visitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx)
{

}

std::any visitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx)
{

}

std::any visitTypeIdList(ZigCCParser::TypeIdListContext *ctx)
{

}

std::any visitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx)
{

}

std::any visitTheOperator(ZigCCParser::TheOperatorContext *ctx)
{

}

std::any visitLiteral(ZigCCParser::LiteralContext *ctx)
{

}

std::vector<utils::TerminalInfo> Visitor::make_all_terminals(const std::vector<antlr4::tree::TerminalNode*>& contexts)
{
    std::vector<utils::TerminalInfo> syntax_nodes;
    syntax_nodes.reserve(contexts.size());
    for (auto* ctx : contexts)
        syntax_nodes.emplace_back(ctx);
    return syntax_nodes;
}
