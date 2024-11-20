#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

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