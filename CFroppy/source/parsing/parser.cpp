#include "parser.hpp"

using namespace cfp;
using namespace cfp::parse;
using namespace cfp::scan;
using namespace cfp::ast;
using enum token::tokenType;

/*!
 * @param tokens stream of tokens (scanner output)
 * @param reporter reporter
 */
parser::parser(std::vector<token> &tokens, const io::reporter &reporter) : reporter(reporter), tokens(tokens){
}


/*!
 * @param err message
 */
parser::parse_error::parse_error(const std::string &err) : runtime_error(err) {
}


/*!
 * @brief execute a parser
 * @return root of AST
 */
std::unique_ptr<expr::expression> parser::parse() {
    try {
        return expr();
    } catch (const parse_error& err) {
        return nullptr;
    }
}


/*!
 * @return true if current token type is END_OF_FILE
 */
bool parser::isAtEnd() const {
    return peek().type==END_OF_FILE;
}


/*!
 * @brief check current type
 * @param type expected type
 * @return true if a current type same as a expected type
 */
bool parser::check(const token::tokenType type) const {
    if(isAtEnd()) return false;
    return type == peek().type;
}


/*!
 * @brief return current token and advance
 * @return current token
 */
token &parser::advance() {
    if(!isAtEnd()) ++current;
    return previous();
}


/*!
 * @brief advance if a current token is expected else throw parse_error
 * @param type expected type
 * @param msg message in parse_error
 * @return current token
 */
token &parser::consume(const token::tokenType type, const std::string &msg) {
    if(check(type)) return advance();
    throw error(peek(), msg);
}


/*!
 * @brief make a report and create parse_error
 * @param token token which has an error
 * @param msg message in parse_error
 * @return parse_error
 */
parser::parse_error parser::error(const token &token, const std::string &msg) const {
    if(token.type==END_OF_FILE) reporter.error(token.line, " at end", msg);
    else reporter.error(token.line, std::format(" at '{}'", token.lexeme), msg);
    return parse_error();
}


/*!
 * @return current token
 */
token &parser::peek() const {
    return tokens[current];
}


/*!
 * @return previously token
 */
token &parser::previous() const {
    return tokens[current-1];
}


/*!
 * @brief check expr productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::expr() {
    return equality();
}


/*!
 * @brief check equality productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::equality() {
    decltype(auto) expr = comparison();

    while (match(BANG, BANG_EQUAL)) {
        decltype(auto) oper = previous();
        decltype(auto) right = comparison();
        expr = std::make_unique<expr::binary>(std::move(expr), std::move(right), oper);
    }

    return expr;
}


/*!
 * @brief check comparision productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::comparison() {
    decltype(auto) expr = term();

    while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
        decltype(auto) oper = previous();
        decltype(auto) right = term();
        expr = std::make_unique<expr::binary>(std::move(expr), std::move(right), oper);
    }

    return expr;
}


/*!
 * @brief check term productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::term() {
    decltype(auto) expr = factor();

    while (match(PLUS, MINUS)) {
        decltype(auto) oper = previous();
        decltype(auto) right = factor();
        expr = std::make_unique<expr::binary>(std::move(expr), std::move(right), oper);
    }

    return expr;
}


/*!
 * @brief check factor productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::factor() {
    decltype(auto) expr = unary();

    while (match(STAR, SLASH)) {
        decltype(auto) oper = previous();
        decltype(auto) right = unary();
        expr = std::make_unique<expr::binary>(std::move(expr), std::move(right), oper);
    }

    return expr;
}


/*!
 * @brief check unary productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::unary() {
    if(match(BANG, MINUS)) {
        decltype(auto) oper = previous();
        return  std::make_unique<expr::unary>(primary(), oper);
    }

    return primary();
}


/*!
 * @brief check primary productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::primary() {
    if(match(TRUE)) return std::make_unique<expr::literal>(literal{true});
    if(match(FALSE)) return std::make_unique<expr::literal>(literal{false});
    if(match(NIL)) return std::make_unique<expr::literal>(literal{});

    if(match(NUMBER, STRING)) {
        return std::make_unique<expr::literal>(previous().literal);
    }

    if(match(LEFT_PAREN)) {
        auto expr = std::make_unique<expr::grouping>(this->expr());
        consume(RIGHT_PAREN, "Expect \')\' after expression.");
        return expr;
    }

    throw error(peek(), "Expect expression.");
}


/*!
 * @brief synchronize in panic mode
 */
void parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == SEMICOLON) return;

        switch (peek().type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
              return;
          default: continue;
        }
        advance();
    }
}
