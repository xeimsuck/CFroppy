#pragma once
#include <variant>

namespace cfp {
    namespace type {
        struct number {
            explicit number(long long val=0) {
                value = val;
            }
            explicit number(double val) {
                value = val;
            }
            std::variant<long long, double> value;
        };
        struct string {
            std::string value;
        };
        struct boolean {
            bool value;
        };
        struct nil {
        };
    }
    struct literal {
        literal(const type::nil val = {}) {
            value = val;
        }
        literal(const type::number& val) {
            value = val;
        }
        literal(const type::boolean val) {
            value = val;
        }
        literal(const type::string& val) {
            value = val;
        }
        std::variant<type::nil, type::number, type::string, type::boolean> value;
    };
}
