#pragma once
#include <stdexcept>

namespace cfp::interpreting{
    class runtime_error final : public std::runtime_error {
    public:
        explicit runtime_error(const std::string& err = "");
    };
}
