#pragma once

struct Token
{
    char value;                 //token value stored as a character
    unsigned int textPos;       //token position in text, used for debugging
    bool escaped;               //flag set if character was escaped

    Token();
};

bool checkOperator(const Token& arg);
bool checkSymbol(const Token& arg);
bool checkInSet(const Token& arg);
bool checkAlt(const Token& arg);
bool checkLParen(const Token& arg);
bool checkRParen(const Token& arg);
bool checkLBracket(const Token& arg);
bool checkRBracket(const Token& arg);
bool checkCaret(const Token& arg);
bool checkDash(const Token& arg);
bool checkDot(const Token& arg);
bool checkEOT(const Token& arg);