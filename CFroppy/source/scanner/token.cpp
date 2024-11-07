#include "token.hpp"

using namespace cfp;
using namespace cfp::scanner;

token::token(const tokenType type, std::string lexeme, std::optional<scanner::literal> literal, const int line)
                    : lexeme(std::move(lexeme)), literal(std::move(literal)) {
    this->type = type;
    this->line = line;
}
