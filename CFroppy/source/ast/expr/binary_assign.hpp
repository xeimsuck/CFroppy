#pragma once
#include "expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::expr {
	/*!
	@brief represent binary assign (+=, -= etc.)
	 */
	struct binary_assign final : expression {
		explicit binary_assign(scan::token name, std::unique_ptr<expression>&& value, scan::token oper);

		scan::literal accept(exprVisitor &visitor) override;

		std::unique_ptr<expression> value;
		scan::token name;
		scan::token oper;
	};
}