#pragma once
#include <functional>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

#include "CompilerException.h"
#include "IR/IR.h"
#include "antlr4-runtime.h"
#include "utils.h"
#include "optional.h"

using namespace std::experimental;

namespace SyntaxModel {
    // forward declare SyntaxNodeBase for std::hash specialization
    class SyntaxNodeBase;
}

namespace IR {
    class ControlFlowGraph;
}

namespace std {
    template <>
    struct hash<SyntaxModel::SyntaxNodeBase> {
        size_t operator()(const SyntaxModel::SyntaxNodeBase& obj) const;
    };
}

namespace SyntaxModel {
    using Identifier = utils::TerminalInfo;
    using Include = utils::TerminalInfo;

    class SyntaxNodeBase {
    public:
        static size_t _instance_count;
        SyntaxNodeBase(const antlr4::misc::Interval& source_interval, const std::list<const SyntaxNodeBase*>& children = std::list<const SyntaxNodeBase*>());
        virtual ~SyntaxNodeBase();

        bool operator==(const SyntaxNodeBase& obj) const;
        bool operator<(const SyntaxNodeBase& obj) const;
        friend std::ostream& operator<<(std::ostream& os, const SyntaxNodeBase& node);

        template <typename T>
        bool is() const
        {
            static const std::string type_name = utils::type_name<T>();
            auto types = getTypenames();
            return types.find(type_name) != types.end();
        }

        template <typename T>
        const T* getFirstParentOfType() const
        {
            auto parent_it = _parenthoods.find(unique_id);
            while (parent_it != _parenthoods.end()) {
                const auto* parent = (*parent_it).second;
                if (parent->is<T>())
                    return dynamic_cast<const T*>(parent);
                parent_it = _parenthoods.find(parent->unique_id);
            }
            return nullptr;
        }

        const SyntaxNodeBase* getParent() const
        {
            auto parent_it = _parenthoods.find(unique_id);
            if (parent_it != _parenthoods.end())
                return (*parent_it).second;
            return nullptr;
        }

        // Returns all children syntaxic elements recursively
        std::list<const SyntaxNodeBase*>
        getAllChildren() const;

        // Returns an list of all children syntaxic elements recursively for which T is their final type (doesn't handle base classes)
        template <typename T>
        std::list<const T*> getAllChildrenOfType() const
        {
            std::list<const T*> all_childrens;

            for (const auto* child : _children)
                if (child != nullptr) {
                    if (child->is<T>())
                        all_childrens.push_back(dynamic_cast<const T*>(child));

                    for (const T* val : child->getAllChildrenOfType<T>())
                        all_childrens.push_back(val);
                }
            return all_childrens;
        }

        const antlr4::misc::Interval source_interval;
        const std::list<const SyntaxNodeBase*> _children;
        const size_t unique_id;

    protected:
        virtual std::unordered_set<std::string> getTypenames() const = 0;
        virtual std::ostream& toString(std::ostream& os) const = 0;

    private:
        static const std::list<const SyntaxNodeBase*> _filter_nullptr_out(const std::list<const SyntaxNodeBase*>& children);
        friend size_t std::hash<SyntaxNodeBase>::operator()(const SyntaxNodeBase&) const;
        static std::unordered_map<size_t, const SyntaxNodeBase*> _parenthoods;
    };

    template <typename... Types>
    struct TN;

    template <typename FirstT, typename... OtherTs>
    struct TN<FirstT, OtherTs...> {
        static inline std::unordered_set<std::string> typenames()
        {
            static const std::string type_name = utils::type_name<FirstT>();
            std::unordered_set<std::string> types(TN<OtherTs...>::typenames());
            types.insert(type_name);
            return types;
        }
    };

    template <>
    struct TN<> {
        static inline std::unordered_set<std::string> typenames() { return { utils::type_name<SyntaxNodeBase>() }; }
    };
}
