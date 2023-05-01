#pragma once
#include <list>

#include "SyntaxModel/Structure.h"

namespace SyntaxModel {

    struct For final : public Structure {
        For(const antlr4::misc::Interval& source_interval, const SyntaxNodeBase* init, const Expression* condition, const Expression* iteration_expression, const std::list<const Instruction*>& instructions);
        virtual ~For() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<For, Structure, Instruction>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const override;

        const SyntaxNodeBase* init;
        const Expression* iteration_expression;
    };
}
