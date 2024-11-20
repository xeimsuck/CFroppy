#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

call::call(std::unique_ptr<expression> &&callee, scan::token paren, std::vector<std::unique_ptr<expression> > arguments)
		: callee(std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments)){
}

scan::literal call::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}
