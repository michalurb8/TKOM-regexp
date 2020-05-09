#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"

int main()
{
    //EXAMPLE USE OF THE SCANNER
    std::string regexp = R"(a?s(a[aac]*)|df)";  //store a regular expression in a string
    Parser parser(regexp);

    std::cout << (parser.Parse() ? "success" : "fail") << std::endl;

    return 0;
}