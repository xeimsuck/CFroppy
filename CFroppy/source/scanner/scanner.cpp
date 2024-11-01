#include "scanner.hpp"

using namespace cfp;

/*!
 * @brief just constructor
 * @param source froppy commands
 */
scanner::scanner(std::string source) : source(std::move(source)){
}



/*!
 * @brief scan source file and return tokens
 * @return all tokens
 */
std::vector<token> scanner::scanTokens() {
    return {};
}
