#include "reporter.hpp"
#include <iostream>
#include <format>

using namespace cfp;
using namespace cfp::io;

reporter::reporter(std::ostream &out, std::istream &in, std::ostream &err) : out(out), err(err), in(in){
}

void reporter::info(const int line, const std::string &msg) const {
    report(line, messageType::INFO, msg);
}

void reporter::warning(const int line, const std::string &msg) const {
    report(line, messageType::WARNING, msg);
}

void reporter::error(const int line, const std::string &msg) const {
    hadError = true;
    report(line, messageType::ERROR, msg);
}

void reporter::message(const std::string &msg, const bool error) const {
    if(error) {
        hadError = true;
        err << msg;
    }
    else out << msg;
}

void reporter::report(const int line, const messageType &type, const std::string &msg) const {
    message(std::format("[line {}] Error: {}\n", line, msg), type!=messageType::INFO);
}

bool reporter::getHadError() const {
    return hadError;
}

void reporter::resetHadError() const {
    hadError = false;
}

