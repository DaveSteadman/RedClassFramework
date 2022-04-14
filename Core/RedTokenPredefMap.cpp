// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

#include "RedTokenPredefMap.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
RedTokenPredefMap* RedTokenPredefMap::m_instanceSingleton = nullptr;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//void RedTokenPredefMap::Add(const RedDataString& cStr, const RedTokenPredefType& cElem)
//{
//    cMap.Add(cStr, cElem); 
//}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefMap::FindPredefFromString(RedDataString cCheckStr, RedTokenPredefType& cElem)
{
    MapListItType cIt(&cTokenMap);

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone()) 
    {
        // Get the item from the list
        RedDataString       cCurrMapStr  = cIt.CurrentId();
        RedTokenPredefType cCurrMapElem = cIt.CurrentData();

        // If the strings match, return the corresponding element
        if (cCheckStr == cCurrMapStr)
        {
            cElem = cCurrMapElem;
            return true;
        }

        // move onto the next item in the list
        cIt.Next();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTokenPredefMap::FindStringFromPredef(RedTokenPredefType cCheckElem, RedDataString& cStr)
{
    MapListItType cIt(&cTokenMap);

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone()) 
    {
        // Get the item from the list
        RedDataString      cCurrMapStr  = cIt.CurrentId();
        RedTokenPredefType cCurrMapElem = cIt.CurrentData();

        // If the strings match, return the corresponding element
        if (cCheckElem == cCurrMapElem)
        {
            cStr =  cCurrMapStr;
            return true;
        }

        // move onto the next item in the list
        cIt.Next();
    }
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

unsigned RedTokenPredefMap::CountMatchCandidates(RedDataString& cCheckStr)
{
    // create map iterator and initialise outputs
    MapListItType      cIt(&cTokenMap);
    RedTokenPredefType cElem;
    unsigned           iNumMatches = 0;
    //int             iCheckLen = cCheckStr.Length();

    // Loop through all the items in the list
    cIt.First();
    while (!cIt.IsDone())
    {
        // Get the item from the list
        RedDataString       cCurrMapStr  = cIt.CurrentId();
        //RedTokenPredefType cCurrMapElem = cIt.CurrentData();

        // if the map string is longer than the check string, create a cropped
        // version of the map string to check against
        if (cCurrMapStr.Length() > cCheckStr.Length())
        {
            RedDataString cCroppedMapStr = cCurrMapStr.SubStr(0, cCheckStr.ContentSize());
            
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

void RedTokenPredefMap::SetupTokenMap(void)
{
    cTokenMap.Add(kIOStringKeywordAttrib,                   RedTokenPredefType::KeywordAttribute());
    cTokenMap.Add(kIOStringKeywordBool,                     RedTokenPredefType::KeywordBool());
    cTokenMap.Add(kIOStringKeywordChar,                     RedTokenPredefType::KeywordChar());
    cTokenMap.Add(kIOStringKeywordClass,                    RedTokenPredefType::KeywordClass());
    cTokenMap.Add(kIOStringKeywordCode,                     RedTokenPredefType::KeywordCode());
    cTokenMap.Add(kIOStringKeywordElse,                     RedTokenPredefType::KeywordElse());
    cTokenMap.Add(kIOStringKeywordEndif,                    RedTokenPredefType::KeywordEndif());
    cTokenMap.Add(kIOStringKeywordEndloop,                  RedTokenPredefType::KeywordEndloop());
    cTokenMap.Add(kIOStringKeywordFalse,                    RedTokenPredefType::KeywordFalse());
    cTokenMap.Add(kIOStringKeywordHeap,                     RedTokenPredefType::KeywordHeap());
    cTokenMap.Add(kIOStringKeywordHelp,                     RedTokenPredefType::KeywordHelp());
    cTokenMap.Add(kIOStringKeywordIf,                       RedTokenPredefType::KeywordIf());
    cTokenMap.Add(kIOStringKeywordLet,                      RedTokenPredefType::KeywordLet());
    cTokenMap.Add(kIOStringKeywordList,                     RedTokenPredefType::KeywordList());
    cTokenMap.Add(kIOStringKeywordLog,                      RedTokenPredefType::KeywordLog());
    cTokenMap.Add(kIOStringKeywordLoop,                     RedTokenPredefType::KeywordLoop());
    cTokenMap.Add(kIOStringKeywordName,                     RedTokenPredefType::KeywordName());
    cTokenMap.Add(kIOStringKeywordNew,                      RedTokenPredefType::KeywordNew());
    cTokenMap.Add(kIOStringKeywordNumber,                   RedTokenPredefType::KeywordNumber());
    cTokenMap.Add(kIOStringKeywordParams,                   RedTokenPredefType::KeywordParams());
    cTokenMap.Add(kIOStringKeywordParent,                   RedTokenPredefType::KeywordParent());
    cTokenMap.Add(kIOStringKeywordRecord,                   RedTokenPredefType::KeywordRecord());
    cTokenMap.Add(kIOStringKeywordReturn,                   RedTokenPredefType::KeywordReturn());
    cTokenMap.Add(kIOStringKeywordRoutine,                  RedTokenPredefType::KeywordRoutine());
    cTokenMap.Add(kIOStringKeywordStack,                    RedTokenPredefType::KeywordStack());
    cTokenMap.Add(kIOStringKeywordString,                   RedTokenPredefType::KeywordString());
    cTokenMap.Add(kIOStringKeywordThen,                     RedTokenPredefType::KeywordThen());
    cTokenMap.Add(kIOStringKeywordTrue,                     RedTokenPredefType::KeywordTrue());
    cTokenMap.Add(kIOStringKeywordWhile,                    RedTokenPredefType::KeywordWhile());

    cTokenMap.Add(kIOStringKeywordAdd,                      RedTokenPredefType::KeywordAdd());
    cTokenMap.Add(kIOStringKeywordData,                     RedTokenPredefType::KeywordData());
    cTokenMap.Add(kIOStringKeywordExit,                     RedTokenPredefType::KeywordExit());
    cTokenMap.Add(kIOStringKeywordLib,                      RedTokenPredefType::KeywordLib());
    cTokenMap.Add(kIOStringKeywordLog,                      RedTokenPredefType::KeywordLog());
    cTokenMap.Add(kIOStringKeywordRun,                      RedTokenPredefType::KeywordRun());
    cTokenMap.Add(kIOStringKeywordInit,                     RedTokenPredefType::KeywordInit());
    cTokenMap.Add(kIOStringKeywordList,                     RedTokenPredefType::KeywordList());

    cTokenMap.Add(kIOStringSymbolAssignPlus,                RedTokenPredefType::SymbolAssignPlus());
    cTokenMap.Add(kIOStringSymbolAssignMinus,               RedTokenPredefType::SymbolAssignMinus());
    cTokenMap.Add(kIOStringSymbolAssignMultiply,            RedTokenPredefType::SymbolAssignMultiply());
    cTokenMap.Add(kIOStringSymbolAssignDivide,              RedTokenPredefType::SymbolAssignDivide());
    cTokenMap.Add(kIOStringSymbolAssignEqual,               RedTokenPredefType::SymbolAssignEqual());

    cTokenMap.Add(kIOStringSymbolBracketOpen,               RedTokenPredefType::SymbolBracketOpen());
    cTokenMap.Add(kIOStringSymbolBracketClose,              RedTokenPredefType::SymbolBracketClose());
    cTokenMap.Add(kIOStringSymbolBracketOpenCurly,          RedTokenPredefType::SymbolBracketOpen());
    cTokenMap.Add(kIOStringSymbolBracketCloseCurly,         RedTokenPredefType::SymbolBracketClose());
    cTokenMap.Add(kIOStringSymbolBracketOpenSquare,         RedTokenPredefType::SymbolBracketOpenSquare());
    cTokenMap.Add(kIOStringSymbolBracketCloseSquare,        RedTokenPredefType::SymbolBracketCloseSquare());

    cTokenMap.Add(kIOStringSymbolCompareEqual,              RedTokenPredefType::SymbolCompareEqual());
    cTokenMap.Add(kIOStringSymbolCompareNotEqual,           RedTokenPredefType::SymbolCompareNotEqual());
    cTokenMap.Add(kIOStringSymbolCompareLessThan,           RedTokenPredefType::SymbolCompareLessThan());
    cTokenMap.Add(kIOStringSymbolCompareGreaterThan,        RedTokenPredefType::SymbolCompareGreaterThan());
    cTokenMap.Add(kIOStringSymbolCompareGreaterThanOrEqual, RedTokenPredefType::SymbolCompareGreaterThanOrEqual());
    cTokenMap.Add(kIOStringSymbolCompareLessThanOrEqual,    RedTokenPredefType::SymbolCompareLessThanOrEqual());

    cTokenMap.Add(kIOStringSymbolLogicAnd,                  RedTokenPredefType::SymbolLogicAnd());
    cTokenMap.Add(kIOStringSymbolLogicNot,                  RedTokenPredefType::SymbolLogicNot());
    cTokenMap.Add(kIOStringSymbolLogicOr,                   RedTokenPredefType::SymbolLogicOr());

    cTokenMap.Add(kIOStringSymbolOperatorPlus,              RedTokenPredefType::SymbolOperatorPlus());
    cTokenMap.Add(kIOStringSymbolOperatorMinus,             RedTokenPredefType::SymbolOperatorMinus());
    cTokenMap.Add(kIOStringSymbolOperatorMultiply,          RedTokenPredefType::SymbolOperatorMultiply());
    cTokenMap.Add(kIOStringSymbolOperatorDivide,            RedTokenPredefType::SymbolOperatorDivide());
    cTokenMap.Add(kIOStringSymbolOperatorPower,             RedTokenPredefType::SymbolOperatorPower());

    cTokenMap.Add(kIOStringSymbolComma,                     RedTokenPredefType::SymbolComma());
    cTokenMap.Add(kIOStringSymbolPeriod,                    RedTokenPredefType::SymbolPeriod());
    cTokenMap.Add(kIOStringSymbolDoubleColon,               RedTokenPredefType::SymbolDoubleColon());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

