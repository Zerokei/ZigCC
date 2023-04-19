
// Generated from ZigCCParser.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "ZigCCParserListener.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of ZigCCParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ZigCCParserBaseListener : public ZigCCParserListener {
public:

  virtual void enterTranslationUnit(ZigCCParser::TranslationUnitContext * /*ctx*/) override { }
  virtual void exitTranslationUnit(ZigCCParser::TranslationUnitContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(ZigCCParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(ZigCCParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterIdExpression(ZigCCParser::IdExpressionContext * /*ctx*/) override { }
  virtual void exitIdExpression(ZigCCParser::IdExpressionContext * /*ctx*/) override { }

  virtual void enterUnqualifiedId(ZigCCParser::UnqualifiedIdContext * /*ctx*/) override { }
  virtual void exitUnqualifiedId(ZigCCParser::UnqualifiedIdContext * /*ctx*/) override { }

  virtual void enterQualifiedId(ZigCCParser::QualifiedIdContext * /*ctx*/) override { }
  virtual void exitQualifiedId(ZigCCParser::QualifiedIdContext * /*ctx*/) override { }

  virtual void enterNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext * /*ctx*/) override { }
  virtual void exitNestedNameSpecifier(ZigCCParser::NestedNameSpecifierContext * /*ctx*/) override { }

  virtual void enterLambdaExpression(ZigCCParser::LambdaExpressionContext * /*ctx*/) override { }
  virtual void exitLambdaExpression(ZigCCParser::LambdaExpressionContext * /*ctx*/) override { }

  virtual void enterLambdaIntroducer(ZigCCParser::LambdaIntroducerContext * /*ctx*/) override { }
  virtual void exitLambdaIntroducer(ZigCCParser::LambdaIntroducerContext * /*ctx*/) override { }

  virtual void enterLambdaCapture(ZigCCParser::LambdaCaptureContext * /*ctx*/) override { }
  virtual void exitLambdaCapture(ZigCCParser::LambdaCaptureContext * /*ctx*/) override { }

  virtual void enterCaptureDefault(ZigCCParser::CaptureDefaultContext * /*ctx*/) override { }
  virtual void exitCaptureDefault(ZigCCParser::CaptureDefaultContext * /*ctx*/) override { }

  virtual void enterCaptureList(ZigCCParser::CaptureListContext * /*ctx*/) override { }
  virtual void exitCaptureList(ZigCCParser::CaptureListContext * /*ctx*/) override { }

  virtual void enterCapture(ZigCCParser::CaptureContext * /*ctx*/) override { }
  virtual void exitCapture(ZigCCParser::CaptureContext * /*ctx*/) override { }

  virtual void enterSimpleCapture(ZigCCParser::SimpleCaptureContext * /*ctx*/) override { }
  virtual void exitSimpleCapture(ZigCCParser::SimpleCaptureContext * /*ctx*/) override { }

  virtual void enterInitcapture(ZigCCParser::InitcaptureContext * /*ctx*/) override { }
  virtual void exitInitcapture(ZigCCParser::InitcaptureContext * /*ctx*/) override { }

  virtual void enterLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext * /*ctx*/) override { }
  virtual void exitLambdaDeclarator(ZigCCParser::LambdaDeclaratorContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(ZigCCParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(ZigCCParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext * /*ctx*/) override { }
  virtual void exitTypeIdOfTheTypeId(ZigCCParser::TypeIdOfTheTypeIdContext * /*ctx*/) override { }

  virtual void enterExpressionList(ZigCCParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(ZigCCParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext * /*ctx*/) override { }
  virtual void exitPseudoDestructorName(ZigCCParser::PseudoDestructorNameContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(ZigCCParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(ZigCCParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(ZigCCParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(ZigCCParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterNewExpression(ZigCCParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(ZigCCParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterNewPlacement(ZigCCParser::NewPlacementContext * /*ctx*/) override { }
  virtual void exitNewPlacement(ZigCCParser::NewPlacementContext * /*ctx*/) override { }

  virtual void enterNewTypeId(ZigCCParser::NewTypeIdContext * /*ctx*/) override { }
  virtual void exitNewTypeId(ZigCCParser::NewTypeIdContext * /*ctx*/) override { }

  virtual void enterNewDeclarator(ZigCCParser::NewDeclaratorContext * /*ctx*/) override { }
  virtual void exitNewDeclarator(ZigCCParser::NewDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerNewDeclarator(ZigCCParser::NoPointerNewDeclaratorContext * /*ctx*/) override { }

  virtual void enterNewInitializer(ZigCCParser::NewInitializerContext * /*ctx*/) override { }
  virtual void exitNewInitializer(ZigCCParser::NewInitializerContext * /*ctx*/) override { }

  virtual void enterDeleteExpression(ZigCCParser::DeleteExpressionContext * /*ctx*/) override { }
  virtual void exitDeleteExpression(ZigCCParser::DeleteExpressionContext * /*ctx*/) override { }

  virtual void enterNoExceptExpression(ZigCCParser::NoExceptExpressionContext * /*ctx*/) override { }
  virtual void exitNoExceptExpression(ZigCCParser::NoExceptExpressionContext * /*ctx*/) override { }

  virtual void enterCastExpression(ZigCCParser::CastExpressionContext * /*ctx*/) override { }
  virtual void exitCastExpression(ZigCCParser::CastExpressionContext * /*ctx*/) override { }

  virtual void enterPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext * /*ctx*/) override { }
  virtual void exitPointerMemberExpression(ZigCCParser::PointerMemberExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(ZigCCParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(ZigCCParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(ZigCCParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(ZigCCParser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(ZigCCParser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterShiftOperator(ZigCCParser::ShiftOperatorContext * /*ctx*/) override { }
  virtual void exitShiftOperator(ZigCCParser::ShiftOperatorContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(ZigCCParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(ZigCCParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(ZigCCParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(ZigCCParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(ZigCCParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(ZigCCParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitExclusiveOrExpression(ZigCCParser::ExclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitInclusiveOrExpression(ZigCCParser::InclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(ZigCCParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(ZigCCParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(ZigCCParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(ZigCCParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(ZigCCParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(ZigCCParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(ZigCCParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(ZigCCParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterExpression(ZigCCParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(ZigCCParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterConstantExpression(ZigCCParser::ConstantExpressionContext * /*ctx*/) override { }
  virtual void exitConstantExpression(ZigCCParser::ConstantExpressionContext * /*ctx*/) override { }

  virtual void enterStatement(ZigCCParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(ZigCCParser::StatementContext * /*ctx*/) override { }

  virtual void enterLabeledStatement(ZigCCParser::LabeledStatementContext * /*ctx*/) override { }
  virtual void exitLabeledStatement(ZigCCParser::LabeledStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(ZigCCParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(ZigCCParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterCompoundStatement(ZigCCParser::CompoundStatementContext * /*ctx*/) override { }
  virtual void exitCompoundStatement(ZigCCParser::CompoundStatementContext * /*ctx*/) override { }

  virtual void enterStatementSeq(ZigCCParser::StatementSeqContext * /*ctx*/) override { }
  virtual void exitStatementSeq(ZigCCParser::StatementSeqContext * /*ctx*/) override { }

  virtual void enterSelectionStatement(ZigCCParser::SelectionStatementContext * /*ctx*/) override { }
  virtual void exitSelectionStatement(ZigCCParser::SelectionStatementContext * /*ctx*/) override { }

  virtual void enterCondition(ZigCCParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(ZigCCParser::ConditionContext * /*ctx*/) override { }

  virtual void enterIterationStatement(ZigCCParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(ZigCCParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterForInitStatement(ZigCCParser::ForInitStatementContext * /*ctx*/) override { }
  virtual void exitForInitStatement(ZigCCParser::ForInitStatementContext * /*ctx*/) override { }

  virtual void enterForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext * /*ctx*/) override { }
  virtual void exitForRangeDeclaration(ZigCCParser::ForRangeDeclarationContext * /*ctx*/) override { }

  virtual void enterForRangeInitializer(ZigCCParser::ForRangeInitializerContext * /*ctx*/) override { }
  virtual void exitForRangeInitializer(ZigCCParser::ForRangeInitializerContext * /*ctx*/) override { }

  virtual void enterJumpStatement(ZigCCParser::JumpStatementContext * /*ctx*/) override { }
  virtual void exitJumpStatement(ZigCCParser::JumpStatementContext * /*ctx*/) override { }

  virtual void enterDeclarationStatement(ZigCCParser::DeclarationStatementContext * /*ctx*/) override { }
  virtual void exitDeclarationStatement(ZigCCParser::DeclarationStatementContext * /*ctx*/) override { }

  virtual void enterDeclarationseq(ZigCCParser::DeclarationseqContext * /*ctx*/) override { }
  virtual void exitDeclarationseq(ZigCCParser::DeclarationseqContext * /*ctx*/) override { }

  virtual void enterDeclaration(ZigCCParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(ZigCCParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterBlockDeclaration(ZigCCParser::BlockDeclarationContext * /*ctx*/) override { }
  virtual void exitBlockDeclaration(ZigCCParser::BlockDeclarationContext * /*ctx*/) override { }

  virtual void enterAliasDeclaration(ZigCCParser::AliasDeclarationContext * /*ctx*/) override { }
  virtual void exitAliasDeclaration(ZigCCParser::AliasDeclarationContext * /*ctx*/) override { }

  virtual void enterSimpleDeclaration(ZigCCParser::SimpleDeclarationContext * /*ctx*/) override { }
  virtual void exitSimpleDeclaration(ZigCCParser::SimpleDeclarationContext * /*ctx*/) override { }

  virtual void enterStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext * /*ctx*/) override { }
  virtual void exitStaticAssertDeclaration(ZigCCParser::StaticAssertDeclarationContext * /*ctx*/) override { }

  virtual void enterEmptyDeclaration(ZigCCParser::EmptyDeclarationContext * /*ctx*/) override { }
  virtual void exitEmptyDeclaration(ZigCCParser::EmptyDeclarationContext * /*ctx*/) override { }

  virtual void enterAttributeDeclaration(ZigCCParser::AttributeDeclarationContext * /*ctx*/) override { }
  virtual void exitAttributeDeclaration(ZigCCParser::AttributeDeclarationContext * /*ctx*/) override { }

  virtual void enterDeclSpecifier(ZigCCParser::DeclSpecifierContext * /*ctx*/) override { }
  virtual void exitDeclSpecifier(ZigCCParser::DeclSpecifierContext * /*ctx*/) override { }

  virtual void enterDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitDeclSpecifierSeq(ZigCCParser::DeclSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext * /*ctx*/) override { }
  virtual void exitStorageClassSpecifier(ZigCCParser::StorageClassSpecifierContext * /*ctx*/) override { }

  virtual void enterFunctionSpecifier(ZigCCParser::FunctionSpecifierContext * /*ctx*/) override { }
  virtual void exitFunctionSpecifier(ZigCCParser::FunctionSpecifierContext * /*ctx*/) override { }

  virtual void enterTypedefName(ZigCCParser::TypedefNameContext * /*ctx*/) override { }
  virtual void exitTypedefName(ZigCCParser::TypedefNameContext * /*ctx*/) override { }

  virtual void enterTypeSpecifier(ZigCCParser::TypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeSpecifier(ZigCCParser::TypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTrailingTypeSpecifier(ZigCCParser::TrailingTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitTypeSpecifierSeq(ZigCCParser::TypeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitTrailingTypeSpecifierSeq(ZigCCParser::TrailingTypeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeLengthModifier(ZigCCParser::SimpleTypeLengthModifierContext * /*ctx*/) override { }

  virtual void enterSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeSignednessModifier(ZigCCParser::SimpleTypeSignednessModifierContext * /*ctx*/) override { }

  virtual void enterSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitSimpleTypeSpecifier(ZigCCParser::SimpleTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterTheTypeName(ZigCCParser::TheTypeNameContext * /*ctx*/) override { }
  virtual void exitTheTypeName(ZigCCParser::TheTypeNameContext * /*ctx*/) override { }

  virtual void enterDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext * /*ctx*/) override { }
  virtual void exitDecltypeSpecifier(ZigCCParser::DecltypeSpecifierContext * /*ctx*/) override { }

  virtual void enterElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitElaboratedTypeSpecifier(ZigCCParser::ElaboratedTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterEnumName(ZigCCParser::EnumNameContext * /*ctx*/) override { }
  virtual void exitEnumName(ZigCCParser::EnumNameContext * /*ctx*/) override { }

  virtual void enterEnumSpecifier(ZigCCParser::EnumSpecifierContext * /*ctx*/) override { }
  virtual void exitEnumSpecifier(ZigCCParser::EnumSpecifierContext * /*ctx*/) override { }

  virtual void enterEnumHead(ZigCCParser::EnumHeadContext * /*ctx*/) override { }
  virtual void exitEnumHead(ZigCCParser::EnumHeadContext * /*ctx*/) override { }

  virtual void enterOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext * /*ctx*/) override { }
  virtual void exitOpaqueEnumDeclaration(ZigCCParser::OpaqueEnumDeclarationContext * /*ctx*/) override { }

  virtual void enterEnumkey(ZigCCParser::EnumkeyContext * /*ctx*/) override { }
  virtual void exitEnumkey(ZigCCParser::EnumkeyContext * /*ctx*/) override { }

  virtual void enterEnumbase(ZigCCParser::EnumbaseContext * /*ctx*/) override { }
  virtual void exitEnumbase(ZigCCParser::EnumbaseContext * /*ctx*/) override { }

  virtual void enterEnumeratorList(ZigCCParser::EnumeratorListContext * /*ctx*/) override { }
  virtual void exitEnumeratorList(ZigCCParser::EnumeratorListContext * /*ctx*/) override { }

  virtual void enterEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext * /*ctx*/) override { }
  virtual void exitEnumeratorDefinition(ZigCCParser::EnumeratorDefinitionContext * /*ctx*/) override { }

  virtual void enterEnumerator(ZigCCParser::EnumeratorContext * /*ctx*/) override { }
  virtual void exitEnumerator(ZigCCParser::EnumeratorContext * /*ctx*/) override { }

  virtual void enterNamespaceName(ZigCCParser::NamespaceNameContext * /*ctx*/) override { }
  virtual void exitNamespaceName(ZigCCParser::NamespaceNameContext * /*ctx*/) override { }

  virtual void enterOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext * /*ctx*/) override { }
  virtual void exitOriginalNamespaceName(ZigCCParser::OriginalNamespaceNameContext * /*ctx*/) override { }

  virtual void enterNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext * /*ctx*/) override { }
  virtual void exitNamespaceDefinition(ZigCCParser::NamespaceDefinitionContext * /*ctx*/) override { }

  virtual void enterNamespaceAlias(ZigCCParser::NamespaceAliasContext * /*ctx*/) override { }
  virtual void exitNamespaceAlias(ZigCCParser::NamespaceAliasContext * /*ctx*/) override { }

  virtual void enterNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext * /*ctx*/) override { }
  virtual void exitNamespaceAliasDefinition(ZigCCParser::NamespaceAliasDefinitionContext * /*ctx*/) override { }

  virtual void enterQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext * /*ctx*/) override { }
  virtual void exitQualifiednamespacespecifier(ZigCCParser::QualifiednamespacespecifierContext * /*ctx*/) override { }

  virtual void enterUsingDeclaration(ZigCCParser::UsingDeclarationContext * /*ctx*/) override { }
  virtual void exitUsingDeclaration(ZigCCParser::UsingDeclarationContext * /*ctx*/) override { }

  virtual void enterUsingDirective(ZigCCParser::UsingDirectiveContext * /*ctx*/) override { }
  virtual void exitUsingDirective(ZigCCParser::UsingDirectiveContext * /*ctx*/) override { }

  virtual void enterAsmDefinition(ZigCCParser::AsmDefinitionContext * /*ctx*/) override { }
  virtual void exitAsmDefinition(ZigCCParser::AsmDefinitionContext * /*ctx*/) override { }

  virtual void enterLinkageSpecification(ZigCCParser::LinkageSpecificationContext * /*ctx*/) override { }
  virtual void exitLinkageSpecification(ZigCCParser::LinkageSpecificationContext * /*ctx*/) override { }

  virtual void enterAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitAttributeSpecifierSeq(ZigCCParser::AttributeSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterAttributeSpecifier(ZigCCParser::AttributeSpecifierContext * /*ctx*/) override { }
  virtual void exitAttributeSpecifier(ZigCCParser::AttributeSpecifierContext * /*ctx*/) override { }

  virtual void enterAlignmentspecifier(ZigCCParser::AlignmentspecifierContext * /*ctx*/) override { }
  virtual void exitAlignmentspecifier(ZigCCParser::AlignmentspecifierContext * /*ctx*/) override { }

  virtual void enterAttributeList(ZigCCParser::AttributeListContext * /*ctx*/) override { }
  virtual void exitAttributeList(ZigCCParser::AttributeListContext * /*ctx*/) override { }

  virtual void enterAttribute(ZigCCParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(ZigCCParser::AttributeContext * /*ctx*/) override { }

  virtual void enterAttributeNamespace(ZigCCParser::AttributeNamespaceContext * /*ctx*/) override { }
  virtual void exitAttributeNamespace(ZigCCParser::AttributeNamespaceContext * /*ctx*/) override { }

  virtual void enterAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext * /*ctx*/) override { }
  virtual void exitAttributeArgumentClause(ZigCCParser::AttributeArgumentClauseContext * /*ctx*/) override { }

  virtual void enterBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext * /*ctx*/) override { }
  virtual void exitBalancedTokenSeq(ZigCCParser::BalancedTokenSeqContext * /*ctx*/) override { }

  virtual void enterBalancedtoken(ZigCCParser::BalancedtokenContext * /*ctx*/) override { }
  virtual void exitBalancedtoken(ZigCCParser::BalancedtokenContext * /*ctx*/) override { }

  virtual void enterInitDeclaratorList(ZigCCParser::InitDeclaratorListContext * /*ctx*/) override { }
  virtual void exitInitDeclaratorList(ZigCCParser::InitDeclaratorListContext * /*ctx*/) override { }

  virtual void enterInitDeclarator(ZigCCParser::InitDeclaratorContext * /*ctx*/) override { }
  virtual void exitInitDeclarator(ZigCCParser::InitDeclaratorContext * /*ctx*/) override { }

  virtual void enterDeclarator(ZigCCParser::DeclaratorContext * /*ctx*/) override { }
  virtual void exitDeclarator(ZigCCParser::DeclaratorContext * /*ctx*/) override { }

  virtual void enterPointerDeclarator(ZigCCParser::PointerDeclaratorContext * /*ctx*/) override { }
  virtual void exitPointerDeclarator(ZigCCParser::PointerDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerDeclarator(ZigCCParser::NoPointerDeclaratorContext * /*ctx*/) override { }

  virtual void enterParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext * /*ctx*/) override { }
  virtual void exitParametersAndQualifiers(ZigCCParser::ParametersAndQualifiersContext * /*ctx*/) override { }

  virtual void enterTrailingReturnType(ZigCCParser::TrailingReturnTypeContext * /*ctx*/) override { }
  virtual void exitTrailingReturnType(ZigCCParser::TrailingReturnTypeContext * /*ctx*/) override { }

  virtual void enterPointerOperator(ZigCCParser::PointerOperatorContext * /*ctx*/) override { }
  virtual void exitPointerOperator(ZigCCParser::PointerOperatorContext * /*ctx*/) override { }

  virtual void enterCvqualifierseq(ZigCCParser::CvqualifierseqContext * /*ctx*/) override { }
  virtual void exitCvqualifierseq(ZigCCParser::CvqualifierseqContext * /*ctx*/) override { }

  virtual void enterCvQualifier(ZigCCParser::CvQualifierContext * /*ctx*/) override { }
  virtual void exitCvQualifier(ZigCCParser::CvQualifierContext * /*ctx*/) override { }

  virtual void enterRefqualifier(ZigCCParser::RefqualifierContext * /*ctx*/) override { }
  virtual void exitRefqualifier(ZigCCParser::RefqualifierContext * /*ctx*/) override { }

  virtual void enterDeclaratorid(ZigCCParser::DeclaratoridContext * /*ctx*/) override { }
  virtual void exitDeclaratorid(ZigCCParser::DeclaratoridContext * /*ctx*/) override { }

  virtual void enterTheTypeId(ZigCCParser::TheTypeIdContext * /*ctx*/) override { }
  virtual void exitTheTypeId(ZigCCParser::TheTypeIdContext * /*ctx*/) override { }

  virtual void enterAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitAbstractDeclarator(ZigCCParser::AbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitPointerAbstractDeclarator(ZigCCParser::PointerAbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerAbstractDeclarator(ZigCCParser::NoPointerAbstractDeclaratorContext * /*ctx*/) override { }

  virtual void enterAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext * /*ctx*/) override { }
  virtual void exitAbstractPackDeclarator(ZigCCParser::AbstractPackDeclaratorContext * /*ctx*/) override { }

  virtual void enterNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext * /*ctx*/) override { }
  virtual void exitNoPointerAbstractPackDeclarator(ZigCCParser::NoPointerAbstractPackDeclaratorContext * /*ctx*/) override { }

  virtual void enterParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext * /*ctx*/) override { }
  virtual void exitParameterDeclarationClause(ZigCCParser::ParameterDeclarationClauseContext * /*ctx*/) override { }

  virtual void enterParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext * /*ctx*/) override { }
  virtual void exitParameterDeclarationList(ZigCCParser::ParameterDeclarationListContext * /*ctx*/) override { }

  virtual void enterParameterDeclaration(ZigCCParser::ParameterDeclarationContext * /*ctx*/) override { }
  virtual void exitParameterDeclaration(ZigCCParser::ParameterDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(ZigCCParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(ZigCCParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterFunctionBody(ZigCCParser::FunctionBodyContext * /*ctx*/) override { }
  virtual void exitFunctionBody(ZigCCParser::FunctionBodyContext * /*ctx*/) override { }

  virtual void enterInitializer(ZigCCParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(ZigCCParser::InitializerContext * /*ctx*/) override { }

  virtual void enterBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext * /*ctx*/) override { }
  virtual void exitBraceOrEqualInitializer(ZigCCParser::BraceOrEqualInitializerContext * /*ctx*/) override { }

  virtual void enterInitializerClause(ZigCCParser::InitializerClauseContext * /*ctx*/) override { }
  virtual void exitInitializerClause(ZigCCParser::InitializerClauseContext * /*ctx*/) override { }

  virtual void enterInitializerList(ZigCCParser::InitializerListContext * /*ctx*/) override { }
  virtual void exitInitializerList(ZigCCParser::InitializerListContext * /*ctx*/) override { }

  virtual void enterBracedInitList(ZigCCParser::BracedInitListContext * /*ctx*/) override { }
  virtual void exitBracedInitList(ZigCCParser::BracedInitListContext * /*ctx*/) override { }

  virtual void enterClassName(ZigCCParser::ClassNameContext * /*ctx*/) override { }
  virtual void exitClassName(ZigCCParser::ClassNameContext * /*ctx*/) override { }

  virtual void enterClassSpecifier(ZigCCParser::ClassSpecifierContext * /*ctx*/) override { }
  virtual void exitClassSpecifier(ZigCCParser::ClassSpecifierContext * /*ctx*/) override { }

  virtual void enterClassHead(ZigCCParser::ClassHeadContext * /*ctx*/) override { }
  virtual void exitClassHead(ZigCCParser::ClassHeadContext * /*ctx*/) override { }

  virtual void enterClassHeadName(ZigCCParser::ClassHeadNameContext * /*ctx*/) override { }
  virtual void exitClassHeadName(ZigCCParser::ClassHeadNameContext * /*ctx*/) override { }

  virtual void enterClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext * /*ctx*/) override { }
  virtual void exitClassVirtSpecifier(ZigCCParser::ClassVirtSpecifierContext * /*ctx*/) override { }

  virtual void enterClassKey(ZigCCParser::ClassKeyContext * /*ctx*/) override { }
  virtual void exitClassKey(ZigCCParser::ClassKeyContext * /*ctx*/) override { }

  virtual void enterMemberSpecification(ZigCCParser::MemberSpecificationContext * /*ctx*/) override { }
  virtual void exitMemberSpecification(ZigCCParser::MemberSpecificationContext * /*ctx*/) override { }

  virtual void enterMemberdeclaration(ZigCCParser::MemberdeclarationContext * /*ctx*/) override { }
  virtual void exitMemberdeclaration(ZigCCParser::MemberdeclarationContext * /*ctx*/) override { }

  virtual void enterMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext * /*ctx*/) override { }
  virtual void exitMemberDeclaratorList(ZigCCParser::MemberDeclaratorListContext * /*ctx*/) override { }

  virtual void enterMemberDeclarator(ZigCCParser::MemberDeclaratorContext * /*ctx*/) override { }
  virtual void exitMemberDeclarator(ZigCCParser::MemberDeclaratorContext * /*ctx*/) override { }

  virtual void enterVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext * /*ctx*/) override { }
  virtual void exitVirtualSpecifierSeq(ZigCCParser::VirtualSpecifierSeqContext * /*ctx*/) override { }

  virtual void enterVirtualSpecifier(ZigCCParser::VirtualSpecifierContext * /*ctx*/) override { }
  virtual void exitVirtualSpecifier(ZigCCParser::VirtualSpecifierContext * /*ctx*/) override { }

  virtual void enterPureSpecifier(ZigCCParser::PureSpecifierContext * /*ctx*/) override { }
  virtual void exitPureSpecifier(ZigCCParser::PureSpecifierContext * /*ctx*/) override { }

  virtual void enterBaseClause(ZigCCParser::BaseClauseContext * /*ctx*/) override { }
  virtual void exitBaseClause(ZigCCParser::BaseClauseContext * /*ctx*/) override { }

  virtual void enterBaseSpecifierList(ZigCCParser::BaseSpecifierListContext * /*ctx*/) override { }
  virtual void exitBaseSpecifierList(ZigCCParser::BaseSpecifierListContext * /*ctx*/) override { }

  virtual void enterBaseSpecifier(ZigCCParser::BaseSpecifierContext * /*ctx*/) override { }
  virtual void exitBaseSpecifier(ZigCCParser::BaseSpecifierContext * /*ctx*/) override { }

  virtual void enterClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext * /*ctx*/) override { }
  virtual void exitClassOrDeclType(ZigCCParser::ClassOrDeclTypeContext * /*ctx*/) override { }

  virtual void enterBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext * /*ctx*/) override { }
  virtual void exitBaseTypeSpecifier(ZigCCParser::BaseTypeSpecifierContext * /*ctx*/) override { }

  virtual void enterAccessSpecifier(ZigCCParser::AccessSpecifierContext * /*ctx*/) override { }
  virtual void exitAccessSpecifier(ZigCCParser::AccessSpecifierContext * /*ctx*/) override { }

  virtual void enterConversionFunctionId(ZigCCParser::ConversionFunctionIdContext * /*ctx*/) override { }
  virtual void exitConversionFunctionId(ZigCCParser::ConversionFunctionIdContext * /*ctx*/) override { }

  virtual void enterConversionTypeId(ZigCCParser::ConversionTypeIdContext * /*ctx*/) override { }
  virtual void exitConversionTypeId(ZigCCParser::ConversionTypeIdContext * /*ctx*/) override { }

  virtual void enterConversionDeclarator(ZigCCParser::ConversionDeclaratorContext * /*ctx*/) override { }
  virtual void exitConversionDeclarator(ZigCCParser::ConversionDeclaratorContext * /*ctx*/) override { }

  virtual void enterConstructorInitializer(ZigCCParser::ConstructorInitializerContext * /*ctx*/) override { }
  virtual void exitConstructorInitializer(ZigCCParser::ConstructorInitializerContext * /*ctx*/) override { }

  virtual void enterMemInitializerList(ZigCCParser::MemInitializerListContext * /*ctx*/) override { }
  virtual void exitMemInitializerList(ZigCCParser::MemInitializerListContext * /*ctx*/) override { }

  virtual void enterMemInitializer(ZigCCParser::MemInitializerContext * /*ctx*/) override { }
  virtual void exitMemInitializer(ZigCCParser::MemInitializerContext * /*ctx*/) override { }

  virtual void enterMeminitializerid(ZigCCParser::MeminitializeridContext * /*ctx*/) override { }
  virtual void exitMeminitializerid(ZigCCParser::MeminitializeridContext * /*ctx*/) override { }

  virtual void enterOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext * /*ctx*/) override { }
  virtual void exitOperatorFunctionId(ZigCCParser::OperatorFunctionIdContext * /*ctx*/) override { }

  virtual void enterLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext * /*ctx*/) override { }
  virtual void exitLiteralOperatorId(ZigCCParser::LiteralOperatorIdContext * /*ctx*/) override { }

  virtual void enterTemplateDeclaration(ZigCCParser::TemplateDeclarationContext * /*ctx*/) override { }
  virtual void exitTemplateDeclaration(ZigCCParser::TemplateDeclarationContext * /*ctx*/) override { }

  virtual void enterTemplateparameterList(ZigCCParser::TemplateparameterListContext * /*ctx*/) override { }
  virtual void exitTemplateparameterList(ZigCCParser::TemplateparameterListContext * /*ctx*/) override { }

  virtual void enterTemplateParameter(ZigCCParser::TemplateParameterContext * /*ctx*/) override { }
  virtual void exitTemplateParameter(ZigCCParser::TemplateParameterContext * /*ctx*/) override { }

  virtual void enterTypeParameter(ZigCCParser::TypeParameterContext * /*ctx*/) override { }
  virtual void exitTypeParameter(ZigCCParser::TypeParameterContext * /*ctx*/) override { }

  virtual void enterSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext * /*ctx*/) override { }
  virtual void exitSimpleTemplateId(ZigCCParser::SimpleTemplateIdContext * /*ctx*/) override { }

  virtual void enterTemplateId(ZigCCParser::TemplateIdContext * /*ctx*/) override { }
  virtual void exitTemplateId(ZigCCParser::TemplateIdContext * /*ctx*/) override { }

  virtual void enterTemplateName(ZigCCParser::TemplateNameContext * /*ctx*/) override { }
  virtual void exitTemplateName(ZigCCParser::TemplateNameContext * /*ctx*/) override { }

  virtual void enterTemplateArgumentList(ZigCCParser::TemplateArgumentListContext * /*ctx*/) override { }
  virtual void exitTemplateArgumentList(ZigCCParser::TemplateArgumentListContext * /*ctx*/) override { }

  virtual void enterTemplateArgument(ZigCCParser::TemplateArgumentContext * /*ctx*/) override { }
  virtual void exitTemplateArgument(ZigCCParser::TemplateArgumentContext * /*ctx*/) override { }

  virtual void enterTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeNameSpecifier(ZigCCParser::TypeNameSpecifierContext * /*ctx*/) override { }

  virtual void enterExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext * /*ctx*/) override { }
  virtual void exitExplicitInstantiation(ZigCCParser::ExplicitInstantiationContext * /*ctx*/) override { }

  virtual void enterExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext * /*ctx*/) override { }
  virtual void exitExplicitSpecialization(ZigCCParser::ExplicitSpecializationContext * /*ctx*/) override { }

  virtual void enterTryBlock(ZigCCParser::TryBlockContext * /*ctx*/) override { }
  virtual void exitTryBlock(ZigCCParser::TryBlockContext * /*ctx*/) override { }

  virtual void enterFunctionTryBlock(ZigCCParser::FunctionTryBlockContext * /*ctx*/) override { }
  virtual void exitFunctionTryBlock(ZigCCParser::FunctionTryBlockContext * /*ctx*/) override { }

  virtual void enterHandlerSeq(ZigCCParser::HandlerSeqContext * /*ctx*/) override { }
  virtual void exitHandlerSeq(ZigCCParser::HandlerSeqContext * /*ctx*/) override { }

  virtual void enterHandler(ZigCCParser::HandlerContext * /*ctx*/) override { }
  virtual void exitHandler(ZigCCParser::HandlerContext * /*ctx*/) override { }

  virtual void enterExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext * /*ctx*/) override { }
  virtual void exitExceptionDeclaration(ZigCCParser::ExceptionDeclarationContext * /*ctx*/) override { }

  virtual void enterThrowExpression(ZigCCParser::ThrowExpressionContext * /*ctx*/) override { }
  virtual void exitThrowExpression(ZigCCParser::ThrowExpressionContext * /*ctx*/) override { }

  virtual void enterExceptionSpecification(ZigCCParser::ExceptionSpecificationContext * /*ctx*/) override { }
  virtual void exitExceptionSpecification(ZigCCParser::ExceptionSpecificationContext * /*ctx*/) override { }

  virtual void enterDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext * /*ctx*/) override { }
  virtual void exitDynamicExceptionSpecification(ZigCCParser::DynamicExceptionSpecificationContext * /*ctx*/) override { }

  virtual void enterTypeIdList(ZigCCParser::TypeIdListContext * /*ctx*/) override { }
  virtual void exitTypeIdList(ZigCCParser::TypeIdListContext * /*ctx*/) override { }

  virtual void enterNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext * /*ctx*/) override { }
  virtual void exitNoeExceptSpecification(ZigCCParser::NoeExceptSpecificationContext * /*ctx*/) override { }

  virtual void enterTheOperator(ZigCCParser::TheOperatorContext * /*ctx*/) override { }
  virtual void exitTheOperator(ZigCCParser::TheOperatorContext * /*ctx*/) override { }

  virtual void enterLiteral(ZigCCParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(ZigCCParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlrcpptest
