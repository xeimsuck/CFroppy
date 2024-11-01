#include "cfroppy.hpp"
#include <fstream>
#include <iostream>
#include "../scanner/scanner.hpp"

using namespace cfp;

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
        std::cout << "Usage: cfp [script]";
        return 1;
    }
    try {
        if(argc==1) prompt();
        else executeFile(argv[1]);
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
void cfroppy::execute(const std::string &source) {
    scanner scanner(source);
    auto tokens = scanner.scanTokens();
    for (auto& token : tokens) {

    }
}



/*!
 * @brief execute commands from script
 * @param path path to script
 */
void cfroppy::executeFile(const std::string &path) {
    std::ifstream file(path);
    if(!file) {
        throw std::runtime_error(std::format("couldn't open the file {}", path));
    }

    std::string source, line;
    while (std::getline(file, line)) {
        if(!source.empty()) source.push_back('\n');
        source+=line;
    }
    execute(source);
    file.close();
}



/*!
 * @brief execute commands interactively
 */
void cfroppy::prompt() {
    std::string line="start";
    while (!line.empty()) {
        std::cout << "> ";
        std::getline(std::cin, line);
        execute(line);
    }
}