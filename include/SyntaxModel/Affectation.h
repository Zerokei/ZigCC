#pragma once
#include "SyntaxModel/Expression.h"
#include "SyntaxModel/SyntaxNode.h"
#include <iostream>

using namespace std;

namespace SyntaxModel {
    struct Affectation final : public Expression {
        enum class Op { EQ,
            POST_INC,
            POST_DEC,
            PRE_INC,
            PRE_DEC,
            PLUS_EQ,
            MIN_EQ,
            DIV_EQ,
            MULT_EQ,
            MODULO_EQ };

        Affectation(const antlr4::misc::Interval& source_interval, const Op op, const Identifier& var, const Expression* array_indice, const Expression* affected_value = nullptr);
        virtual ~Affectation() = default;
        friend bool inline operator<(const Affectation& lhs, const Affectation& rhs) { return lhs.var < rhs.var; }
        friend inline bool operator==(const Affectation& lhs, const Affectation& rhs) { return lhs.var == rhs.var; }
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Instruction, Expression, Affectation>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        virtual Type getExprType(const StaticAnalysis::StaticAnalyser* analyser) const override;
        virtual IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, optional<IR::symbol_t> dest, const IR::AddTmpStackVar_fn& add_stack_variable) const override;

        const Op op;
        const Identifier var;
        const Expression* array_indice;
        const Expression* affected_value;
        const bool isUnaryAffectation;
    };
}
