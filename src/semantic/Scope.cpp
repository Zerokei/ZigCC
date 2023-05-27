#include "semantic/Scope.h"

using namespace ZigCC;

bool Scope::setVariable(const std::string &name, llvm::Value *value)
{
    if (this->variables.find(name) != this->variables.end()) {
        return false;
    }
    this->variables[name] = value;
    return true;
}

llvm::Value *Scope::getVariable(const std::string &name)
{
    try {
        return this->variables.at(name);
    } catch (std::out_of_range) {
        return nullptr;
    }
}

bool Scope::setClass(const std::string &name, ClassType *classType, llvm::Type *type)
{
    for (auto &pair : this->classes) {
        if (std::get<0>(pair) == name) {
            return false;
        }
    }
    this->classes.push_back(std::make_tuple(name, classType, type));
    return true;
}

ClassType *Scope::getClass(const std::string &name)
{
    
    for (auto &pair : this->classes) {
        if (std::get<0>(pair) == name) {
            return std::get<1>(pair);
        }
    }
    return nullptr;
}