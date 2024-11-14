#pragma once
#include "expression.hpp"


namespace cfp::parse {
    struct expression;
    struct binary;
    struct grouping;
    struct literal;
    struct unary;

    class astVisitor {
    public:
        virtual ~astVisitor() = default;

        scan::literal visit(expression& expr) {
            return expr.accept(*this);
        }

        virtual scan::literal visit(binary& expr) = 0;
        virtual scan::literal visit(grouping& expr) = 0;
        virtual scan::literal visit(literal& expr) = 0;
        virtual scan::literal visit(unary& expr) = 0;
    };
}