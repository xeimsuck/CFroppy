#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param expr expression
 * @return computed literal
 */
scan::literal exprVisitor::visit(expression &expr)  {
	return expr.accept(*this);
}