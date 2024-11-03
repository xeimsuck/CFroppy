#pragma once
#include <string>
#include <vector>
#include "token.hpp"
#include "../io/reporter.hpp"

namespace cfp {
    class scanner {
    public:
        explicit scanner(std::string source, const cpf::reporter& reporter);
        const std::vector<token>& getTokens();
    private:
        void scanToken();
        void addToken(const token::tokenType& type, const std::optional<literal>& literal = std::nullopt);
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
        const cpf::reporter& reporter;
        std::string source;
        std::vector<token> tokens;
        int start = 0, current = 0, line = 1;
    };
}
