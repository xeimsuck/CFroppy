#include "interpreter.hpp"
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>
#include <random>
#include <thread>
#include <bits/ranges_algo.h>
#include "runtime_error.hpp"

using namespace cfp;
using namespace cfp::interpreting;
using namespace scan::types;
using enum scan::token::tokenType;

struct break_throw {};
struct return_throw {
	scan::literal value;
};

namespace native {
	/*!
	 * @brief output string
	 */
	callable::native print = [](const std::vector<scan::literal>& vars) {
		std::cout << vars[0].stringify() << std::flush;
		return scan::literal{};
	};

	/*!
	 * @brief output string
	 */
	callable::native println = [](const std::vector<scan::literal>& vars) {
		std::cout << vars[0].stringify() << std::endl;
		return scan::literal{};
	};

	/*!
	 * @brief output string to error stream
	 */
	callable::native eprint = [](const std::vector<scan::literal>& vars) {
		std::cerr << vars[0].stringify() << std::endl;
		return scan::literal{};
	};

	/*!
	 * @brief gets string from input stream
	 */
	callable::native input = [](const std::vector<scan::literal>& vars) {
		string in;
		std::cin >> in;
		return scan::literal(in);
	};


	/*!
	 * @brief returns random integer in range [min, max]
	 */
	callable::native random = [](const std::vector<scan::literal>& l) {
		const auto min = l[0].toInteger();
		const auto max = l[1].toInteger();
		if(!min.has<integer>() || !max.has<integer>()) return scan::literal{};

		static std::random_device dev;
		static std::mt19937 rng(dev());

		std::uniform_int_distribution<std::mt19937::result_type> dist(min.getInteger(), max.getInteger());

		return scan::literal{static_cast<long long>(dist(rng))};
	};


	/*!
	 * @brief concatenates arguments to string
	 */
	callable::native format = [](const std::vector<scan::literal>& vars) {
		std::string res;
		std::ranges::for_each(vars, [&res](const auto& var) {
			res+=var.stringify();
		});
		return scan::literal{res};
	};


	/*!
	 * @brief returns current time in unix format
	 */
	callable::native time = [](const std::vector<scan::literal>& vars) {
		return scan::literal{static_cast<integer>(std::time(nullptr))};
	};


	/*!
	 * @brief return current time in (is not standard)
	 */
	callable::native clock = [](const std::vector<scan::literal>& vars) {
		return scan::literal{static_cast<integer>(std::clock())};
	};


	/*!
	 * @brief cast time in unix format into date
	 */
	callable::native date = [](const std::vector<scan::literal>& vars) {
		if(!vars[0].has<integer>()) return scan::literal{};
		const time_t time = vars[0].getInteger();
		return scan::literal(string(std::asctime(std::localtime(&time))));
	};


	/*!
	 * @brief sleep on n milliseconds
	 */
	callable::native sleep = [](const std::vector<scan::literal>& vars) {
		if(vars[0].has<integer>()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(vars[0].getInteger()));
		}
		return scan::literal{};
	};


	/*!
	 * @brief return duration between two clock() in ms
	 */
	callable::native duration = [](const std::vector<scan::literal>& vars) {
		if(!vars[0].has<integer>() || !vars[1].has<integer>()) return scan::literal{};

		const auto dur = static_cast<decimal>(vars[1].getInteger()-vars[0].getInteger()) /  CLOCKS_PER_SEC * 1000;

		return scan::literal{dur};
	};


	/*!
	 * @brief cast variable to string
	 */
	callable::native to_string = [](const std::vector<scan::literal>& vars) {
		return vars[0].toString();
	};


	/*!
	 * @brief cast variable to decimal
	 */
	callable::native to_decimal = [](const std::vector<scan::literal>& vars) {
		return vars[0].toDecimal();
	};


	/*!
	 * @brief cast variable to integer
	 */
	callable::native to_integer = [](const std::vector<scan::literal>& vars) {
		return vars[0].toInteger();
	};


	/*!
	 * @brief cast variable to boolean
	 */
	callable::native to_boolean = [](const std::vector<scan::literal>& vars) {
		return vars[0].toBoolean();
	};


	/*!
	 * @brief return true if variable is instance of type
	 */
	callable::native is_instance = [](const std::vector<scan::literal>& vars) {
		if(!vars[1].has<string>()) return scan::literal{};
		return scan::literal{vars[0].getType()==vars[1].getString()};
	};


	/*!
	 * @brief return square
	 */
	callable::native sqrt = [](const std::vector<scan::literal>& vars) {
		const auto var = vars[0].toDecimal();

		if(var.has<decimal>()) return scan::literal(std::sqrt(var.getDecimal()));

		return scan::literal{};
	};
}



/*!
 * @param reporter reporter
 */
interpreter::interpreter(const io::reporter& reporter) : reporter(reporter), env(std::make_unique<environment>()) {
	// io stream
	env->define("print", scan::literal(callable(1, native::print)));
	env->define("println", scan::literal(callable(1, native::println)));
	env->define("eprint", scan::literal(callable(1, native::eprint)));
	env->define("input", scan::literal(callable(0, native::input)));

	// string
	env->define("format", scan::literal(callable(callable::variadic_arity, native::format)));

	// random
	env->define("rand", scan::literal(callable(2, native::random)));

	// chrono
	env->define("time", scan::literal(callable(0, native::time)));
	env->define("clock", scan::literal(callable(0, native::clock)));
	env->define("date", scan::literal(callable(1, native::date)));
	env->define("sleep", scan::literal(callable(1, native::sleep)));

	// casts
	env->define("duration", scan::literal(callable(2, native::duration)));
	env->define("to_string", scan::literal(callable(1, native::to_string)));
	env->define("to_decimal", scan::literal(callable(1, native::to_decimal)));
	env->define("to_integer", scan::literal(callable(1, native::to_integer)));
	env->define("to_boolean", scan::literal(callable(1, native::to_boolean)));

	// math
	env->define("sqrt", scan::literal(callable(1, native::sqrt)));


	// other
	env->define("is_instance", scan::literal(callable(2, native::is_instance)));
}

/*!
 * @brief execute statements
 * @param stmts list of parsed statements
 */
int interpreter::interpret(const std::vector<std::unique_ptr<ast::stmt::statement>> &stmts) {
    try {
        for(decltype(auto) stmt : stmts) {
            execute(stmt);
        }
    } catch (const break_throw&) {
		reporter.runtime_error("'break' must be used in loop.");
    } catch (const return_throw& val){
		const auto v = val.value.toInteger();
    	if(!v.has<integer>()) {
    		reporter.runtime_error("'return' in global scope must return an integer type.");
    		return -1;
    	}
    	return static_cast<int>(v.getInteger());
	} catch (const runtime_error& ex) {
        reporter.runtime_error(ex);
		return -1;
    }
	return 0;
}

/*!
 * @brief execute one statement
 * @param stmt statement
 */
void interpreter::execute(const std::unique_ptr<ast::stmt::statement> &stmt) {
    stmt->accept(*this);
}


/*!
 * @brief execute block of statements
 * @param stmts statements
 * @param newEnv environment
 * @param env environment
 */
void interpreter::executeBlock(const std::vector<std::unique_ptr<ast::stmt::statement>>& stmts, std::shared_ptr<environment> newEnv) {
	std::swap(env, newEnv);

	std::ranges::for_each(stmts, [this](auto&& stmt) {
		execute(stmt);
	});

	std::swap(env, newEnv);
}


/*!
 * @brief execute function
 * @param func function to execute
 * @param arguments arguments
 * @brief function return value
 */
scan::literal interpreter::executeFunction(callable func, const std::vector<scan::literal>& arguments) {
	if(func.isNative()) return func.getNative()(arguments);


	auto funcEnv = std::make_unique<environment>(func.getClosure());
	const auto declaration = func.getDeclaration();

	for(int i = 0; i < declaration->params.size(); ++i) {
		funcEnv->define(declaration->params[i].lexeme, arguments[i]);
	}

	try {
		executeBlock(declaration->body, std::move(funcEnv));
	} catch (const return_throw& return_val) {
		return return_val.value;
	}
	return scan::literal{};
}


/*!
 * @brief execute instance
 * @param inst
 * @param arguments instance arguments
 * @return object
 */
scan::literal interpreter::executeInstance(const constructor& inst, const std::vector<scan::literal> &arguments) {
	return scan::literal(instance(inst.environment, inst.name));
}




/*!
 * @brief evaluate binary expressions
 * @param expr binary expression
 * @return literal
 */
scan::literal interpreter::visit(ast::expr::binary &expr) {
    const auto left = evaluate(expr.left);
    const auto right = evaluate(expr.right);

    switch (expr.oper.type) {
        case PLUS: return left+right;
        case MINUS: return left-right;
        case STAR: return left*right;
        case SLASH: return left/right;
        case GREATER: return scan::literal(left>right);
        case GREATER_EQUAL: return scan::literal(left>=right);
        case LESS: return scan::literal(left<right);
        case LESS_EQUAL: return scan::literal(left<=right);
        case EQUAL_EQUAL: return scan::literal(left==right);
        case BANG_EQUAL: return scan::literal(left!=right);
        default: return scan::literal{};
    }
}

/*!
 * @brief evaluate unary expression
 */
scan::literal interpreter::visit(ast::expr::grouping &expr) {
    return evaluate(expr.expr);
}

/*!
 * @brief evaluate literal expression
 */
scan::literal interpreter::visit(ast::expr::literal &expr) {
    return expr.value;
}

/*!
 * @brief evaluate unary expression
 */
scan::literal interpreter::visit(ast::expr::unary &expr) {
    const auto right = evaluate(expr.expr);

    switch (expr.oper.type) {
        case MINUS:
            return -right;
        case BANG:
            return scan::literal(!right);
        default: return scan::literal{};
    }
}

/*!
 * @brief evaluate variable expression
 */
scan::literal interpreter::visit(ast::expr::variable &expr) {
	return env->get(expr.name.lexeme);
}

/*!
 * @brief evaluate assign expression
 */
scan::literal interpreter::visit(ast::expr::assign &expr) {
	return env->assign(expr.name.lexeme, evaluate(expr.value));
}


/*!
 * @brief evaluate binary assign
 */
scan::literal interpreter::visit(ast::expr::binary_assign &expr) {
	const auto value = evaluate(expr.value);

	switch (expr.oper.type) {
		case PLUS_EQUAL: return env->assign(expr.name.lexeme, env->get(expr.name.lexeme)+value);
		case MINUS_EQUAL: return env->assign(expr.name.lexeme, env->get(expr.name.lexeme)-value);
		case STAR_EQUAL: return env->assign(expr.name.lexeme, env->get(expr.name.lexeme)*value);
		case SLASH_EQUAL: return env->assign(expr.name.lexeme, env->get(expr.name.lexeme)/value);
		default: return scan::literal{};
	}
}



/*!
 * @brief evaluate logical expression
 */
scan::literal interpreter::visit(ast::expr::logical &expr) {
	const auto left = evaluate(expr.left);

	if(expr.oper.type==OR) {
		if(static_cast<bool>(left)) return scan::literal{true};
	} else if(expr.oper.type==AND) {
		if(!static_cast<bool>(left)) return scan::literal{false};
	}

	return evaluate(expr.right);
}


/*!
 * @brief evaluate visit expression
 */
scan::literal interpreter::visit(ast::expr::call &expr) {
	const auto callee = evaluate(expr.callee);

	std::vector<scan::literal> arguments;
	for(decltype(auto) arg : expr.arguments) {
		arguments.push_back(evaluate(arg));
	}

	if(callee.has<callable>()) {
		return executeFunction(callee.getCallable(), arguments);
	}

	if(callee.has<constructor>()) {
		return executeInstance(callee.getConstructor(), arguments);
	}

	throw runtime_error("Can only call functions and classes.");
}


/*!
 * @brief return member
 */
scan::literal interpreter::visit(ast::expr::member &expr) {
	auto super = evaluate(expr.super);

	if(!super.has<instance>()) {
		throw runtime_error("Variable must be instance of class.");
	}
	decltype(auto) inst = super.getInstance();

	const auto mem = dynamic_cast<ast::expr::variable*>(expr.mem.get());
	if(!mem) {
		throw runtime_error("Class member must be identifier.");
	}

	if(!inst.environment->contain(mem->name.lexeme)) {
		throw runtime_error(std::format("Class '{}' has no member '{}'.", super.getType(), mem->name.lexeme));
	}

	return inst.environment->get(mem->name.lexeme);
}




/*!
 * @brief execute expression statement
 */
void interpreter::visit(ast::stmt::expression &stmt) {
    evaluate(stmt.expr);
}


/*!
 * @brief execute variable statement
 */
void interpreter::visit(ast::stmt::let &stmt) {
	env->define(stmt.name.lexeme, evaluate(stmt.initializer));
}


/*!
 * @brief execute block of statements
 */
void interpreter::visit(ast::stmt::block &stmt) {
	executeBlock(stmt.statements, std::make_shared<environment>(env));
}


/*!
 * @brief execute if-else statement
 */
void interpreter::visit(ast::stmt::if_else &stmt) {
	if(static_cast<bool>(evaluate(stmt.condition))) {
		stmt.ifBranch->accept(*this);
	} else if(stmt.elseBranch) {
		stmt.elseBranch->accept(*this);
	}
}


/*!
 * @brief execute while loop
 */
void interpreter::visit(ast::stmt::loop &stmt) {
	auto loopEnv = std::make_shared<environment>(env);
	std::swap(env, loopEnv);

	if(stmt.initializer) stmt.initializer->accept(*this);
	while (evaluate(stmt.condition)) {
		try {
			stmt.body->accept(*this);
			if(stmt.increment) evaluate(stmt.increment);
		} catch (break_throw b) { break; }
	}

	std::swap(env, loopEnv);
}


/*!
 * @brief break
 */
void interpreter::visit(ast::stmt::break_loop &stmt) {
	throw break_throw{};
}


/*!
 * @brief define function
 */
void interpreter::visit(ast::stmt::function &stmt) {
	env->define(stmt.name.lexeme, scan::literal(callable(&stmt, env)));
	env = std::make_shared<environment>(env);
}


/*!
 * @brief return
 */
void interpreter::visit(ast::stmt::return_fn &stmt) {
	throw return_throw(evaluate(stmt.value));
}


/*!
 * @brief define a class
 */
void interpreter::visit(ast::stmt::class_ &stmt) {
	auto classEnv = std::make_shared<environment>(env);

	for(decltype(auto) method : stmt.methods) {
		classEnv->define(method->name.lexeme, scan::literal(callable(method.get(), classEnv)));
	}

	for(decltype(auto) variable : stmt.variables) {
		classEnv->define(variable->name.lexeme, evaluate(variable->initializer));
	}

	env->define(stmt.name.lexeme, scan::literal(constructor(std::move(classEnv), stmt.name.lexeme)));
}



/*!
 * @brief evaluate expression
 */
scan::literal interpreter::evaluate(const std::unique_ptr<ast::expr::expression> &expr) {
	if(!expr) return scan::literal{}; // return nil
    return expr->accept(*this);
}