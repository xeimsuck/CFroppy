#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

block::block(std::vector<std::unique_ptr<statement>> statements) : statements(std::move(statements)){
}

void block::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}
