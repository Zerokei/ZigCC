#pragma once

namespace ZigCC {

class FrontEnd {
public:
    // Parse an input stream and return an AST.
    void parse(std::ifstream& fs);
};

}
