#include "runtime_error.hpp"

using namespace cfp;
using namespace cfp::interpreting;

/*!
 * @param err error message
 */
runtime_error::runtime_error(const std::string &err) : std::runtime_error(err) {
}
