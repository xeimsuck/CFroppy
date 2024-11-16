#pragma once
#include "../ast/visitor.hpp"

namespace cfp::interpreting {
    class interpreter final : public ast::visitor{
    public:
        scan::literal visit(ast::expr::unary &expr) override;
        scan::literal visit(ast::expr::literal &expr) override;
        scan::literal visit(ast::expr::grouping &expr) override;
        scan::literal visit(ast::expr::binary &expr) override;

    private:
        scan::literal evaluate(const std::unique_ptr<ast::expr::expression>& expr);
        static bool isTruthy(const scan::literal& value);
    };
}
