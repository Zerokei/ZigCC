#include "SyntaxModel/Expression.h"
#include "SyntaxModel/Definition.h"
#include "SyntaxModel/Function.h"
#include "SyntaxModel/SyntaxNode.h"

#include "StaticAnalysis.h"

namespace SyntaxModel {

    Expression::Expression(const antlr4::misc::Interval& source_interval, const std::list<const SyntaxNodeBase*>& children)
        : Instruction(source_interval, children)
    {
    }

    VariableUsage::VariableUsage(const antlr4::misc::Interval& source_interval, const Identifier& name)
        : Expression(source_interval)
        , name(name)
    {
    }

    std::ostream& Expression::toString(std::ostream& os) const
    {
        os << "expression" << std::endl;
        return os;
    }

    std::ostream& VariableUsage::toString(std::ostream& os) const
    {
        os << name;
        return os;
    }

    Type VariableUsage::getExprType(const StaticAnalysis::StaticAnalyser* analyser) const
    {
        auto var = analyser->getVariableOfUsage(this);
        return *(var.type);
    }

    IR::ExecutionBlock* VariableUsage::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        StaticAnalysis::Variable var = cfg.static_analyser->getVariableOfUsage(this);
        auto stack_var = IR::ControlFlowGraph::getStackVariableFromVariable(var, this);
        if (stack_var)
            eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, stack_var.value().toAddressOperandSyntax(), dest));
        else {
            // TODO: handle globals here
        }
        return eb;
    }
}
