#pragma once
#include <memory>
#include "../scanner/token.hpp"

namespace cfp::ast::expr {
    struct expression;
    struct binary;
    struct grouping;
    struct literal;
    struct unary;

    class exprVisitor {
    public:
        virtual ~exprVisitor() = default;

        scan::literal visit(expression& expr);

        virtual scan::literal visit(binary& expr) = 0;
        virtual scan::literal visit(grouping& expr) = 0;
        virtual scan::literal visit(literal& expr) = 0;
        virtual scan::literal visit(unary& expr) = 0;
    };

    struct expression {
        virtual ~expression() = default;

        virtual scan::literal accept(exprVisitor& visitor) = 0;
    };

    struct binary final : expression {
        binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper);

        scan::literal accept(exprVisitor& visitor) override;

        std::unique_ptr<expression> left;
        std::unique_ptr<expression> right;
        scan::token oper;
    };

    struct grouping final : expression {
        explicit grouping(std::unique_ptr<expression>&& expr);

        scan::literal accept(exprVisitor &visitor) override;

        std::unique_ptr<expression> expr;
    };

    struct literal final : expression {
        explicit literal(scan::literal value);

        scan::literal accept(exprVisitor &visitor) override;

        scan::literal value;
    };

    struct unary final : expression {
        explicit unary(std::unique_ptr<expression>&& expr, scan::token oper);

        scan::literal accept(exprVisitor &visitor) override;

        std::unique_ptr<expression> expr;
        scan::token oper;
    };
}