#include "Parser.h"
#include <iostream>

Parser::Parser(std::string text)
:errorDesc(""), scanner(text), valid(false)
{
}

upNode Parser::Parse() //Reg -> Alt, $;
{
    accept();
    upNode root = nullptr;
    valid = false;

    //Parsing ALT:
    upNode alt = ParseAlt();
    if(alt == nullptr) throw "No expression detected.";

    //Parsing $:
    if(checkEOT(scanner.getCurrentToken()))
    {
        upNode eot = std::make_unique<SymbolNode>(0x03);
        root = std::make_unique<ConNode>(alt, eot);
    }
    else throw "Expecting EOT";

    valid = true;
    return root;
}

upNode Parser::ParseAlt() //Alt -> Con, {"|", Con};
{
    upNode leftAlt = nullptr;

    //Parsing CON:
    leftAlt = ParseCon();
    if(leftAlt == nullptr) throw "Alternative should start with concatenation";

    //Checking if next token is |, if so, parsing CON again:
    while(checkAlt(scanner.getCurrentToken()))
    {
        accept();
        upNode rightAlt = ParseCon();
        if(rightAlt == nullptr) throw "No concatenation after alternative sign";
        leftAlt = std::make_unique<AltNode>(leftAlt, rightAlt);
    }

    return leftAlt;
}

upNode Parser::ParseCon() //Con -> Elem, {Elem};
{
    upNode leftCon = nullptr;
    
    //Parsing element:
    leftCon = ParseElem();
    if(leftCon == nullptr) throw "A concatenation should start with an element";

    //Parsing concatenated elements:
    upNode rightCon = nullptr;
    while((rightCon = ParseElem()) != nullptr)
    {
        leftCon = std::make_unique<ConNode>(leftCon, rightCon);
    }

    return leftCon;
}

upNode Parser::ParseElem() //Elem -> (symbol, Paren, Set), [op];
{
    upNode elem = nullptr;
    //Parsing symbol:
    elem = ParseSymbol();
    //Parsing paren:
    if(elem == nullptr) elem = ParseParen();
    //Parsing set:
    if(elem == nullptr) elem = ParseSet();
    if(elem == nullptr) return nullptr;

    //Parsing operator:
    upNode op = ParseOp(elem);
}

upNode Parser::ParseParen() //Paren -> "(", Alt, ")";
{
    upNode paren = nullptr;

    //Parsing (:
    if(checkLParen(scanner.getCurrentToken())) accept();
    else return nullptr;

    //Parsing ALT:
    paren = ParseAlt();
    if(paren == nullptr) throw "There must be an alternative inside ()";

    //Parsing ):
    if(checkRParen(scanner.getCurrentToken())) accept();
    else throw "No closing bracket";

    return paren;
}

bool Parser::ParseInSet()//(charMap& arg) //Inter -> inset, ["-", inset];
{
    //cale do zmiany
    /*unsigned char first = 5;
    unsigned char second = 10;
    //Parsing first element of interval:
    if(checkInSet(scanner.getCurrentToken()))
    {
        first = scanner.getCurrentToken().value;
        accept();
    }
    else return false;

    //checking if - is next:
    if(checkDash(scanner.getCurrentToken()))
    {
        accept();
        //if so, parsing second element:
        if(checkInSet(scanner.getCurrentToken()))
        {
            second = scanner.getCurrentToken().value;
            accept();
        }
        else throw "'-' must be followed by a symbol";
    }
    return true;*/
}

upNode Parser::ParseSet() //Set -> "[", ["^"], ("]" | InSet), {InSet}, "]";
{
    /*
    //Parse [:
    if(checkLBracket(scanner.getCurrentToken())) accept();
    else return nullptr;

    NodeSet* set = new NodeSet();
    //Parse ^ (optional)
    if(checkCaret(scanner.getCurrentToken()))
    {
        accept();
        set->caret = true;
    }
    //Parse ] as an element
    if(checkRBracket(scanner.getCurrentToken()))
    {
        accept();
        set->RBracket = true;
    }
    else if(!ParseInSet()) throw "Set cannot be empty []";
    
    //Parse set symbols in a loop:
    while(ParseInSet()) {}

    //Parse ]:
    if(checkRBracket(scanner.getCurrentToken())) accept();
    else throw "Expecting a ] symbol";

    return set;*/
}

upNode Parser::ParseSymbol()
{
    upNode symbol = nullptr;
    if(checkSymbol(scanner.getCurrentToken()))
    {
        symbol = std::make_unique<SymbolNode>();
        accept();
    }
    return symbol;
}

upNode Parser::ParseOp(upNode elem)
{
    upNode op = nullptr;
    if(checkOperator(scanner.getCurrentToken()))
    {
        switch(scanner.getCurrentToken().value)
        {
            case '*':
                op = std::make_unique<KleeneNode>(elem);
                break;
            case '+':
                op = std::make_unique<PlusNode>(elem);
                break;
            case '?':
                op = std::make_unique<OptionalNode>(elem);
                break;
            default:
                throw "Wrong operator";
        }
        accept();
    }
    return op;
}

unsigned int Parser::getErrorPos() const
{
    return scanner.getCurrentToken().textPos;
}

const std::string& Parser::getErrorDesc() const
{
    return errorDesc;
}

bool Parser::getCorrect() const
{
    return valid;
}

void Parser::accept()
{
    scanner.getNextToken();
}

//parsing according to the following grammar:
/*
    Reg -> Alt, $;
    Alt -> Con, {"|", Con};
    Con -> Elem, {Elem};
    Elem -> (symbol, Paren, Set), [op];
    Paren -> "(", Alt, ")";
    Set -> "[", ["^"], ("]" | Inter), {Inter}, "]";
    Inter -> inset, ["-", inset];

    symbol -> ?all escaped? + "]" + "." + "^" + "$" + "-";
    inset -> ?all? - "-" - "]";
    op -> "*", "+", "?";
*/