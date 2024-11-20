#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent if-else statement
	 */
	struct if_else final : statement {
		if_else(std::unique_ptr<expr::expression>&& cond, std::unique_ptr<statement>&& ifBranch,
				std::unique_ptr<statement>&& elseBranch);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<expr::expression> condition;
		std::unique_ptr<statement> ifBranch;
		std::unique_ptr<statement> elseBranch;
	};
}