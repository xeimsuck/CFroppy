#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent variable expression
	 */
	struct variable final : expression {
		explicit variable(scan::token name);

		scan::literal accept(exprVisitor &visitor) override;

		scan::token name;
	};
}