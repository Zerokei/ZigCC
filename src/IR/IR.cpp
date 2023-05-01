#include "IR/IR.h"
#include "CompilerException.h"
#include "StaticAnalysis.h"
#include "SyntaxModel/Definition.h"
#include "SyntaxModel/Function.h"

#include <fstream>

namespace IR {
    std::set<Register> Register::_registers;
    //std::array<Register, 6> Register::_ABIArgsRegisters;

    Register::Register(symbol_t name64bits, symbol_t name32bits, symbol_t name16bits, symbol_t name8bits, bool isABICallArg, bool isOwnedByCaller, bool useAsTmp, bool isExtendedReg)
        : name64bits(name64bits)
        , name32bits(name32bits)
        , name16bits(name16bits)
        , name8bits(name8bits)
        , isABICallArg(isABICallArg)
        , isOwnedByCaller(isOwnedByCaller)
        , useAsTmp(useAsTmp)
        , isExtendedReg(isExtendedReg)
    {
        _registers.insert(*this);
        //if (isABICallArg)
        //    _ABIArgsRegisters.push_back(*this);
    }

    symbol_t Register::getName(SyntaxModel::PrimitiveType size) const
    {
        switch (size) {
        case SyntaxModel::PrimitiveType::INT64_T:
            return name64bits;
        case SyntaxModel::PrimitiveType::INT32_T:
            return name32bits;
        case SyntaxModel::PrimitiveType::INT16_T:
            return name16bits;
        case SyntaxModel::PrimitiveType::CHAR:
            return name8bits;
        }
        throw new CompilerException("Huston, we have a problem!");
    }

    //std::array<Register, 6> Register::getABIArgsRegisters() { return _ABIArgsRegisters; }
    std::set<Register> Register::getRegisters() { return _registers; }
    bool Register::operator==(const Register& other) const { return other.name64bits == name64bits; };
    bool Register::operator<(const Register& other) const { return other.name64bits < name64bits; };

    const Register Register::rax("%rax", "%eax", "%ax", "%al", false, false, false);
    const Register Register::rbx("%rbx", "%ebx", "%bx", "%bl", false, true, false);
    const Register Register::rcx("%rcx", "%ecx", "%cx", "%cl", true, false, false);
    const Register Register::rdx("%rdx", "%edx", "%dx", "%dl", true, false, false);
    const Register Register::rbp("%rbp", "%ebp", "%bp", "%bpl", false, true, false);
    const Register Register::rsp("%rsp", "%esp", "%sp", "%spl", false, false, false);
    const Register Register::rsi("%rsi", "%esi", "%si", "%sil", true, false, false);
    const Register Register::rdi("%rdi", "%edi", "%di", "%dil", true, false, false);

    const Register Register::r8("%r8", "%r8d", "%r8w", "%r8b", true, false, false, true);
    const Register Register::r9("%r9", "%r9d", "%r9w", "%r9b", true, false, false, true);
    const Register Register::r10("%r10", "%r9d", "%r9w", "%r9b", false, false, true, true);
    const Register Register::r11("%r11", "%r9d", "%r9w", "%r9b", false, false, true, true);
    const Register Register::r12("%r12", "%r9d", "%r9w", "%r9b", false, true, false, true);
    const Register Register::r13("%r13", "%r9d", "%r9w", "%r9b", false, true, false, true);
    const Register Register::r14("%r14", "%r9d", "%r9w", "%r9b", false, true, false, true);
    const Register Register::r15("%r15", "%r9d", "%r9w", "%r9b", false, true, false, true);


    const symbol_t Instruction::RETQ = "retq";
    const symbol_t Instruction::PUSHQ = "pushq";
    const symbol_t Instruction::POPQ = "popq";
    const symbol_t Instruction::CALL = "callq";
    const symbol_t Instruction::MOVQ = "movq";
    const symbol_t Instruction::MOVZBQ = "movzbq";
    const symbol_t Instruction::MOVABSQ = "movabsq";
    const symbol_t Instruction::NOP = "nop";
    const symbol_t Instruction::JNE = "jne";
    const symbol_t Instruction::JE = "je";
    const symbol_t Instruction::JMP = "jmp";
    const symbol_t Instruction::CMPQ = "cmpq";
    const symbol_t Instruction::SETE = "sete";
    const symbol_t Instruction::ADDQ = "addq";
    const symbol_t Instruction::NEGQ = "negq";
    const symbol_t Instruction::IMULL = "imull";
    const symbol_t Instruction::IDIVQ = "idivq";
    const symbol_t Instruction::SUBQ = "subq";
    const symbol_t Instruction::CQO = "cqo";
    const symbol_t Instruction::SETNE = "setne";
    const symbol_t Instruction::SETL = "setl";
    const symbol_t Instruction::SETLE = "setle";
    const symbol_t Instruction::SETG = "setg";
    const symbol_t Instruction::SETGE = "setge";

    Instruction::Instruction(symbol_t op, optional<symbol_t> x, optional<symbol_t> y, optional<symbol_t> dest)
        : op(op)
        , x(x)
        , y(y)
        , dest(dest)
    {
    }

    size_t Instruction::OperandCount() const
    {
        if (x && y && dest)
            return 3;
        else if (x && y)
            return 2;
        else if (x)
            return 1;
        else if (!x && !y && !dest)
            return 0;

        throw new CompilerException("Invalid IR instruction operands.");
    }

    void Instruction::GenerateAssembly(std::ostringstream& stream) const
    {
        stream << "\t" << op;
        if (x)
            stream << " " << x.value();
        if (y)
            stream << ", " << y.value();
        if (dest)
            stream << ", " << dest.value();
        stream << std::endl;
    }

    ExecutionBlock* Instruction::divide_64bits(ExecutionBlock* eb, bool getRemainder, symbol_t x, symbol_t y, symbol_t dest)
    {
        //TODO: make sure this couldn't be simplified into using IDIV
        eb->AppendInstruction(Instruction(Instruction::MOVQ, x, Register::rax.name64bits));
        eb->AppendInstruction(Instruction(Instruction::MOVQ, y, Register::rbx.name64bits));
        eb->AppendInstruction(Instruction(Instruction::CQO));
        eb->AppendInstruction(Instruction(Instruction::IDIVQ, Register::rbx.name64bits));
        if (getRemainder)
            eb->AppendInstruction(Instruction(Instruction::MOVQ, Register::rdx.name64bits, dest));
        else
            eb->AppendInstruction(Instruction(Instruction::MOVQ, Register::rax.name64bits, dest));
        return eb;
    }

    ExecutionBlock::ExecutionBlock(const std::string& label)
        : _label(label)
    {
    }

    void ExecutionBlock::GenerateAssembly(std::ostringstream& stream, std::function<void(const Instruction&)> onInstrGeneration) const
    {
        stream << _label << ":" << std::endl;

        for (auto instr : _instructions) {
            onInstrGeneration(instr);
            instr.GenerateAssembly(stream);
        }
    }

    std::list<Instruction>::iterator ExecutionBlock::AppendInstruction(const Instruction& instr)
    {
        if(instr.x && instr.y && instr.x.value().find("(%") != std::string::npos && instr.y.value().find("(%") != std::string::npos) {
            _instructions.push_back(Instruction(Instruction::MOVQ, instr.x, Register::r10.name64bits));
            _instructions.push_back(Instruction(instr.op, Register::r10.name64bits, instr.y, instr.dest));
        } else
            _instructions.push_back(instr);
        return --_instructions.end();
    }

    void ExecutionBlock::InsertInstruction(const Instruction& instr, std::list<Instruction>::iterator instr_it) {
        if(instr.x && instr.y && instr.x.value().find("(%") != std::string::npos && instr.y.value().find("(%") != std::string::npos) {
            _instructions.insert(++instr_it, Instruction(Instruction::MOVQ, instr.x, Register::r10.name64bits));
            _instructions.insert(++instr_it, Instruction(instr.op, Register::r10.name64bits, instr.y, instr.dest));
        } else
            _instructions.insert(++instr_it, instr);
    }

    ControlFlowGraph::ControlFlowGraph(const SyntaxModel::Program* ast, const StaticAnalysis::StaticAnalyser* anaylser, const std::string& target)
        : static_analyser(anaylser)
        , _target(target)
    {
        for(const auto& reg : Register::getRegisters())
            if(reg.useAsTmp)
                _tmpRegisterUsage.emplace(reg, false);

        try {
            ast->generateIR(*this, nullptr);
            GenerateAssembly();
        } catch (const CompilerException* e) {
            std::cout << "ERROR: " << e->what() << std::endl;
        }
    }

    ControlFlowGraph::~ControlFlowGraph()
    {
        for (auto p : _blocks)
            delete p.second;
    }

    void ControlFlowGraph::GenerateAssembly()
    {
        // Generate Prolog
        std::ostringstream stream;
        stream << ".globl main" << std::endl;
        //stream << ".type main, @function" << std::endl;

        // Generate core assembly
        auto* eb = _first_block;

        while (eb != nullptr) {
            eb->GenerateAssembly(stream, [this](auto instr) {
                this->freeTmpRegisters();
            });
            eb = eb->_next_eb;
        }

        std::cout << stream.str() << std::endl;

        std::ofstream out("file.s");
        out << stream.str();
        out.close();
    }

    void ControlFlowGraph::freeTmpRegisters()
    {
        for(const auto& p : _tmpRegisterUsage)
            _tmpRegisterUsage[p.first] = false;
        _freeTmpStackVars = true;
    }

    symbol_t ControlFlowGraph::getFreeTmpRegister(SyntaxModel::PrimitiveType size, const AddTmpStackVar_fn& addTmpStackVar)
    {
        /*for(const auto& p : _tmpRegisterUsage) {
            if(!p.second) {
                auto& reg = p.first;
                _tmpRegisterUsage[reg] = true;
                return reg.getName(size);
            }
        }*/

        // We don't have free tmp register anymore, so we have to use stack
        if(addTmpStackVar) {
            symbol_t varAddressOperand = addTmpStackVar(size, _freeTmpStackVars);
            _freeTmpStackVars = false;
            return varAddressOperand;
        }
        throw new CompilerException("Can't create temporary variable (no free register and no way to create a stack variable)");
    }

    StackVariable::StackVariable(int64_t offset, size_t size, const std::string& name)
        : offset(offset)
        , size(size)
        , name(name)
    {
    }

    symbol_t StackVariable::toAddressOperandSyntax() const
    {
        return AddressOperandSyntax(Register::rbp.name64bits, offset);
    }

    std::string ControlFlowGraph::CreateLabel(std::string prefix, const SyntaxModel::SyntaxNodeBase* node)
    {
        static std::unordered_map<std::string, size_t> label_counters;

        if (node != nullptr) {
            // Append function name to label if given node is a children of a function
            auto* func = node->getFirstParentOfType<SyntaxModel::Function>();
            if (func != nullptr)
                prefix = func->id.text + "_" + prefix;
        }

        // If we already created a label with the same name, we increment its counter
        if (label_counters.find(prefix) != label_counters.end()) {
            size_t count = ++label_counters[prefix];
            prefix += "_" + std::to_string(count);
        } else
            label_counters.emplace(prefix, 0);
        return "." + prefix;
    }

    ExecutionBlock* ControlFlowGraph::CreateExecutionBlock(const std::string& label, ExecutionBlock* const eb_to_queue_on)
    {
        auto eb = _makeExecutionBlock(label);
        if (_first_block == nullptr)
            _first_block = eb;
        if (eb_to_queue_on != nullptr) {
            if (eb_to_queue_on->_next_eb != nullptr)
                throw new CompilerException("'eb_to_queue_on' execution block already have a pointer to its next block");
            eb_to_queue_on->_next_eb = eb;
        }
        return eb;
    }

    std::experimental::optional<StackVariable> ControlFlowGraph::getStackVariableFromVariable(const StaticAnalysis::Variable& var, const SyntaxModel::SyntaxNodeBase* node)
    {
        auto func = node->getFirstParentOfType<SyntaxModel::Function>();
        if (func != nullptr) {
            auto stack_defs_it = func->stackVariables.find(var.def_unique_id);
            if (stack_defs_it != func->stackVariables.end()) {
                for (const StackVariable& stack_var : stack_defs_it->second) {
                    if (stack_var.name == var.name.text)
                        return stack_var;
                }
            }
            throw new CompilerException("Couldn't find stack variable from a local variable");
        }
        return std::experimental::nullopt;
    }

    ExecutionBlock* ControlFlowGraph::_makeExecutionBlock(const std::string& label)
    {
        auto b = new ExecutionBlock(label);
        _blocks.emplace(label, b);
        return b;
    }
}
