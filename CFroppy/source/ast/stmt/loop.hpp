#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent loop
	 */
	struct loop final : statement {
		loop(std::unique_ptr<statement>&& initializer, std::unique_ptr<expr::expression>&& condition,
			 std::unique_ptr<expr::expression>&& increment, std::unique_ptr<statement>&& body);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<statement> initializer;
		std::unique_ptr<expr::expression> increment;
		std::unique_ptr<expr::expression> condition;
		std::unique_ptr<statement> body;
	};
}