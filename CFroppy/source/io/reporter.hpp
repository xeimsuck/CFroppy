#pragma once

#include <iostream>
#include <string>

namespace cfp::io {
    class reporter {
    public:
        explicit reporter(std::ostream& out = std::cout,
                        std::istream& in = std::cin,
                        std::ostream& err = std::cerr);
        void info(int line, const std::string& msg) const;
        void warning(int line, const std::string& msg) const;
        void error(int line, const std::string& msg) const;
        void message(const std::string& msg, bool error = false) const;
        bool getHadError() const;
        void resetHadError() const;
    private:
        enum class messageType {
            INFO,
            WARNING,
            ERROR,
        };
        void report(int line, const messageType& type, const std::string& msg) const;

    private:
        mutable bool hadError = false;
        std::ostream& out;
        std::ostream& err;
        std::istream& in;
    };
}
