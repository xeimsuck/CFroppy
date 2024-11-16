#pragma once
#include <vector>
#include "../ast/expression.hpp"
#include "../ast/statement.hpp"

namespace cfp::interpreting {
    class interpreter final : public ast::expr::exprVisitor,
                              public ast::stmt::stmtVisitor {
    public:
        void interpret(const std::vector<std::unique_ptr<ast::stmt::statement>>& stmts);

        scan::literal visit(ast::expr::unary &expr) override;
        scan::literal visit(ast::expr::literal &expr) override;
        scan::literal visit(ast::expr::grouping &expr) override;
        scan::literal visit(ast::expr::binary &expr) override;

        void visit(ast::stmt::expression &stmt) override;
        void visit(ast::stmt::print &stmt) override;

    private:
        void execute(const std::unique_ptr<ast::stmt::statement>& stmt);

        scan::literal evaluate(const std::unique_ptr<ast::expr::expression>& expr);
        static bool isTruthy(const scan::literal& value);
    };
}
