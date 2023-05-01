#include "SyntaxModel/Function.h"
#include "SyntaxModel/PrimitiveType.h"
#include "SyntaxModel/Return.h"
#include "SyntaxModel/Structure.h"
#include "utils.h"

namespace SyntaxModel {

    Args::Args(const antlr4::misc::Interval& source_interval, const std::list<const Type*>& types, const std::vector<Identifier>& names)
        : SyntaxNodeBase(source_interval, utils::container_cast(types))
        , types(types)
        , names(names)
    {
    }

    Function::Function(const antlr4::misc::Interval& source_interval, const std::list<const Definition*>& definitions, const std::list<const Instruction*>& instructions, const Args* arguments, const Identifier& id, const Type* returnType)
        : SyntaxNodeBase(source_interval, utils::children_list(definitions, instructions, arguments, returnType))
        , definitions(definitions)
        , instructions(instructions)
        , arguments(arguments)
        , id(id)
        , returnType(returnType)
        , stackVariables(computeARStack(arguments, definitions))
    {
    }

    static const antlr4::misc::Interval _dummy_interval;

    Putchar::Putchar()
        : Function(_dummy_interval, {}, {}, new Args(_dummy_interval, { new Type(_dummy_interval, PrimitiveType::INT32_T, false) }, { Identifier("character") }), Identifier("putchar"), new Type(_dummy_interval, PrimitiveType::INT32_T, false))
    {
    }

    std::ostream& Function::toString(std::ostream& os) const
    {
        if (returnType == nullptr)
            os << "void ";
        else
            os << *(returnType) << " ";
        os << id;
        os << "(";
        if (arguments != nullptr)
            os << *(arguments);
        os << ") {" << endl;
        for (auto dec : definitions)
            os << *dec;
        for (auto instr : instructions)
            os << *instr;
        os << "}" << endl;
        return os;
    }

    IR::ExecutionBlock* Function::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb) const
    {
        if (!this->is<Putchar>()) {
            eb = cfg.CreateExecutionBlock(id.text, eb);

            // Generate prologue: Reserve function stack size and update rsp and rbp registers
            size_t reservedStackSize = getARStackSize();
            eb->AppendInstruction(IR::Instruction(IR::Instruction::PUSHQ, IR::Register::rbp.name64bits));
            auto prologue_instr_it = eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, IR::Register::rsp.name64bits, IR::Register::rbp.name64bits));
            auto fill_prologue = [eb, &prologue_instr_it, &reservedStackSize, &cfg](size_t stack_size) {
                if (reservedStackSize > 0)
                    eb->InsertInstruction(IR::Instruction(IR::Instruction::SUBQ, cfg.CreateConstant(stack_size), IR::Register::rsp.name64bits), prologue_instr_it);
            };
            pullArgsFromRegisters(eb);

            IR::AddTmpStackVar_fn add_stack_variable = [&reservedStackSize](PrimitiveType size, bool freeTmpStackVars) {
                static std::vector<IR::StackVariable> tmp_stack_variable;
                static size_t used_tmp_stack_var = 0;
                if (freeTmpStackVars)
                    used_tmp_stack_var = 0;
                used_tmp_stack_var++;
                if (used_tmp_stack_var > tmp_stack_variable.size()) {
                    size_t bytesize = 8;//SyntaxModel::Type::sizeOf(size);
                    reservedStackSize += bytesize;
                    IR::StackVariable stackVar(-reservedStackSize, bytesize, "!tmp" + tmp_stack_variable.size());
                    tmp_stack_variable.push_back(stackVar);
                    return stackVar.toAddressOperandSyntax();
                } else
                    return tmp_stack_variable[used_tmp_stack_var - 1].toAddressOperandSyntax();
            };

            for (auto* def : definitions) {
                auto stack_var_it = stackVariables.find(def->unique_id);
                eb = def->generateIR(cfg, eb, stack_var_it->second, add_stack_variable);
            }

            IR::GenerateIREpilogue_fn generateIREpilogue = [&reservedStackSize, &cfg](IR::ExecutionBlock* eb) {
                if (reservedStackSize > 0)
                    eb->AppendInstruction(IR::Instruction(IR::Instruction::ADDQ, cfg.CreateConstant(reservedStackSize), IR::Register::rsp.name64bits));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::POPQ, IR::Register::rbp.name64bits));
                eb->AppendInstruction(IR::Instruction(IR::Instruction::RETQ));
            };

            for (auto* instr : instructions) {
                if (instr->is<Structure>()) {
                    auto strucure_instr = dynamic_cast<const Structure*>(instr);
                    eb = strucure_instr->generateIR(cfg, eb, nullopt, add_stack_variable, generateIREpilogue);
                } else
                    eb = instr->generateIR(cfg, eb, nullopt, add_stack_variable);
                if (instr->is<Return>()) {
                    fill_prologue(reservedStackSize);
                    generateIREpilogue(eb);
                    return eb;
                }
            }

            fill_prologue(reservedStackSize);

            // If we reach the end of eb, it means we didn't executed any main return statements (thus we return 0)
            if (id.text == "main")
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, IR::ControlFlowGraph::CreateConstant(0), IR::Register::rax.name64bits));

            // Generate epilogue
            generateIREpilogue(eb);
        }
        return eb;
    }

    size_t Function::getARStackSize() const
    {
        size_t reserved_size = (arguments != nullptr ? arguments->names.size() * 8 : 0);
        for (const auto* def : definitions)
            reserved_size += def->names.size() * 8;
        return reserved_size;
    }

    void Function::pullArgsFromRegisters(IR::ExecutionBlock* eb) const
    {
        if (arguments != nullptr) {
            std::array<std::string, 6> args_regs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
            for (size_t r_idx = 0; r_idx < arguments->names.size(); ++r_idx)
                eb->AppendInstruction(IR::Instruction(IR::Instruction::MOVQ, args_regs[r_idx], "-" + std::to_string(8 * r_idx) + "(" + IR::Register::rbp.name64bits + ")"));
        }
    }

    std::unordered_map<size_t, std::vector<IR::StackVariable>> Function::computeARStack(const Args* args, const std::list<const Definition*>& defs)
    {
        std::unordered_map<size_t, std::vector<IR::StackVariable>> stackVariables;
        int64_t offset = 0;
        for (auto* def : defs) {
            std::vector<IR::StackVariable> vars;
            vars.reserve(def->names.size());
            for (auto n : def->names) {
                offset -= 8;
                vars.emplace_back(offset, 8, n.text);
            }
            stackVariables.emplace(def->unique_id, vars);
        }
        return stackVariables;
    }

    IR::ExecutionBlock* Args::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb) const
    {
        return eb;
    }

    std::ostream& Args::toString(std::ostream& os) const
    {
        int i = 0;
        for (auto type : types) {
            os << *type << names[i];
            if (types.size() > 1)
                os << ", ";
            i++;
        }
        return os;
    }
}
