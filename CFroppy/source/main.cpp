#include "core/cfroppy.hpp"

using namespace cfp::core;

int main(const int argc, char*argv[]) {
    auto& prog = cfroppy::init();
    return prog.run(argc, argv);
}
