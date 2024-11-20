#pragma once
#include <memory>
#include "statement.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent lexical scope
	 */
	struct block final : statement {
		explicit block(std::vector<std::unique_ptr<statement>> statements);

		void accept(stmtVisitor &visitor) override;

		std::vector<std::unique_ptr<statement>> statements;
	};
}