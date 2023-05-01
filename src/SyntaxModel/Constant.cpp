#include "SyntaxModel/Constant.h"

namespace SyntaxModel {
    ArrayConstant<PrimitiveType::CHAR>* make_array_const_from_string(const antlr4::misc::Interval& source_interval, antlr4::tree::TerminalNode* str_token)
    {
        std::string str = str_token->getSymbol()->getText();
        // TODO: remove escaping backslashs (e.g. regex "[^\\]?\\(.)|([^\\])" )
        str = str.substr(1, str.length() - 2);
        std::list<const Constant<PrimitiveType::CHAR>*> values(str.length());
        for (const auto& c : str)
            values.push_back(new Constant<PrimitiveType::CHAR>(source_interval, c));

        return new ArrayConstant<PrimitiveType::CHAR>(source_interval, values);
    }
}
