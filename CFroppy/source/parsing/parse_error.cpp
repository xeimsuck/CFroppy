#include "parse_error.hpp"

using namespace cfp;
using namespace cfp::parse;

/*!
 * @param err error message
 * @param line line of error
 * @param where where is error
 */
parse_error::parse_error(const std::string &err, const int line, std::string where)
			: std::runtime_error(err), where_(std::move(where)) {
	line_ = line;
}

int parse_error::line() const {
	return line_;
}

const std::string &parse_error::where() const {
	return where_;
}
