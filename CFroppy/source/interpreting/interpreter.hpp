#pragma once
#include "../ast/visitor.hpp"

namespace cfp::interpreting {
    class interpreter final : public ast::visitor{
    public:
        scan::literal visit(ast::unary &expr) override;
        scan::literal visit(ast::literal &expr) override;
        scan::literal visit(ast::grouping &expr) override;
        scan::literal visit(ast::binary &expr) override;

    private:
        scan::literal evaluate(const std::unique_ptr<ast::expression>& expr);
        static bool isTruthy(const scan::literal& value);
    };
}
