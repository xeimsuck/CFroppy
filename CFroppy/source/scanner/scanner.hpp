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
        [[nodiscard]] bool match(char expected) const;
        bool advanceIfMatch(char expected);

    private:
        const cpf::reporter& reporter;
        std::string source;
        std::vector<token> tokens;
        int start = 0, current = 0, line = 1;
    };
}
