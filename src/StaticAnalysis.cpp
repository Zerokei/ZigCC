#include <iostream>
#include <unordered_map>

#include "StaticAnalysis.h"

namespace StaticAnalysis {

    Variable::Variable(const SyntaxModel::Definition& def, const size_t index)
        : def_unique_id(def.unique_id)
        , name(def.names[index])
        , type(def.type)
        , array_size((def.sizes.size() > index) ? *utils::get_at(def.sizes, index) : nullptr)
        , init_value((def.init_values.size() > index) ? *utils::get_at(def.init_values, index) : nullptr)

    {
    }

    Variable::Variable(SyntaxModel::Identifier name)

        : def_unique_id(static_cast<size_t>(-1))
        , name(name)
        , type(nullptr)
        , array_size(nullptr)
        , init_value(nullptr)
    {
    }

    StaticAnalyser::StaticAnalyser(const SyntaxModel::Program* ast)
        : _ast(ast)
    {
    }

    void StaticAnalyser::Analyse()
    {
        // Make a set of all variables, variables for which there is a usage will be removed from this set
        std::set<Variable> unused_globals = FindGlobals(_ast->definitions);

        for (const auto* func : _ast->functions) {
            DefineFunctionVariables(func);
            FindFuncVarUsages(func, unused_globals);
        }

        for (const auto& var : unused_globals)
            error<false>("Global variable '", var.name.text, "' is unused.");

        ResolveFunctionCalls();
    }

    std::set<Variable> StaticAnalyser::FindGlobals(const std::list<const SyntaxModel::Definition*>& defs)
    {
        std::set<Variable> unused_globals;
        for (const auto* def : defs) {
            // Add declaration's variables to set
            for (size_t i = 0; i < def->names.size(); ++i) {
                // We make sure we didn't already declared this variable before adding it in global variables vector
                auto var = Variable(*def, i);
                if (std::find(_global_variables.begin(), _global_variables.end(), var) != _global_variables.end())
                    error<true>("Global variable '", var.name.text, "' have already been declared.");
                _global_variables.push_back(var);
                unused_globals.insert(var);
            }

            // We search for variables usages in initialization expression
            for (const auto& init_expr : def->init_values) {
                for (const auto& var_usage : init_expr->getAllChildrenOfType<SyntaxModel::VariableUsage>())
                    ResolveVarUsage(_var_usage_resolution, var_usage, var_usage->name, unused_globals);
                for (const auto& affectation : init_expr->getAllChildrenOfType<SyntaxModel::Affectation>())
                    ResolveVarUsage(_affectation_resolution, affectation, affectation->var, unused_globals);
            }
        }
        return unused_globals;
    }

    void StaticAnalyser::DefineFunctionVariables(const SyntaxModel::Function* func)
    {
        std::vector<Variable> vars;
        vars.reserve(func->definitions.size());

        for (const auto* def : func->definitions) {
            for (size_t i = 0; i < def->names.size(); ++i) {
                auto var = Variable(*def, i);
                if (std::find(vars.begin(), vars.end(), var) != vars.end())
                    error<true>("Local variable '", var.name.text, "' have already been declared in function '", func->id.text, "'.");
                vars.push_back(var);
            }
        }
        _function_variables.emplace(func->unique_id, vars);
    }

    void StaticAnalyser::FindFuncVarUsages(const SyntaxModel::Function* func, std::set<Variable>& unused_globals)
    {
        auto* func_locals = new std::vector<Variable>((*_function_variables.find(func->unique_id)).second);
        auto* unused_locals = new std::set<Variable>(func_locals->cbegin(), func_locals->cend());

        std::list<const SyntaxModel::For*> for_loops = func->getAllChildrenOfType<SyntaxModel::For>();

        for (auto var_usage : func->getAllChildrenOfType<SyntaxModel::VariableUsage>())
            ResolveVarUsage(_var_usage_resolution, var_usage, var_usage->name, unused_globals, unused_locals, func_locals);
        for (auto affectation : func->getAllChildrenOfType<SyntaxModel::Affectation>())
            ResolveVarUsage(_affectation_resolution, affectation, affectation->var, unused_globals, unused_locals, func_locals);

        // make sure we found at least one usage for each local variable
        for (const auto& var : *unused_locals)
            error<false>("Local variable '", var.name.text, "' is unused in function '", func->id.text, "'.");
    }

    void StaticAnalyser::ResolveFunctionCalls()
    {
        // Make a set of function ids in order to accelerate function lookup
        std::unordered_map<std::string, const SyntaxModel::Function*> func_lookup_table;
        for (const auto* func : _ast->functions)
            func_lookup_table.emplace(func->id.text, func);

        // Resolve function calls
        for (const auto* usage : _ast->getAllChildrenOfType<SyntaxModel::FunctionCall>()) {
            auto it = func_lookup_table.find(usage->func_name.text);
            if (it == func_lookup_table.end())
                error<true>("Function '", usage->func_name.text, "' not declared.");
            else {
                _called_functions.insert(it->second->unique_id);
                _function_call_resolution.emplace(usage->unique_id, it->second);
            }
        }
    }

    bool StaticAnalyser::FindForLoopVarDef(const SyntaxModel::SyntaxNodeBase* var_usage, const SyntaxModel::Identifier& var_id, std::map<size_t, Variable>& var_resolution_map)
    {
        auto* parent_for_loop = var_usage->getFirstParentOfType<SyntaxModel::For>();
        if (parent_for_loop != nullptr && parent_for_loop->init != nullptr && parent_for_loop->init->is<SyntaxModel::Definition>()) {
            auto* for_init_def = dynamic_cast<const SyntaxModel::Definition*>(parent_for_loop->init);
            for (size_t i = 0; i < for_init_def->names.size(); ++i) {
                if (for_init_def->names[i].text == var_id.text) {
                    if (for_init_def->init_values.size() <= i)
                        error<true>("Can't declare variable in for loop init statement without initializing it.");
                    else {
                        var_resolution_map.emplace(var_usage->unique_id, Variable(*for_init_def, i));
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void StaticAnalyser::ResolveVarUsage(std::map<size_t, Variable>& var_resolution_map, const SyntaxModel::SyntaxNodeBase* var_usage, const SyntaxModel::Identifier& var_id, std::set<Variable>& unused_globals, std::set<Variable>* unused_locals, const std::vector<Variable>* func_locals)
    {
        Variable dummy_var(var_id);
        auto global_it = std::find(_global_variables.cbegin(), _global_variables.cend(), dummy_var);
        if (func_locals != nullptr && unused_locals != nullptr) {
            auto local_it = std::find(func_locals->cbegin(), func_locals->cend(), dummy_var);
            if (local_it != func_locals->cend()) {
                var_resolution_map.emplace(var_usage->unique_id, *local_it);
                unused_locals->erase(*local_it);
            } else {
                if (!FindForLoopVarDef(var_usage, var_id, var_resolution_map))
                    error<true>("Local variable '", var_id.text, "' not declared.");
            }
        } else if (global_it != _global_variables.cend()) {
            var_resolution_map.emplace(var_usage->unique_id, *global_it);
            unused_globals.erase(*global_it);
        } else
            error<true>("Global variable '", var_id.text, "' not declared.");
    }
}
