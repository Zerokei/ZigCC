#pragma once
#include "SyntaxModel/Structure.h"
#include "SyntaxModel/SyntaxNode.h"

namespace SyntaxModel {

    struct While final : public Structure {
        While(const antlr4::misc::Interval& source_interval, const Expression* condition, const std::list<const Instruction*>& instructions);
        virtual ~While() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Structure, Instruction, While>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const override;
    };
}
