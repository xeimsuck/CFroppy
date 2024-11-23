#pragma once
#include <string>
#include <variant>
#include <functional>
#include <memory>
#include "../interpreting/environment.hpp"

/*!
    @file
    @author Xeim
    @version 1.0
    @data 16.11.24
 */

namespace cfp::ast::stmt {
    struct class_;
    struct function;
}

namespace cfp::interpreting {
    class environment;
}

namespace cfp::scan {
    class literal;

    namespace types {
        /*!
        @brief represent callable type
         */
        class callable {
        public:
            using native = std::function<literal(const std::vector<literal>&)>;
            static constexpr int variadic_arity = -1;
            static constexpr int max_arity = 255;

            callable(int arity, native func);
            explicit callable(ast::stmt::function* declaration, std::shared_ptr<interpreting::environment> closure);

            [[nodiscard]] bool isNative() const;
            native getNative();
            [[nodiscard]] ast::stmt::function* getDeclaration() const;
            [[nodiscard]] std::shared_ptr<interpreting::environment> getClosure() const;
            [[nodiscard]] int arity() const;

        private:
            int arity_=0;
            native native_=nullptr;
            ast::stmt::function* declaration = nullptr;
            std::shared_ptr<interpreting::environment> closure;
        };


        /*!
        @brief represent instantiation
         */
        struct constructor {
            explicit constructor(std::shared_ptr<interpreting::environment> environment, std::string name);

            std::string name;
            std::shared_ptr<interpreting::environment> environment;
        };


        /*!
        @brief represent class instance
         */
        struct instance {
            explicit instance(const std::shared_ptr<interpreting::environment>& classEnv, std::string name);

            std::string name;
            std::shared_ptr<interpreting::environment> environment;
        };

        // simple types
        using boolean = bool;
        using decimal = double;
        using integer = long long;
        using nil = std::monostate;
        inline constexpr nil nil_v;
        using string = std::string;
    }

    /*!
    @brief represent literal
     */
    class literal {
    public:
        explicit literal(types::nil = types::nil_v);
        explicit literal(types::integer val);
        explicit literal(types::decimal val);
        explicit literal(types::string val);
        explicit literal(types::boolean val);
        explicit literal(types::callable val);
        explicit literal(types::constructor val);
        explicit literal(types::instance val);

        template<typename T>
        [[nodiscard]] bool has() const {
            return std::holds_alternative<T>(value);
        }

        [[nodiscard]] literal toBoolean() const;
        [[nodiscard]] literal toInteger() const;
        [[nodiscard]] literal toDecimal() const;
        [[nodiscard]] literal toString() const;
        [[nodiscard]] literal toCallable() const;

        [[nodiscard]] types::boolean getBoolean() const;
        [[nodiscard]] types::integer getInteger() const;
        [[nodiscard]] types::decimal getDecimal() const;
        [[nodiscard]] types::string getString() const;
        [[nodiscard]] types::callable getCallable() const;
        [[nodiscard]] types::constructor getConstructor() const;
        [[nodiscard]] types::instance getInstance() const;

        void setBoolean(types::boolean);
        void setInteger(types::integer);
        void setDecimal(types::decimal);
        void setString(types::string);
        void setCallable(types::callable);
        void setNil();

        [[nodiscard]] std::string stringify() const;
        [[nodiscard]] std::string getType() const;

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
        std::variant<types::nil, types::boolean, types::integer, types::decimal, types::string, types::callable, types::constructor, types::instance> value;
    };
}
