#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param name variable name
 * @param value value
 * @param oper binary operator
 */
binary_assign::binary_assign(scan::token name, std::unique_ptr<expression>&& value, scan::token oper)
		   : value(std::move(value)), name(std::move(name)), oper(std::move(oper)){
}

/*!
 * @param visitor visitor
 */
scan::literal binary_assign::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}
