#include "interpreter.hpp"
#include <iostream>
#include "runtimeError.hpp"

using namespace cfp;
using namespace cfp::interpreting;
using namespace scan::types;
using enum scan::token::tokenType;

/*!
 * @param reporter reporter
 */
interpreter::interpreter(const io::reporter& reporter) : reporter(reporter) {
}

/*!
 * @brief execute statements
 * @param stmts list of parsed statements
 */
void interpreter::interpret(const std::vector<std::unique_ptr<ast::stmt::statement>> &stmts) {
    try {
        for(decltype(auto) stmt : stmts) {
            execute(stmt);
        }
    } catch (const runtime_error& ex) {
        reporter.error(ex);
    }
}

/*!
 * @brief execute one statement
 * @param stmt statement
 */
void interpreter::execute(const std::unique_ptr<ast::stmt::statement> &stmt) {
    stmt->accept(*this);
}

/*!
 * @brief evaluate binary expressions
 * @param expr binary expression
 * @return literal
 */
scan::literal interpreter::visit(ast::expr::binary &expr) {
    const auto left = evaluate(expr.left);
    const auto right = evaluate(expr.right);

    switch (expr.oper.type) {
        case PLUS: return left+right;
        case MINUS: return left-right;
        case STAR: return left*right;
        case SLASH: return left/right;
        case GREATER: return scan::literal(left>right);
        case GREATER_EQUAL: return scan::literal(left>=right);
        case LESS: return scan::literal(left<right);
        case LESS_EQUAL: return scan::literal(left<=right);
        case EQUAL_EQUAL: return scan::literal(left==right);
        case BANG_EQUAL: return scan::literal(left!=right);
        default: return {};
    }
}

/*!
 * @brief evaluate unary expression
 */
scan::literal interpreter::visit(ast::expr::grouping &expr) {
    return evaluate(expr.expr);
}

/*!
 * @brief evaluate literal expression
 */
scan::literal interpreter::visit(ast::expr::literal &expr) {
    return expr.value;
}

/*!
 * @brief evaluate unary expression
 */
scan::literal interpreter::visit(ast::expr::unary &expr) {
    const auto right = evaluate(expr.expr);

    switch (expr.oper.type) {
        case MINUS:
            return -right;
        case BANG:
            return scan::literal(!right);
        default: return {};
    }
}

/*!
 * @brief evaluate variable expression
 */
scan::literal interpreter::visit(ast::expr::variable &expr) {
	return environment_.get(expr.name.lexeme);
}


/*!
 * @brief evaluate expression statement
 */
void interpreter::visit(ast::stmt::expression &stmt) {
    evaluate(stmt.expr);
}

/*!
 * @brief evaluate print statement
 */
void interpreter::visit(ast::stmt::print &stmt) {
    const auto literal = evaluate(stmt.expr);
    std::cout << literal.stringify() << std::endl;
}

/*!
 * @param stmt evaluate variable statement
 */
void interpreter::visit(ast::stmt::var &stmt) {
	environment_.define(stmt.name.lexeme, evaluate(stmt.initializer));
}


/*!
 * @brief evaluate expression
 */
scan::literal interpreter::evaluate(const std::unique_ptr<ast::expr::expression> &expr) {
	if(!expr) return scan::literal{}; // return nil
    return expr->accept(*this);
}