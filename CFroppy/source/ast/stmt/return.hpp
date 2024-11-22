#pragma once
#include <memory>
#include "statement.hpp"
#include "../../token/token.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent return statement
	 */
	struct return_fn final : statement {
		return_fn(scan::token keyword, std::unique_ptr<expr::expression>&& value);

		void accept(stmtVisitor &visitor) override;

		scan::token keyword;
		std::unique_ptr<expr::expression> value;
	};
}
