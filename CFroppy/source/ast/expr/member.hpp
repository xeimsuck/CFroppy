#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent binary expression
	 */
	struct member final : expression {
		member(std::unique_ptr<expression>&& super, std::unique_ptr<expression>&& mem);

		scan::literal accept(exprVisitor& visitor) override;

		std::unique_ptr<expression> super;
		std::unique_ptr<expression> mem;
	};
}