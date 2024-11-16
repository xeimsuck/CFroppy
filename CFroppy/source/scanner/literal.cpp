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

std::string literal::stringify() const {
    if(has<boolean>()) return getBoolean() ? "true" : "false";
    if(has<string>()) return getString();
    if(has<integer>()) return std::to_string(getInteger());
    if(has<decimal>()) return std::to_string(getDecimal());
    return "nil";
}


bool literal::operator==(const literal &rhs) const {
    return value==rhs.value;
}

bool literal::operator!=(const literal &rhs) const {
    return value!=rhs.value;
}

bool literal::operator>(const literal &rhs) const {
    return value>rhs.value;
}

bool literal::operator>=(const literal &rhs) const {
    return value>=rhs.value;
}

bool literal::operator<(const literal &rhs) const {
    return value<rhs.value;
}

bool literal::operator<=(const literal &rhs) const {
    return value<=rhs.value;
}

literal literal::operator-() const {
    if(has<integer>()) {
        return literal(-getInteger());
    }
    if(has<decimal>()) {
        return literal(-getDecimal());
    }
    return {};
}

literal::operator bool() const {
    if(has<boolean>()) return getBoolean();
    return !has<nil>();
}

bool literal::operator!() const {
    return !static_cast<bool>(*this);
}

literal literal::operator+(const literal &rhs) const {
    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() + rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) + rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() + static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() + rhs.getDecimal());
    } else if(has<types::string>() && rhs.has<types::string>()) {
        return scan::literal(getString()+rhs.getString());
    }
    return {};
}

literal literal::operator-(const literal &rhs) const {

    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() - rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) - rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() - static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() - rhs.getDecimal());
    }
    return {};
}

literal literal::operator*(const literal &rhs) const {
    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() * rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) * rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() * static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() * rhs.getDecimal());
    }
    return {};
}

literal literal::operator/(const literal &rhs) const {
    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() / rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) / rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() / static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() / rhs.getDecimal());
    }
    return {};
}

literal::operator std::string() const {
    return stringify();
}
