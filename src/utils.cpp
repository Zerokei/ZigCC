#include "utils.h"

namespace utils {
    TerminalInfo::TerminalInfo(antlr4::tree::TerminalNode* terminal)
    {
        if (terminal != nullptr) {
            text = terminal->getSymbol()->getText();
            line = terminal->getSymbol()->getLine();
            column = terminal->getSymbol()->getCharPositionInLine();
        }
    }

    TerminalInfo::TerminalInfo(const std::string& text, size_t line, size_t column)
        : text(text)
        , line(line)
        , column(column)
    {
    }

    std::ostream& operator<<(std::ostream& os, const TerminalInfo& ti)
    {
        os << ti.text;
        return os;
    }
}
