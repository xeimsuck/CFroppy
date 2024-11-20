#pragma once
#include "expression.hpp"
#include "binary.hpp"
#include "literal.hpp"
#include "grouping.hpp"
#include "unary.hpp"
#include "variable.hpp"
#include "assign.hpp"
#include "binary_assign.hpp"
#include "logical.hpp"


namespace cfp::ast::expr {
	/*!
	@brief realize visitor pattern for expressions
	 */
	struct exprVisitor {
		virtual ~exprVisitor() = default;

		scan::literal visit(expression& expr);

		virtual scan::literal visit(binary& expr) = 0;
		virtual scan::literal visit(grouping& expr) = 0;
		virtual scan::literal visit(literal& expr) = 0;
		virtual scan::literal visit(unary& expr) = 0;
		virtual scan::literal visit(variable& expr) = 0;
		virtual scan::literal visit(assign& expr) = 0;
		virtual scan::literal visit(binary_assign& expr) = 0;
		virtual scan::literal visit(logical& expr) = 0;
	};
}