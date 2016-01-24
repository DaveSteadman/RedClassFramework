// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// %license%
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIParseStack.h"

// ============================================================================
// Creation & Init
// ============================================================================



// ============================================================================
// Simple access routines
// ============================================================================
/*

void RedVSIParseStack::QueueItem(RedVSIParseTreeInterface* pNode)
{
    cList.AddLast(pNode);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIStringDataMap::FindData(RedString cId, RedType*& pData)
{
    return cMapList.Find(cId, pData);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int RedVSIStringDataMap::FindIdByPos(int iPos, RedString& cId)
{
    return cMapList.FindIdByPos(iPos, cId);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int RedVSIStringDataMap::FindDataByPos(int iPos, RedType*& pData)
{
    return cMapList.FindDataByPos(iPos, pData);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSIStringDataMap::NumItems(void)
{
    return cMapList.NumItems();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIStringDataMap::DelItem(RedString cId)
{
    cMapList.Del(cId);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIStringDataMap::DelAllItems(void)
{
    cMapList.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSIStringStringTypeMap RedVSIStringDataMap::GetTypeList(void)
{
    RedVSIStringStringTypeMap cTypeList;
    
    IteratorType cIt(&cMapList);
    cIt.First();
    
    while (!cIt.IsDone())
    {
        RedString  cCurrId   = cIt.CurrentId();
        RedType*   pCurrData = cIt.CurrentData();
        
        cTypeList.AddItem( cCurrId, pCurrData->Type() );
        
        cIt.Next();
    }
    return cTypeList;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/