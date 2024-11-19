#include "statement.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

/*!
 * @param stmt statement
 */
void stmtVisitor::visit(statement& stmt) {
    stmt.accept(*this);
}


/*!
 * @param expr expression
 */
expression::expression(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 */
void expression::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param expr print expression
 */
print::print(std::unique_ptr<expr::expression> &&expr) : expr(std::move(expr)) {
}

/*!
 * @param visitor visitor
 */
void print::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param name variable
 * @param initializer value
 */
var::var(scan::token name, std::unique_ptr<expr::expression> &&initializer)
                       : name(std::move(name)), initializer(std::move(initializer)){
}

/*!
 * @param visitor visitor
 */
void var::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param statements block statements
 */
block::block(std::vector<std::unique_ptr<statement>> statements) : statements(std::move(statements)){
}

/*!
 * @param visitor visitor
 */
void block::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param cond conditional
 * @param ifBranch if conditional is true
 * @param elseBranch if conditional is false (optional)
 */
if_else::if_else(std::unique_ptr<expr::expression> &&cond, std::unique_ptr<statement> &&ifBranch, std::unique_ptr<statement> &&elseBranch)
                 : condition(std::move(cond)), ifBranch(std::move(ifBranch)), elseBranch(std::move(elseBranch)) {
}

/*!
 * @param visitor visitor
 */
void if_else::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param initializer initializer (optional)
 * @param condition conditional (optional)
 * @param increment increment (optional)
 * @param body loop body
 */
loop::loop(std::unique_ptr<statement> &&initializer, std::unique_ptr<expr::expression> &&condition,
           std::unique_ptr<expr::expression> &&increment, std::unique_ptr<statement> &&body)
     : initializer(std::move(initializer)), increment(std::move(increment)), condition(std::move(condition)), body(std::move(body)){
}


/*!
 * @param visitor visitor
 */
void loop::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}


/*!
 * @param visitor visitor
 */
void break_loop::accept(stmtVisitor &visitor) {
    visitor.visit(*this);
}
