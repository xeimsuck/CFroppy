#pragma once
#include <memory>
#include "../../token/token.hpp"

/*!
    @file
    @brief Contains classes to represent expressions
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::ast::expr {
	struct exprVisitor;

    /*!
    @brief superclass for all kinds of expressions
     */
    struct expression {
        virtual ~expression() = default;

        virtual scan::literal accept(exprVisitor& visitor) = 0;
    };
}