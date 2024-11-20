#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent literal expression
	 */
	struct literal final : expression {
		explicit literal(scan::literal value);

		scan::literal accept(exprVisitor &visitor) override;

		scan::literal value;
	};
}