#include "scanner.hpp"

#include <unordered_map>
#include <unordered_set>

using namespace cfp;
using namespace cfp::scanner;
using enum cfp::scanner::token::tokenType;

static std::unordered_map<std::string, cfp::scanner::token::tokenType> keywords{
    {"and",    AND},
    {"class",  CLASS},
    {"else",   ELSE},
    {"false",  FALSE},
    {"for",    FOR},
    {"fun",    FUN},
    {"if",     IF},
    {"nil",    NIL},
    {"or",     OR},
    {"print",  PRINT},
    {"return", RETURN},
    {"super",  SUPER},
    {"this",   THIS},
    {"true",   TRUE},
    {"var",    VAR},
    {"while",  WHILE}
};

/*!
 * @brief just constructor
 * @param source froppy commands
 * @param reporter reference to reporter object
 */
cfp::scanner::scanner::scanner(std::string source, const io::reporter& reporter)
                    : source(std::move(source)), reporter(reporter){
}



/*!
 * @brief scan source file and return tokens
 * @return all tokens
 */
const std::vector<token>& cfp::scanner::scanner::getTokens() {
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
void cfp::scanner::scanner::scanToken() {
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
        case ' ':
        case '\t':
        case '\r': break;
        case '\n': ++line; break;
        case '\"': string(); break;
        default:
            if(isDigit(ch)) number();
            else if(isAlpha(ch)) identifier();
            else reporter.error(line, std::format("Unexpected character \'{}\'", ch));
            break;
    }
}


/*!
 * @brief add a token
 * @param type token type
 * @param lexeme lexeme
 * @param literal literal
 */
void cfp::scanner::scanner::addToken(const token::tokenType &type, const std::optional<literal> &literal) {
    tokens.emplace_back(type, source.substr(start, current-start), literal, line);
}



/*!
 * @return true if current in the end of source
 */
bool cfp::scanner::scanner::isAtEnd() const {
    return current>=source.size();
}


/*!
 * @brief return current symbol and advance it
 * @return current symbol
 */
char cfp::scanner::scanner::advance() {
    return isAtEnd()?'\0':source[current++];
}


/*!
 * @brief advance if match return true
 * @param expected expected character
 * @return true if expected equal a current character
 */
bool cfp::scanner::scanner::match(const char expected) {
    if(isAtEnd()&&source[current]!=expected) return false;
    ++current;
    return true;
}


/*!
 * @return current character or null terminator if it is at end
 */
char cfp::scanner::scanner::peek() const {
    return isAtEnd()?'\0':source[current];
}


/*!
 * @return next character or null terminator if it is at end
 */
char cfp::scanner::scanner::peekNext() const {
    if(current+1>=source.size()) return '\0';
    return source[current+1];
}



/*!
 * @brief digits are 0-9
 * @return true if ch is digit
 */
bool cfp::scanner::scanner::isDigit(const char ch) {
    return std::isdigit(ch);
}



/*!
 * @return true if ch is digit ur alphabetic
 */
bool cfp::scanner::scanner::isAlphaNumber(const char ch) {
    return isDigit(ch) || isAlpha(ch);
}



/*!
 * @brief alphabetic characters are uppercase/lowercase english letters and '_'
 * @return true if ch is alphabetic character
 */
bool cfp::scanner::scanner::isAlpha(const char ch) {
    return std::isalpha(ch)||ch=='_';
}



/*!
 * @brief add string literal token
 */
void cfp::scanner::scanner::string() {
    while (!isAtEnd() && peek()!='\"') {
        if(peek()=='\n') ++line;
        advance();
    }

    if(isAtEnd()) {
        reporter.error(line, "Unterminated string");
        return;
    }

    // Closing "
    advance();

    // Add token
    auto value = source.substr(start+1, current-start-2);
    addToken(STRING, literal(std::move(value)));
}



/*!
 * @brief add number literal token
 */
void cfp::scanner::scanner::number() {
    while (std::isdigit(peek())) advance();

    // Fractional part
    bool isFractional = false;
    if(peek()=='.'&&std::isdigit(peekNext())) {
        isFractional = true;
        advance();
        while (std::isdigit(peek())) advance();
    }

    // add token
    const auto value = source.substr(start, current-start);
    if(isFractional) addToken(NUMBER, literal(std::stod(value)));
    else addToken(NUMBER, literal(std::stoll(value)));
}


/*!
 * @brief add identifier token
 */
void cfp::scanner::scanner::identifier() {
    while (isAlphaNumber(peek())) advance();

    // add token
    const auto word = source.substr(start, current-start);
    const auto type = keywords.contains(word) ? keywords[word] : IDENTIFIER;
    addToken(type);
}
