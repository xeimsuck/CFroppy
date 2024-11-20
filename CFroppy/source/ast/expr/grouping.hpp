#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent grouping expression
	 */
	struct grouping final : expression {
		explicit grouping(std::unique_ptr<expression>&& expr);

		scan::literal accept(exprVisitor &visitor) override;

		std::unique_ptr<expression> expr;
	};
}