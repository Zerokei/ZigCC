#pragma once

#include "grammar/Visitor.h"
namespace ZigCC {

class FrontEnd {
public:
    Visitor visitor;

    // Parse an input stream and return an AST.
    void parse(std::ifstream& fs);
};

}
