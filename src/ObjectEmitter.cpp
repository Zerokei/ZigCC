#include "ObjectEmitter.h"
#include <cstdlib>

void ZigCC::ObjectEmitter::emit(const std::unique_ptr<llvm::Module> &module, const std::string &filename, std::string &error)
{
    auto targetTriple = "riscv64-unknown-linux-gnu";
    // auto targetTriple = llvm::sys::getDefaultTargetTriple();
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    if (!target) return;

    auto cpu = "generic-rv64";
    // auto cpu = "generic";
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
    std::system("clang -target riscv64-unknown-linux-gnu -march=rv64g -c ir.ll -o a.o");
    std::system("riscv64-linux-gnu-gcc -no-pie a.o");
    std::system("rm a.o"); 
}
