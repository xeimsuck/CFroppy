#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

expression::expression(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}


void expression::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}