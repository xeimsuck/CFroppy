#include "expression.hpp"
#include "astVisitor.hpp"

using namespace cfp;
using namespace cfp::parse;


binary::binary(std::unique_ptr<expression> left, std::unique_ptr<expression> right, scan::token oper)
            : left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

void binary::accept(astVisitor &visitor) {
    visitor.visit(*this);
}


void grouping::accept(astVisitor &visitor) {
    visitor.visit(*this);
}

grouping::grouping(std::unique_ptr<expression> expr) : expr(std::move(expr)) {
}


literal::literal(scan::literal value) : value(std::move(value)) {
}

void literal::accept(astVisitor &visitor) {
    visitor.visit(*this);
}


unary::unary(std::unique_ptr<expression> expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}

void unary::accept(astVisitor &visitor) {
    visitor.visit(*this);
}