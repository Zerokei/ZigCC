#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>

namespace ZigCC
{
enum Access {
    Public,
    Private,
    Protected
};
class ClassType {
public:
    std::unordered_map<std::string, Access> variables;
};
class Scope
{
public:
    std::unordered_map<std::string, llvm::Value *> variables;
    std::unordered_map<std::string, ClassType *> classes;
    llvm::Function *currentFunction = nullptr; // 如果是 nullptr 则说明当前是全局变量的 scope（有且仅有一个这样的 scope）
    
    Scope(llvm::Function *_currentFunction = nullptr) : currentFunction(_currentFunction) {}
    bool setVariable(const std::string &name, llvm::Value *);
    llvm::Value *getVariable(const std::string &name);
    bool setClass(const std::string &name, ClassType *classType);
    ClassType *getClass(const std::string &name);
};
}
