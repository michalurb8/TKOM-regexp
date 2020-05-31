#include "Parser.h"
#include <vector>

Parser::Parser(std::string text)
:scanner(text)
{
}

void Parser::setRegExp(std::string text)
{
    scanner = Scanner(text);
}

upNode Parser::Parse() //Reg -> Alt, $;
{
    accept(); //load first token to the scanner
    Node::reset(); //reset the tree structure
    upNode root = nullptr;

    //Parsing ALT:
    upNode alt = ParseAlt();
    if(alt == nullptr) throw "No expression detected.";

    //Parsing $:
    if(checkEOT(scanner.getCurrentToken()))
    {
        upNode eot = std::make_unique<SymbolNode>(0x03);
        root = std::make_unique<ConNode>(std::move(alt), std::move(eot));
    }
    else throw "Expecting EOT";

    return root;
}

upNode Parser::ParseAlt() //Alt -> Con, {"|", Con};
{
    //Parsing CON:
    upNode leftAlt = ParseCon();
    if(leftAlt == nullptr) throw "Alternative should start with concatenation";

    //Checking if next token is |, if so, parsing CON again:
    while(checkAlt(scanner.getCurrentToken()))
    {
        accept();
        upNode rightAlt = ParseCon();
        if(rightAlt == nullptr) throw "No concatenation after alternative sign";
        leftAlt = std::make_unique<AltNode>(std::move(leftAlt), std::move(rightAlt));
    }

    return leftAlt;
}

upNode Parser::ParseCon() //Con -> Elem, {Elem};
{
    //Parsing element:
    upNode leftCon = ParseElem();
    if(leftCon == nullptr) throw "A concatenation should start with an element";

    //Parsing concatenated elements:
    upNode rightCon = nullptr;
    while((rightCon = ParseElem()) != nullptr)
    {
        leftCon = std::make_unique<ConNode>(std::move(leftCon), std::move(rightCon));
    }

    return leftCon;
}

upNode Parser::ParseElem() //Elem -> (symbol, Paren, Set), [op];
{
    //Parsing symbol:
    upNode elem = ParseSymbol();
    //Parsing paren:
    if(elem == nullptr) elem = ParseParen();
    //Parsing set:
    if(elem == nullptr) elem = ParseSet();
    if(elem == nullptr) return nullptr;

    //If no operator, returning elem:
    if(!checkOperator(scanner.getCurrentToken()))
    {
        return elem;
    }

    upNode op = nullptr;
    switch(scanner.getCurrentToken().value)
    {
        case '*':
            op = std::make_unique<KleeneNode>(std::move(elem));
            break;
        case '+':
            op = std::make_unique<PlusNode>(std::move(elem));
            break;
        case '?':
            op = std::make_unique<OptionalNode>(std::move(elem));
            break;
        default:
            throw "Wrong operator";
    }
    accept();
    return op;
}

upNode Parser::ParseParen() //Paren -> "(", Alt, ")";
{
    //Parsing (:
    if(checkLParen(scanner.getCurrentToken())) accept();
    else return nullptr;

    //Parsing ALT:
    upNode paren = ParseAlt();
    if(paren == nullptr) throw "There must be an alternative inside ()";

    //Parsing ):
    if(checkRParen(scanner.getCurrentToken())) accept();
    else throw "No closing bracket";

    return paren;
}

charRange Parser::ParseInSet()//(charMap& arg) //Inter -> inset, ["-", inset];
{
    char first = 5;
    char second = 10;
    //Parsing first element of interval:
    if(checkInSet(scanner.getCurrentToken()))
    {
        first = scanner.getCurrentToken().value;
        accept();
    }
    else return charRange{0x03,0x03};

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
    } //if not, returning
    else return charRange{first, first};

    return charRange{first,second};
}

upNode Parser::ParseSet()
//Set -> "[", ["^"], ("]" | InSet), {InSet}, "]";
{
    //Parse [:
    if(checkLBracket(scanner.getCurrentToken())) accept();
    else return nullptr;

    bool caret = false;
    charRange range = {0x03, 0x03};
    std::vector<charRange> ranges;

    //Parse ^ (optional)
    if(checkCaret(scanner.getCurrentToken()))
    {
        accept();
        caret = true;
    }
    //Parse ] as an element (optional)
    if(checkRBracket(scanner.getCurrentToken()))
    {
        accept();
        ranges.push_back(charRange{']',']'});
    }
    else
    {
        range = ParseInSet();
        if(range.first == 0x03) throw "Set cannot be empty []";
        ranges.push_back(range);
    }
    
    //Parse set symbols in a loop:
    while((range = ParseInSet()).first != 0x03)
    {
        ranges.push_back(range);
    }

    //Parse ]:
    if(checkRBracket(scanner.getCurrentToken())) accept();
    else throw "Expecting a ] symbol";


    upNode set;
    if(caret)
        set = std::make_unique<NegativeSetNode>(ranges);
    else
        set = std::make_unique<SetNode>(ranges);

    return set;
}

upNode Parser::ParseSymbol()
{
    upNode symbol = nullptr;
    if(checkSymbol(scanner.getCurrentToken()))
    {
        if(checkDot(scanner.getCurrentToken()))
        {
            std::vector<charRange> empty;
            symbol = std::make_unique<NegativeSetNode>(empty);
        }
        else
        {
            symbol = std::make_unique<SymbolNode>(scanner.getCurrentToken().value);
        }
        accept();
    }
    return symbol;
}

unsigned int Parser::getErrorPos() const
{
    return scanner.getCurrentToken().textPos;
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