#include "SyntaxModel/Affectation.h"

#include "StaticAnalysis.h"

namespace SyntaxModel {
    Affectation::Affectation(const antlr4::misc::Interval& source_interval, const Op op, const Identifier& var, const Expression* array_indice, const Expression* affected_value)
        : Expression(source_interval, { affected_value, array_indice })
        , op(op)
        , var(var)
        , array_indice(array_indice)
        , affected_value(affected_value)
        , isUnaryAffectation(op == Op::POST_INC || op == Op::PRE_INC || op == Op::PRE_DEC || op == Op::POST_DEC)
    {
        if (affected_value != nullptr && isUnaryAffectation)
            throw new CompilerException("Can't affect an expression while performing an unary affectation");
        else if (affected_value == nullptr && !isUnaryAffectation)
            throw new CompilerException("Can't perform a binary affectation while there is no value to affect");
    }

    std::ostream& Affectation::toString(std::ostream& os) const
    {
        os << var << " op" << static_cast<int>(op);
        if (affected_value != nullptr)
            os << " " << *affected_value;
        os << std::endl;
        return os;
    }

    Type Affectation::getExprType(const StaticAnalysis::StaticAnalyser* analyser) const
    {
        // Return affected variable type
        auto var = analyser->getVariableOfAffectation(this);
        return *(var.type);
    }

    IR::ExecutionBlock* Affectation::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        auto analyser = cfg.static_analyser;
        auto var = analyser->getVariableOfAffectation(this);
        auto stack_var = IR::ControlFlowGraph::getStackVariableFromVariable(var, this);

        auto generateAffectedValue = [&cfg, &eb, &add_stack_variable, this]() {
            auto value_reg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable);
            if (!isUnaryAffectation)
                eb = affected_value->generateIR(cfg, eb, value_reg, add_stack_variable);
            return value_reg;
        };

        if (!stack_var)
            throw new CompilerException("Globals affectation not supported yet"); // TODO: handle globals
        else {
            IR::symbol_t var_symbol = stack_var.value().toAddressOperandSyntax();
            // TODO: optimize affectation to var usage
            // TODO: handle arrays
            switch (op) {
            case Op::EQ:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, generateAffectedValue(), var_symbol));
                if (dest)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, dest));
                break;
            case Op::PRE_DEC:
            case Op::PRE_INC: {
                eb->AppendInstruction(IR::Instruction(op == Op::PRE_DEC ? IR::Instruction::SUBQ : IR::Instruction::ADDQ, cfg.CreateConstant(1), var_symbol));
                if (dest)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, dest));
                break;
            case Op::POST_DEC:
            case Op::POST_INC:
                if (dest) {
                    auto tmp_reg = cfg.getFreeTmpRegister(PrimitiveType::INT64_T, add_stack_variable); // this temporary register is nescessary when this affectation is used in the value of another affectation
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, tmp_reg));
                    eb->AppendInstruction(IR::Instruction(op == Op::POST_DEC ? IR::Instruction::SUBQ : IR::Instruction::ADDQ, cfg.CreateConstant(1), var_symbol));
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, tmp_reg, dest));
                } else
                    eb->AppendInstruction(IR::Instruction(op == Op::POST_DEC ? IR::Instruction::SUBQ : IR::Instruction::ADDQ, cfg.CreateConstant(1), var_symbol));
                break;
            }
            case Op::PLUS_EQ:
            case Op::MIN_EQ:
                eb->AppendInstruction(IR::Instruction(op == Op::PLUS_EQ ? IR::Instruction::ADDQ : IR::Instruction::SUBQ, generateAffectedValue(), var_symbol));
                if (dest)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, dest));
                break;
            case Op::DIV_EQ:
            case Op::MODULO_EQ:
                eb = IR::Instruction::divide_64bits(eb, op == Op::MODULO_EQ, var_symbol, generateAffectedValue(), var_symbol);
                if (dest)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, dest));
                break;
            case Op::MULT_EQ:
                eb->AppendInstruction(IR::Instruction(IR::Instruction::IMULL, var_symbol, generateAffectedValue(), var_symbol));
                if (dest)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, var_symbol, dest));
                break;
            }
        }
        return eb;
    }
}
