#pragma once
#include "../parsing/astVisitor.hpp"

namespace cfp::interpreting {
    class interpreter final : public parse::astVisitor{
    public:
        scan::literal visit(parse::unary &expr) override;
        scan::literal visit(parse::literal &expr) override;
        scan::literal visit(parse::grouping &expr) override;
        scan::literal visit(parse::binary &expr) override;

    private:
        scan::literal evaluate(const std::unique_ptr<parse::expression>& expr);
        static bool isTruthy(const scan::literal& value);
    };
}
