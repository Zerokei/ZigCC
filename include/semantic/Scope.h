#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>

namespace ZigCC
{
class Scope
{
public:
    std::unordered_map<std::string, llvm::Value *> variables;
    std::unordered_map<std::string, llvm::Value *> classes;
    llvm::Function *currentFunction = nullptr; // 如果是 nullptr 则说明当前是全局变量的 scope（有且仅有一个这样的 scope）
    
    Scope(llvm::Function *_currentFunction = nullptr) : currentFunction(_currentFunction) {}
    bool setVariable(const std::string &name, llvm::Value *);
    llvm::Value *getVariable(const std::string &name);
};
}
