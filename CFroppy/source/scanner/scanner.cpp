#include "scanner.hpp"

#include <unordered_map>
#include <unordered_set>

using namespace cfp;
using enum token::tokenType;

/*!
 * @brief just constructor
 * @param source froppy commands
 * @param reporter reference to reporter object
 */
scanner::scanner(std::string source, const cpf::reporter& reporter)
                    : source(std::move(source)), reporter(reporter){
}



/*!
 * @brief scan source file and return tokens
 * @return all tokens
 */
const std::vector<token>& scanner::getTokens() {
    if(!tokens.empty()) return tokens;

    while(!isAtEnd()) {
        scanToken();
        start = current;
    }
    tokens.emplace_back(token::tokenType::END_OF_FILE, "", std::nullopt, line);

    return tokens;
}


/*!
 * @brief return token located at the current position
 * @return token
 */
void scanner::scanToken() {
    char ch = advance();

    switch (ch) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if(match('/')) {
                while (!isAtEnd() && peek()!='\n') advance();
            } else {
                addToken(SLASH);
            }
            break;
        default: reporter.error(line, std::format("Unexpected character \'{}\'", ch)); break;
    }
}


/*!
 * @brief add a token
 * @param type token type
 * @param lexeme lexeme
 * @param literal literal
 */
void scanner::addToken(const token::tokenType &type, const std::optional<literal> &literal) {
    tokens.emplace_back(type, source.substr(start, current-start), literal, line);
}



/*!
 * @return true if current in the end of source
 */
bool scanner::isAtEnd() const {
    return current>=source.size();
}


/*!
 * @brief return current symbol and advance it
 * @return current symbol
 */
char scanner::advance() {
    return isAtEnd()?'\0':source[current++];
}


/*!
 * @brief advance if match return true
 * @param expected expected character
 * @return true if expected equal a current character
 */
bool scanner::match(const char expected) {
    if(isAtEnd()&&source[current]!=expected) return false;
    ++current;
    return true;
}


/*!
 * @return current character or null terminator if it is at end
 */
char scanner::peek() const {
    return isAtEnd()?'\0':source[current];
}

