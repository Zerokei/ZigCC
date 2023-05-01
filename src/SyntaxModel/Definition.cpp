#include "SyntaxModel/Definition.h"
#include "utils.h"

namespace SyntaxModel {
    Definition::Definition(const antlr4::misc::Interval& source_interval, const Type* type, const std::vector<Identifier>& names, const std::list<const Expression*>& init_values)
        : SyntaxNodeBase(source_interval, utils::children_list(type, init_values))
        , type(type)
        , names(names)
        , init_values(init_values)
    {
    }

    Definition::Definition(const antlr4::misc::Interval& source_interval, const Type* type, const std::vector<Identifier>& names, const std::list<const size_constant*>& sizes, const std::list<const Expression*>& init_arrays)
        : SyntaxNodeBase(source_interval, utils::children_list(type, init_values, sizes))
        , type(type)
        , names(names)
        , init_values(init_arrays)
        , sizes(sizes)
    {
    }

    std::ostream& Definition::toString(std::ostream& os) const
    {
        os << *(type) << " ";
        int i = 0;
        for (auto name : names) {
            os << name;
            auto it = utils::get_at(init_values, i);
            if (init_values.size() && it != init_values.cend())
                os << "=" << *(*it);
            i++;
        }
        os << std::endl;
        return os;
    }

    IR::ExecutionBlock* Definition::generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, const std::vector<IR::StackVariable>& stack_variables, const IR::AddTmpStackVar_fn& add_stack_variable) const
    {
        //TODO: remove it: const auto* analyser = cfg.getAnalyser();

        // TODO: handle arrays
        if (init_values.size() > 0) {
            for (size_t i = 0; i < stack_variables.size(); ++i) {
                //TODO: Type type = expr->getExprType(analyser); (if stack variable doesn't have the same size as init expression's type, perform an implicit cast)
                eb = (*utils::get_at(init_values, i))->generateIR(cfg, eb, stack_variables[i].toAddressOperandSyntax(), add_stack_variable);
            }
        }
        return eb;
    }
}
