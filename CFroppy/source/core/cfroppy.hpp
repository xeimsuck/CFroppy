#pragma once
#include <string>
#include "../io/reporter.hpp"

namespace cfp {
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
        cpf::reporter reporter;
    };
}
