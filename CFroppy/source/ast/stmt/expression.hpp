#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent statement of expression
	 */
	struct expression final : statement {
		explicit expression(std::unique_ptr<expr::expression>&& expr);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<expr::expression> expr;
	};
}