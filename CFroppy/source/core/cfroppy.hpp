#pragma once
#include <string>
#include "../io/reporter.hpp"

/*!
    @file
    @brief Contains main class that run translation
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::core {
    /*!
    @brief combines all translation phases
     */
    class cfroppy {
    public:
        cfroppy(const cfroppy&) = delete;
        cfroppy(cfroppy&&) = delete;
        cfroppy& operator =(const cfroppy&) = delete;
        cfroppy& operator =(cfroppy&&) = delete;

        static cfroppy& init();

        int run(int argc, char** argv);
    private:
        cfroppy() = default;

        int execute(const std::string &source);
        int executeFile(const std::string &path);
        int prompt();

    private:
        io::reporter reporter;
    };
}
