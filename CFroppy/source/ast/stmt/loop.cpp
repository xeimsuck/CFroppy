#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

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