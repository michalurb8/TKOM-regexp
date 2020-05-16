#pragma once

struct Token
{
    char value;                 //token value stored as a string
    unsigned int textPos;       //token position in text, used for debugging
    bool escaped;

    Token();
};

void print(Token arg);          //for debugging

bool checktest(const Token& arg);
bool checkOperator(const Token& arg);
bool checkSymbol(const Token& arg);
bool checkInBrackets(const Token& arg);
bool checkAlt(const Token& arg);
bool checkLParen(const Token& arg);
bool checkRParen(const Token& arg);
bool checkLBracket(const Token& arg);
bool checkRBracket(const Token& arg);
bool checkCaret(const Token& arg);
bool checkDash(const Token& arg);
bool checkEOT(const Token& arg);