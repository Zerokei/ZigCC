#include <list>

#include "SyntaxModel/Return.h"
#include "SyntaxModel/Structure.h"
#include "utils.h"

namespace SyntaxModel {

    Structure::Structure(const antlr4::misc::Interval& source_interval, const Expression* condition, const std::list<const Instruction*>& instructions, const std::list<const SyntaxNodeBase*>& additionnal_children)
        : Instruction(source_interval, utils::children_list(condition, instructions, additionnal_children))
        , condition(condition)
        , instructions(instructions)
    {
    }

    std::ostream& Structure::toString(std::ostream& os) const
    {
        os << "structure" << std::endl;
        return os;
    }

    IR::ExecutionBlock* Structure::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        throw new CompilerException("Sorry for that");
    }

    IR::ExecutionBlock* Structure::generateInstructionBlock(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, const std::list<const Instruction*>& instructions, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue)
    {
        for (auto* instr : instructions) {
            if (instr->is<Structure>()) {
                auto strucure_instr = dynamic_cast<const Structure*>(instr);
                eb = strucure_instr->generateIR(cfg, eb, nullopt, add_stack_variable, gen_epilogue);
            } else
                eb = instr->generateIR(cfg, eb, nullopt, add_stack_variable);
            if (instr->is<Return>())
                gen_epilogue(eb);
        }
        return eb;
    }
}
