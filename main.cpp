#include <iostream>

int main(int argc, const char **argv) {
    std::cout << "Hello World!" << std::endl;
}

/* Methods to call
 * match
 * - functionDecl()
 * - whileStmt()
 * - forStmt()
 * - varDecl()
 *
 *
 ** Output to a file: clang-query main.cpp -c "match functionDecl()" > output.txt
 ** Print entire AST: clang++ -Xclang -ast-dump -fsyntax-only main.cpp
 *
 */
