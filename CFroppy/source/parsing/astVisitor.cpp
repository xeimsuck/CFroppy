#include "astVisitor.hpp"

using namespace cfp;
using namespace cfp::parse;

void astVisitor::visit(expression &expr) {
    expr.accept(*this);
}