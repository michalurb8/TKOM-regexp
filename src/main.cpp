#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"

int main()
{
    //EXAMPLE USE OF THE SCANNER
    std::string regexp = R"(a*\\\*bc\)";        //store a regular expression in a string
    Source source(regexp);                      //create a source object for that string
    Scanner scanner(&source);                   //create a scanner object for the source

    Token temp;
    do                                          //return token until EOT
    {
        temp = scanner.getNextToken();
        print(temp);
    } while(temp.getValue() != 0x03);
    return 0;
}