
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIIOElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;

class RedVSITokenElementMap
{
public:

    RedVSITokenElementMap(void);
    ~RedVSITokenElementMap(void);

    void Add(const RedString& cStr, const RedVSIIOElement& cElem);

    int  Find(RedString& cCheckStr, RedVSIIOElement& cElem);
    int  FindString(RedVSIIOElement& cCheckElem, RedString& cStr);

    int  CountMatchCandidates(RedString& cCheckStr);

    const int  NumItems(void) const { return cMap.NumItems(); };
    const int  IsEmpty(void)  const { return cMap.IsEmpty();  };

private:

    typedef RedMapList<RedString, RedVSIIOElement>         MapListType;
    typedef RedMapListIterator<RedString, RedVSIIOElement> MapListItType;

    MapListType cMap;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
