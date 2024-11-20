#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param expr grouped expression
 */
grouping::grouping(std::unique_ptr<expression>&& expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal grouping::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}
