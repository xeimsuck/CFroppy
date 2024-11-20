#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent unary expression
	 */
	struct unary final : expression {
		explicit unary(std::unique_ptr<expression>&& expr, scan::token oper);

		scan::literal accept(exprVisitor &visitor) override;

		std::unique_ptr<expression> expr;
		scan::token oper;
	};
}