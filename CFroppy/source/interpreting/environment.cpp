#include "environment.hpp"
#include <format>

using namespace cfp;
using namespace cfp::interpreting;

/*!
 * @brief define new variable
 * @param name variable name
 * @param value variable value
 */
void environment::define(const std::string &name, scan::literal value) {
	if(values.contains(name)) {
		throw runtime_error(std::format("Value with name {} already defined.", name));
	}
	values[name] = std::move(value);
}

/*!
 * @brief undefine variable
 * @param name variable name
 */
void environment::undefine(const std::string &name) {
	values.erase(name);
}

/*!
 * @brief return variable value
 * @param name name of variable
 * @return value of variable
 */
scan::literal environment::get(const std::string &name) {
	if(!values.contains(name)) {
		throw runtime_error(std::format("There is no variable with name {}.", name));
	}
	return values[name];
}

