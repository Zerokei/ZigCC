#include "SyntaxModel/SyntaxNode.h"

namespace std {
    size_t hash<SyntaxModel::SyntaxNodeBase>::operator()(const SyntaxModel::SyntaxNodeBase& obj) const
    {
        return hash<size_t>()(obj.unique_id);
    }
}

namespace SyntaxModel {
    size_t SyntaxNodeBase::_instance_count = 0;
    std::unordered_map<size_t, const SyntaxNodeBase*> SyntaxNodeBase::_parenthoods;

    SyntaxNodeBase::SyntaxNodeBase(const antlr4::misc::Interval& source_interval, const std::list<const SyntaxNodeBase*>& children)
        : source_interval(source_interval)
        , _children(_filter_nullptr_out(children))
        , unique_id(_instance_count++)
    {
        for (const auto* child : _children)
            if (child != nullptr)
                _parenthoods.emplace(child->unique_id, this);
    }

    SyntaxNodeBase::~SyntaxNodeBase()
    {
        for (const auto* child : _children) {
            if (child != nullptr) {
                _parenthoods.erase(child->unique_id);
                delete child;
            }
        }
    }

    const std::list<const SyntaxNodeBase*> SyntaxNodeBase::_filter_nullptr_out(const std::list<const SyntaxNodeBase*>& children)
    {
        std::list<const SyntaxNodeBase*> new_children;
        for (const auto* child : children) {
            if (child != nullptr)
                new_children.push_back(child);
        }
        return new_children;
    }

    bool SyntaxNodeBase::operator==(const SyntaxNodeBase& obj) const { return unique_id == obj.unique_id; }
    bool SyntaxNodeBase::operator<(const SyntaxNodeBase& obj) const { return unique_id < obj.unique_id; }

    std::ostream& operator<<(std::ostream& os, const SyntaxNodeBase& node) { return node.toString(os); }

    std::list<const SyntaxNodeBase*> SyntaxNodeBase::getAllChildren() const
    {
        std::list<const SyntaxNodeBase*> all_childrens;

        for (const auto* child : _children)
            if (child != nullptr) {
                all_childrens.push_back(child);
                for (auto val : child->getAllChildren())
                    all_childrens.push_back(val);
            }
        return all_childrens;
    }
}
