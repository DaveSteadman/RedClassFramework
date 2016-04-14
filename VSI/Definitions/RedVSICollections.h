// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

using namespace Red::Core;

namespace Red {
namespace VSI {

class RedVSICmdInterface;
class RedVSIParseTreeInterface;
class RedVSILangElement;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedStackLIFO<RedVSICmdInterface*> RedVSICmdStack;

typedef RedDoubleLinkedList<RedVariant>         RedVSIVariantList;
typedef RedDoubleLinkedListIterator<RedVariant> RedVSIVariantListIterator;

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

