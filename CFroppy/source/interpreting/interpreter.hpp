#pragma once
#include <vector>
#include "../ast/expr/exprVisitor.hpp"
#include "../ast/stmt/stmtVisitor.hpp"
#include "../io/reporter.hpp"
#include "environment.hpp"

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
        int interpret(const std::vector<std::unique_ptr<ast::stmt::statement>>& stmts);

        scan::literal visit(ast::expr::unary &expr) override;
        scan::literal visit(ast::expr::literal &expr) override;
        scan::literal visit(ast::expr::grouping &expr) override;
        scan::literal visit(ast::expr::binary &expr) override;
        scan::literal visit(ast::expr::variable &expr) override;
        scan::literal visit(ast::expr::assign &expr) override;
        scan::literal visit(ast::expr::binary_assign &expr) override;
        scan::literal visit(ast::expr::logical &expr) override;
        scan::literal visit(ast::expr::call &expr) override;

        void visit(ast::stmt::expression &stmt) override;
        void visit(ast::stmt::var &stmt) override;
        void visit(ast::stmt::block &stmt) override;
        void visit(ast::stmt::if_else &stmt) override;
        void visit(ast::stmt::loop &stmt) override;
        void visit(ast::stmt::break_loop &stmt) override;
        void visit(ast::stmt::function &stmt) override;
        void visit(ast::stmt::return_fn &stmt) override;
        void visit(ast::stmt::class_ &stmt) override;

    private:
        void execute(const std::unique_ptr<ast::stmt::statement>& stmt);
        void executeBlock(const std::vector<std::unique_ptr<ast::stmt::statement>>& stmts, std::shared_ptr<environment> env);
        scan::literal executeFunction(scan::types::callable func, const std::vector<scan::literal>& arguments);

        scan::literal evaluate(const std::unique_ptr<ast::expr::expression>& expr);

        const io::reporter& reporter;
        std::shared_ptr<environment> env;
    };
}
