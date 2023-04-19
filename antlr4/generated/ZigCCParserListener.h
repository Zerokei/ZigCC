
// Generated from ZigCCParser.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "ZigCCParser.h"


namespace antlrcpptest {

/**
 * This interface defines an abstract listener for a parse tree produced by ZigCCParser.
 */
class  ZigCCParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterTranslationUnit(ZigCCParser::TranslationUnitContext *ctx) = 0;
  virtual void exitTranslationUnit(ZigCCParser::TranslationUnitContext *ctx) = 0;

  virtual void enterPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(ZigCCParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterIdExpression(ZigCCParser::IdExpressionContext *ctx) = 0;
  virtual void exitIdExpression(ZigCCParser::IdExpressionContext *ctx) = 0;

  virtual void enterUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx) = 0;
  virtual void exitUnqualifiedId(ZigCCParser::UnqualifiedIdContext *ctx) = 0;

  virtual void enterQualifiedId(ZigCCParser::QualifiedIdContext *ctx) = 0;
  virtual void exitQualifiedId(ZigCCParser::QualifiedIdContext *ctx) = 0;

  virtual void enterNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx) = 0;
  virtual void exitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext *ctx) = 0;

  virtual void enterLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx) = 0;
  virtual void exitLambdaExpression(ZigCCParser::LambdaExpressionContext *ctx) = 0;

  virtual void enterLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx) = 0;
  virtual void exitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext *ctx) = 0;

  virtual void enterLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx) = 0;
  virtual void exitLambdaCapture(ZigCCParser::LambdaCaptureContext *ctx) = 0;

  virtual void enterCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx) = 0;
  virtual void exitCaptureDefault(ZigCCParser::CaptureDefaultContext *ctx) = 0;

  virtual void enterCaptureList(ZigCCParser::CaptureListContext *ctx) = 0;
  virtual void exitCaptureList(ZigCCParser::CaptureListContext *ctx) = 0;

  virtual void enterCapture(ZigCCParser::CaptureContext *ctx) = 0;
  virtual void exitCapture(ZigCCParser::CaptureContext *ctx) = 0;

  virtual void enterSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx) = 0;
  virtual void exitSimpleCapture(ZigCCParser::SimpleCaptureContext *ctx) = 0;

  virtual void enterInitcapture(ZigCCParser::InitcaptureContext *ctx) = 0;
  virtual void exitInitcapture(ZigCCParser::InitcaptureContext *ctx) = 0;

  virtual void enterLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx) = 0;
  virtual void exitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext *ctx) = 0;

  virtual void enterPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(ZigCCParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx) = 0;
  virtual void exitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext *ctx) = 0;

  virtual void enterExpressionList(ZigCCParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(ZigCCParser::ExpressionListContext *ctx) = 0;

  virtual void enterPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx) = 0;
  virtual void exitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext *ctx) = 0;

  virtual void enterUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(ZigCCParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(ZigCCParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterNewExpression(ZigCCParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(ZigCCParser::NewExpressionContext *ctx) = 0;

  virtual void enterNewPlacement(ZigCCParser::NewPlacementContext *ctx) = 0;
  virtual void exitNewPlacement(ZigCCParser::NewPlacementContext *ctx) = 0;

  virtual void enterNewTypeId(ZigCCParser::NewTypeIdContext *ctx) = 0;
  virtual void exitNewTypeId(ZigCCParser::NewTypeIdContext *ctx) = 0;

  virtual void enterNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx) = 0;
  virtual void exitNewDeclarator(ZigCCParser::NewDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext *ctx) = 0;

  virtual void enterNewInitializer(ZigCCParser::NewInitializerContext *ctx) = 0;
  virtual void exitNewInitializer(ZigCCParser::NewInitializerContext *ctx) = 0;

  virtual void enterDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx) = 0;
  virtual void exitDeleteExpression(ZigCCParser::DeleteExpressionContext *ctx) = 0;

  virtual void enterNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx) = 0;
  virtual void exitNoExceptExpression(ZigCCParser::NoExceptExpressionContext *ctx) = 0;

  virtual void enterCastExpression(ZigCCParser::CastExpressionContext *ctx) = 0;
  virtual void exitCastExpression(ZigCCParser::CastExpressionContext *ctx) = 0;

  virtual void enterPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx) = 0;
  virtual void exitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(ZigCCParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(ZigCCParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(ZigCCParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterShiftOperator(ZigCCParser::ShiftOperatorContext *ctx) = 0;
  virtual void exitShiftOperator(ZigCCParser::ShiftOperatorContext *ctx) = 0;

  virtual void enterRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(ZigCCParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(ZigCCParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterAndExpression(ZigCCParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(ZigCCParser::AndExpressionContext *ctx) = 0;

  virtual void enterExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx) = 0;
  virtual void exitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext *ctx) = 0;

  virtual void enterInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx) = 0;
  virtual void exitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(ZigCCParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(ZigCCParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(ZigCCParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterExpression(ZigCCParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(ZigCCParser::ExpressionContext *ctx) = 0;

  virtual void enterConstantExpression(ZigCCParser::ConstantExpressionContext *ctx) = 0;
  virtual void exitConstantExpression(ZigCCParser::ConstantExpressionContext *ctx) = 0;

  virtual void enterStatement(ZigCCParser::StatementContext *ctx) = 0;
  virtual void exitStatement(ZigCCParser::StatementContext *ctx) = 0;

  virtual void enterLabeledStatement(ZigCCParser::LabeledStatementContext *ctx) = 0;
  virtual void exitLabeledStatement(ZigCCParser::LabeledStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(ZigCCParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterCompoundStatement(ZigCCParser::CompoundStatementContext *ctx) = 0;
  virtual void exitCompoundStatement(ZigCCParser::CompoundStatementContext *ctx) = 0;

  virtual void enterStatementSeq(ZigCCParser::StatementSeqContext *ctx) = 0;
  virtual void exitStatementSeq(ZigCCParser::StatementSeqContext *ctx) = 0;

  virtual void enterSelectionStatement(ZigCCParser::SelectionStatementContext *ctx) = 0;
  virtual void exitSelectionStatement(ZigCCParser::SelectionStatementContext *ctx) = 0;

  virtual void enterCondition(ZigCCParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(ZigCCParser::ConditionContext *ctx) = 0;

  virtual void enterIterationStatement(ZigCCParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(ZigCCParser::IterationStatementContext *ctx) = 0;

  virtual void enterForInitStatement(ZigCCParser::ForInitStatementContext *ctx) = 0;
  virtual void exitForInitStatement(ZigCCParser::ForInitStatementContext *ctx) = 0;

  virtual void enterForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx) = 0;
  virtual void exitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext *ctx) = 0;

  virtual void enterForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx) = 0;
  virtual void exitForRangeInitializer(ZigCCParser::ForRangeInitializerContext *ctx) = 0;

  virtual void enterJumpStatement(ZigCCParser::JumpStatementContext *ctx) = 0;
  virtual void exitJumpStatement(ZigCCParser::JumpStatementContext *ctx) = 0;

  virtual void enterDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx) = 0;
  virtual void exitDeclarationStatement(ZigCCParser::DeclarationStatementContext *ctx) = 0;

  virtual void enterDeclarationseq(ZigCCParser::DeclarationseqContext *ctx) = 0;
  virtual void exitDeclarationseq(ZigCCParser::DeclarationseqContext *ctx) = 0;

  virtual void enterDeclaration(ZigCCParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(ZigCCParser::DeclarationContext *ctx) = 0;

  virtual void enterBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx) = 0;
  virtual void exitBlockDeclaration(ZigCCParser::BlockDeclarationContext *ctx) = 0;

  virtual void enterAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx) = 0;
  virtual void exitAliasDeclaration(ZigCCParser::AliasDeclarationContext *ctx) = 0;

  virtual void enterSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx) = 0;
  virtual void exitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext *ctx) = 0;

  virtual void enterStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx) = 0;
  virtual void exitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext *ctx) = 0;

  virtual void enterEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx) = 0;
  virtual void exitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext *ctx) = 0;

  virtual void enterAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx) = 0;
  virtual void exitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext *ctx) = 0;

  virtual void enterDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx) = 0;
  virtual void exitDeclSpecifier(ZigCCParser::DeclSpecifierContext *ctx) = 0;

  virtual void enterDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx) = 0;
  virtual void exitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext *ctx) = 0;

  virtual void enterStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx) = 0;
  virtual void exitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext *ctx) = 0;

  virtual void enterFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx) = 0;
  virtual void exitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext *ctx) = 0;

  virtual void enterTypedefName(ZigCCParser::TypedefNameContext *ctx) = 0;
  virtual void exitTypedefName(ZigCCParser::TypedefNameContext *ctx) = 0;

  virtual void enterTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx) = 0;
  virtual void exitTypeSpecifier(ZigCCParser::TypeSpecifierContext *ctx) = 0;

  virtual void enterTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx) = 0;
  virtual void exitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext *ctx) = 0;

  virtual void enterTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx) = 0;
  virtual void exitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext *ctx) = 0;

  virtual void enterTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx) = 0;
  virtual void exitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext *ctx) = 0;

  virtual void enterSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx) = 0;
  virtual void exitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext *ctx) = 0;

  virtual void enterSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx) = 0;
  virtual void exitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext *ctx) = 0;

  virtual void enterSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx) = 0;
  virtual void exitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext *ctx) = 0;

  virtual void enterTheTypeName(ZigCCParser::TheTypeNameContext *ctx) = 0;
  virtual void exitTheTypeName(ZigCCParser::TheTypeNameContext *ctx) = 0;

  virtual void enterDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx) = 0;
  virtual void exitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext *ctx) = 0;

  virtual void enterElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx) = 0;
  virtual void exitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext *ctx) = 0;

  virtual void enterEnumName(ZigCCParser::EnumNameContext *ctx) = 0;
  virtual void exitEnumName(ZigCCParser::EnumNameContext *ctx) = 0;

  virtual void enterEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx) = 0;
  virtual void exitEnumSpecifier(ZigCCParser::EnumSpecifierContext *ctx) = 0;

  virtual void enterEnumHead(ZigCCParser::EnumHeadContext *ctx) = 0;
  virtual void exitEnumHead(ZigCCParser::EnumHeadContext *ctx) = 0;

  virtual void enterOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx) = 0;
  virtual void exitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext *ctx) = 0;

  virtual void enterEnumkey(ZigCCParser::EnumkeyContext *ctx) = 0;
  virtual void exitEnumkey(ZigCCParser::EnumkeyContext *ctx) = 0;

  virtual void enterEnumbase(ZigCCParser::EnumbaseContext *ctx) = 0;
  virtual void exitEnumbase(ZigCCParser::EnumbaseContext *ctx) = 0;

  virtual void enterEnumeratorList(ZigCCParser::EnumeratorListContext *ctx) = 0;
  virtual void exitEnumeratorList(ZigCCParser::EnumeratorListContext *ctx) = 0;

  virtual void enterEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx) = 0;
  virtual void exitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext *ctx) = 0;

  virtual void enterEnumerator(ZigCCParser::EnumeratorContext *ctx) = 0;
  virtual void exitEnumerator(ZigCCParser::EnumeratorContext *ctx) = 0;

  virtual void enterNamespaceName(ZigCCParser::NamespaceNameContext *ctx) = 0;
  virtual void exitNamespaceName(ZigCCParser::NamespaceNameContext *ctx) = 0;

  virtual void enterOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx) = 0;
  virtual void exitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext *ctx) = 0;

  virtual void enterNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx) = 0;
  virtual void exitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext *ctx) = 0;

  virtual void enterNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx) = 0;
  virtual void exitNamespaceAlias(ZigCCParser::NamespaceAliasContext *ctx) = 0;

  virtual void enterNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx) = 0;
  virtual void exitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext *ctx) = 0;

  virtual void enterQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx) = 0;
  virtual void exitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext *ctx) = 0;

  virtual void enterUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx) = 0;
  virtual void exitUsingDeclaration(ZigCCParser::UsingDeclarationContext *ctx) = 0;

  virtual void enterUsingDirective(ZigCCParser::UsingDirectiveContext *ctx) = 0;
  virtual void exitUsingDirective(ZigCCParser::UsingDirectiveContext *ctx) = 0;

  virtual void enterAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx) = 0;
  virtual void exitAsmDefinition(ZigCCParser::AsmDefinitionContext *ctx) = 0;

  virtual void enterLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx) = 0;
  virtual void exitLinkageSpecification(ZigCCParser::LinkageSpecificationContext *ctx) = 0;

  virtual void enterAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx) = 0;
  virtual void exitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext *ctx) = 0;

  virtual void enterAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx) = 0;
  virtual void exitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext *ctx) = 0;

  virtual void enterAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx) = 0;
  virtual void exitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext *ctx) = 0;

  virtual void enterAttributeList(ZigCCParser::AttributeListContext *ctx) = 0;
  virtual void exitAttributeList(ZigCCParser::AttributeListContext *ctx) = 0;

  virtual void enterAttribute(ZigCCParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(ZigCCParser::AttributeContext *ctx) = 0;

  virtual void enterAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx) = 0;
  virtual void exitAttributeNamespace(ZigCCParser::AttributeNamespaceContext *ctx) = 0;

  virtual void enterAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx) = 0;
  virtual void exitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext *ctx) = 0;

  virtual void enterBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx) = 0;
  virtual void exitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext *ctx) = 0;

  virtual void enterBalancedtoken(ZigCCParser::BalancedtokenContext *ctx) = 0;
  virtual void exitBalancedtoken(ZigCCParser::BalancedtokenContext *ctx) = 0;

  virtual void enterInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx) = 0;
  virtual void exitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext *ctx) = 0;

  virtual void enterInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx) = 0;
  virtual void exitInitDeclarator(ZigCCParser::InitDeclaratorContext *ctx) = 0;

  virtual void enterDeclarator(ZigCCParser::DeclaratorContext *ctx) = 0;
  virtual void exitDeclarator(ZigCCParser::DeclaratorContext *ctx) = 0;

  virtual void enterPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx) = 0;
  virtual void exitPointerDeclarator(ZigCCParser::PointerDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext *ctx) = 0;

  virtual void enterParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx) = 0;
  virtual void exitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext *ctx) = 0;

  virtual void enterTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx) = 0;
  virtual void exitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext *ctx) = 0;

  virtual void enterPointerOperator(ZigCCParser::PointerOperatorContext *ctx) = 0;
  virtual void exitPointerOperator(ZigCCParser::PointerOperatorContext *ctx) = 0;

  virtual void enterCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx) = 0;
  virtual void exitCvqualifierseq(ZigCCParser::CvqualifierseqContext *ctx) = 0;

  virtual void enterCvQualifier(ZigCCParser::CvQualifierContext *ctx) = 0;
  virtual void exitCvQualifier(ZigCCParser::CvQualifierContext *ctx) = 0;

  virtual void enterRefqualifier(ZigCCParser::RefqualifierContext *ctx) = 0;
  virtual void exitRefqualifier(ZigCCParser::RefqualifierContext *ctx) = 0;

  virtual void enterDeclaratorid(ZigCCParser::DeclaratoridContext *ctx) = 0;
  virtual void exitDeclaratorid(ZigCCParser::DeclaratoridContext *ctx) = 0;

  virtual void enterTheTypeId(ZigCCParser::TheTypeIdContext *ctx) = 0;
  virtual void exitTheTypeId(ZigCCParser::TheTypeIdContext *ctx) = 0;

  virtual void enterAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx) = 0;
  virtual void exitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext *ctx) = 0;

  virtual void enterPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx) = 0;
  virtual void exitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext *ctx) = 0;

  virtual void enterAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx) = 0;
  virtual void exitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext *ctx) = 0;

  virtual void enterNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx) = 0;
  virtual void exitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext *ctx) = 0;

  virtual void enterParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx) = 0;
  virtual void exitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext *ctx) = 0;

  virtual void enterParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx) = 0;
  virtual void exitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext *ctx) = 0;

  virtual void enterParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx) = 0;
  virtual void exitParameterDeclaration(ZigCCParser::ParameterDeclarationContext *ctx) = 0;

  virtual void enterFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(ZigCCParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterFunctionBody(ZigCCParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(ZigCCParser::FunctionBodyContext *ctx) = 0;

  virtual void enterInitializer(ZigCCParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(ZigCCParser::InitializerContext *ctx) = 0;

  virtual void enterBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx) = 0;
  virtual void exitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext *ctx) = 0;

  virtual void enterInitializerClause(ZigCCParser::InitializerClauseContext *ctx) = 0;
  virtual void exitInitializerClause(ZigCCParser::InitializerClauseContext *ctx) = 0;

  virtual void enterInitializerList(ZigCCParser::InitializerListContext *ctx) = 0;
  virtual void exitInitializerList(ZigCCParser::InitializerListContext *ctx) = 0;

  virtual void enterBracedInitList(ZigCCParser::BracedInitListContext *ctx) = 0;
  virtual void exitBracedInitList(ZigCCParser::BracedInitListContext *ctx) = 0;

  virtual void enterClassName(ZigCCParser::ClassNameContext *ctx) = 0;
  virtual void exitClassName(ZigCCParser::ClassNameContext *ctx) = 0;

  virtual void enterClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx) = 0;
  virtual void exitClassSpecifier(ZigCCParser::ClassSpecifierContext *ctx) = 0;

  virtual void enterClassHead(ZigCCParser::ClassHeadContext *ctx) = 0;
  virtual void exitClassHead(ZigCCParser::ClassHeadContext *ctx) = 0;

  virtual void enterClassHeadName(ZigCCParser::ClassHeadNameContext *ctx) = 0;
  virtual void exitClassHeadName(ZigCCParser::ClassHeadNameContext *ctx) = 0;

  virtual void enterClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx) = 0;
  virtual void exitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext *ctx) = 0;

  virtual void enterClassKey(ZigCCParser::ClassKeyContext *ctx) = 0;
  virtual void exitClassKey(ZigCCParser::ClassKeyContext *ctx) = 0;

  virtual void enterMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx) = 0;
  virtual void exitMemberSpecification(ZigCCParser::MemberSpecificationContext *ctx) = 0;

  virtual void enterMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx) = 0;
  virtual void exitMemberdeclaration(ZigCCParser::MemberdeclarationContext *ctx) = 0;

  virtual void enterMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx) = 0;
  virtual void exitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext *ctx) = 0;

  virtual void enterMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx) = 0;
  virtual void exitMemberDeclarator(ZigCCParser::MemberDeclaratorContext *ctx) = 0;

  virtual void enterVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx) = 0;
  virtual void exitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext *ctx) = 0;

  virtual void enterVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx) = 0;
  virtual void exitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext *ctx) = 0;

  virtual void enterPureSpecifier(ZigCCParser::PureSpecifierContext *ctx) = 0;
  virtual void exitPureSpecifier(ZigCCParser::PureSpecifierContext *ctx) = 0;

  virtual void enterBaseClause(ZigCCParser::BaseClauseContext *ctx) = 0;
  virtual void exitBaseClause(ZigCCParser::BaseClauseContext *ctx) = 0;

  virtual void enterBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx) = 0;
  virtual void exitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext *ctx) = 0;

  virtual void enterBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx) = 0;
  virtual void exitBaseSpecifier(ZigCCParser::BaseSpecifierContext *ctx) = 0;

  virtual void enterClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx) = 0;
  virtual void exitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext *ctx) = 0;

  virtual void enterBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx) = 0;
  virtual void exitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext *ctx) = 0;

  virtual void enterAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx) = 0;
  virtual void exitAccessSpecifier(ZigCCParser::AccessSpecifierContext *ctx) = 0;

  virtual void enterConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx) = 0;
  virtual void exitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext *ctx) = 0;

  virtual void enterConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx) = 0;
  virtual void exitConversionTypeId(ZigCCParser::ConversionTypeIdContext *ctx) = 0;

  virtual void enterConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx) = 0;
  virtual void exitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext *ctx) = 0;

  virtual void enterConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx) = 0;
  virtual void exitConstructorInitializer(ZigCCParser::ConstructorInitializerContext *ctx) = 0;

  virtual void enterMemInitializerList(ZigCCParser::MemInitializerListContext *ctx) = 0;
  virtual void exitMemInitializerList(ZigCCParser::MemInitializerListContext *ctx) = 0;

  virtual void enterMemInitializer(ZigCCParser::MemInitializerContext *ctx) = 0;
  virtual void exitMemInitializer(ZigCCParser::MemInitializerContext *ctx) = 0;

  virtual void enterMeminitializerid(ZigCCParser::MeminitializeridContext *ctx) = 0;
  virtual void exitMeminitializerid(ZigCCParser::MeminitializeridContext *ctx) = 0;

  virtual void enterOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx) = 0;
  virtual void exitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext *ctx) = 0;

  virtual void enterLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx) = 0;
  virtual void exitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext *ctx) = 0;

  virtual void enterTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx) = 0;
  virtual void exitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext *ctx) = 0;

  virtual void enterTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx) = 0;
  virtual void exitTemplateparameterList(ZigCCParser::TemplateparameterListContext *ctx) = 0;

  virtual void enterTemplateParameter(ZigCCParser::TemplateParameterContext *ctx) = 0;
  virtual void exitTemplateParameter(ZigCCParser::TemplateParameterContext *ctx) = 0;

  virtual void enterTypeParameter(ZigCCParser::TypeParameterContext *ctx) = 0;
  virtual void exitTypeParameter(ZigCCParser::TypeParameterContext *ctx) = 0;

  virtual void enterSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx) = 0;
  virtual void exitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext *ctx) = 0;

  virtual void enterTemplateId(ZigCCParser::TemplateIdContext *ctx) = 0;
  virtual void exitTemplateId(ZigCCParser::TemplateIdContext *ctx) = 0;

  virtual void enterTemplateName(ZigCCParser::TemplateNameContext *ctx) = 0;
  virtual void exitTemplateName(ZigCCParser::TemplateNameContext *ctx) = 0;

  virtual void enterTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx) = 0;
  virtual void exitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext *ctx) = 0;

  virtual void enterTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx) = 0;
  virtual void exitTemplateArgument(ZigCCParser::TemplateArgumentContext *ctx) = 0;

  virtual void enterTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx) = 0;
  virtual void exitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext *ctx) = 0;

  virtual void enterExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx) = 0;
  virtual void exitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext *ctx) = 0;

  virtual void enterExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx) = 0;
  virtual void exitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext *ctx) = 0;

  virtual void enterTryBlock(ZigCCParser::TryBlockContext *ctx) = 0;
  virtual void exitTryBlock(ZigCCParser::TryBlockContext *ctx) = 0;

  virtual void enterFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx) = 0;
  virtual void exitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext *ctx) = 0;

  virtual void enterHandlerSeq(ZigCCParser::HandlerSeqContext *ctx) = 0;
  virtual void exitHandlerSeq(ZigCCParser::HandlerSeqContext *ctx) = 0;

  virtual void enterHandler(ZigCCParser::HandlerContext *ctx) = 0;
  virtual void exitHandler(ZigCCParser::HandlerContext *ctx) = 0;

  virtual void enterExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx) = 0;
  virtual void exitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext *ctx) = 0;

  virtual void enterThrowExpression(ZigCCParser::ThrowExpressionContext *ctx) = 0;
  virtual void exitThrowExpression(ZigCCParser::ThrowExpressionContext *ctx) = 0;

  virtual void enterExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx) = 0;
  virtual void exitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext *ctx) = 0;

  virtual void enterDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx) = 0;
  virtual void exitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext *ctx) = 0;

  virtual void enterTypeIdList(ZigCCParser::TypeIdListContext *ctx) = 0;
  virtual void exitTypeIdList(ZigCCParser::TypeIdListContext *ctx) = 0;

  virtual void enterNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx) = 0;
  virtual void exitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext *ctx) = 0;

  virtual void enterTheOperator(ZigCCParser::TheOperatorContext *ctx) = 0;
  virtual void exitTheOperator(ZigCCParser::TheOperatorContext *ctx) = 0;

  virtual void enterLiteral(ZigCCParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(ZigCCParser::LiteralContext *ctx) = 0;


};

}  // namespace antlrcpptest
