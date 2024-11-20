#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param name variable name
 * @param value new value
 */
assign::assign(scan::token name, std::unique_ptr<expression> &&value)
				  : value(std::move(value)), name(std::move(name)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal assign::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}