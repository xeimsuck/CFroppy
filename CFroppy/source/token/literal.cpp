#include "literal.hpp"
#include <format>
#include "../interpreting/runtime_error.hpp"

using namespace cfp;
using namespace cfp::scan;
using namespace cfp::scan::types;

callable::callable(const int arity, native func) : arity_(arity), native_(std::move(func)) {
}

int callable::arity() const {
    return arity_;
}


literal callable::call(interpreting::interpreter *interpreter, const std::vector<literal> &arguments) const {
    if(arguments.size()!=arity_) {
        throw interpreting::runtime_error(std::format("Expected {} arguments but got {}\n", arity_, arguments.size()));
    }
    if(native_) {
        return native_(interpreter, arguments);
    }
    return scan::literal{};
}


literal::literal(nil val) : value(val) {
}

literal::literal(boolean val) : value(val) {
}

literal::literal(decimal val) : value(val) {
}

literal::literal(integer val) : value(val) {
}

literal::literal(string val) : value(std::move(val)){
}

literal::literal(callable val) : value(std::move(val)) {
}


literal literal::toBoolean() const {
    if(has<boolean>()) return literal(getBoolean()); // return bool
    if(has<integer>()) return literal(static_cast<bool>(getInteger())); // return true if integer != 0
    if(has<decimal>()) return literal(static_cast<bool>(getDecimal())); // return true if decimal != 0
    return literal{}; // return nil
}

literal literal::toCallable() const {
    if(has<callable>()) return literal(getCallable());
    return literal{}; // return nil
}

literal literal::toDecimal() const {
    if(has<boolean>()) return literal(static_cast<decimal>(getBoolean())); // return 1.0 if true, otherwise 0.0
    if(has<integer>()) return literal(static_cast<decimal>(getInteger())); // return casted integer
    if(has<decimal>()) return literal(getDecimal()); // return decimal
    return literal{}; // return nil
}

literal literal::toInteger() const {
    if(has<boolean>()) return literal(static_cast<integer>(getBoolean())); // return 1.0 if true, otherwise 0.0
    if(has<integer>()) return literal(getInteger()); // return casted integer
    if(has<decimal>()) return literal(static_cast<integer>(getDecimal())); // return decimal
    return literal{}; // return nil
}

literal literal::toString() const {
    return literal(stringify());
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

callable literal::getCallable() const {
    return std::get<callable>(value);
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

void literal::setCallable(callable val) {
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
    if(has<callable>()) return "callable";
    return "nil";
}


bool literal::operator==(const literal &rhs) const {
    if(has<integer>()) {
        if(rhs.has<integer>()) return getInteger() == rhs.getInteger();
        if(rhs.has<decimal>()) return static_cast<decimal>(getInteger()) == rhs.getDecimal();
    } else if(has<decimal>()) {
        if(rhs.has<integer>()) return getDecimal() == static_cast<decimal>(rhs.getInteger());
        if(rhs.has<decimal>()) return getDecimal() == rhs.getDecimal();
    } else if(has<string>() && rhs.has<string>()) {
        return getString()==rhs.getString();
    } else if(has<boolean>() && rhs.has<boolean>()) {
        return getBoolean()==rhs.getBoolean();
    }
    return has<nil>()&&rhs.has<nil>();
}

bool literal::operator!=(const literal &rhs) const {
    return !(*this==rhs);
}

bool literal::operator>(const literal &rhs) const {
    if(has<integer>()) {
        if(rhs.has<integer>()) return getInteger() > rhs.getInteger();
        if(rhs.has<decimal>()) return static_cast<decimal>(getInteger()) > rhs.getDecimal();
    } else if(has<decimal>()) {
        if(rhs.has<integer>()) return getDecimal() > static_cast<decimal>(rhs.getInteger());
        if(rhs.has<decimal>()) return getDecimal() > rhs.getDecimal();
    } else if(has<string>() && rhs.has<string>()) {
        return getString() > rhs.getString();
    } else if(has<boolean>() && rhs.has<boolean>()) {
        return getBoolean() > rhs.getBoolean();
    }
    return false;
}

bool literal::operator>=(const literal &rhs) const {
    if(has<integer>()) {
        if(rhs.has<integer>()) return getInteger() >= rhs.getInteger();
        if(rhs.has<decimal>()) return static_cast<decimal>(getInteger()) >= rhs.getDecimal();
    } else if(has<decimal>()) {
        if(rhs.has<integer>()) return getDecimal() >= static_cast<decimal>(rhs.getInteger());
        if(rhs.has<decimal>()) return getDecimal() >= rhs.getDecimal();
    } else if(has<string>() && rhs.has<string>()) {
        return getString() >= rhs.getString();
    } else if(has<boolean>() && rhs.has<boolean>()) {
        return getBoolean() >= rhs.getBoolean();
    }
    return has<nil>()&&rhs.has<nil>();
}

bool literal::operator<(const literal &rhs) const {
    if(has<integer>()) {
        if(rhs.has<integer>()) return getInteger() < rhs.getInteger();
        if(rhs.has<decimal>()) return static_cast<decimal>(getInteger()) < rhs.getDecimal();
    } else if(has<decimal>()) {
        if(rhs.has<integer>()) return getDecimal() < static_cast<decimal>(rhs.getInteger());
        if(rhs.has<decimal>()) return getDecimal() < rhs.getDecimal();
    } else if(has<string>() && rhs.has<string>()) {
        return getString() < rhs.getString();
    } else if(has<boolean>() && rhs.has<boolean>()) {
        return getBoolean() < rhs.getBoolean();
    }
    return false;
}

bool literal::operator<=(const literal &rhs) const {
    if(has<integer>()) {
        if(rhs.has<integer>()) return getInteger() <= rhs.getInteger();
        if(rhs.has<decimal>()) return static_cast<decimal>(getInteger()) <= rhs.getDecimal();
    } else if(has<decimal>()) {
        if(rhs.has<integer>()) return getDecimal() <= static_cast<decimal>(rhs.getInteger());
        if(rhs.has<decimal>()) return getDecimal() <= rhs.getDecimal();
    } else if(has<string>() && rhs.has<string>()) {
        return getString() <= rhs.getString();
    } else if(has<boolean>() && rhs.has<boolean>()) {
        return getBoolean() <= rhs.getBoolean();
    }
    return has<nil>()&&rhs.has<nil>();
}

literal literal::operator-() const {
    if(has<integer>()) {
        return literal(-getInteger());
    }
    if(has<decimal>()) {
        return literal(-getDecimal());
    }
    return scan::literal{};
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
    return scan::literal{};
}

literal literal::operator-(const literal &rhs) const {

    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() - rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) - rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() - static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() - rhs.getDecimal());
    }
    return scan::literal{};
}

literal literal::operator*(const literal &rhs) const {
    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() * rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) * rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() * static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() * rhs.getDecimal());
    }
    return scan::literal{};
}

literal literal::operator/(const literal &rhs) const {
    if(has<types::integer>()) {
        if(rhs.has<types::integer>()) return literal(getInteger() / rhs.getInteger());
        if(rhs.has<types::decimal>()) return literal(static_cast<types::decimal>(getInteger()) / rhs.getDecimal());
    } else if(has<types::decimal>()) {
        if(rhs.has<types::integer>()) return literal(getDecimal() / static_cast<types::decimal>(rhs.getInteger()));
        if(rhs.has<types::decimal>()) return literal(getDecimal() / rhs.getDecimal());
    }
    return scan::literal{};
}

literal::operator std::string() const {
    return stringify();
}
