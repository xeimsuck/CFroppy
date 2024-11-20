#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

void break_loop::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}
