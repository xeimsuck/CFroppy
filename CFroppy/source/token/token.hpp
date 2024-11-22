#pragma once
#include <optional>
#include <string>
#include "literal.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::scan {
    /*!
    @brief represent token
     */
    struct token {
        enum class tokenType {
            // Single-character tokens.
            LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
            COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

            // One or two character tokens.
            BANG, BANG_EQUAL,
            EQUAL, EQUAL_EQUAL,
            GREATER, GREATER_EQUAL,
            LESS, LESS_EQUAL,
            PLUS_EQUAL, MINUS_EQUAL,
            STAR_EQUAL, SLASH_EQUAL,

            // Literals.
            IDENTIFIER, STRING, NUMBER,

            // Keywords.
            AND, CLASS, ELSE, FALSE, FN, FOR, IF, NIL, OR,
            RETURN, SUPER, THIS, TRUE, LET, WHILE, BREAK, LOOP,

            END_OF_FILE
        };

        tokenType type;
        std::string lexeme;
        scan::literal literal;
        int line;

        token(tokenType type, std::string lexeme, scan::literal literal, int line);
    };
}
