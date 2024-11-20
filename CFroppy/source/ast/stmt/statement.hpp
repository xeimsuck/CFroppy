#pragma once
#include <memory>
#include <vector>

/*!
    @file
    @brief Contains classes to represent statements
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::ast::stmt {
	struct stmtVisitor;

    /*!
    @brief superclass for all kinds of statements
     */
    struct statement {
        virtual ~statement() = default;

        virtual void accept(stmtVisitor& visitor) = 0;
    };
}