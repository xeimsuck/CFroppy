#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;


unary::unary(std::unique_ptr<expression>&& expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}


scan::literal unary::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}