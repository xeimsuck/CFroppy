#pragma once
#include <stdexcept>

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::interpreting{
    /*!
    @brief represent runtime error
     */
    class runtime_error final : public std::runtime_error {
    public:
        explicit runtime_error(const std::string& err = "");
    };
}
