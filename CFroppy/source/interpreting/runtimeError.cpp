#include "runtimeError.hpp"

using namespace cfp;
using namespace cfp::interpreting;

runtime_error::runtime_error(const std::string &err) : std::runtime_error(err) {
}
