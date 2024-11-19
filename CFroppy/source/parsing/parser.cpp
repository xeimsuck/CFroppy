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
std::vector<std::unique_ptr<stmt::statement>> parser::parse() {
    std::vector<std::unique_ptr<stmt::statement>> statements;
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
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
 * @brief parse expr productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::expr() {
    return assignment();
}


/*!
 * @brief parse assignment production
 * @return expression
 */
std::unique_ptr<expr::expression> parser::assignment() {
	auto expr = logical_or();

	if(match(EQUAL)) {
		decltype(auto) equals = previous();
		auto value = this->expr();

		if(const auto var = dynamic_cast<expr::variable*>(expr.get())) {
			return std::make_unique<expr::assign>(var->name, std::move(value));
		}

		throw error(equals, "Invalid assignment target.");
	}

	return expr;
}


/*!
 * @brief parse logical_or production
 * @return expression
 */
std::unique_ptr<expr::expression> parser::logical_or() {
	auto expr = logical_and();

	if(match(OR)) {
		const auto& oper = previous();
		auto right = logical_and();
		return std::make_unique<expr::logical>(std::move(expr), std::move(right), oper);
	}

	return expr;
}


/*!
 * @brief parse logical_and production
 * @return expression
 */
std::unique_ptr<expr::expression> parser::logical_and() {
	auto expr = equality();

	if(match(AND)) {
		const auto& oper = previous();
		auto right = equality();
		return std::make_unique<expr::logical>(std::move(expr), std::move(right), oper);
	}

	return expr;
}


/*!
 * @brief parse equality productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::equality() {
    decltype(auto) expr = comparison();

    while (match(EQUAL_EQUAL, BANG_EQUAL)) {
        decltype(auto) oper = previous();
        decltype(auto) right = comparison();
        expr = std::make_unique<expr::binary>(std::move(expr), std::move(right), oper);
    }

    return expr;
}


/*!
 * @brief parse comparison productions
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
 * @brief parse term productions
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
 * @brief parse factor productions
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
 * @brief parse unary productions
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
 * @brief parse primary productions
 * @return expression
 */
std::unique_ptr<expr::expression> parser::primary() {
    if(match(TRUE)) return std::make_unique<expr::literal>(literal{true});
    if(match(FALSE)) return std::make_unique<expr::literal>(literal{false});
    if(match(NIL)) return std::make_unique<expr::literal>(literal{});

    if(match(NUMBER, STRING)) {
        return std::make_unique<expr::literal>(previous().literal);
    }

	if(match(IDENTIFIER)) {
		return std::make_unique<expr::variable>(previous());
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
          default: break;
        }

        advance();
    }
}


/*!
 * @brief parse current declaration
 * @return declaration statement
 */
std::unique_ptr<stmt::statement> parser::declaration() {
	try {
		if(match(VAR)) {
			return varDeclaration();
		}
		return statement();
	} catch (const parse_error& ex) {
		synchronize();
		return nullptr;
	}
}


/*!
 * @brief parse variable declaration
 * @return variable declaration statement
 */
std::unique_ptr<stmt::var> parser::varDeclaration() {
	token name = consume(IDENTIFIER, "Expect variable name.");

	std::unique_ptr<expr::expression> initializer;
	if(match(EQUAL)) {
		initializer = expr();
	}

	consume(SEMICOLON, "Expect ; after variable declaration.");

	return std::make_unique<stmt::var>(std::move(name), std::move(initializer));
}


/*!
 * @brief parse a current block (lexical scope)
 * @return block
 */
std::unique_ptr<stmt::block> parser::block() {
	std::vector<std::unique_ptr<stmt::statement>> statements;

	while (!check(RIGHT_BRACE) && !isAtEnd()) {
		statements.push_back(declaration());
	}

	consume(RIGHT_BRACE, "Expect '}' after block.");

	return std::make_unique<stmt::block>(std::move(statements));
}



/*!
 * @brief parse a current statement
 * @return statement
 */
std::unique_ptr<stmt::statement> parser::statement() {
    if(match(PRINT)) return printStatement();
	if(match(LEFT_BRACE)) return block();
	if(match(IF)) return ifStatement();
    return expressionStatement();
}


/*!
 * @brief parse print statement
 * @return print statement
 */
std::unique_ptr<stmt::print> parser::printStatement() {
    decltype(auto) expr = this->expr();
    consume(SEMICOLON, "Expect ; after expression.");
    return std::make_unique<stmt::print>(std::move(expr));
}

/*!
 * @brief parse expression statement
 * @return expression statement
 */
std::unique_ptr<stmt::expression> parser::expressionStatement() {
    decltype(auto) expr = this->expr();
    consume(SEMICOLON, "Expect ; after expression.");
    return std::make_unique<stmt::expression>(std::move(expr));
}


/*!
 * @brief parse if-else statement
 * @return if-else statement
 */
std::unique_ptr<stmt::if_else> parser::ifStatement() {
	consume(LEFT_PAREN, "Expect '(' after 'if'.");
	auto conditional = expr();
	consume(RIGHT_PAREN, "Expect ')' after 'if'.");

	auto ifBranch = statement();
	std::unique_ptr<stmt::statement> elseBranch = nullptr;
	if(match(ELSE)) {
		elseBranch = statement();
	}

	return std::make_unique<stmt::if_else>(std::move(conditional), std::move(ifBranch), std::move(elseBranch));
}
