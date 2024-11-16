#include "reporter.hpp"
#include <iostream>
#include <format>

using namespace cfp;
using namespace cfp::io;

reporter::reporter(std::ostream &out, std::istream &in, std::ostream &err) : out(out), err(err), in(in){
}

void reporter::info(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::INFO, where, msg);
}

void reporter::warning(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::WARNING, where, msg);
}

void reporter::error(const int line, const std::string& where, const std::string &msg) const {
    report(line, messageType::ERROR, where, msg);
}

void reporter::error(const interpreting::runtime_error &err) const {
    message(std::format("[runtime] Error: {}\n", err.what()), true);
}


void reporter::message(const std::string &msg, const bool error) const {
    if(error) {
        hadError = true;
        err << msg;
    }
    else out << msg;
}

void reporter::report(const int line, const messageType &type, const std::string& where, const std::string &msg) const {
    message(std::format("[line {}] Error{}: {}\n", line, where, msg), type==messageType::ERROR);
}

bool reporter::getHadError() const {
    return hadError;
}

void reporter::resetHadError() const {
    hadError = false;
}

