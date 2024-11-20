#pragma once
#include <vector>
#include "../ast/expr/exprVisitor.hpp"
#include "../ast/stmt/stmtVisitor.hpp"
#include "../io/reporter.hpp"
#include "../token/token.hpp"

namespace cfp::parse {
    /*!
     *  @brief parse stream of tokens into AST
     */
    class parser {
    public:
        parser(std::vector<scan::token>& tokens, const io::reporter& reporter);
        std::vector<std::unique_ptr<ast::stmt::statement>> parse();

    private:
        std::unique_ptr<ast::expr::expression> expr();
        std::unique_ptr<ast::expr::expression> assignment();
        std::unique_ptr<ast::expr::expression> logical_or();
        std::unique_ptr<ast::expr::expression> logical_and();
        std::unique_ptr<ast::expr::expression> equality();
        std::unique_ptr<ast::expr::expression> comparison();
        std::unique_ptr<ast::expr::expression> term();
        std::unique_ptr<ast::expr::expression> factor();
        std::unique_ptr<ast::expr::expression> binary_assignment();
        std::unique_ptr<ast::expr::expression> unary();
        std::unique_ptr<ast::expr::expression> call();
        std::unique_ptr<ast::expr::expression> primary();

        std::unique_ptr<ast::stmt::statement> declaration();
        std::unique_ptr<ast::stmt::var> varDeclaration();
        std::unique_ptr<ast::stmt::block> block();
        std::unique_ptr<ast::stmt::statement> statement();
        std::unique_ptr<ast::stmt::print> printStatement();
        std::unique_ptr<ast::stmt::expression> expressionStatement();
        std::unique_ptr<ast::stmt::if_else> ifStatement();
        std::unique_ptr<ast::stmt::loop> whileStatement();
        std::unique_ptr<ast::stmt::loop> forStatement();
        std::unique_ptr<ast::stmt::break_loop> breakStatement();

        std::unique_ptr<ast::expr::expression> finishCall(std::unique_ptr<ast::expr::expression>&& callee);
        void synchronize();

        [[nodiscard]] bool isAtEnd() const;
        [[nodiscard]] bool check(scan::token::tokenType type) const;

        scan::token& advance();
        scan::token& consume(scan::token::tokenType type, const std::string& msg);
        parse_error error(const scan::token& token, const std::string& msg) const;
        [[nodiscard]] scan::token& peek() const;
        [[nodiscard]] scan::token& previous() const;

        /*!
        @brief advance if current type of token matches with at least one of expected
         */
        template<std::same_as<scan::token::tokenType>... T>
        bool match(T... types) {
            for(decltype(auto) type : {types...}) {
                if(check(type)) {
                    advance();
                    return true;
                }
            }
            return false;
        }

    private:
        const io::reporter& reporter;
        std::vector<scan::token>& tokens;
        int current = 0;
    };
}
