#include "SyntaxModel/For.h"

namespace SyntaxModel {
    For::For(const antlr4::misc::Interval& source_interval, const SyntaxNodeBase* init, const Expression* condition, const Expression* iteration_expression, const std::list<const Instruction*>& instructions)
        : Structure(source_interval, condition, instructions, utils::children_list(init, iteration_expression))
        , init(init)
        , iteration_expression(iteration_expression)
    {
    }

    std::ostream& For::toString(std::ostream& os) const
    {
        auto to_string = [&os](auto* ptr) { if(ptr != nullptr) {os << *ptr;} };
        os << "for(";
        to_string(init);
        os << ";";
        to_string(condition);
        os << ";";
        to_string(iteration_expression);
        os << ") {" << std::endl;
        for (const auto* instr : instructions)
            to_string(instr);
        os << "}" << std::endl;
        return os;
    }

    IR::ExecutionBlock* For::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const
    {
        // TODO: ...
        return eb;
    }
}
