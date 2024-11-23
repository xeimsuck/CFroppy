#include "scanner.hpp"

#include <unordered_map>
#include <unordered_set>

using namespace cfp;
using namespace cfp::scan;
using enum token::tokenType;

static std::unordered_map<std::string, token::tokenType> keywords{
    {"and",     AND},
    {"class",   CLASS},
    {"else",    ELSE},
    {"false",   FALSE},
    {"for",     FOR},
    {"fn",      FN},
    {"if",      IF},
    {"nil",     NIL},
    {"or",      OR},
    {"return",  RETURN},
    {"super",   SUPER},
    {"this",    THIS},
    {"true",    TRUE},
    {"let",     LET},
    {"while",   WHILE},
    {"loop",    LOOP},
    {"break",   BREAK}
};

/*!
 * @brief just constructor
 * @param source froppy commands
 * @param reporter reference to reporter object
 */
cfp::scan::scanner::scanner(std::string source, const io::reporter& reporter)
                    : source(std::move(source)), reporter(reporter){
}



/*!
 * @brief scan source file and return tokens
 * @return all tokens
 */
std::vector<token>& scanner::getTokens() {
    if(!tokens.empty()) return tokens;

    while(!isAtEnd()) {
        scanToken();
        start = current;
    }
    tokens.emplace_back(END_OF_FILE, "", literal{}, line);

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
        case '-':
            addToken(match('=') ? MINUS_EQUAL : MINUS);
            break;
        case '+':
            addToken(match('=') ? PLUS_EQUAL : PLUS);
            break;
        case '*':
            addToken(match('=') ? STAR_EQUAL : STAR);
            break;
        case ';': addToken(SEMICOLON); break;
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
            } else if(match('*')) {
                while (!isAtEnd()) {
                    if(peek()=='*') {
                        advance();
                        if(peek()=='\0') reporter.parse_error(line, "", "Unfinished multi-line comment");
                        if(peek()=='/') {
                            advance();
                            break;
                        }
                    } else if(peek()=='\n') ++line;
                    advance();
                }
            } else {
                addToken(match('=') ? SLASH_EQUAL : SLASH);
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
            else reporter.parse_error(line, "", std::format("Unexpected character \'{}\'", ch));
            break;
    }
}


/*!
 * @brief add a token
 * @param type token type
 * @param lexeme lexeme
 * @param literal literal
 */
void scanner::addToken(const token::tokenType &type, literal literal) {
    tokens.emplace_back(type, source.substr(start, current-start), std::move(literal), line);
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
    if(isAtEnd()||source[current]!=expected) return false;
    ++current;
    return true;
}


/*!
 * @return current character or null terminator if it is at end
 */
char scanner::peek() const {
    return isAtEnd()?'\0':source[current];
}


/*!
 * @return next character or null terminator if it is at end
 */
char scanner::peekNext() const {
    if(current+1>=source.size()) return '\0';
    return source[current+1];
}



/*!
 * @brief digits are 0-9
 * @return true if ch is digit
 */
bool scanner::isDigit(const char ch) {
    return std::isdigit(ch);
}



/*!
 * @return true if ch is digit ur alphabetic
 */
bool scanner::isAlphaNumber(const char ch) {
    return isDigit(ch) || isAlpha(ch);
}



/*!
 * @brief alphabetic characters are uppercase/lowercase english letters and '_'
 * @return true if ch is alphabetic character
 */
bool scanner::isAlpha(const char ch) {
    return std::isalpha(ch)||ch=='_';
}



/*!
 * @brief add string literal token
 */
void scanner::string() {
    std::string value;
    while (!isAtEnd() && peek()!='\"') {
        if(peek()=='\n') ++line;
        else if(peek()=='\\') {
            advance();
            switch (peek()) {
                case '\\': value.push_back('\\'); break;
                case 'n': value.push_back('\n'); break;
                case 'a': value.push_back('\a'); break;
                case 'r': value.push_back('\r'); break;
                case 'v': value.push_back('\v'); break;
                case 't': value.push_back('\t'); break;
                case 'b': value.push_back('\b'); break;
                case 'f': value.push_back('\f'); break;
                case '"': value.push_back('"'); break;
                default: reporter.parse_error(line, "", std::format("Unknown escape sequence '\\{}", peek()));
            }
            advance();
        } else {
            value.push_back(advance());
        }
    }

    if(isAtEnd()) {
        reporter.parse_error(line, "", "Unterminated string");
        return;
    }

    // Closing "
    advance();

    // Add token
    addToken(STRING, literal(std::move(value)));
}



/*!
 * @brief add number literal token
 */
void scanner::number() {
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
void scanner::identifier() {
    while (isAlphaNumber(peek())) advance();

    // add token
    const auto word = source.substr(start, current-start);
    const auto type = keywords.contains(word) ? keywords[word] : IDENTIFIER;
    addToken(type);
}
