#pragma once
#include <string>
#include <vector>
#include "../token/token.hpp"
#include "../io/reporter.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::scan {
    /*!
    @brief translate source to the flow of tokens
     */
    class scanner {
    public:
        explicit scanner(std::string source, const io::reporter& reporter);
        std::vector<token>& getTokens();
    private:
        void scanToken();
        void addToken(const token::tokenType& type, scan::literal literal = scan::literal{});
        [[nodiscard]] bool isAtEnd() const;

        char advance();
        [[nodiscard]] char peek() const;
        [[nodiscard]] char peekNext() const;
        bool match(char expected);

        static bool isDigit(char ch);
        static bool isAlpha(char ch);
        static bool isAlphaNumber(char ch);

        void string();
        void number();
        void identifier();

    private:
        const io::reporter& reporter;
        std::string source;
        std::vector<token> tokens;
        int start = 0, current = 0, line = 1;
    };
}