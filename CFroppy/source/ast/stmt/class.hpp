#pragma once
#include <memory>
#include "function.hpp"
#include "let.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent 'break' for loops
	 */
	struct class_ final : statement{
		class_(scan::token name, std::vector<scan::token> bases, std::vector<std::unique_ptr<function>> methods, std::vector<std::unique_ptr<let>> variables);

		void accept(stmtVisitor &visitor) override;

		scan::token name;
		std::vector<scan::token> bases;
		std::vector<std::unique_ptr<function>> methods;
		std::vector<std::unique_ptr<let>> variables;
	};
}