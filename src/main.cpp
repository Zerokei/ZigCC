#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>

#include "antlr4-runtime.h"
#include "grammar/FrontEnd.h"

using namespace antlr4;

int main(int argc, char* argv[])
{
    std::string InputFile;
    std::string TargetFile = "a.s";

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

    // Open source file and compile it
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
    
    // StaticAnalysis::StaticAnalyser* analyser = new StaticAnalysis::StaticAnalyser(program);
    // analyser->Analyse();
    // IR::ControlFlowGraph cfg = IR::ControlFlowGraph(program, analyser, TargetFile);
    
    // delete analyser;
    return EXIT_SUCCESS;
}