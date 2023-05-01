#pragma once

#include "SyntaxModel/SyntaxModel.h"
#include "antlr4-runtime.h"
#include "grammar/ZigCCParserBaseVisitor.h"
#include "utils.h"

class Visitor : public ZigCCParserBaseVisitor {
public:
    virtual antlrcpp::Any visitProgram(ZigCCParser::ProgramContext* ctx) override;
    virtual antlrcpp::Any visitFunctioncall(ZigCCParser::FunctioncallContext* ctx) override;
    virtual antlrcpp::Any visitFunction(ZigCCParser::FunctionContext* ctx) override;
    virtual antlrcpp::Any visitArgs(ZigCCParser::ArgsContext* ctx) override;
    virtual antlrcpp::Any visitDeclare(ZigCCParser::DeclareContext* context) override;
    virtual antlrcpp::Any visitDefine(ZigCCParser::DefineContext* context) override;
    virtual antlrcpp::Any visitReturn(ZigCCParser::ReturnContext* context) override;
    virtual antlrcpp::Any visitBreak(ZigCCParser::BreakContext* ctx) override;
    virtual antlrcpp::Any visitContinue(ZigCCParser::ContinueContext* ctx) override;
    virtual antlrcpp::Any visitInteger(ZigCCParser::IntegerContext* ctx) override;
    virtual antlrcpp::Any visitChar_literal(ZigCCParser::Char_literalContext* ctx) override;
    virtual antlrcpp::Any visitString_literal(ZigCCParser::String_literalContext* ctx) override;
    virtual antlrcpp::Any visitVariable_usage(ZigCCParser::Variable_usageContext* ctx) override;
    virtual antlrcpp::Any visitIf(ZigCCParser::IfContext* ctx) override;
    virtual antlrcpp::Any visitWhile(ZigCCParser::WhileContext* ctx) override;
    virtual antlrcpp::Any visitElse(ZigCCParser::ElseContext* ctx) override;
    virtual antlrcpp::Any visitDeftable(ZigCCParser::DeftableContext* ctx) override;
    virtual antlrcpp::Any visitDecltable(ZigCCParser::DecltableContext* ctx) override;
    virtual antlrcpp::Any visitArray_expr(ZigCCParser::Array_exprContext* ctx) override;
    virtual antlrcpp::Any visitAtomic_type(ZigCCParser::Atomic_typeContext* ctx) override;
    virtual antlrcpp::Any visitType(ZigCCParser::TypeContext* ctx) override;
    virtual antlrcpp::Any visitExpression_instr(ZigCCParser::Expression_instrContext* ctx) override;
    virtual antlrcpp::Any visitParenthesis(ZigCCParser::ParenthesisContext* ctx) override;
    virtual antlrcpp::Any visitFor(ZigCCParser::ForContext* ctx) override;
    virtual antlrcpp::Any visitDef_or_expr(ZigCCParser::Def_or_exprContext* ctx) override;

    // Binary ops
    virtual antlrcpp::Any visitBinadd(ZigCCParser::BinaddContext *ctx) override;
    virtual antlrcpp::Any visitBinmul(ZigCCParser::BinmulContext *ctx) override;
    virtual antlrcpp::Any visitInfequal(ZigCCParser::InfequalContext* ctx) override;
    virtual antlrcpp::Any visitDifferent(ZigCCParser::DifferentContext* ctx) override;
    virtual antlrcpp::Any visitPlus(ZigCCParser::PlusContext* ctx) override;
    virtual antlrcpp::Any visitMult(ZigCCParser::MultContext* ctx) override;
    virtual antlrcpp::Any visitMinus(ZigCCParser::MinusContext* ctx) override;
    virtual antlrcpp::Any visitInf(ZigCCParser::InfContext* ctx) override;
    virtual antlrcpp::Any visitDiv(ZigCCParser::DivContext* ctx) override;
    virtual antlrcpp::Any visitEqual(ZigCCParser::EqualContext* ctx) override;
    virtual antlrcpp::Any visitSup(ZigCCParser::SupContext* ctx) override;
    virtual antlrcpp::Any visitSupequal(ZigCCParser::SupequalContext* context) override;
    virtual antlrcpp::Any visitModulo(ZigCCParser::ModuloContext* ctx) override;

    // Unary ops
    virtual antlrcpp::Any visitNot(ZigCCParser::NotContext* ctx) override;
    virtual antlrcpp::Any visitUnary_minus(ZigCCParser::Unary_minusContext* ctx) override;

    // Unaray affectations
    virtual antlrcpp::Any visitPost_inc(ZigCCParser::Post_incContext* ctx) override;
    virtual antlrcpp::Any visitPre_dec(ZigCCParser::Pre_decContext* ctx) override;
    virtual antlrcpp::Any visitPost_dec(ZigCCParser::Post_decContext* ctx) override;
    virtual antlrcpp::Any visitPre_inc(ZigCCParser::Pre_incContext* ctx) override;

    // Binary affectations
    virtual antlrcpp::Any visitAffect_eq(ZigCCParser::Affect_eqContext* ctx) override;
    virtual antlrcpp::Any visitPlus_equal(ZigCCParser::Plus_equalContext* ctx) override;
    virtual antlrcpp::Any visitMinus_equal(ZigCCParser::Minus_equalContext* ctx) override;
    virtual antlrcpp::Any visitDiv_equal(ZigCCParser::Div_equalContext* ctx) override;
    virtual antlrcpp::Any visitMult_equal(ZigCCParser::Mult_equalContext* ctx) override;
    virtual antlrcpp::Any visitModulo_equal(ZigCCParser::Modulo_equalContext* ctx) override;

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
