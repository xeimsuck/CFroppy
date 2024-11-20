#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent binary expression
	 */
	struct binary final : expression {
		binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper);

		scan::literal accept(exprVisitor& visitor) override;

		std::unique_ptr<expression> left;
		std::unique_ptr<expression> right;
		scan::token oper;
	};
}