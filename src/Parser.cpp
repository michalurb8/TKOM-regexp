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
        root = new Node(alt, eot, '*', Node::CON);
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

bool Parser::ParseInSet(NodeSet* arg)//(charMap& arg) //Inter -> inset, ["-", inset];
{
    unsigned char first = 5;
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
        arg->addChars(first, second);
    }
    else arg->addChar(first);

    std::cout << first << " " << second << std::endl;
    return true;
}

Node* Parser::ParseSet() //Set -> "[", ["^"], ("]" | InSet), {InSet}, "]";
{
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
    else if(!ParseInSet(set)) throw "Set cannot be empty []";
    
    //Parse set symbols in a loop:
    while(ParseInSet(set)) {}

    //Parse ]:
    if(checkRBracket(scanner.getCurrentToken())) accept();
    else throw "Expecting a ] symbol";

    return set;
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