#include "expression.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;

/*!
 * @param expr expression
 * @return computed literal
 */
scan::literal exprVisitor::visit(expression &expr)  {
    return expr.accept(*this);
}


/*!
 * @param left left operand
 * @param right right operand
 * @param oper operator
 */
binary::binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper)
            : left(std::move(left)), right(std::move(right)), oper(std::move(oper)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal binary::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


/*!
 * @param expr grouped expression
 */
grouping::grouping(std::unique_ptr<expression>&& expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal grouping::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


/*!
 * @param value literal
 */
literal::literal(scan::literal value) : value(std::move(value)) {
}


/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal literal::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


/*!
 * @param expr operand
 * @param oper operator
 */
unary::unary(std::unique_ptr<expression>&& expr, scan::token oper) : expr(std::move(expr)), oper(std::move(oper)){
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal unary::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


/*!
 * @param name variable name
 */
variable::variable(scan::token name) : name(std::move(name)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal variable::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}


/*!
 * @param name variable name
 * @param value new value
 */
assign::assign(scan::token name, std::unique_ptr<expression> &&value)
                  : value(std::move(value)), name(std::move(name)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal assign::accept(exprVisitor &visitor) {
    return visitor.visit(*this);
}
