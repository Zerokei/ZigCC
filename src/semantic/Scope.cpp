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
