#pragma once

#include <string>

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

        void execute(const std::string &source);
        void executeFile(const std::string &path);
        void prompt();
    };
}
