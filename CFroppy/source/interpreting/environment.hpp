#pragma once
#include <unordered_map>
#include "../scanner/literal.hpp"
#include "runtimeError.hpp"

/*!
	@file
	@author Xeim
	@version 1.0
	@data 16.11.24
 */

namespace cfp::interpreting {
	/*!
	@brief represent program environment
	 */
	class environment {
	public:
		explicit environment(environment* enclosing = nullptr);
		environment(const environment&) = delete;
		environment& operator=(const environment&) = delete;
		environment(environment&& env) noexcept;
		environment& operator=(environment&& env) noexcept;
		~environment() = default;

	private:
		friend void swap(environment& lhs, environment& rhs) noexcept {
			std::swap(lhs.values, rhs.values);
			std::swap(lhs.enclosing, rhs.enclosing);
		}

	public:
		void define(const std::string& name, scan::literal value);
		void undefine(const std::string& name);
		scan::literal assign(const std::string& name, scan::literal value);
		scan::literal get(const std::string& name);

	public:
		scan::literal& consume(const std::string& name);
		std::unordered_map<std::string, scan::literal> values;
		environment* enclosing = nullptr;
	};
}