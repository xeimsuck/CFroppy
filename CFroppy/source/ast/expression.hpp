#pragma once
#include <memory>
#include "../scanner/token.hpp"

/*!
    @file
    @brief Contains classes to represent expressions
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::ast::expr {
    struct expression;
    struct binary;
    struct grouping;
    struct literal;
	struct unary;
	struct variable;


    /*!
    @brief realize visitor pattern for expressions
     */
    class exprVisitor {
    public:
        virtual ~exprVisitor() = default;

        scan::literal visit(expression& expr);

        virtual scan::literal visit(binary& expr) = 0;
        virtual scan::literal visit(grouping& expr) = 0;
        virtual scan::literal visit(literal& expr) = 0;
        virtual scan::literal visit(unary& expr) = 0;
        virtual scan::literal visit(variable& expr) = 0;
    };


    /*!
    @brief superclass for all kinds of expressions
     */
    struct expression {
        virtual ~expression() = default;

        virtual scan::literal accept(exprVisitor& visitor) = 0;
    };


    /*!
    @brief represent binary expression
     */
    struct binary final : expression {
        binary(std::unique_ptr<expression>&& left, std::unique_ptr<expression>&& right, scan::token oper);

        scan::literal accept(exprVisitor& visitor) override;

        std::unique_ptr<expression> left;
        std::unique_ptr<expression> right;
        scan::token oper;
    };


    /*!
    @brief represent grouping expression
     */
    struct grouping final : expression {
        explicit grouping(std::unique_ptr<expression>&& expr);

        scan::literal accept(exprVisitor &visitor) override;

        std::unique_ptr<expression> expr;
    };


    /*!
    @brief represent literal expression
     */
    struct literal final : expression {
        explicit literal(scan::literal value);

        scan::literal accept(exprVisitor &visitor) override;

        scan::literal value;
    };


    /*!
    @brief represent unary expression
     */
    struct unary final : expression {
        explicit unary(std::unique_ptr<expression>&& expr, scan::token oper);

        scan::literal accept(exprVisitor &visitor) override;

        std::unique_ptr<expression> expr;
        scan::token oper;
    };


    /*!
    @brief represent variable expression
     */
    struct variable final : expression {
        explicit variable(scan::token name);

        scan::literal accept(exprVisitor &visitor) override;

        scan::token name;
    };
}