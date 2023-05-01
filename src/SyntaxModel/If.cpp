#include "SyntaxModel/If.h"

namespace SyntaxModel {

    If::If(const antlr4::misc::Interval& source_interval, const Expression* condition, const std::list<const Instruction*>& instructions, const Else* else_clause)
        : Structure(source_interval, condition, instructions, { else_clause })
        , else_clause(else_clause)
    {
    }

    std::ostream& If::toString(std::ostream& os) const
    {
        os << "if(" << *condition << ") {" << std::endl;
        for (auto instr : instructions)
            os << *instr;
        os << "}" << std::endl;
        if (else_clause != nullptr)
            os << *else_clause;
        return os;
    }

    IR::ExecutionBlock* If::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const
    {
        auto cond_reg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);
        eb = condition->generateIR(cfg, eb, cond_reg, add_stack_variable); // TODO: split condition expression on && and || binary operator in order to avoid evaluating unescessary expressions
        IR::symbol_t end_if_then_label = cfg.CreateLabel(else_clause == nullptr ? "end_if" : "else", this);

        eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, IR::ControlFlowGraph::CreateConstant(0), cond_reg));
        eb->AppendInstruction(IR::Instruction(IR::Instruction::JE, end_if_then_label));

        eb = generateInstructionBlock(cfg, eb, instructions, add_stack_variable, gen_epilogue);
        auto* end_if_then = cfg.CreateExecutionBlock(end_if_then_label, eb);

        if (else_clause != nullptr) {
            IR::symbol_t end_else_label = cfg.CreateLabel("end_else", this);
            eb->AppendInstruction(IR::Instruction(IR::Instruction::JMP, end_else_label));
            end_if_then = else_clause->generateIR(cfg, end_if_then, add_stack_variable, gen_epilogue);
            return cfg.CreateExecutionBlock(end_else_label, end_if_then);
        }
        return end_if_then;
    }
}
