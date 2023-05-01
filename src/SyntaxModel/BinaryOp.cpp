#include "SyntaxModel/BinaryOp.h"
#include "SyntaxModel/PrimitiveType.h"

namespace SyntaxModel {

    BinaryOp::BinaryOp(const antlr4::misc::Interval& source_interval, const Expression* leftExpression, const Expression* rightExpression, const Op op)
        : Expression(source_interval, { leftExpression, rightExpression })
        , leftExpression(leftExpression)
        , rightExpression(rightExpression)
        , op(op)
    {
    }

    std::ostream& BinaryOp::toString(std::ostream& os) const
    {
        os << *(leftExpression) << " op" << static_cast<std::underlying_type<BinaryOp::Op>::type>(op) << " " << *(rightExpression);
        return os;
    }

    Type BinaryOp::getExprType(const StaticAnalysis::StaticAnalyser* analyser) const
    {
        // Returns type according to sub expressions, implicit cast rules and operator type rules
        auto left_type = leftExpression->getExprType(analyser);
        auto right_type = leftExpression->getExprType(analyser);

        if (left_type.isArray || right_type.isArray)
            // TODO: make an alias for pointer type depending on target architecture
            return Type(source_interval, PrimitiveType::INT64_T, false); // BinaryOps interprets arrays as pointers (INT64_T);

        if (op == Op::AND || op == Op::OR || op == Op::SUP || op == Op::SUP_EQ || op == Op::INF || op == Op::INF_EQ || op == Op::DIFFERENT || op == Op::EQUAL)
            return Type(source_interval, PrimitiveType::INT32_T, false); // Implicit cast to boolean (INT32_T)
        else {
            if (left_type.type == PrimitiveType::INT64_T || right_type.type == PrimitiveType::INT64_T)
                return Type(source_interval, PrimitiveType::INT64_T, false);
            return Type(source_interval, PrimitiveType::INT32_T, false);
        }
    }

    IR::ExecutionBlock* BinaryOp::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        IR::symbol_t leftExpressionReg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);
        eb = leftExpression->generateIR(cfg, eb, leftExpressionReg, add_stack_variable);
        IR::symbol_t rightExpressionReg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);
        eb = rightExpression->generateIR(cfg, eb, rightExpressionReg, add_stack_variable);

        if (dest) {
            switch (op) {
            case Op::PLUS:
            case Op::MINUS:
                eb->AppendInstruction(IR::Instruction((op == Op::PLUS ? IR::Instruction::ADDQ : IR::Instruction::SUBQ), rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, leftExpressionReg, dest));
                break;
            case Op::MULT:
                /*Type t = getExprType(cfg.static_analyser);
            if (t.type != Type::PrimitiveType::INT64_T) {
                if (t.type == Type::PrimitiveType::INT32_T)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::IMULL, subExprReg1, subExprReg2));
                else if (t.type == Type::PrimitiveType::CHAR)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::IMULL, subExprReg1, subExprReg2, subExprReg2));
                else
                    throw new CompilerException("Expesssion type not supported");
            } else {*/
                //TODO: make sure I don't need IMULQ here instead of IMULL
                eb->AppendInstruction(IR::Instruction(IR::Instruction::IMULL, leftExpressionReg, rightExpressionReg, rightExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, rightExpressionReg, dest.value()));
                break;
            case Op::MODULO:
            case Op::DIV:
                eb = IR::Instruction::divide_64bits(eb, op == Op::MODULO, leftExpressionReg, rightExpressionReg, dest.value());
                break;
            case Op::EQUAL:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETE, IR::Register::r11.name8bits));
                break;
            case Op::DIFFERENT:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETNE, IR::Register::r11.name8bits));
                break;
            case Op::SUP:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETG, IR::Register::r11.name8bits));
                break;
            case Op::SUP_EQ:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETGE, IR::Register::r11.name8bits));
                break;
            case Op::INF:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETL, IR::Register::r11.name8bits));
                break;
            case Op::INF_EQ:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, rightExpressionReg, leftExpressionReg));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::SETLE, IR::Register::r11.name8bits));
                break;
            case Op::AND:
                break;
            case Op::OR:
                break;
            }
            if(op == Op::EQUAL || op == Op::DIFFERENT || op == Op::SUP || op == Op::SUP_EQ || op == Op::INF || op == Op::INF_EQ) {
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVZBQ, IR::Register::r11.name8bits, IR::Register::r10.name64bits));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, IR::Register::r10.name64bits, dest.value()));
            }
        }
        return eb;
    }
}
