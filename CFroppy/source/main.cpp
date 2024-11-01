#include "core/cfroppy.hpp"

int main(const int argc, char*argv[]) {
    auto& prog = cfp::cfroppy::init();
    return prog.run(argc, argv);
}
