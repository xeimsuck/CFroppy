#include "visitor.hpp"

using namespace cfp;
using namespace cfp::ast;

scan::literal visitor::visit(expression &expr)  {
    return expr.accept(*this);
}
