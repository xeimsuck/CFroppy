#pragma once
#include <memory>
#include "function.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent 'break' for loops
	 */
	struct class_ final : statement{
		class_(scan::token name, std::vector<std::unique_ptr<function>> methods);

		void accept(stmtVisitor &visitor) override;

		scan::token name;
		std::vector<std::unique_ptr<function>> methods;
	};
}