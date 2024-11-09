#include "literal.hpp"

using namespace cfp;
using namespace cfp::scan;
using namespace cfp::scan::types;

literal::literal(nil val) {
    value = val;
}

literal::literal(boolean val) {
    value = val;
}

literal::literal(decimal val) {
    value = val;
}

literal::literal(integer val) {
    value = val;
}

literal::literal(string val) {
    value = std::move(val);
}

boolean literal::getBoolean() const {
    return std::get<boolean>(value);
}

integer literal::getInteger() const {
    return std::get<integer>(value);
}

decimal literal::getDecimal() const {
    return std::get<decimal>(value);
}

string literal::getString() const {
    return std::get<string>(value);
}

void literal::setBoolean(boolean val) {
    value = val;
}

void literal::setInteger(integer val) {
    value = val;
}

void literal::setDecimal(decimal val) {
    value = val;
}

void literal::setString(string val) {
    value = std::move(val);
}

void literal::setNil() {
    value = nil_v;
}
