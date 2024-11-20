#pragma once
#include <iostream>
#include <string>
#include "../interpreting/runtime_error.hpp"
#include "../parsing/parse_error.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::io {
    /*!
    @brief represent input/output interface
     */
    class reporter {
    public:
        explicit reporter(std::ostream& out = std::cout,
                        std::istream& in = std::cin,
                        std::ostream& err = std::cerr);

        void parse_info(int line, const std::string& where, const std::string &msg) const;
        void parse_error(int line, const std::string& where, const std::string &msg) const;
        void parse_error(const parse::parse_error& err) const;

        void runtime_error(const std::string& err) const;
        void runtime_error(const interpreting::runtime_error& err) const;

        void report(const std::string& msg, bool isError) const;

        [[nodiscard]] bool getHadError() const;
        void resetHadError() const;
    private:
        void parse_report(int line, const std::string& where, const std::string &msg, bool isError) const;
        void runtime_report(const std::string &msg) const;

        mutable bool hadError = false;
        std::ostream& out;
        std::ostream& err;
        std::istream& in;
    };
}
