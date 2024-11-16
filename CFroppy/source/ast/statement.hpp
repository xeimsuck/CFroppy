#pragma once
#include <memory>
#include "expression.hpp"
#include "../scanner/token.hpp"

namespace cfp::ast::stmt {
    struct statement;
    struct expression;
    struct print;

    class stmtVisitor {
    public:
        virtual ~stmtVisitor() = default;

        void visit(statement& stmt);

        virtual void visit(expression& stmt) = 0;
        virtual void visit(print& stmt) = 0;
    };

    struct statement {
        virtual ~statement() = default;

        virtual void accept(stmtVisitor& visitor) = 0;
    };

    struct expression final : statement {
        explicit expression(std::unique_ptr<expr::expression>&& expr);

        void accept(stmtVisitor &visitor) override;

        std::unique_ptr<expr::expression> expr;
    };

    struct print final : statement {
        explicit print(std::unique_ptr<expr::expression>&& expr);

        void accept(stmtVisitor &visitor) override;

        std::unique_ptr<expr::expression> expr;
    };
}