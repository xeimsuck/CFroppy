#pragma once
#include <memory>
#include "statement.hpp"
#include "../expr/expression.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent 'break' for loops
	 */
	struct break_loop final : statement{
		break_loop() = default;

		void accept(stmtVisitor &visitor) override;
	};
}