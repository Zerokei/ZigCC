#pragma once
#include <list>
#include <string>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <set>

#include "antlr4-runtime.h"

namespace SyntaxModel {
    // forward declare SyntaxNodeBase for utils::children_list method
    class SyntaxNodeBase;
}

namespace utils {
    struct TerminalInfo {
        TerminalInfo(antlr4::tree::TerminalNode* terminal);
        TerminalInfo(const std::string& text, size_t line = 0, size_t column = 0);
        std::string text = "";
        size_t line = 0;
        size_t column = 0;
        friend inline bool operator<(const TerminalInfo& lhs, const TerminalInfo& rhs) { return lhs.text < rhs.text; }
        friend inline bool operator==(const TerminalInfo& lhs, const TerminalInfo& rhs) { return lhs.text == rhs.text; }
        friend std::ostream& operator<<(std::ostream& os, const TerminalInfo& ti);
    };

    template <class T>
    void delete_all(const std::list<T*> vect_of_pointers)
    {
        for (auto* ptr : vect_of_pointers)
            delete ptr;
    }

    template <typename Test, template <typename...> class Ref>
    struct is_specialization : std::false_type {
    };

    template <template <typename...> class Ref, typename... Args>
    struct is_specialization<Ref<Args...>, Ref> : std::true_type {
    };

    // container_cast utility from https://stackoverflow.com/questions/38304299/how-can-i-define-operators-so-that-a-array-of-user-defined-types-can-be-transfor/38304806#38304806
    template <class SourceContainer>
    class ContainerConverter {
        const SourceContainer& s_;

    public:
        explicit ContainerConverter(const SourceContainer& s)
            : s_(s)
        {
        }

        template <class TargetContainer>
        operator TargetContainer() const { return TargetContainer(s_.begin(), s_.end()); }
    };

    // container_cast utility from https://stackoverflow.com/questions/38304299/how-can-i-define-operators-so-that-a-array-of-user-defined-types-can-be-transfor/38304806#38304806
    template <class C>
    ContainerConverter<C> container_cast(const C& c) { return ContainerConverter<C>(c); }

    namespace {
        template <typename... Args>
        struct _ChildrenList;

        template <typename FirstT, typename... Args>
        struct _ChildrenList<FirstT, Args...> {
            template <typename F = FirstT>
            static inline typename std::enable_if<!is_specialization<F, std::list>::value, std::list<const SyntaxModel::SyntaxNodeBase*>>::type
            children_list(FirstT first, Args... args)
            {
                auto merged = _ChildrenList<Args...>::children_list(args...);
                merged.push_back(static_cast<const SyntaxModel::SyntaxNodeBase*>(first));
                return merged;
            }

            template <typename F = FirstT>
            static inline typename std::enable_if<is_specialization<F, std::list>::value, std::list<const SyntaxModel::SyntaxNodeBase*>>::type
            children_list(FirstT first, Args... args)
            {
                auto merged = _ChildrenList<Args...>::children_list(args...);
                merged.splice(merged.end(), container_cast(first));
                return merged;
            }
        };

        template <>
        struct _ChildrenList<> {
            static inline std::list<const SyntaxModel::SyntaxNodeBase*> children_list() { return {}; }
        };
    }

    template <typename... Args>
    std::list<const SyntaxModel::SyntaxNodeBase*> children_list(Args... args) { return _ChildrenList<Args...>::children_list(args...); }

    template <typename T>
    typename std::list<T>::const_iterator get_at(const std::list<T>& list, size_t index)
    {
        if (index < list.size()) {
            auto it = list.begin();
            std::advance(it, index);
            return it;
        }
        return list.end();
    }

    template <class T>
    std::string type_name()
    {
        typedef typename std::remove_reference<T>::type TR;
        std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                nullptr, nullptr),
#else
            nullptr,
#endif
            std::free);
        std::string r = own != nullptr ? own.get() : typeid(TR).name();
        if (std::is_const<TR>::value)
            r += " const";
        if (std::is_volatile<TR>::value)
            r += " volatile";
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
        return r;
    }
}
