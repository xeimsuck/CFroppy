#pragma once
#include <memory>
#include "statement.hpp"
#include "../../token/token.hpp"

namespace cfp::ast::stmt {
	/*!
	@brief represent function statement
	 */
	struct function final : statement {
		function(scan::token name, std::vector<scan::token> params, std::vector<std::unique_ptr<statement>> body);

		void accept(stmtVisitor &visitor) override;

		scan::token name;
		std::vector<scan::token> params;
		std::vector<std::unique_ptr<statement>> body;
	};
}
