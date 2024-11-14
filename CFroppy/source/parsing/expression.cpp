#include "expression.hpp"
#include "astVisitor.hpp"

using namespace cfp;
using namespace cfp::parse;


binary::binary(std::unique_ptr<expression> left, std::unique_ptr<expression> right, scan::token oper)
            : left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

scan::literal binary::accept(astVisitor &visitor) {
    return visitor.visit(*this);
}


scan::literal grouping::accept(astVisitor &visitor) {
    return visitor.visit(*this);
}

grouping::grouping(std::unique_ptr<expression> expr) : expr(std::move(expr)) {
}


literal::literal(scan::literal value) : value(std::move(value)) {
}

scan::literal literal::accept(astVisitor &visitor) {
    return visitor.visit(*this);
}


unary::unary(std::unique_ptr<expression> expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}

scan::literal unary::accept(astVisitor &visitor) {
    return visitor.visit(*this);
}