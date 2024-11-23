#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

class_::class_(scan::token name, std::vector<std::unique_ptr<function>> methods, std::vector<std::unique_ptr<let>> variables)
	: name(std::move(name)), methods(std::move(methods)), variables(std::move(variables)){
}

void class_::accept(stmtVisitor &visitor) {
	visitor.visit(*this);
}
