#include "stmtVisitor.hpp"

using namespace cfp;
using namespace cfp::ast;
using namespace cfp::ast::stmt;

/*!
 * @param stmt statement
 */
void stmtVisitor::visit(statement& stmt) {
	stmt.accept(*this);
}