
#pragma once
#include <list>

#include "SyntaxModel/Expression.h"
#include "SyntaxModel/Instruction.h"
#include "SyntaxModel/SyntaxNode.h"

namespace SyntaxModel {

    struct Structure : public Instruction {
        Structure(const antlr4::misc::Interval& source_interval, const Expression* condition, const std::list<const Instruction*>& instructions, const std::list<const SyntaxNodeBase*>& additionnal_children = std::list<const SyntaxNodeBase*>());
        virtual ~Structure() = default;
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilog) const = 0;
        static IR::ExecutionBlock* generateInstructionBlock(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, const std::list<const Instruction*>& instructions, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue);

        const Expression* condition;
        const std::list<const Instruction*> instructions;
    };
}
