#include <iostream>
#include <algorithm>
#include "Node.h"

NodeSet::NodeSet()
:caret(false), RBracket(false)
{
    value = 'S';
    type = Node::SET;
    for(short i = 0; i < 8; ++i) map[i] = 0;
}