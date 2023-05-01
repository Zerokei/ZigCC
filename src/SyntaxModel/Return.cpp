#include "SyntaxModel/Return.h"
#include "SyntaxModel/Function.h"

namespace SyntaxModel {

    Return::Return(const antlr4::misc::Interval& source_interval, const Expression* expression)
        : Instruction(source_interval, { expression })
        , expression(expression)
    {
    }

    std::ostream& Return::toString(std::ostream& os) const
    {
        os << "return" << std::endl;
        return os;
    }

    IR::ExecutionBlock* Return::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        // Generate IR instructions to compute return expression
        if (expression != nullptr)
            eb = expression->generateIR(cfg, eb, IR::Register::rax.name64bits, add_stack_variable);
        return eb;
    }
}
