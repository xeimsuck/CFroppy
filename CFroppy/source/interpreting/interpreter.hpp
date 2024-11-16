#pragma once
#include <vector>
#include "../ast/expression.hpp"
#include "../ast/statement.hpp"
#include "../io/reporter.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::io {
    class reporter;
}

namespace cfp::interpreting {
    /*!
    @brief execute statements
     */
    class interpreter final : public ast::expr::exprVisitor,
                              public ast::stmt::stmtVisitor {
    public:
        explicit interpreter(const io::reporter& reporter);
        void interpret(const std::vector<std::unique_ptr<ast::stmt::statement>>& stmts);

        scan::literal visit(ast::expr::unary &expr) override;
        scan::literal visit(ast::expr::literal &expr) override;
        scan::literal visit(ast::expr::grouping &expr) override;
        scan::literal visit(ast::expr::binary &expr) override;

        void visit(ast::stmt::expression &stmt) override;
        void visit(ast::stmt::print &stmt) override;

    private:
        void execute(const std::unique_ptr<ast::stmt::statement>& stmt);

        scan::literal evaluate(const std::unique_ptr<ast::expr::expression>& expr);;

        const io::reporter& reporter;
    };
}
