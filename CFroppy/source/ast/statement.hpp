#pragma once
#include <memory>
#include <vector>
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
	struct var;
	struct block;
	struct if_else;
	struct loop;


    /*!
    @brief realize visitor pattern for statements
     */
    class stmtVisitor {
    public:
        virtual ~stmtVisitor() = default;

        void visit(statement& stmt);

        virtual void visit(expression& stmt) = 0;
        virtual void visit(print& stmt) = 0;
        virtual void visit(var& stmt) = 0;
        virtual void visit(block& stmt) = 0;
        virtual void visit(if_else& stmt) = 0;
        virtual void visit(loop& stmt) = 0;
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


    /*!
    @brief represent var initialization
     */
    struct var final : statement {
        explicit var(scan::token name, std::unique_ptr<expr::expression>&& initializer);

        void accept(stmtVisitor &visitor) override;

        scan::token name;
        std::unique_ptr<expr::expression> initializer;
    };


	/*!
	@brief represent lexical scope
	 */
	struct block final : statement {
		explicit block(std::vector<std::unique_ptr<statement>> statements);

		void accept(stmtVisitor &visitor) override;

		std::vector<std::unique_ptr<statement>> statements;
	};


	/*!
	@brief represent if-else statement
	 */
	struct if_else final : statement {
		if_else(std::unique_ptr<expr::expression>&& cond, std::unique_ptr<statement>&& ifBranch,
				std::unique_ptr<statement>&& elseBranch);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<expr::expression> condition;
		std::unique_ptr<statement> ifBranch;
		std::unique_ptr<statement> elseBranch;
	};

	/*!
	@brief represent loop
	 */
	struct loop final : statement {
		loop(std::unique_ptr<statement>&& initializer, std::unique_ptr<expr::expression>&& condition,
			 std::unique_ptr<expr::expression>&& increment, std::unique_ptr<statement>&& body);

		void accept(stmtVisitor &visitor) override;

		std::unique_ptr<statement> initializer;
		std::unique_ptr<expr::expression> increment;
		std::unique_ptr<expr::expression> condition;
		std::unique_ptr<statement> body;
	};
}