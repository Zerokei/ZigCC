#include "SyntaxModel/Else.h"
#include "SyntaxModel/Structure.h"
#include "SyntaxModel/SyntaxNode.h"
#include "utils.h"

namespace SyntaxModel {

    Else::Else(const antlr4::misc::Interval& source_interval, const std::list<const Instruction*>& instructions)
        : SyntaxNodeBase(source_interval, utils::container_cast(instructions))
        , instructions(instructions)
    {
    }

    std::ostream& Else::toString(std::ostream& os) const
    {
        os << "else {" << std::endl;
        for (auto instr : instructions)
            os << *(instr);
        os << "}" << std::endl;
        return os;
    }

    IR::ExecutionBlock* Else::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const
    {
        return Structure::generateInstructionBlock(cfg, eb, instructions, add_stack_variable, gen_epilogue);
    }
}
