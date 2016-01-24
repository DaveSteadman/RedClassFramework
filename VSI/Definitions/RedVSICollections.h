
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSICmdInterface;
class RedVSIParseTreeInterface;
class RedVSILangElement;

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedStackLIFO<RedVSICmdInterface*> RedVSICmdStack;

typedef RedDoubleLinkedList<RedVariant>         RedVSIDataList;
typedef RedDoubleLinkedListIterator<RedVariant> RedVSIDataListIterator;

typedef RedMapList<int, RedType*>           RedVSIIntDataMap;
typedef RedMapListIterator<int, RedType*>   RedVSIIntDataMapIterator;

// Stack of parse tree elements, to order execution
typedef RedStackLIFO<RedVSIParseTreeInterface*> RedVSIParseStack;

// Map of parse tree elements and results
typedef RedMapList<RedVSIParseTreeInterface*, RedVariant>         RedVSIParseDataMap;
typedef RedMapListIterator<RedVSIParseTreeInterface*, RedVariant> RedVSIParseDataMapIterator;

typedef RedDoubleLinkedList<RedVSIParseTreeInterface*>         RedVSIParseList;
typedef RedDoubleLinkedListIterator<RedVSIParseTreeInterface*> RedVSIParseListIterator;


typedef RedMapList<RedString, RedVSILangElement>           RedVSIStringLangElementMap;
typedef RedMapListIterator<RedString, RedVSILangElement>   RedVSIStringLangElementMapIterator;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

