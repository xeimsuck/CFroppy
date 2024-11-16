#pragma once
#include "../scanner/scanner.hpp"
#include "expression.hpp"

namespace cfp::ast {
    namespace expr {
        struct expression;
        struct binary;
        struct unary;
        struct literal;
        struct grouping;
    }

    class visitor {
    public:
        virtual ~visitor() = default;

        scan::literal visit(expr::expression& expr);

        virtual scan::literal visit(expr::binary& expr) = 0;
        virtual scan::literal visit(expr::grouping& expr) = 0;
        virtual scan::literal visit(expr::literal& expr) = 0;
        virtual scan::literal visit(expr::unary& expr) = 0;
    };
}