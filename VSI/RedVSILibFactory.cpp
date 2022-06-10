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
#include "RedCoreConsts.h"

#include <stdio.h>
#include "stdlib.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILibFactory.h"
#include "RedTokenFactory.h"
#include "RedTokenBuffer.h"
#include "RedVSICmdFactory.h"
#include "RedVSICmdSerialiser.h"

using namespace Red::Core;

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedVSILibFactory::RedVSILibFactory(RedVSILib* pNewLib)
{
    pLib = pNewLib;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Tml
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSILibFactory::InputTmlClass(RedTinyMLElement* pTopTmlNode, RedLog& cAnalysis)
{
    if ((pTopTmlNode == NULL) || (!pTopTmlNode->IsNode()))
    {
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlClass: Top-level node not TinyML Node");
        return;
    }

    if (pTopTmlNode->Name() != kIOStringKeywordClass)
    {
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlClass: Top-level node not a class");
        return;
    }

    RedVSILibClass* pNewClass = new RedVSILibClass;

    RedTinyMLNode* pTmlNode = (RedTinyMLNode*)pTopTmlNode;


    RedTinyMLLeaf* pName = RedTinyMLAction::NodeFirstNamedLeaf(*pTmlNode, kIOStringKeywordName);
    RedDataString x(pName->Data());
    pNewClass->SetClassName(x);

    RedTinyMLNode::TmlElementListItType routineIt = pTmlNode->ElementListIterator();

    routineIt.First();
    while (!routineIt.IsDone())
    {
        RedTinyMLElement* pCurrElem = routineIt.CurrentItem();

        if (pCurrElem->IsNode())
        {
            RedTinyMLNode* pCurrNode = dynamic_cast<RedTinyMLNode*>(pCurrElem);
            if (pCurrNode->Name() == kIOStringKeywordRoutine)
            {
                RedVSILibRoutine* newRoutine = InputTmlRoutine(*pCurrNode, cAnalysis);

                if ((newRoutine != NULL) && (!cAnalysis.ContainsError()))
                    pNewClass->AddRoutine(newRoutine);
            }
        }
        routineIt.Next();
    }

    if (!cAnalysis.ContainsError())
    {
        pLib->AddClass(pNewClass);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Add a Tml-Class to library
RedVSILibRoutine* RedVSILibFactory::InputTmlRoutine(RedTinyMLNode& cRoutineNode, RedLog& cAnalysis)
{
    if (cRoutineNode.Name() != kIOStringKeywordRoutine)
    {
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Top-level node not a routine");
        return NULL;
    }

    RedVSILibRoutine* newRoutine = new RedVSILibRoutine;

    // name
    RedTinyMLLeaf* pName = RedTinyMLAction::NodeFirstNamedLeaf(cRoutineNode, kIOStringKeywordName);
    if (pName == NULL)
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Routine has no name");
    else
        newRoutine->cName = pName->Data();

    // params
    RedTinyMLNode* pParams = RedTinyMLAction::NodeFirstNamedNode(cRoutineNode, kIOStringKeywordParams);
    if (pParams != NULL)
    {
        RedTinyMLNode::TmlElementListItType paramIt = pParams->ElementListIterator();
        paramIt.First();
        while (!paramIt.IsDone())
        {
            RedTinyMLElement* pElem = paramIt.CurrentItem();
            if (pElem->IsLeaf())
            {
                RedTinyMLLeaf* pLeaf = (RedTinyMLLeaf*)pElem;
                RedDataString paramName(pLeaf->Name());
                RedDataString paramTypeStr(pLeaf->Data());

                RedDataType paramType;
                if      (paramTypeStr == kIOStringKeywordBool)   paramType = kDataTypeBool;
                else if (paramTypeStr == kIOStringKeywordChar)   paramType = kDataTypeChar;
                else if (paramTypeStr == kIOStringKeywordNumber) paramType = kDataTypeNum;
                else if (paramTypeStr == kIOStringKeywordString) paramType = kDataTypeStr;

                newRoutine->AddParam(paramName, paramType);
            }
            paramIt.Next();
        }
    }

    // code
    RedTinyMLLeaf* pTmlCode = RedTinyMLAction::NodeFirstNamedLeaf(cRoutineNode, kIOStringKeywordCode);
    if (pTmlCode == NULL)
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Routine has no code");
    else
    {
        RedDataString c = pTmlCode->Data();

        RedTokenBuffer cInputBuffer;
        int iCreateResult = RedTokenFactory::CreateTokens(c, cInputBuffer);

        RedDataString debugText = cInputBuffer.DebugDump();


        if (iCreateResult && !cAnalysis.ContainsError())
        {
            // Process the code, creating the tree of code objects
            RedVSICmd* pVsiCode = RedVSICmdFactory::RunConstuctionCompetition(cInputBuffer, cAnalysis);

            newRoutine->SetCode(pVsiCode);
        }
    }

    // add or lose the new class
    if (cAnalysis.ContainsError())
    {
        delete newRoutine;
        newRoutine = NULL;
    }

    return newRoutine;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedVSILibFactory::OutputTmlClass(const RedDataString& classname)
{
    // Find the class
    RedVSILibClass* pClass = pLib->FindClass(classname);
    if (pClass == NULL) return NULL;

    RedTokenPredefMap* pTokenMap = RedTokenPredefMap::getInstance();

    // Create the class node
    RedTinyMLNode* pClassTml = new RedTinyMLNode("class");
    pClassTml->CreateChildLeaf("name", pClass->ClassName());

    // Iterate across each routine in the class
    RedVSILibClass::RoutineIteratorType cIt = pClass->GetRoutineIterator();
    cIt.First();
    while (!cIt.IsDone())
    {
        // find the routine we want
        RedVSILibRoutine* pCurrRtn = cIt.CurrentItem();

        // get the routine details
        RedDataString                  cOutName;
        RedVSIParamTypeList cOutParamList;
        RedVSICmd* pOutCode;
        pCurrRtn->GetDetails(cOutName, cOutParamList, pOutCode);

        // Create and name the routine node
        RedTinyMLNode* pRoutine = new RedTinyMLNode("routine");
        pRoutine->CreateChildLeaf("name", cOutName);

        // O=convert the params if we have any
        if (cOutParamList.NumItems() > 0)
        {
            RedTinyMLNode* pParamNode = pRoutine->CreateChildNode("params");

            RedVSIParamTypeListIterator paramIt(&cOutParamList);
            paramIt.First();
            while (!paramIt.IsDone())
            {
                RedDataString         paramName = paramIt.CurrentId();
                RedDataType           paramType = paramIt.CurrentData();
                RedTokenPredefType    paramTypeIoElem;
                RedDataString         paramTypeStr;

                if      (paramType.IsBool())    paramTypeIoElem = RedTokenPredefType::KeywordBool();
                else if (paramType.IsChar())    paramTypeIoElem = RedTokenPredefType::KeywordChar();
                else if (paramType.IsList())    paramTypeIoElem = RedTokenPredefType::KeywordList();
                else if (paramType.IsNum())     paramTypeIoElem = RedTokenPredefType::KeywordNumber();
                else if (paramType.IsRecord())  paramTypeIoElem = RedTokenPredefType::KeywordRecord();
                else if (paramType.IsStr())     paramTypeIoElem = RedTokenPredefType::KeywordString();

                pTokenMap->FindStringFromPredef(paramTypeIoElem, paramTypeStr);
                pParamNode->CreateChildLeaf(paramName, paramTypeStr);

                paramIt.Next();
            }
        }

        // convert the code into tokens, and then to a string
        RedTokenBuffer cTokenBuffer;
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pOutCode);
        RedBufferOutput outBuf;
        RedVSICmdSerialiser::TokenBufferToOutputBuffer(cTokenBuffer, outBuf);
        pRoutine->CreateChildLeaf("code", outBuf.ExtractData());

        // Add the completed routine into the class
        pClassTml->AddChildNode(pRoutine);

        // Move onto the next class in the library
        cIt.Next();
    }

    return pClassTml;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedVSILibFactory::OutputTmlRoutine(const RedDataString& classname, const RedDataString& routinename)
{
    RedVSILibClass* pClass = pLib->FindClass(classname);

    RedVSILibClass::RoutineIteratorType cIt = pClass->GetRoutineIterator();
    cIt.First();
    while (!cIt.IsDone())
    {
        //// find the routine we want
        //RedVSILibRoutine* pCurrRtn = cIt.CurrentItem();
        //if (pCurrRtn->cName == routinename)
        //{
        //    // get the routine details
        //    RedDataString                  cOutName;
        //    RedVSIStringLangElementMap cOutParamList;
        //    RedVSICmd* pOutCode;
        //    pCurrRtn->GetDetails(cOutName, cOutParamList, pOutCode);

        //    // convert the code into tokens
        //    RedTokenBuffer cTokenBuffer;
        //    RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pOutCode);

        //    // turn code tokens into a string
        //    RedTinyMLNode* pRoutine = new RedTinyMLNode("routine");
        //    pRoutine->CreateChildLeaf("name", cOutName);
        //}

        cIt.Next();
    }

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


