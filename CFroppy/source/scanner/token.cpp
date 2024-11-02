#include "token.hpp"

cfp::token::token(const tokenType _type, std::string _lexeme, std::optional<cfp::literal> _literal, const int _line)
                    : lexeme(std::move(_lexeme)), literal(std::move(_literal)) {
    type = _type;
    line = _line;
}
