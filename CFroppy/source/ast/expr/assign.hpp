#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent assign expression
	 */
	struct assign final : expression {
		explicit assign(scan::token name, std::unique_ptr<expression>&& value);

		scan::literal accept(exprVisitor &visitor) override;

		std::unique_ptr<expression> value;
		scan::token name;
	};
}