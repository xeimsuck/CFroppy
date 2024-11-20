#pragma once
#include <vector>
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent call expression
	 */
	struct call final : expression {
		call(std::unique_ptr<expression>&& callee, scan::token paren, std::vector<std::unique_ptr<expression>> arguments);

		scan::literal accept(exprVisitor& visitor) override;

		std::unique_ptr<expression> callee;
		scan::token paren;
		std::vector<std::unique_ptr<expression>> arguments;
	};
}