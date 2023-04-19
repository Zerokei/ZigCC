
// Generated from ZigCCParser.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "ZigCCParser.h"


namespace antlrcpptest {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by ZigCCParser.
 */
class  ZigCCParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ZigCCParser.
   */
    virtual std::any visitTranslationUnit(ZigCCParser::TranslationUnitContext *context) = 0;

    virtual std::any visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitIdExpression(ZigCCParser::IdExpressionContext *context) = 0;

    virtual std::any visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *context) = 0;

    virtual std::any visitQualifiedId(ZigCCParser::QualifiedIdContext *context) = 0;

    virtual std::any visitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *context) = 0;

    virtual std::any visitLambdaExpression(ZigCCParser::LambdaExpressionContext *context) = 0;

    virtual std::any visitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *context) = 0;

    virtual std::any visitLambdaCapture(ZigCCParser::LambdaCaptureContext *context) = 0;

    virtual std::any visitCaptureDefault(ZigCCParser::CaptureDefaultContext *context) = 0;

    virtual std::any visitCaptureList(ZigCCParser::CaptureListContext *context) = 0;

    virtual std::any visitCapture(ZigCCParser::CaptureContext *context) = 0;

    virtual std::any visitSimpleCapture(ZigCCParser::SimpleCaptureContext *context) = 0;

    virtual std::any visitInitcapture(ZigCCParser::InitcaptureContext *context) = 0;

    virtual std::any visitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *context) = 0;

    virtual std::any visitPostfixExpression(ZigCCParser::PostfixExpressionContext *context) = 0;

    virtual std::any visitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *context) = 0;

    virtual std::any visitExpressionList(ZigCCParser::ExpressionListContext *context) = 0;

    virtual std::any visitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *context) = 0;

    virtual std::any visitUnaryExpression(ZigCCParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitUnaryOperator(ZigCCParser::UnaryOperatorContext *context) = 0;

    virtual std::any visitNewExpression(ZigCCParser::NewExpressionContext *context) = 0;

    virtual std::any visitNewPlacement(ZigCCParser::NewPlacementContext *context) = 0;

    virtual std::any visitNewTypeId(ZigCCParser::NewTypeIdContext *context) = 0;

    virtual std::any visitNewDeclarator(ZigCCParser::NewDeclaratorContext *context) = 0;

    virtual std::any visitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *context) = 0;

    virtual std::any visitNewInitializer(ZigCCParser::NewInitializerContext *context) = 0;

    virtual std::any visitDeleteExpression(ZigCCParser::DeleteExpressionContext *context) = 0;

    virtual std::any visitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *context) = 0;

    virtual std::any visitCastExpression(ZigCCParser::CastExpressionContext *context) = 0;

    virtual std::any visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitShiftExpression(ZigCCParser::ShiftExpressionContext *context) = 0;

    virtual std::any visitShiftOperator(ZigCCParser::ShiftOperatorContext *context) = 0;

    virtual std::any visitRelationalExpression(ZigCCParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(ZigCCParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitAndExpression(ZigCCParser::AndExpressionContext *context) = 0;

    virtual std::any visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *context) = 0;

    virtual std::any visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitExpression(ZigCCParser::ExpressionContext *context) = 0;

    virtual std::any visitConstantExpression(ZigCCParser::ConstantExpressionContext *context) = 0;

    virtual std::any visitStatement(ZigCCParser::StatementContext *context) = 0;

    virtual std::any visitLabeledStatement(ZigCCParser::LabeledStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(ZigCCParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitCompoundStatement(ZigCCParser::CompoundStatementContext *context) = 0;

    virtual std::any visitStatementSeq(ZigCCParser::StatementSeqContext *context) = 0;

    virtual std::any visitSelectionStatement(ZigCCParser::SelectionStatementContext *context) = 0;

    virtual std::any visitCondition(ZigCCParser::ConditionContext *context) = 0;

    virtual std::any visitIterationStatement(ZigCCParser::IterationStatementContext *context) = 0;

    virtual std::any visitForInitStatement(ZigCCParser::ForInitStatementContext *context) = 0;

    virtual std::any visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *context) = 0;

    virtual std::any visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *context) = 0;

    virtual std::any visitJumpStatement(ZigCCParser::JumpStatementContext *context) = 0;

    virtual std::any visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *context) = 0;

    virtual std::any visitDeclarationseq(ZigCCParser::DeclarationseqContext *context) = 0;

    virtual std::any visitDeclaration(ZigCCParser::DeclarationContext *context) = 0;

    virtual std::any visitBlockDeclaration(ZigCCParser::BlockDeclarationContext *context) = 0;

    virtual std::any visitAliasDeclaration(ZigCCParser::AliasDeclarationContext *context) = 0;

    virtual std::any visitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *context) = 0;

    virtual std::any visitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *context) = 0;

    virtual std::any visitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *context) = 0;

    virtual std::any visitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *context) = 0;

    virtual std::any visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *context) = 0;

    virtual std::any visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *context) = 0;

    virtual std::any visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *context) = 0;

    virtual std::any visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *context) = 0;

    virtual std::any visitTypedefName(ZigCCParser::TypedefNameContext *context) = 0;

    virtual std::any visitTypeSpecifier(ZigCCParser::TypeSpecifierContext *context) = 0;

    virtual std::any visitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *context) = 0;

    virtual std::any visitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *context) = 0;

    virtual std::any visitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *context) = 0;

    virtual std::any visitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *context) = 0;

    virtual std::any visitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *context) = 0;

    virtual std::any visitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *context) = 0;

    virtual std::any visitTheTypeName(ZigCCParser::TheTypeNameContext *context) = 0;

    virtual std::any visitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *context) = 0;

    virtual std::any visitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *context) = 0;

    virtual std::any visitEnumName(ZigCCParser::EnumNameContext *context) = 0;

    virtual std::any visitEnumSpecifier(ZigCCParser::EnumSpecifierContext *context) = 0;

    virtual std::any visitEnumHead(ZigCCParser::EnumHeadContext *context) = 0;

    virtual std::any visitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *context) = 0;

    virtual std::any visitEnumkey(ZigCCParser::EnumkeyContext *context) = 0;

    virtual std::any visitEnumbase(ZigCCParser::EnumbaseContext *context) = 0;

    virtual std::any visitEnumeratorList(ZigCCParser::EnumeratorListContext *context) = 0;

    virtual std::any visitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *context) = 0;

    virtual std::any visitEnumerator(ZigCCParser::EnumeratorContext *context) = 0;

    virtual std::any visitNamespaceName(ZigCCParser::NamespaceNameContext *context) = 0;

    virtual std::any visitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *context) = 0;

    virtual std::any visitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *context) = 0;

    virtual std::any visitNamespaceAlias(ZigCCParser::NamespaceAliasContext *context) = 0;

    virtual std::any visitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *context) = 0;

    virtual std::any visitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *context) = 0;

    virtual std::any visitUsingDeclaration(ZigCCParser::UsingDeclarationContext *context) = 0;

    virtual std::any visitUsingDirective(ZigCCParser::UsingDirectiveContext *context) = 0;

    virtual std::any visitAsmDefinition(ZigCCParser::AsmDefinitionContext *context) = 0;

    virtual std::any visitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *context) = 0;

    virtual std::any visitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *context) = 0;

    virtual std::any visitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *context) = 0;

    virtual std::any visitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *context) = 0;

    virtual std::any visitAttributeList(ZigCCParser::AttributeListContext *context) = 0;

    virtual std::any visitAttribute(ZigCCParser::AttributeContext *context) = 0;

    virtual std::any visitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *context) = 0;

    virtual std::any visitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *context) = 0;

    virtual std::any visitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *context) = 0;

    virtual std::any visitBalancedtoken(ZigCCParser::BalancedtokenContext *context) = 0;

    virtual std::any visitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *context) = 0;

    virtual std::any visitInitDeclarator(ZigCCParser::InitDeclaratorContext *context) = 0;

    virtual std::any visitDeclarator(ZigCCParser::DeclaratorContext *context) = 0;

    virtual std::any visitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *context) = 0;

    virtual std::any visitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *context) = 0;

    virtual std::any visitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *context) = 0;

    virtual std::any visitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *context) = 0;

    virtual std::any visitPointerOperator(ZigCCParser::PointerOperatorContext *context) = 0;

    virtual std::any visitCvqualifierseq(ZigCCParser::CvqualifierseqContext *context) = 0;

    virtual std::any visitCvQualifier(ZigCCParser::CvQualifierContext *context) = 0;

    virtual std::any visitRefqualifier(ZigCCParser::RefqualifierContext *context) = 0;

    virtual std::any visitDeclaratorid(ZigCCParser::DeclaratoridContext *context) = 0;

    virtual std::any visitTheTypeId(ZigCCParser::TheTypeIdContext *context) = 0;

    virtual std::any visitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *context) = 0;

    virtual std::any visitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *context) = 0;

    virtual std::any visitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *context) = 0;

    virtual std::any visitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *context) = 0;

    virtual std::any visitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *context) = 0;

    virtual std::any visitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *context) = 0;

    virtual std::any visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *context) = 0;

    virtual std::any visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *context) = 0;

    virtual std::any visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionBody(ZigCCParser::FunctionBodyContext *context) = 0;

    virtual std::any visitInitializer(ZigCCParser::InitializerContext *context) = 0;

    virtual std::any visitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *context) = 0;

    virtual std::any visitInitializerClause(ZigCCParser::InitializerClauseContext *context) = 0;

    virtual std::any visitInitializerList(ZigCCParser::InitializerListContext *context) = 0;

    virtual std::any visitBracedInitList(ZigCCParser::BracedInitListContext *context) = 0;

    virtual std::any visitClassName(ZigCCParser::ClassNameContext *context) = 0;

    virtual std::any visitClassSpecifier(ZigCCParser::ClassSpecifierContext *context) = 0;

    virtual std::any visitClassHead(ZigCCParser::ClassHeadContext *context) = 0;

    virtual std::any visitClassHeadName(ZigCCParser::ClassHeadNameContext *context) = 0;

    virtual std::any visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *context) = 0;

    virtual std::any visitClassKey(ZigCCParser::ClassKeyContext *context) = 0;

    virtual std::any visitMemberSpecification(ZigCCParser::MemberSpecificationContext *context) = 0;

    virtual std::any visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *context) = 0;

    virtual std::any visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *context) = 0;

    virtual std::any visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *context) = 0;

    virtual std::any visitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *context) = 0;

    virtual std::any visitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *context) = 0;

    virtual std::any visitPureSpecifier(ZigCCParser::PureSpecifierContext *context) = 0;

    virtual std::any visitBaseClause(ZigCCParser::BaseClauseContext *context) = 0;

    virtual std::any visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *context) = 0;

    virtual std::any visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *context) = 0;

    virtual std::any visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *context) = 0;

    virtual std::any visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *context) = 0;

    virtual std::any visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *context) = 0;

    virtual std::any visitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *context) = 0;

    virtual std::any visitConversionTypeId(ZigCCParser::ConversionTypeIdContext *context) = 0;

    virtual std::any visitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *context) = 0;

    virtual std::any visitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *context) = 0;

    virtual std::any visitMemInitializerList(ZigCCParser::MemInitializerListContext *context) = 0;

    virtual std::any visitMemInitializer(ZigCCParser::MemInitializerContext *context) = 0;

    virtual std::any visitMeminitializerid(ZigCCParser::MeminitializeridContext *context) = 0;

    virtual std::any visitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *context) = 0;

    virtual std::any visitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *context) = 0;

    virtual std::any visitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *context) = 0;

    virtual std::any visitTemplateparameterList(ZigCCParser::TemplateparameterListContext *context) = 0;

    virtual std::any visitTemplateParameter(ZigCCParser::TemplateParameterContext *context) = 0;

    virtual std::any visitTypeParameter(ZigCCParser::TypeParameterContext *context) = 0;

    virtual std::any visitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *context) = 0;

    virtual std::any visitTemplateId(ZigCCParser::TemplateIdContext *context) = 0;

    virtual std::any visitTemplateName(ZigCCParser::TemplateNameContext *context) = 0;

    virtual std::any visitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *context) = 0;

    virtual std::any visitTemplateArgument(ZigCCParser::TemplateArgumentContext *context) = 0;

    virtual std::any visitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *context) = 0;

    virtual std::any visitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *context) = 0;

    virtual std::any visitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *context) = 0;

    virtual std::any visitTryBlock(ZigCCParser::TryBlockContext *context) = 0;

    virtual std::any visitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *context) = 0;

    virtual std::any visitHandlerSeq(ZigCCParser::HandlerSeqContext *context) = 0;

    virtual std::any visitHandler(ZigCCParser::HandlerContext *context) = 0;

    virtual std::any visitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *context) = 0;

    virtual std::any visitThrowExpression(ZigCCParser::ThrowExpressionContext *context) = 0;

    virtual std::any visitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *context) = 0;

    virtual std::any visitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *context) = 0;

    virtual std::any visitTypeIdList(ZigCCParser::TypeIdListContext *context) = 0;

    virtual std::any visitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *context) = 0;

    virtual std::any visitTheOperator(ZigCCParser::TheOperatorContext *context) = 0;

    virtual std::any visitLiteral(ZigCCParser::LiteralContext *context) = 0;


};

}  // namespace antlrcpptest
