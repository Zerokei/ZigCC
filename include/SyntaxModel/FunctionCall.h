#pragma once
#include <list>

#include "SyntaxModel/Expression.h"
#include "SyntaxModel/SyntaxNode.h"

namespace SyntaxModel {
    struct FunctionCall final : public Expression {
        FunctionCall(const antlr4::misc::Interval& source_interval, const std::list<const Expression*>& args, const Identifier& func_name);
        virtual ~FunctionCall() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Instruction, Expression, FunctionCall>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual Type getExprType(const StaticAnalysis::StaticAnalyser* analyser) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const override;

        const std::list<const Expression*> args;
        const Identifier func_name;
    };
}
