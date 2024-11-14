#pragma once
#include <memory>
#include "../scanner/token.hpp"

namespace cfp::parse {
    class astVisitor;

    struct expression {
        virtual ~expression() = default;

        virtual scan::literal accept(astVisitor& visitor) = 0;
    };

    struct binary final : expression {
        binary(std::unique_ptr<expression> left, std::unique_ptr<expression> right, scan::token oper);

        scan::literal accept(astVisitor& visitor) override;

        std::unique_ptr<expression> left;
        std::unique_ptr<expression> right;
        scan::token oper;
    };

    struct grouping final : expression {
        explicit grouping(std::unique_ptr<expression> expr);

        scan::literal accept(astVisitor &visitor) override;

        std::unique_ptr<expression> expr;
    };

    struct literal final : expression {
        explicit literal(scan::literal value);

        scan::literal accept(astVisitor &visitor) override;

        scan::literal value;
    };

    struct unary final : expression {
        explicit unary(std::unique_ptr<expression> expr, scan::token oper);

        scan::literal accept(astVisitor &visitor) override;

        std::unique_ptr<expression> expr;
        scan::token oper;
    };
}