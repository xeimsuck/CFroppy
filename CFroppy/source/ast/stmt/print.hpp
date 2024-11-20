#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent print statement
	 */
	struct print final : statement {
		explicit print(std::unique_ptr<expr::expression>&& expr);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<expr::expression> expr;
	};
}