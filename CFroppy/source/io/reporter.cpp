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

/*!
 * @brief output info message to the output stream
 */
void reporter::info(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::INFO, where, msg);
}

/*!
 * @brief output warning message to the output stream
 */
void reporter::warning(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::WARNING, where, msg);
}

/*!
 * @brief output error message to the error stream
 */
void reporter::error(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::ERROR, where, msg);
}

/*!
 * @brief output runtime_error to the error stream
 */
void reporter::error(const interpreting::runtime_error &err) const {
    message(std::format("[runtime] Error: {}\n", err.what()), true);
}

/*!
 * @param msg a message is outputted
 * @param error if true method outputs to the error stream
 */
void reporter::message(const std::string &msg, const bool error) const {
    if(error) {
        hadError = true;
        err << msg;
    }
    else out << msg;
}

/*!
 * @brief report messages
 */
void reporter::report(const int line, const messageType &type, const std::string& where, const std::string &msg) const {
    message(std::format("[line {}] Error{}: {}\n", line, where, msg), type==messageType::ERROR);
}

/*!
 * @return return true if reporter has error output
 */
bool reporter::getHadError() const {
    return hadError;
}

/*!
 * @brief reset hasError
 */
void reporter::resetHadError() const {
    hadError = false;
}

