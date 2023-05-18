#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <llvm/Support/TargetSelect.h>

#include "antlr4-runtime.h"
#include "grammar/FrontEnd.h"
#include "grammar/Visitor.h"
#include "ObjectEmitter.h"
#include "JIT.h"

using namespace antlr4;

int main(int argc, char* argv[])
{
    std::string InputFile;
    std::string TargetFile = "a.o";

    // Deal with the input argument
    int InvalidArg = 0;
    int NoInputFile = 1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'o') {
                if (i == argc - 1) {
                    std::cout << "ZigCC: error: missing filename after '-o'" << std::endl;
                    InvalidArg = 1;
                }
                TargetFile = argv[++i];
            }
            else {
                std::cout << "ZigCC: error: unrecognized command line option " << argv[i] << std::endl;
                InvalidArg = 1;
            }
        } else
            InputFile = argv[i];
            NoInputFile = 0;
    }
    if (NoInputFile)
        std::cout << "ZigCC: fatal error: no input files" << std::endl;
    if (InvalidArg || NoInputFile) {
        std::cout << "compilation terminated." << std::endl;
        return EXIT_FAILURE;
    }

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    // Open source file and compile it（生成 LLVM IR）
    std::ifstream fs(InputFile);
    ZigCC::FrontEnd FE;
    if (fs.is_open()) {
        FE.parse(fs);
        fs.close();
    } else {
        std::cout << "ZigCC: error: " << InputFile << ": No such file or directory" << std::endl;
        std::cout << "compilation terminated." << std::endl;
        return EXIT_FAILURE;
    }

    // 输出并编译 LLVM IR
    std::string error;
    ZigCC::ObjectEmitter::emit(FE.visitor.module, TargetFile, error);
    if (!error.empty()) {
        llvm::errs() << error;
    }

    // JIT（动态链接库相关）
    auto jit = ZigCC::JIT::create(FE.visitor.module, FE.visitor.llvm_context);
    // 使用 registerSymbols() 函数注册需要用到的符号（Symbol），并将它们与对应的函数指针关联起来
    // 在这个例子中，将 printf 函数与字符串 "printf" 关联起来（后续可以继续添加）
    jit->registerSymbols(
        [&](llvm::orc::MangleAndInterner interner) {
            llvm::orc::SymbolMap symbolMap;
            // Add symbols here（可以动态解析这些函数）
            symbolMap[interner("printf")] = llvm::JITEvaluatedSymbol::fromPointer(printf);
            symbolMap[interner("scanf")] = llvm::JITEvaluatedSymbol::fromPointer(scanf);
            return symbolMap;
        });

    // 使用 lookup() 函数查找名为 "main" 的函数，并将其转换为一个函数指针类型（int()）。
    auto entry = jit->lookup<int()>("main");
    if (!entry) {
        llvm::errs() << entry.takeError();
    }
    entry.get()();
    return EXIT_SUCCESS;
}