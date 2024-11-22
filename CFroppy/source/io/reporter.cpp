#include "reporter.hpp"
#include <iostream>
#include <format>

using namespace cfp;
using namespace cfp::io;

/*!
 * @param out output stream
 * @param in input stream
 * @param err error stream
 */
reporter::reporter(std::ostream &out, std::istream &in, std::ostream &err) : out(out), err(err), in(in){
}


void reporter::report(const std::string &msg, const bool isError) const {
	   if(isError) {
		      hadError = true;
		      std::cerr << msg;
	   } else std::cout << msg;
}


/*!
 * @return true if it has error
 */
bool reporter::getHadError() const {
	   return hadError;
}

/*!
 * @brief
 */
void reporter::resetHadError() const {
	   hadError = false;
}



/*!
 * @brief output info message to the output stream
 */
void reporter::parse_info(const int line, const std::string& where, const std::string &msg) const {
    parse_report(line, where, msg, false);
}


/*!
 * @brief output error message to the error stream
 */
void reporter::parse_error(const int line, const std::string& where, const std::string &msg) const {
    parse_report(line, where, msg, true);
}

/*!
 * @brief output parse error to error stream
 */
void reporter::parse_error(const parse::parse_error &err) const {
	   parse_error(err.line(), err.where(), err.what());
}



/*!
 * @brief output runtime_error to the error stream
 */
void reporter::runtime_error(const std::string& str) const {
	   runtime_report(str);
}

/*!
 * @brief output runtime_error to the error stream
 */
void reporter::runtime_error(const interpreting::runtime_error &err) const {
    runtime_error(err.what());
}





/*!
 * @brief report parse messages
 */
void reporter::parse_report(const int line, const std::string& where, const std::string &msg, const bool isError) const {
    report(std::format("[line {}] Error{}: {}\n", line, where, msg), isError);
}


/*!
 * @brief report runtime errors
 */
void reporter::runtime_report(const std::string &msg) const {
    report(std::format("Error: {}\n", msg), true);
}