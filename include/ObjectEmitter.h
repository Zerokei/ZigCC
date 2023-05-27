#pragma once

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

namespace ZigCC
{
class ObjectEmitter
{
public:
    static void emit(const std::unique_ptr<llvm::Module> &module, const std::string &filename, std::string &error);
};
}
