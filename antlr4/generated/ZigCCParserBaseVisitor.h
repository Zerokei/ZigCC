
// Generated from ZigCCParser.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "ZigCCParserVisitor.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of ZigCCParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ZigCCParserBaseVisitor : public ZigCCParserVisitor {
public:

  virtual std::any visitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpression(ZigCCParser::IdExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedId(ZigCCParser::QualifiedIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaptureList(ZigCCParser::CaptureListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCapture(ZigCCParser::CaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitcapture(ZigCCParser::InitcaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(ZigCCParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewExpression(ZigCCParser::NewExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewPlacement(ZigCCParser::NewPlacementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewTypeId(ZigCCParser::NewTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewInitializer(ZigCCParser::NewInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastExpression(ZigCCParser::CastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpression(ZigCCParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(ZigCCParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(ZigCCParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementSeq(ZigCCParser::StatementSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(ZigCCParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(ZigCCParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForInitStatement(ZigCCParser::ForInitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJumpStatement(ZigCCParser::JumpStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(ZigCCParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedefName(ZigCCParser::TypedefNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTheTypeName(ZigCCParser::TheTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumName(ZigCCParser::EnumNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumHead(ZigCCParser::EnumHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumkey(ZigCCParser::EnumkeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumbase(ZigCCParser::EnumbaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeratorList(ZigCCParser::EnumeratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumerator(ZigCCParser::EnumeratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceName(ZigCCParser::NamespaceNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUsingDirective(ZigCCParser::UsingDirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeList(ZigCCParser::AttributeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(ZigCCParser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBalancedtoken(ZigCCParser::BalancedtokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarator(ZigCCParser::DeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerOperator(ZigCCParser::PointerOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCvQualifier(ZigCCParser::CvQualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRefqualifier(ZigCCParser::RefqualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaratorid(ZigCCParser::DeclaratoridContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTheTypeId(ZigCCParser::TheTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionBody(ZigCCParser::FunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializer(ZigCCParser::InitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializerClause(ZigCCParser::InitializerClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializerList(ZigCCParser::InitializerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBracedInitList(ZigCCParser::BracedInitListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassName(ZigCCParser::ClassNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassHead(ZigCCParser::ClassHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassKey(ZigCCParser::ClassKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPureSpecifier(ZigCCParser::PureSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseClause(ZigCCParser::BaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemInitializerList(ZigCCParser::MemInitializerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemInitializer(ZigCCParser::MemInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeminitializerid(ZigCCParser::MeminitializeridContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateParameter(ZigCCParser::TemplateParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParameter(ZigCCParser::TypeParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateId(ZigCCParser::TemplateIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateName(ZigCCParser::TemplateNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTryBlock(ZigCCParser::TryBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHandlerSeq(ZigCCParser::HandlerSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHandler(ZigCCParser::HandlerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThrowExpression(ZigCCParser::ThrowExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeIdList(ZigCCParser::TypeIdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTheOperator(ZigCCParser::TheOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(ZigCCParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace antlrcpptest
