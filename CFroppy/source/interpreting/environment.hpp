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
		void define(const std::string& name, scan::literal value);
		void undefine(const std::string& name);
		scan::literal get(const std::string& name);
	private:
		std::unordered_map<std::string, scan::literal> values;
	};
}