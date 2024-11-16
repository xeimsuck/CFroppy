#include "statement.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

/*!
 * @param stmt statement
 */
void stmtVisitor::visit(statement& stmt) {
    stmt.accept(*this);
}


/*!
 * @param expr expression
 */
expression::expression(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 */
void expression::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param expr print expression
 */
print::print(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 */
void print::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}
