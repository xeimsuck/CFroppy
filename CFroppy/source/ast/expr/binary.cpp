#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param left left operand
 * @param right right operand
 * @param oper operator
 */
binary::binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper)
			: left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal binary::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}
