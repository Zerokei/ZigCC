#pragma once
#include "SyntaxModel/Instruction.h"
#include "SyntaxModel/SyntaxNode.h"
#include "SyntaxModel/Type.h"

namespace StaticAnalysis {
    class StaticAnalyser;
}

namespace SyntaxModel {
    struct Expression : public Instruction {
        Expression(const antlr4::misc::Interval& source_interval, const std::list<const SyntaxNodeBase*>& children = {});
        virtual ~Expression() = default;
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual Type getExprType(const StaticAnalysis::StaticAnalyser* analyser) const = 0;
    };

    struct VariableUsage final : public Expression {
        VariableUsage(const antlr4::misc::Interval& source_interval, const Identifier& name);
        virtual ~VariableUsage() = default;
        friend bool inline operator<(const VariableUsage& lhs, const VariableUsage& rhs) { return lhs.name < rhs.name; }
        friend inline bool operator==(const VariableUsage& lhs, const VariableUsage& rhs) { return lhs.name == rhs.name; }
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Instruction, Expression, VariableUsage>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual Type getExprType(const StaticAnalysis::StaticAnalyser* analyser) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const override;

        const Identifier name;
    };
}
