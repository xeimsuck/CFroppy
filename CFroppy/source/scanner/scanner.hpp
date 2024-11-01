#pragma once

#include <string>
#include <vector>
#include "token.hpp"

namespace cfp {
    class scanner {
    public:
        explicit scanner(std::string source);
        std::vector<token> scanTokens();
    private:
        std::string source;
    };
}
