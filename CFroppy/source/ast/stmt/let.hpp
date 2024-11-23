#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent var initialization
	 */
	struct let final : statement {
		explicit let(scan::token name, std::unique_ptr<expr::expression>&& initializer);

		void accept(stmtVisitor &visitor) override;

		scan::token name;
		std::unique_ptr<expr::expression> initializer;
	};
}