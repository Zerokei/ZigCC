#pragma once
#include "SyntaxModel/Expression.h"
#include "SyntaxModel/SyntaxNode.h"

namespace SyntaxModel {
    struct UnaryOp final : public Expression {
        enum class Op { MINUS,
            NOT };
        UnaryOp(const antlr4::misc::Interval& source_interval, const Expression* expression, const Op op);
        virtual ~UnaryOp() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<UnaryOp>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual Type getExprType(const StaticAnalysis::StaticAnalyser* analyser) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const override;

        const Expression* expression;
        const Op op;
    };
}
