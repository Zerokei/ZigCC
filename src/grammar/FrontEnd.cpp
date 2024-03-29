#include "grammar/FrontEnd.h"
#include "grammar/ZigCCLexer.h"
#include "grammar/ZigCCParser.h"
#include "antlr4-runtime.h"
#include "llvm/Support/Debug.h"

using namespace antlr4;

namespace ZigCC {

void FrontEnd::parse(std::ifstream& fs) {
    // Stream it to lexer
#ifdef DEBUG
    std::cout << "# Executing lexer" << std::endl;
#endif
    ANTLRInputStream input(fs);
    ZigCCLexer lexer(&input);

    // Print tokens
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    if (lexer.getNumberOfSyntaxErrors() > 0) {
        std::cout << "Lexer errors : " << lexer.getNumberOfSyntaxErrors() << std::endl;
        return ;
    }
#ifdef DEBUG
    for (auto token : tokens.getTokens()) {
        cout << token->toString() << endl;
    }

    // Parse tokens
    std::cout << "# Parsing tokens to obtain AST" << std::endl;
#endif
    ZigCCParser parser(&tokens);
    tree::ParseTree* tree = parser.translationUnit();
#ifdef DEBUG
    cout << tree->toStringTree(&parser) << endl;
#endif
    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cout << "Parser errors : " << parser.getNumberOfSyntaxErrors() << std::endl;
        return ;
    }

    // Build syntaxic model (AST)
#ifdef DEBUG
    std::cout << "# Translate Antlr context AST to SyntaxModel AST with Visitor class" << std::endl;
#endif
    antlrcpp::Any ast = visitor.visit(tree);
}

}
