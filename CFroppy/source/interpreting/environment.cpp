#include "environment.hpp"
#include <format>
#include "runtime_error.hpp"


using namespace cfp;
using namespace cfp::interpreting;


/*!
 * @param enclosing enclosing environment
 */
environment::environment(std::shared_ptr<environment> enclosing) : enclosing(std::move(enclosing)) {
}


/*!
 * @brief move-constructor
 */
environment::environment(environment &&env) noexcept {
	enclosing = env.enclosing;
	env.enclosing = nullptr;
	env.values = std::move(env.values);
}


/*!
 * @brief move-assignment
 */
environment &environment::operator=(environment &&env) noexcept {
	if(&env==this) return *this;
	enclosing = env.enclosing;
	env.enclosing = nullptr;
	env.values = std::move(env.values);
	return *this;
}


/*!
 * @brief define a new variable
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
 * @brief assign a value to a variable
 * @param name variable name
 * @param value assigned value
 * @return assigned value
 */
scan::literal environment::assign(const std::string &name, scan::literal value) {
	return consume(name)=std::move(value);
}


/*!
 * @brief return variable value
 * @param name name of variable
 * @return value of variable
 */
scan::literal environment::get(const std::string &name) {
	return consume(name);
}


/*!
 * @brief if variable defined return value otherwise runtime error
 * @param name variable name
 * @return variable value
 */
scan::literal &environment::consume(const std::string &name) {
	if(values.contains(name)) return values[name];
	if(enclosing) return enclosing->consume(name);

	throw runtime_error(std::format("Undefined variable '{}'.", name));
}
