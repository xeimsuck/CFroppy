#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

print::print(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

void print::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}