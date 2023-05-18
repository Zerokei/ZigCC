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
    static void emit(const std::unique_ptr<llvm::Module> &module, const std::string &filename, std::string &error)
    {
        auto targetTriple = "riscv64-unknown-linux-gnu";
        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
        if (!target) return;

        auto cpu = "generic-rv64";
        auto features = "";

        llvm::TargetOptions opt;
        auto RM = llvm::Optional<llvm::Reloc::Model>();
        auto targetMachine = target->createTargetMachine(targetTriple, cpu, features, opt, RM);

        module->setDataLayout(targetMachine->createDataLayout());
        module->setTargetTriple(targetTriple);

        std::error_code ec;
        llvm::raw_fd_ostream ir("ir.ll", ec, llvm::sys::fs::OF_None);
        module->print(ir, nullptr);
        ir.close();

        llvm::raw_fd_ostream dest(filename, ec, llvm::sys::fs::OF_None);
        if (ec) {
            error = "Could not open file: " + ec.message();
            return;
        }

        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;
        if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            error = "TargetMachine can't emit a file of this type";
            return;
        }
        pass.run(*module);
        dest.flush();
    }
};
}
