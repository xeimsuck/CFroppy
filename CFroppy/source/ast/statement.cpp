#include "statement.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

void stmtVisitor::visit(statement& stmt) {
    stmt.accept(*this);
}


expression::expression(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

void expression::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


print::print(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

void print::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}