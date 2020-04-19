#include "Token.h"
#include <iostream>

void Assert(bool check, std::string message)
{
    if(!check) std::cout << "ERROR in test: " << message << std::endl;
}

int main()
{
    Token temp;
    std::string mess = temp.getValue ;
    std::cout << mess << std::endl;
    //Assert(temp.getValue=="", "DEFAULT_TOKEN_EMPTY");
}