#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param value literal
 */
literal::literal(scan::literal value) : value(std::move(value)) {
}


/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal literal::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}