#pragma once
#include <list>

#include "SyntaxModel/Definition.h"
#include "SyntaxModel/Instruction.h"
#include "SyntaxModel/SyntaxNode.h"
#include "SyntaxModel/Type.h"

namespace SyntaxModel {

    struct Args final : public SyntaxNodeBase {
        Args(const antlr4::misc::Interval& source_interval, const std::list<const Type*>& types, const std::vector<Identifier>& names);
        virtual ~Args() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Args>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb) const;

        const std::list<const Type*> types;
        const std::vector<Identifier> names;
    };

    struct Function : public SyntaxNodeBase {
        Function(const antlr4::misc::Interval& source_interval, const std::list<const Definition*>& definitions, const std::list<const Instruction*>& instructions, const Args* arguments, const Identifier& id, const Type* returnType);
        virtual ~Function() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Function>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb) const;
        size_t getARStackSize() const;
        friend inline bool operator<(const Function& lhs, const Function& rhs) { return lhs.id < rhs.id; }

        const std::list<const Definition*> definitions;
        const std::list<const Instruction*> instructions;
        const Args* arguments;
        const Identifier id;
        const Type* returnType;
        const std::unordered_map<size_t, std::vector<IR::StackVariable>> stackVariables;

    private:
        void pullArgsFromRegisters(IR::ExecutionBlock* eb) const;
        static std::unordered_map<size_t, std::vector<IR::StackVariable>> computeARStack(const Args* args, const std::list<const Definition*>& defs);
    };

    struct Putchar final : public Function {
        Putchar();
        virtual ~Putchar() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Function, Putchar>::typenames(); }
    };
}
