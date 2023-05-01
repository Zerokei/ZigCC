#include "SyntaxModel/UnaryOp.h"
#include "SyntaxModel/PrimitiveType.h"

namespace SyntaxModel {

    UnaryOp::UnaryOp(const antlr4::misc::Interval& source_interval, const Expression* expression, const Op op)
        : Expression(source_interval, { expression })
        , expression(expression)
        , op(op)
    {
    }

    std::ostream& UnaryOp::toString(std::ostream& os) const
    {
        os << "op" << static_cast<std::underlying_type<UnaryOp::Op>::type>(op) << *expression << std::endl;
        return os;
    }

    Type UnaryOp::getExprType(const StaticAnalysis::StaticAnalyser* analyser) const
    {
        // Returns type according to sub expression, implicit cast rules and operator type rules
        auto expr_type = expression->getExprType(analyser);

        if (expr_type.isArray)
            // TODO: make an alias for pointer type depending on target architecture
            return Type(source_interval, PrimitiveType::INT64_T, false); // BinaryOps interprets arrays as pointers (INT64_T);

        if (op == Op::MINUS) {
            if (expr_type.type == PrimitiveType::CHAR)
                return Type(source_interval, PrimitiveType::INT32_T, false); // Implicit cast to INT32_T
            return expr_type;
        } else // if (op == Op::NOT)
            return Type(source_interval, PrimitiveType::INT32_T, false); // Implicit cast to boolean (INT32_T)
    }

    IR::ExecutionBlock* UnaryOp::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        auto subExprReg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);
        eb = expression->generateIR(cfg, eb, subExprReg, add_stack_variable);

        if (op == Op::MINUS) {
            eb->AppendInstruction(IR::Instruction(IR::Instruction::NEGQ, subExprReg));
            eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, subExprReg, dest));
        } else if (op == Op::NOT) {
            eb->AppendInstruction(IR::Instruction(IR::Instruction::CMPQ, IR::ControlFlowGraph::CreateConstant(0), subExprReg));
            eb->AppendInstruction(IR::Instruction(IR::Instruction::SETE, IR::Register::r11.name8bits));
            eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVZBQ, IR::Register::r11.name8bits, dest));
        }
        return eb;
    }
}
