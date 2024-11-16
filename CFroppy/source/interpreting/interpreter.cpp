#include "interpreter.hpp"

using namespace cfp;
using namespace cfp::interpreting;
using namespace scan::types;
using enum scan::token::tokenType;

scan::literal interpreter::visit(ast::binary &expr) {
    const auto left = evaluate(expr.left);
    const auto right = evaluate(expr.right);

    switch (expr.oper.type) {
        case PLUS: return left+right;
        case MINUS: return left-right;
        case STAR: return left*right;
        case SLASH: return left/right;
        case GREATER: return scan::literal(left>right);
        case GREATER_EQUAL: return scan::literal(left>=right);
        case LESS: return scan::literal(left<right);
        case LESS_EQUAL: return scan::literal(left<=right);
        case EQUAL_EQUAL: return scan::literal(left==right);
        case BANG_EQUAL: return scan::literal(left!=right);
        default: return {};
    }
}

scan::literal interpreter::visit(ast::grouping &expr) {
    return evaluate(expr.expr);
}

scan::literal interpreter::visit(ast::literal &expr) {
    return expr.value;
}

scan::literal interpreter::visit(ast::unary &expr) {
    const auto right = evaluate(expr.expr);

    switch (expr.oper.type) {
        case MINUS:
            return -right;
        case BANG:
            return scan::literal(!right);
        default: return {};
    }
}


scan::literal interpreter::evaluate(const std::unique_ptr<ast::expression> &expr) {
    return expr->accept(*this);
}

bool interpreter::isTruthy(const scan::literal &value) {
    if(value.has<boolean>()) return value.getBoolean();
    return !value.has<nil>();
}