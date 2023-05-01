#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>

#include "antlr4-runtime.h"
#include "IR/IR.h"
#include "StaticAnalysis.h"
#include "SyntaxModel/SyntaxModel.h"
#include "Visitor.h"
#include "grammar/ZigCCLexer.h"
#include "grammar/ZigCCParser.h"
#include "grammar/ZigCCParserBaseVisitor.h"

using namespace antlr4;
using namespace antlrcpptest;

const SyntaxModel::Program* Parse(ifstream& fs)
{
    // Stream it to lexer
#ifdef DEBUG
    cout << "# Executing lexer" << endl;
#endif
    ANTLRInputStream input(fs);
    ZigCCLexer lexer(&input);

    // Print tokens
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    if (lexer.getNumberOfSyntaxErrors() > 0) {
        cout << "Lexer errors : " << lexer.getNumberOfSyntaxErrors() << endl;
        return nullptr;
    }
#ifdef DEBUG
    for (auto token : tokens.getTokens()) {
        cout << token->toString() << endl;
    }

    // Parse tokens
    cout << "# Parsing tokens to obtain AST" << endl;
#endif
    ZigCCParser parser(&tokens);
    tree::ParseTree* tree = parser.translationUnit();
#ifdef DEBUG
    cout << tree->toStringTree(&parser) << endl;
#endif
    if (parser.getNumberOfSyntaxErrors() > 0) {
        cout << "Parser errors : " << parser.getNumberOfSyntaxErrors() << endl;
        return nullptr;
    }

    // Build syntaxic model (AST)
#ifdef DEBUG
    cout << "# Translate Antlr context AST to SyntaxModel AST with Visitor class" << endl;
#endif
    Visitor v;
    antlrcpp::Any ast = v.visit(tree);
    if (ast.is<SyntaxModel::Program*>()) {
        auto prog = ast.as<SyntaxModel::Program*>();
#ifdef DEBUG
        cout << *prog << endl;
#endif
        return prog;
    }
    return nullptr;
}

const StaticAnalysis::StaticAnalyser* StaticAnalysis(const SyntaxModel::Program* ast)
{
    cout << "# Solve variable scopes and run static analysis" << endl;
    auto analyser = new StaticAnalysis::StaticAnalyser(ast);
    analyser->Analyse();
    return analyser;
}

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
    const SyntaxModel::Program* program;
    if (fs.is_open()) {
        program = Parse(fs);
        if (program == nullptr)
            return EXIT_FAILURE;
        fs.close();
    } else {
        std::cout << "ZigCC: error: " << InputFile << ": No such file or directory" << std::endl;
        std::cout << "compilation terminated." << std::endl;
        return EXIT_FAILURE;
    }
    const StaticAnalysis::StaticAnalyser * analyser = StaticAnalysis(program);
    IR::ControlFlowGraph cfg = IR::ControlFlowGraph(program, analyser, TargetFile);
    
    delete analyser;
    delete program;
    return EXIT_SUCCESS;
}
