#pragma once
#include <list>
#include <vector>

#include "IR/IR.h"
#include "SyntaxModel/Constant.h"
#include "SyntaxModel/Expression.h"
#include "SyntaxModel/Instruction.h"
#include "SyntaxModel/PrimitiveType.h"
#include "SyntaxModel/SyntaxNode.h"
#include "SyntaxModel/Type.h"

using namespace std;

namespace SyntaxModel {

    //TODO: store array size for array declarations/defintions
    struct Definition final : public SyntaxNodeBase {
        using size_constant = Constant<PrimitiveType::INT32_T>;

        Definition(const antlr4::misc::Interval& source_interval, const Type* type, const std::vector<Identifier>& names, const std::list<const Expression*>& init_values = {});
        Definition(const antlr4::misc::Interval& source_interval, const Type* type, const std::vector<Identifier>& names, const std::list<const size_constant*>& sizes, const std::list<const Expression*>& init_arrays = {});
        virtual ~Definition() = default;
        virtual std::unordered_set<std::string> getTypenames() const override { return TN<Definition>::typenames(); }
        virtual std::ostream& toString(std::ostream& os) const override;
        IR::ExecutionBlock* generateIR(IR::ControlFlowGraph& cfg, IR::ExecutionBlock* eb, const std::vector<IR::StackVariable>& stack_variables, const IR::AddTmpStackVar_fn& add_stack_variable) const;

        const Type* type;
        const std::vector<Identifier> names;
        const std::list<const Expression*> init_values;
        const std::list<const size_constant*> sizes = {};
    };
}
