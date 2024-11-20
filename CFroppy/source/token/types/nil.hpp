#pragma once
#include <variant>

namespace cfp::scan::types {
	using nil = std::monostate;
	inline constexpr nil nil_v;
}