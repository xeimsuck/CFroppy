#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;


variable::variable(scan::token name) : name(std::move(name)) {
}


scan::literal variable::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}