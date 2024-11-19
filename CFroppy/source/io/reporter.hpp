#pragma once
#include <iostream>
#include <string>
#include "../interpreting/runtimeError.hpp"

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
        void info(int line, const std::string& where, const std::string& msg) const;
        void warning(int line, const std::string& where, const std::string& msg) const;
        void error(int line, const std::string& where, const std::string& msg) const;
        void runtime_error(const interpreting::runtime_error& err) const;
        void runtime_error(const std::string& str) const;
        void message(const std::string& msg, bool error = false) const;
        bool getHadError() const;
        void resetHadError() const;
    private:
        enum class messageType {
            INFO,
            WARNING,
            ERROR,
        };
        void report(int line, const messageType& type, const std::string& where, const std::string& msg) const;

    private:
        mutable bool hadError = false;
        std::ostream& out;
        std::ostream& err;
        std::istream& in;
    };
}
