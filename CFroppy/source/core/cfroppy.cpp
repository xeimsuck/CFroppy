#include "cfroppy.hpp"
#include <fstream>
#include <iostream>
#include "../interpreting/interpreter.hpp"
#include "../parsing/parser.hpp"
#include "../scanner/scanner.hpp"

using namespace cfp;
using namespace cfp::core;
using namespace cfp::scan;

/*!
 * @return Singleton froppy
 */
cfroppy &cfroppy::init() {
    static cfroppy singleton;
    return singleton;
}



/*!
 * @brief run interpreter
 * @param argc arguments count
 * @param argv arguments values
 * @return 0 if successful
 */
int cfroppy::run(const int argc, char **argv) {
    if(argc>2) {
        reporter.message("Usage: cfp [script]", true);
        return 1;
    }
    try {
        return argc == 1 ? prompt() : executeFile(argv[1]);
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
    }
}



/*!
 * @brief execute commands
 * @param source froppy source
 */
int cfroppy::execute(const std::string &source) {
    scan::scanner scanner(source, reporter);
    decltype(auto) tokens = scanner.getTokens();

    parse::parser parser(tokens, reporter);
    const auto ast = parser.parse();

    if(!reporter.getHadError()) {
        interpreting::interpreter interpreter;
        ast->accept(interpreter);
    }

    return reporter.getHadError()?1:0;
}



/*!
 * @brief execute commands from script
 * @param path path to script
 */
int cfroppy::executeFile(const std::string &path) {
    std::ifstream file(path);
    if(!file) {
        reporter.message(std::format("couldn't open the file {}", path), true);
        return 1;
    }

    std::string source, line;
    while (std::getline(file, line)) {
        if(!source.empty()) source.push_back('\n');
        source+=line;
    }
    return execute(source);;
}



/*!
 * @brief execute commands interactively
 */
int cfroppy::prompt() {
    std::string line="\n";
    while (!line.empty()) {
        std::cout << "> ";
        std::getline(std::cin, line);
        execute(line);
        reporter.resetHadError();
    }
    return 0;
}