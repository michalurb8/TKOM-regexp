#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"

int main()
{
    //EXAMPLE USE OF THE SCANNER
    std::string regexp = R"(a*[]]\+[])";        //store a regular expression in a string
    Source source(regexp);                      //create a source object for that string
    Scanner scanner(&source);                   //create a scanner object for the source
    Scanner::returnCode code;

    Token* tokenPtr = new Token();              //create a token
    while(tokenPtr->getType() != Token::EOT)    //return token until EOT
    {
        code = scanner.getNextToken(tokenPtr);
        if(code != Scanner::SUCCESS) std::cout << "ERROR, code: " << code << std::endl;
        else tokenPtr->print();
    }
    //program outputs all tokens correctly,
    //also correctly recognizes a missing bracket and returns a proper error code
    delete tokenPtr;
    return 0;
}



//other regular expressions to test on:

//std::string regexp = R"([]][^dsfg][][][^^][a][a[]])";
//std::string regexp = R"(!@#$%^&*()_-=+}{][:""]}":/?><,.")";