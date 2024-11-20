#pragma once
#include <string>
#include <variant>
#include "types/boolean.hpp"
#include "types/decimal.hpp"
#include "types/integer.hpp"
#include "types/string.hpp"
#include "types/nil.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */


namespace cfp::scan {
    /*!
    @brief represent literal
     */
    class literal {
    public:
        literal(types::nil = types::nil_v);
        explicit literal(types::integer val);
        explicit literal(types::decimal val);
        explicit literal(types::string val);
        explicit literal(types::boolean val);

        template<typename T>
        [[nodiscard]] bool has() const {
            return std::holds_alternative<T>(value);
        }

        [[nodiscard]] types::boolean getBoolean() const;
        [[nodiscard]] types::integer getInteger() const;
        [[nodiscard]] types::decimal getDecimal() const;
        [[nodiscard]] types::string getString() const;

        void setBoolean(types::boolean);
        void setInteger(types::integer);
        void setDecimal(types::decimal);
        void setString(types::string);
        void setNil();

        [[nodiscard]] std::string stringify() const;

        // equality
        bool operator==(const literal & rhs) const;
        bool operator!=(const literal & rhs) const;

        // comparison
        bool operator>(const literal& rhs) const;
        bool operator>=(const literal& rhs) const;
        bool operator<(const literal& rhs) const;
        bool operator<=(const literal& rhs) const;

        // unary
        literal operator-() const;
        bool operator!() const;

        // term
        literal operator+(const literal& rhs) const;
        literal operator-(const literal& rhs) const;

        // factor
        literal operator*(const literal& rhs) const;
        literal operator/(const literal& rhs) const;

        // cast
        explicit operator bool() const;
        explicit operator std::string() const;
    private:
        std::variant<types::nil, types::boolean, types::integer, types::decimal, types::string> value;
    };
}
