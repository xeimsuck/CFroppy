#include "expression.hpp"
#include "visitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

binary::binary(std::unique_ptr<expression> left, std::unique_ptr<expression> right, scan::token oper)
            : left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

scan::literal binary::accept(visitor &visitor) {
    return visitor.visit(*this);
}


scan::literal grouping::accept(visitor &visitor) {
    return visitor.visit(*this);
}

grouping::grouping(std::unique_ptr<expression> expr) : expr(std::move(expr)) {
}


literal::literal(scan::literal value) : value(std::move(value)) {
}

scan::literal literal::accept(visitor &visitor) {
    return visitor.visit(*this);
}


unary::unary(std::unique_ptr<expression> expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}

scan::literal unary::accept(visitor &visitor) {
    return visitor.visit(*this);
}