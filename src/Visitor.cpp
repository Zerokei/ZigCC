#include <cstdint>
#include <string>
#include <vector>

#include "SyntaxModel/SyntaxModel.h"
#include "Visitor.h"

// TODO: add checks for nullptr
// TODO: replace static_cast with dynamic_cast?

namespace SM = SyntaxModel;
using PT = SM::PrimitiveType;

antlrcpp::Any Visitor::visitProgram(ZigCCParser::ProgramContext* ctx)
{
    std::vector<SM::Include> includes;
    for (auto* inc : ctx->INCLUDE())
        includes.push_back(SM::Include(inc));
    auto definitions = visit_all<SM::Definition>(ctx->decl_or_def());
    auto functions = visit_all<SM::Function>(ctx->function());
    functions.push_back(new SM::Putchar()); // We add putchar function which is defined by default
    return new SM::Program(ctx->getSourceInterval(), includes, functions, definitions);
}

antlrcpp::Any Visitor::visitFunctioncall(ZigCCParser::FunctioncallContext* ctx)
{
    auto args = visit_all<SM::Expression>(ctx->expression());
    auto func_name = SM::Identifier(ctx->IDENTIFIER());
    return static_cast<SM::Expression*>(new SM::FunctionCall(ctx->getSourceInterval(), args, func_name));
}

antlrcpp::Any Visitor::visitFunction(ZigCCParser::FunctionContext* ctx)
{
    auto id = SM::Identifier(ctx->IDENTIFIER());
    auto args = visit_single<SM::Args>(ctx->args());
    auto definitions = visit_all<SM::Definition>(ctx->decl_or_def());
    auto return_type = visit_single<SM::Type>(ctx->type());
    auto instructions = visit_all<SM::Instruction>(ctx->instruction());
    return new SM::Function(ctx->getSourceInterval(), definitions, instructions, args, id, return_type);
}

antlrcpp::Any Visitor::visitArgs(ZigCCParser::ArgsContext* ctx)
{
    auto names = make_all_terminals(ctx->IDENTIFIER());
    auto types = visit_all<SM::Type>(ctx->type());
    return new SM::Args(ctx->getSourceInterval(), types, names);
}

antlrcpp::Any Visitor::visitDeclare(ZigCCParser::DeclareContext* ctx)
{
    auto type = visit_single<SM::Type>(ctx->atomic_type());
    auto names = make_all_terminals(ctx->IDENTIFIER());
    return new SM::Definition(ctx->getSourceInterval(), type, names);
}

const std::list<const SM::Definition::size_constant*> Visitor::parseArraySizes(const std::vector<antlr4::tree::TerminalNode*>& integers)
{
    // Parse array sizes from their tokens to build Constant<INT32_T> instances
    std::list<const SM::Definition::size_constant*> sizes;
    for (auto* terminal : integers) {
        // Find source interval from terminal node and make a Constant<INT32_T> for each specified size
        auto interval = antlr4::misc::Interval(terminal->getSymbol()->getStartIndex(), terminal->getSymbol()->getStopIndex()); // TODO: make sure this is the right interval
        sizes.push_back(SM::make_constant_from_terminal<PT::INT32_T>(interval, terminal));
    }
    return sizes;
}

antlrcpp::Any Visitor::visitDecltable(ZigCCParser::DecltableContext* ctx)
{
    auto* type = visit_single<SM::Type>(ctx->atomic_type());
    auto* array_type = new SM::Type(type->source_interval, type->type, true);
    delete type;
    auto names = make_all_terminals(ctx->IDENTIFIER());
    auto sizes = parseArraySizes(ctx->INTEGER());
    return new SM::Definition(ctx->getSourceInterval(), array_type, names, sizes);
}

antlrcpp::Any Visitor::visitDeftable(ZigCCParser::DeftableContext* ctx)
{
    auto type = visit_single<SM::Type>(ctx->atomic_type());
    auto array_type = new SM::Type(type->source_interval, type->type, true);
    delete type;
    auto names = make_all_terminals(ctx->IDENTIFIER());
    auto sizes = parseArraySizes(ctx->INTEGER());
    auto init_arrays = visit_all<SM::Expression>(ctx->expression());
    return new SM::Definition(ctx->getSourceInterval(), array_type, names, sizes, init_arrays);
}

antlrcpp::Any Visitor::visitDefine(ZigCCParser::DefineContext* ctx)
{
    auto type = visit_single<SM::Type>(ctx->atomic_type());
    auto names = make_all_terminals(ctx->IDENTIFIER());
    auto init_values = visit_all<SM::Expression>(ctx->expression());
    return new SM::Definition(ctx->getSourceInterval(), type, names, init_values);
}

antlrcpp::Any Visitor::visitReturn(ZigCCParser::ReturnContext* ctx)
{
    auto returned_expr = visit_single<SM::Expression>(ctx->expression());
    return static_cast<SM::Instruction*>(new SM::Return(ctx->getSourceInterval(), returned_expr));
}

antlrcpp::Any Visitor::visitBreak(ZigCCParser::BreakContext* ctx) { return static_cast<SM::Instruction*>(new SM::Break(ctx->getSourceInterval())); }
antlrcpp::Any Visitor::visitContinue(ZigCCParser::ContinueContext* ctx) { return static_cast<SM::Instruction*>(new SM::Continue(ctx->getSourceInterval())); }

antlrcpp::Any Visitor::visitInfequal(ZigCCParser::InfequalContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::INF_EQ); }
antlrcpp::Any Visitor::visitDifferent(ZigCCParser::DifferentContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::DIFFERENT); }
antlrcpp::Any Visitor::visitPlus(ZigCCParser::PlusContext* ctx) { return SM::BinaryOp::Op::PLUS; }
antlrcpp::Any Visitor::visitMult(ZigCCParser::MultContext* ctx) { return SM::BinaryOp::Op::MULT; }
antlrcpp::Any Visitor::visitMinus(ZigCCParser::MinusContext* ctx) { return SM::BinaryOp::Op::MINUS; }
antlrcpp::Any Visitor::visitInf(ZigCCParser::InfContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::INF); }
antlrcpp::Any Visitor::visitDiv(ZigCCParser::DivContext* ctx) { return SM::BinaryOp::Op::DIV; }
antlrcpp::Any Visitor::visitEqual(ZigCCParser::EqualContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::EQUAL); }
antlrcpp::Any Visitor::visitSup(ZigCCParser::SupContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::SUP); }
antlrcpp::Any Visitor::visitSupequal(ZigCCParser::SupequalContext* ctx) { return visitBinaryOp(ctx, SM::BinaryOp::Op::SUP_EQ); }
antlrcpp::Any Visitor::visitModulo(ZigCCParser::ModuloContext* ctx) { return SM::BinaryOp::Op::MODULO; }

antlrcpp::Any Visitor::visitBinadd(ZigCCParser::BinaddContext *ctx)
{
    auto op = visit(ctx->opPLUS());
    return visitBinaryOp(ctx, op);
}

antlrcpp::Any Visitor::visitBinmul(ZigCCParser::BinmulContext *ctx)
{
    auto op = visit(ctx->opMULT());
    return visitBinaryOp(ctx, op);
}

antlrcpp::Any Visitor::visitNot(ZigCCParser::NotContext* ctx)
{
    auto expr = visit_single<SM::Expression>(ctx->expression());
    return static_cast<SM::Expression*>(new SM::UnaryOp(ctx->getSourceInterval(), expr, SM::UnaryOp::Op::NOT));
}

antlrcpp::Any Visitor::visitUnary_minus(ZigCCParser::Unary_minusContext* ctx)
{
    auto expr = visit_single<SM::Expression>(ctx->expression());
    return static_cast<SM::Expression*>(new SM::UnaryOp(ctx->getSourceInterval(), expr, SM::UnaryOp::Op::MINUS));
}

// Parse int64_t from token (we assume here this is int64_t, if int32_t is needed an implicit cast will be performed unless optimized away)
antlrcpp::Any Visitor::visitInteger(ZigCCParser::IntegerContext* ctx)
{
    return static_cast<SM::Expression*>(SM::make_constant_from_terminal<PT::INT64_T>(ctx->getSourceInterval(), ctx->INTEGER()));
}
antlrcpp::Any Visitor::visitChar_literal(ZigCCParser::Char_literalContext* ctx)
{
    return static_cast<SM::Expression*>(SM::make_constant_from_terminal<PT::CHAR>(ctx->getSourceInterval(), ctx->QUOTED_CHAR_LITERAL()));
}
antlrcpp::Any Visitor::visitString_literal(ZigCCParser::String_literalContext* ctx) { return static_cast<SM::Expression*>(SM::make_array_const_from_string(ctx->getSourceInterval(), ctx->STRING_LITERAL())); }

antlrcpp::Any Visitor::visitVariable_usage(ZigCCParser::Variable_usageContext* ctx)
{
    auto var_name = SM::Identifier(ctx->IDENTIFIER());
    return static_cast<SM::Expression*>(new SM::VariableUsage(ctx->getSourceInterval(), var_name));
}

antlrcpp::Any Visitor::visitIf(ZigCCParser::IfContext* ctx)
{
    auto condition = visit_single<SM::Expression>(ctx->expression());
    auto instructions = visit_all<SM::Instruction>(ctx->instruction());
    auto else_clause = visit_single<SM::Else>(ctx->else_structure());
    return static_cast<SM::Instruction*>(new SM::If(ctx->getSourceInterval(), condition, instructions, else_clause));
}

antlrcpp::Any Visitor::visitWhile(ZigCCParser::WhileContext* ctx)
{
    auto condition = visit_single<SM::Expression>(ctx->expression());
    auto instructions = visit_all<SM::Instruction>(ctx->instruction());
    return static_cast<SM::Instruction*>(new SM::While(ctx->getSourceInterval(), condition, instructions));
}

antlrcpp::Any Visitor::visitElse(ZigCCParser::ElseContext* ctx)
{
    auto instructions = visit_all<SM::Instruction>(ctx->instruction());
    return new SM::Else(ctx->getSourceInterval(), instructions);
}

antlrcpp::Any Visitor::visitArray_expr(ZigCCParser::Array_exprContext* ctx)
{
    if (ctx->INTEGER().size() > 0) {
        return static_cast<SM::Expression*>(SM::make_array_const<PT::INT64_T>(ctx->getSourceInterval(), ctx->INTEGER()));
    } else if (ctx->QUOTED_CHAR_LITERAL().size() > 0) {
        return static_cast<SM::Expression*>(SM::make_array_const<PT::CHAR>(ctx->getSourceInterval(), ctx->QUOTED_CHAR_LITERAL()));
    }
    return nullptr;
}

antlrcpp::Any Visitor::visitAtomic_type(ZigCCParser::Atomic_typeContext* ctx)
{
    if (ctx->CHAR() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::CHAR, false);
    } else if (ctx->INT32_T() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::INT32_T, false);
    } else if (ctx->INT64_T() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::INT64_T, false);
    }
    return nullptr;
}

antlrcpp::Any Visitor::visitType(ZigCCParser::TypeContext* ctx)
{
    if (ctx->CHAR() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::CHAR, ctx->ARRAY_BRACKETS() != nullptr);
    } else if (ctx->INT32_T() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::INT32_T, ctx->ARRAY_BRACKETS() != nullptr);
    } else if (ctx->INT64_T() != nullptr) {
        return new SM::Type(ctx->getSourceInterval(), PT::INT64_T, ctx->ARRAY_BRACKETS() != nullptr);
    }
    return nullptr;
}

antlrcpp::Any Visitor::visitExpression_instr(ZigCCParser::Expression_instrContext* ctx)
{
    // Don't touch and don't ask why!
    return static_cast<SM::Instruction*>(visit_single<SM::Expression>(ctx->expression()));
}

antlrcpp::Any Visitor::visitParenthesis(ZigCCParser::ParenthesisContext* ctx)
{
    return visit_single<SM::Expression>(ctx->expression());
}

antlrcpp::Any Visitor::visitFor(ZigCCParser::ForContext* ctx)
{
    auto init = visit_single<SM::SyntaxNodeBase>(ctx->def_or_expr(0));
    auto condition = visit_single<SM::SyntaxNodeBase>(ctx->def_or_expr(1));
    if (condition->is<SM::Definition>())
        throw new CompilerException("For loop doesn't support definitions in their condition statements for now");
    auto condition_expr = dynamic_cast<const SM::Expression*>(condition);
    auto iteration_expression = visit_single<SM::Expression>(ctx->expression());
    auto instructions = visit_all<SM::Instruction>(ctx->instruction());
    return static_cast<SM::Instruction*>(new SM::For(ctx->getSourceInterval(), init, condition_expr, iteration_expression, instructions));
}

antlrcpp::Any Visitor::visitDef_or_expr(ZigCCParser::Def_or_exprContext* ctx)
{
    if (ctx->definition() != nullptr)
        return static_cast<SM::SyntaxNodeBase*>(visit_single<SM::Definition>(ctx->definition()));
    else
        return static_cast<SM::SyntaxNodeBase*>(visit_single<SM::Expression>(ctx->expression()));
}

antlrcpp::Any Visitor::visitPre_inc(ZigCCParser::Pre_incContext* ctx) { return visitUnaryAffectation(SM::Affectation::Op::PRE_INC, ctx); }
antlrcpp::Any Visitor::visitPre_dec(ZigCCParser::Pre_decContext* ctx) { return visitUnaryAffectation(SM::Affectation::Op::PRE_DEC, ctx); }
antlrcpp::Any Visitor::visitPost_inc(ZigCCParser::Post_incContext* ctx) { return visitUnaryAffectation(SM::Affectation::Op::POST_INC, ctx); }
antlrcpp::Any Visitor::visitPost_dec(ZigCCParser::Post_decContext* ctx) { return visitUnaryAffectation(SM::Affectation::Op::POST_DEC, ctx); }
antlrcpp::Any Visitor::visitAffect_eq(ZigCCParser::Affect_eqContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::EQ, ctx); }
antlrcpp::Any Visitor::visitPlus_equal(ZigCCParser::Plus_equalContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::PLUS_EQ, ctx); }
antlrcpp::Any Visitor::visitMinus_equal(ZigCCParser::Minus_equalContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::MIN_EQ, ctx); }
antlrcpp::Any Visitor::visitDiv_equal(ZigCCParser::Div_equalContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::DIV_EQ, ctx); }
antlrcpp::Any Visitor::visitMult_equal(ZigCCParser::Mult_equalContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::MULT_EQ, ctx); }
antlrcpp::Any Visitor::visitModulo_equal(ZigCCParser::Modulo_equalContext* ctx) { return visitBinaryAffectation(SM::Affectation::Op::MODULO_EQ, ctx); }

std::vector<utils::TerminalInfo> Visitor::make_all_terminals(const std::vector<antlr4::tree::TerminalNode*>& contexts)
{
    std::vector<utils::TerminalInfo> syntax_nodes;
    syntax_nodes.reserve(contexts.size());
    for (auto* ctx : contexts)
        syntax_nodes.emplace_back(ctx);
    return syntax_nodes;
}
