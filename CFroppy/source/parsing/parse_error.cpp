#include "parse_error.hpp"

using namespace cfp;
using namespace cfp::parse;

/*!
 * @param err error message
 */

parse_error::parse_error(const std::string &err) : std::runtime_error(err) {
}
