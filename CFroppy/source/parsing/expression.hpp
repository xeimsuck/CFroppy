#pragma once
#include "../scanner/token.hpp"

namespace cfp::parse {
    class ASTVisitor;

    struct expression {
        virtual ~expression() = default;

        virtual void accept(ASTVisitor& visitor) = 0;
    };

    struct binary final : expression {
        binary(expression& left, expression& right, scan::token oper);

        void accept(ASTVisitor& visitor) override;

        expression& left;
        expression& right;
        scan::token oper;
    };

    struct grouping final : expression {
        explicit grouping(expression& expr);

        void accept(ASTVisitor &visitor) override;

        expression& expr;
    };

    struct literal final : expression {
        explicit literal(scan::literal value);

        void accept(ASTVisitor &visitor) override;

        scan::literal value;
    };

    struct unary final : expression {
        explicit unary(expression& expr, scan::token oper);

        void accept(ASTVisitor &visitor) override;

        expression& expr;
        scan::token oper;
    };
}