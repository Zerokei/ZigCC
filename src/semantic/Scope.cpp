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

bool Scope::setClass(const std::string &name, ClassType *classType)
{
    for (auto &pair : this->classes) {
        if (pair.first == name) {
            return false;
        }
    }
    this->classes.push_back(std::make_pair(name, classType));
    return true;
}

ClassType *Scope::getClass(const std::string &name)
{
    
    for (auto &pair : this->classes) {
        if (pair.first == name) {
            return pair.second;
        }
    }
    return nullptr;
}