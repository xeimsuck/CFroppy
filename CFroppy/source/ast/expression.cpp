#include "expression.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

scan::literal exprVisitor::visit(expr::expression &expr)  {
    return expr.accept(*this);
}


binary::binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper)
            : left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

scan::literal binary::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


grouping::grouping(std::unique_ptr<expression>&& expr) : expr(std::move(expr)) {
}


scan::literal grouping::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


literal::literal(scan::literal value) : value(std::move(value)) {
}

scan::literal literal::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


unary::unary(std::unique_ptr<expression>&& expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}

scan::literal unary::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}