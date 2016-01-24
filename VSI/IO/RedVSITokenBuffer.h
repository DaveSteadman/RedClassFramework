
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIToken.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSITokenBuffer
{
public:

    typedef RedDoubleLinkedList<RedVSIToken>          ListType;
    typedef RedDoubleLinkedListIterator<RedVSIToken>  IteratorType;

    RedVSITokenBuffer(void) { Init(); };
    
    // Inherited: RedType    
    void    Init(void);
    
    void    AppendToken(const RedVSIToken& cNewTok);

    IteratorType GetIterator(void)    { IteratorType cIt(&cTokenList); return cIt; };

    // all depricated on creation of iterator
    RedVSIToken GetToken(void);
    RedVSIToken GetToken(int iTokenIndex);
    void        SetTokenIndex(int iTokenIndex) { iCurrListIndex = iTokenIndex; };
    int         GetTokenIndex(void)        { return iCurrListIndex; };
    void        SetTokenIndexBackOne(void) { if(iCurrListIndex>0) iCurrListIndex--; };

    int         CurrIndexAtLastToken(void) { return (iCurrListIndex == cTokenList.NumItems()); };

    RedString   DebugDump(void);

private:

    ListType      cTokenList;
    int           iCurrListIndex;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
