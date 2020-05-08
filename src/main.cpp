#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"
#include "Parser.h"

int main()
{
    //EXAMPLE USE OF THE SCANNER
    std::string regexp = R"(a++)";        //store a regular expression in a string
    Source source(regexp);                      //create a source object for that string
    Scanner scanner(&source);                   //create a scanner object for the source
    Parser parser(&scanner);

    Token temp;
    do                                          //return token until EOT
    {
        temp = scanner.getNextToken();
        //print(temp);
    } while(temp.value != 0x03);
    source.reset();
    std::cout << (parser.Parse() ? "success" : "fail") << std::endl;

    return 0;
}