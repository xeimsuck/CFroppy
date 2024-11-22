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
        reporter.report("Usage: cfp [script]", true);
        return 1;
    }
    try {
        if(argc==1) prompt();
        else {
            auto code = executeFile(argv[1]);
            std::cout << std::endl << std::format("Process finished with exit code {}.", code);
        }
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
    }
    return 0;
}



/*!
 * @brief execute commands
 * @param source froppy source
 */
int cfroppy::execute(const std::string &source) {
    scan::scanner scanner(source, reporter);
    decltype(auto) tokens = scanner.getTokens();

    parse::parser parser(tokens, reporter);
    const auto stmts = parser.parse();

    if(reporter.getHadError()) return -3;

    interpreting::interpreter interpreter(reporter);
    return interpreter.interpret(stmts);
}



/*!
 * @brief execute commands from script
 * @param path path to script
 */
int cfroppy::executeFile(const std::string &path) {
    std::ifstream file(path);
    if(!file) {
        reporter.report(std::format("Couldn't open the file {}", path), true);
        return 1;
    }

    std::string source, line;
    while (std::getline(file, line)) {
        if(!source.empty()) source.push_back('\n');
        source+=line;
    }
    return execute(source);
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