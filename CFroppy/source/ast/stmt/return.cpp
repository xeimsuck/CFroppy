#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

return_fn::return_fn(scan::token keyword, std::unique_ptr<expr::expression> &&value)
	: keyword(std::move(keyword)), value(std::move(value)){
}

void return_fn::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}
