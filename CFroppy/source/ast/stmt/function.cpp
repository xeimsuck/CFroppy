#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

function::function(scan::token name, std::vector<scan::token> params, std::vector<std::unique_ptr<statement>> body)
	: name(std::move(name)), params(std::move(params)), body(std::move(body)){
}

void function::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}

