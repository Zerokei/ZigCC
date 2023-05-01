#include "SyntaxModel/While.h"

namespace SyntaxModel {

    While::While(const antlr4::misc::Interval& source_interval, const Expression* condition, const std::list<const Instruction*>& instructions)
        : Structure(source_interval, condition, instructions)
    {
    }

    std::ostream& While::toString(std::ostream& os) const
    {
        os << "while(" << *condition << ") {" << std::endl;
        for (auto instr : instructions)
            os << *instr;
        os << "}" << std::endl;
        return os;
    }

    IR::ExecutionBlock* While::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable, const IR::GenerateIREpilogue_fn& gen_epilogue) const
    {
        auto cond_reg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);

        IR::symbol_t while_body_label = cfg.CreateLabel("while_body", this);
        eb->AppendInstruction(IR::Instruction(IR::Instruction::JMP, while_body_label));

        auto* while_body = cfg.CreateExecutionBlock(while_body_label, eb);
        while_body = condition->generateIR(cfg, while_body, cond_reg, add_stack_variable);

        IR::symbol_t while_end_label = cfg.CreateLabel("while_end", this);
        auto* while_end = cfg.CreateExecutionBlock(while_end_label, while_body);

        while_body->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, IR::ControlFlowGraph::CreateConstant(0), cond_reg));
        while_body->AppendInstruction(IR::Instruction(IR::Instruction::JE, while_end_label));
        while_body = generateInstructionBlock(cfg, while_body, instructions, add_stack_variable, gen_epilogue);
        while_body->AppendInstruction(IR::Instruction(IR::Instruction::JMP, while_body_label));

        return while_end;
    }
}
