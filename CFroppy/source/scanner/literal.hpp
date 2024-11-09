#pragma once
#include <string>
#include <variant>

namespace cfp::scan {
    namespace types {
        using nil = std::monostate;
        using integer = long long;
        using decimal = double;
        using boolean = bool;
        using string = std::string;

        inline constexpr nil nil_v;
    }
    class literal {
    public:
        explicit literal(types::nil = types::nil_v);
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

    private:
        std::variant<types::nil, types::boolean, types::integer, types::decimal, types::string> value;
    };
}
