#pragma once
#include <memory>
#include "expression.hpp"
#include "../scanner/token.hpp"

/*!
    @file
    @brief Contains classes to represent statements
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::ast::stmt {
    struct statement;
    struct expression;
    struct print;


    /*!
    @brief realize visitor pattern for statenents
     */
    class stmtVisitor {
    public:
        virtual ~stmtVisitor() = default;

        void visit(statement& stmt);

        virtual void visit(expression& stmt) = 0;
        virtual void visit(print& stmt) = 0;
    };


    /*!
    @brief superclass for all kinds of statements
     */
    struct statement {
        virtual ~statement() = default;

        virtual void accept(stmtVisitor& visitor) = 0;
    };


    /*!
    @brief represent statement of expression
     */
    struct expression final : statement {
        explicit expression(std::unique_ptr<expr::expression>&& expr);

        void accept(stmtVisitor &visitor) override;

        std::unique_ptr<expr::expression> expr;
    };


    /*!
    @brief represent print statement
     */
    struct print final : statement {
        explicit print(std::unique_ptr<expr::expression>&& expr);

        void accept(stmtVisitor &visitor) override;

        std::unique_ptr<expr::expression> expr;
    };
}