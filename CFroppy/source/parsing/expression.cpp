#include "expression.hpp"
#include "astVisitor.hpp"

using namespace cfp;
using namespace cfp::parse;


binary::binary(expression &left, expression &right, scan::token oper)  : left(left), right(right), oper(std::move(oper)) {
}

void binary::accept(astVisitor &visitor) {
    visitor.visit(*this);
}


void grouping::accept(astVisitor &visitor) {
    visitor.visit(*this);
}

grouping::grouping(expression &expr) : expr(expr) {
}


literal::literal(scan::literal value) : value(std::move(value)) {
}

void literal::accept(astVisitor &visitor) {
    visitor.visit(*this);
}


unary::unary(expression &expr, scan::token oper) : expr(expr), oper(std::move(oper)){
}

void unary::accept(astVisitor &visitor) {
    visitor.visit(*this);
}