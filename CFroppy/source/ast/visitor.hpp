#pragma once
#include "expression.hpp"


namespace cfp::ast {
    struct expression;
    struct binary;
    struct grouping;
    struct literal;
    struct unary;

    class visitor {
    public:
        virtual ~visitor() = default;

        scan::literal visit(expression& expr);

        virtual scan::literal visit(binary& expr) = 0;
        virtual scan::literal visit(grouping& expr) = 0;
        virtual scan::literal visit(literal& expr) = 0;
        virtual scan::literal visit(unary& expr) = 0;
    };
}