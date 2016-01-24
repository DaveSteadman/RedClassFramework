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

#include "RedCoreNamespace.h"

#include "RedVSITokenElementMap.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSITokenElementMap::RedVSITokenElementMap(void)
{

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSITokenElementMap::~RedVSITokenElementMap(void)
{
    cMap.DelAll();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSITokenElementMap::Add(const RedString& cStr, const RedVSIIOElement& cElem)
{
    cMap.Add(cStr, cElem); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSITokenElementMap::Find(RedString& cCheckStr, RedVSIIOElement& cElem)
{
    MapListItType cIt(&cMap);

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone()) 
    {
        // Get the item from the list
        RedString  cCurrMapStr  = cIt.CurrentId();
        RedVSIIOElement cCurrMapElem = cIt.CurrentData();

        // If the strings match, return the corresponding element
        if (cCheckStr == cCurrMapStr)
        {
            cElem = cCurrMapElem;
            return 1;
        }

        // move onto the next item in the list
        cIt.Next();
    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSITokenElementMap::FindString(RedVSIIOElement& cCheckElem, RedString& cStr)
{
    MapListItType cIt(&cMap);

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone()) 
    {
        // Get the item from the list
        RedString  cCurrMapStr  = cIt.CurrentId();
        RedVSIIOElement cCurrMapElem = cIt.CurrentData();

        // If the strings match, return the corresponding element
        if (cCheckElem == cCurrMapElem)
        {
            cStr =  cCurrMapStr;
            return 1;
        }

        // move onto the next item in the list
        cIt.Next();
    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int RedVSITokenElementMap::CountMatchCandidates(RedString& cCheckStr)
{
    // create map iterator and initialise outputs
    MapListItType   cIt(&cMap);
    RedVSIIOElement cElem;
    int             iNumMatches = 0;
    int             iCheckLen = cCheckStr.Length();

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone())
    {
        // Get the item from the list
        RedString       cCurrMapStr  = cIt.CurrentId();
        //RedVSIIOElement cCurrMapElem = cIt.CurrentData();

        // if the map string is longer than the check string, create a cropped
        // version of the map string to check against
        if (cCurrMapStr.Length() > cCheckStr.Length())
        {
            RedString cCroppedMapStr = cCurrMapStr.SubStr(0, iCheckLen-1);
            
            // if the cropped match string matches the check string, we have a potential match
            if (cCroppedMapStr == cCheckStr)
                iNumMatches++;
        }

        // If the string lengths match, and the contents match, increment the 
        // number of matches and set the output
        else if ( (cCurrMapStr.Length()==cCheckStr.Length()) && (cCurrMapStr==cCheckStr) )
        {
            iNumMatches++;
        }

        // move onto the next item in the list
        cIt.Next();
    }
    
    // return false only if we found no matches
    return iNumMatches;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

