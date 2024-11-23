#include "exprVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::expr;


/*!
 * @param super im so fucking tired
 * @param mem sorry
 */
member::member(std::unique_ptr<expression>&& super, std::unique_ptr<expression>&& mem)
			: super(std::move(super)), mem(std::move(mem)) {
}

/*!
 * @param visitor visitor
 * @return computed literal
 */
scan::literal member::accept(exprVisitor &visitor) {
	return visitor.visit(*this);
}
