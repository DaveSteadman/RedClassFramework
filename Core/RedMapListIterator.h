
#pragma once

// Include Files
#include "RedMapList.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {


template<class IdClass, class DataClass>
class RedMapListIterator
{
public:

    typedef RedMapList<IdClass, DataClass> MapType;
    enum TESearchDir { eForwards, eBackwards };

    RedMapListIterator(MapType* pNewMap);

    void        First(void);
    void        Next(void);
    const int   IsDone(void);
    IdClass     CurrentId(void);
    DataClass   CurrentData(void);

    void        DeleteCurrentItem(void)              { pList->Del(iCurrIndex); };
    void        SetSearchDirection(TESearchDir eDir) { eSearchDir = eDir; };
    const int   GetListIndex(void)                   { return iCurrIndex; };

private:

    int         iCurrIndex;
    MapType*    pList;
    TESearchDir eSearchDir;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
RedMapListIterator<IdClass, DataClass>::RedMapListIterator(MapType* pNewMap)
{
    pList       = pNewMap;
    eSearchDir  = eForwards;
    iCurrIndex  = pList->FirstIndex();

    First();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
void RedMapListIterator<IdClass, DataClass>::First(void)
{
    if (eSearchDir == eForwards)
        iCurrIndex = pList->FirstIndex();
    else
        iCurrIndex = pList->LastIndex();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
void RedMapListIterator<IdClass, DataClass>::Next(void)
{
    if (eSearchDir == eForwards)
        iCurrIndex++;
    else
        iCurrIndex--;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
const int RedMapListIterator<IdClass, DataClass>::IsDone(void)
{
    int iSearchDone = 0;

    if (pList->IsEmpty()) return 1;

    if (eSearchDir == eForwards)
    {
        if (iCurrIndex > pList->LastIndex())
            iSearchDone = 1;
    }
    else
    {
        if (iCurrIndex < pList->FirstIndex())
            iSearchDone = 1;
    }

    return iSearchDone;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
IdClass RedMapListIterator<IdClass, DataClass>::CurrentId(void) 
{
    IdClass Id;
    
    if (!pList->FindIdByIndex(iCurrIndex, Id))
        throw;    
    
    return Id;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class IdClass, class DataClass>
DataClass RedMapListIterator<IdClass, DataClass>::CurrentData(void) 
{
    DataClass Data;
    
    if (!pList->FindDataByIndex(iCurrIndex, Data))
        throw;   
         
    return Data;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


