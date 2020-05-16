#include "Parser.h"
#include <iostream>

Parser::Parser(std::string text)
:errorDesc(""), scanner(text), valid(false)
{
}

Node* Parser::Parse() //Reg -> Alt, $;
{
    accept();
    Node* root = nullptr;
    valid = false;

    //Parsing ALT:
    Node* alt = ParseAlt();
    if(alt == nullptr) throw "No expression detected.";

    //Parsing $:
    if(checkEOT(scanner.getCurrentToken()))
    {
        Node* eot = new Node('E', Node::END);
        root = new Node(alt, eot, 'R', Node::CON);
    }
    else throw "Expecting EOT";

    valid = true;
    return root;
}

Node* Parser::ParseAlt() //Alt -> Con, {"|", Con};
{
    Node* leftAlt = nullptr;

    //Parsing CON:
    leftAlt = ParseCon();
    if(leftAlt == nullptr) throw "Alternative should start with concatenation";

    //Checking if next token |, if so, parsing CON again:
    while(checkAlt(scanner.getCurrentToken()))
    {
        accept();
        Node* rightAlt = ParseCon();
        if(rightAlt == nullptr) throw "No concatenation after alternative sign";
        leftAlt = new Node(leftAlt, rightAlt, '|', Node::ALT);
    }


    return leftAlt;
}

Node* Parser::ParseCon() //Con -> Elem, {Elem};
{
    Node* leftCon = nullptr;
    
    //Parsing element:
    leftCon = ParseElem();
    if(leftCon == nullptr) throw "A concatenation should start with an element";

    //Parsing concatenated elements:
    Node* rightCon = nullptr;
    while((rightCon = ParseElem()) != nullptr)
    {
        leftCon = new Node(leftCon, rightCon, '*', Node::CON);
    }

    return leftCon;
}

Node* Parser::ParseElem() //Elem -> (symbol, Paren, Set), [op];
{
    Node* elem = nullptr;
    //Parsing symbol:
    elem = ParseSymbol();
    //Parsing paren:
    if(elem == nullptr) elem = ParseParen();
    //Parsing set:
    if(elem == nullptr) elem = ParseSet();
    if(elem == nullptr) return nullptr;

    //Parsing operator:
    elem = ParseOp(elem);

    return elem;
}

Node* Parser::ParseParen() //Paren -> "(", Alt, ")";
{
    Node* paren = nullptr;

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

void Parser::ParseInter()//(charMap& arg) //Inter -> inset, ["-", inset];
{
    Node* interval;
    //Parsing first element of interval:
    if(checkInBrackets(scanner.getCurrentToken())) accept();
    else return;
    //Checking if it is a set (- sign):
    if(checkInterval(scanner.getCurrentToken()))
    {
        accept();
        //if so, parsing second element:
        if(checkInBrackets(scanner.getCurrentToken())) accept();
        else
        {
            errorDesc = "Current token does not match any set[] element";
            //return false;
        }
    }
    return;
}

Node* Parser::ParseSet() //Set -> "[", ["^"], ("]" | Inter), {Inter}, "]";
{
    Node* set = nullptr;
    bool caret = false;
    bool RBracet = false;
    //trying to parse first bracket:
    if(checkLBracket(scanner.getCurrentToken())) accept();
    else return nullptr;
    //trying to parse caret (optional):
    if(checkCaret(scanner.getCurrentToken()))
    {
        accept();
        caret = true;
    }
    //trying to parse right bracket as an element
    if(checkRBracket(scanner.getCurrentToken()))
    {
        accept();
        RBracet = true;
    }
    //otherwise parsing a set symbol
    else
    {
        return set;
    }
    if(true) {}
    else throw  "ABC";
    {
        errorDesc = "[] cannot be empty";
        //return false;
    }
    //Parsing set symbols in a loop
    //while(ParseInter()){}
    //Parsing the right bracket
    if(checkRBracket(scanner.getCurrentToken()))
    {
        accept();
    }
    else
    {
        errorDesc = "Current token does not match ] symbol";
        //return false;
    }
    return nullptr;
}

Node* Parser::ParseSymbol()
{
    Node* symbol = nullptr;
    if(checkSymbol(scanner.getCurrentToken()))
    {
        symbol = new Node(scanner.getCurrentToken().value, Node::SYMBOL);
        accept();
    }
    return symbol;
}

Node* Parser::ParseOp(Node* arg)
{
    Node* op = nullptr;
    if(checkOperator(scanner.getCurrentToken()))
    {
        switch(scanner.getCurrentToken().value)
        {
            case '*':
                op = new Node(arg, nullptr, '*', Node::KLEENE);
                break;
            case '+':
                op = new Node(arg, nullptr, '+', Node::PLUS);
                break;
            case '?':
                op = new Node(arg, nullptr, '?', Node::OPTIONAL);
                break;
            default:
                throw "Wrong operator";
        }
        accept();
    }
    else op = arg;
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