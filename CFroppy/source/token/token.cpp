#include "token.hpp"

using namespace cfp;
using namespace cfp::scan;

token::token(const tokenType type, std::string lexeme, scan::literal literal, const int line)
                    : lexeme(std::move(lexeme)), literal(std::move(literal)) {
    this->type = type;
    this->line = line;
}
