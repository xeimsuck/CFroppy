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

        void visit(expression& expr);
        virtual void visit(binary& expr) = 0;
        virtual void visit(grouping& expr) = 0;
        virtual void visit(literal& expr) = 0;
        virtual void visit(unary& expr) = 0;
    };
}