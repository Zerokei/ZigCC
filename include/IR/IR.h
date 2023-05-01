#pragma once
#include <array>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "SyntaxModel/PrimitiveType.h"
#include "optional.h"
#include "utils.h"

using namespace std::experimental;

namespace StaticAnalysis {
    class StaticAnalyser;
    class Variable;
}

namespace SyntaxModel {
    struct Program;
    struct Definition;
}

namespace IR {
    class ExecutionBlock;
    using symbol_t = std::string;
    using GenerateIREpilogue_fn = std::function<void(ExecutionBlock*)>;
    using AddTmpStackVar_fn = std::function<symbol_t(SyntaxModel::PrimitiveType, bool)>;

    struct Register {

        Register(symbol_t name64bits, symbol_t name32bits, symbol_t name16bits, symbol_t name8bits, bool isABICallArg, bool isOwnedByCaller, bool useAsTmp, bool isExtendedReg = false);
        symbol_t getName(SyntaxModel::PrimitiveType size) const;
        //static std::array<Register, 6> getABIArgsRegisters();
        static std::set<Register> getRegisters();
        bool operator==(const Register& other) const;
        bool operator<(const Register& other) const;

        const symbol_t name64bits;
        const symbol_t name32bits;
        const symbol_t name16bits;
        const symbol_t name8bits;
        const bool isABICallArg;
        const bool isOwnedByCaller;
        const bool useAsTmp;
        const bool isExtendedReg;

        static const Register rax, rbx, rcx, rdx, rbp, rsp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15;

    private:
        //static std::array<Register, 6> _ABIArgsRegisters;
        static std::set<Register> _registers;
    };

    struct Instruction {
        static const symbol_t RETQ;
        static const symbol_t PUSHQ;
        static const symbol_t POPQ;
        static const symbol_t CALL;
        static const symbol_t MOVQ;
        static const symbol_t MOVZBQ;
        static const symbol_t MOVABSQ;
        static const symbol_t NOP;
        static const symbol_t JNE;
        static const symbol_t JE;
        static const symbol_t JMP;
        static const symbol_t CMPQ;
        static const symbol_t SETE;
        static const symbol_t ADDQ;
        static const symbol_t NEGQ;
        static const symbol_t IMULL;
        static const symbol_t IDIVQ;
        static const symbol_t SUBQ;
        static const symbol_t CQO;
        static const symbol_t SETNE;
        static const symbol_t SETL;
        static const symbol_t SETLE;
        static const symbol_t SETG;
        static const symbol_t SETGE;

        Instruction(symbol_t op = NOP, optional<symbol_t> x = nullopt, optional<symbol_t> y = nullopt, optional<symbol_t> dest = nullopt);
        void GenerateAssembly(std::ostringstream& stream) const;
        size_t OperandCount() const;
        static ExecutionBlock* divide_64bits(ExecutionBlock* eb, bool getRemainder, symbol_t x, symbol_t y, symbol_t dest);

        const symbol_t op;
        const optional<symbol_t> x;
        const optional<symbol_t> y;
        const optional<symbol_t> dest;
    };

    class ControlFlowGraph;

    class ExecutionBlock {
    public:
        std::list<Instruction>::iterator AppendInstruction(const Instruction& instr);
        void InsertInstruction(const Instruction& instr, std::list<Instruction>::iterator instr_it);
        const std::string _label;

    private:
        void GenerateAssembly(std::ostringstream& stream, std::function<void(const Instruction&)> onInstrGeneration) const;
        ExecutionBlock(const std::string& label);
        ExecutionBlock* _next_eb = nullptr;
        std::list<Instruction> _instructions;

        friend class ControlFlowGraph;
    };

    struct StackVariable {
        StackVariable(int64_t offset, size_t size, const std::string& name);
        symbol_t toAddressOperandSyntax() const;
        const int64_t offset;
        const size_t size;
        const std::string name;
    };

    class ControlFlowGraph final {
    public:
        ControlFlowGraph(const SyntaxModel::Program* ast, const StaticAnalysis::StaticAnalyser* anaylser, const std::string& target);
        ~ControlFlowGraph();
        void GenerateAssembly();

        template <typename T>
        static inline symbol_t CreateConstant(const T& value) { return "$" + std::to_string(value); }

        std::string CreateLabel(std::string prefix, const SyntaxModel::SyntaxNodeBase* node);
        ExecutionBlock* CreateExecutionBlock(const std::string& label, ExecutionBlock* const eb_to_queue_on);
        static std::experimental::optional<StackVariable> getStackVariableFromVariable(const StaticAnalysis::Variable& var, const SyntaxModel::SyntaxNodeBase* node);
        symbol_t getFreeTmpRegister(SyntaxModel::PrimitiveType size, const AddTmpStackVar_fn& add_stack_variable);

        const StaticAnalysis::StaticAnalyser* const static_analyser;

    private:
        void freeTmpRegisters();
        ExecutionBlock* _makeExecutionBlock(const std::string& label);
        std::unordered_map<std::string, ExecutionBlock*> _blocks;
        std::map<Register, bool> _tmpRegisterUsage;
        ExecutionBlock* _first_block = nullptr;
        bool _freeTmpStackVars = false;
        const std::string& _target;
    };

    template <typename OffsetT>
    symbol_t AddressOperandSyntax(symbol_t reg, OffsetT offset = OffsetT(), symbol_t mult_offset = "")
    {
        std::stringstream st;
        if (offset == OffsetT())
            st << "(" << reg;
        else {
            if (std::is_same<OffsetT, int64_t>::value)
                st << offset << "(";
            else
                st << "(" << offset << ", ";
            st << reg;
        }
        if (mult_offset != "")
            st << ", " << mult_offset;
        st << ")";
        return st.str();
    }
}
