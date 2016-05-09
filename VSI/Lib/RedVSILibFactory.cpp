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
#include "RedTmlNamespace.h"

#include <stdio.h>
#include "stdlib.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSILibFactory.h"
#include "RedVSITokenFactory.h"
#include "RedVSITokenBuffer.h"
#include "RedVSICmdFactory.h"
#include "RedVSICmdSerialiser.h"

using namespace Red::Core;
using namespace Red::TinyML;

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

void RedVSILibFactory::InputTmlClass(RedTmlNode cClassNode, RedLog& cAnalysis)
{
    if (cClassNode.Name() != kVSIIOElementKeywordClass)
    {
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlClass: Top-level node not a class");
        return;
    }

    RedVSILibClass* pNewClass = new RedVSILibClass;

    RedTmlLeaf* pName = RedTmlAction::NodeFirstNamedLeaf(cClassNode, kVSIIOElementKeywordName);
    RedString x ( pName->Data() );
    pNewClass->SetClassName(x);

    Red::TinyML::RedTmlNode::TmlNodeListItType routineIt = cClassNode.NodeIterator();

    routineIt.First();
    while (!routineIt.IsDone())
    {
        RedTmlElement* pCurrElem = routineIt.CurrentItem();

        if (pCurrElem->IsNode())
        {
            RedTmlNode* pCurrNode = dynamic_cast<RedTmlNode*>(pCurrElem);
            if (pCurrNode->Name() == kVSIIOElementKeywordRoutine)
            {
                RedVSILibRoutine* newRoutine = InputTmlRoutine(*pCurrNode, cAnalysis);

                if ((newRoutine != REDNULL) && (!cAnalysis.IsError()))
                    pNewClass->AddRoutine(newRoutine);
            }
        }
        routineIt.Next();
    }

    if (!cAnalysis.IsError())
    {
        pLib->AddClass(pNewClass);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Add a Tml-Class to library
RedVSILibRoutine* RedVSILibFactory::InputTmlRoutine(RedTmlNode& cRoutineNode, RedLog& cAnalysis)
{
    if (cRoutineNode.Name() != kVSIIOElementKeywordRoutine)
    {
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Top-level node not a routine");
        return REDNULL;
    }

    RedVSILibRoutine* newRoutine = new RedVSILibRoutine;

    // name
    RedTmlLeaf* pName = RedTmlAction::NodeFirstNamedLeaf(cRoutineNode, kVSIIOElementKeywordName);
    if (pName == REDNULL)
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Routine has no name");
    else
        newRoutine->SetName(pName->Data());

    // params
    RedTmlNode* pParams = RedTmlAction::NodeFirstNamedNode(cRoutineNode, kVSIIOElementKeywordParams);
    if (pParams != REDNULL)
    {
        RedTmlNode::TmlNodeListItType paramIt = pParams->NodeIterator();
        paramIt.First();
        while (!paramIt.IsDone())
        {
            RedTmlElement* pElem = paramIt.CurrentItem();
            if (pElem->IsLeaf())
            {
                RedTmlLeaf* pLeaf = (RedTmlLeaf*)pElem;
                RedString paramName(pLeaf->Name());
                RedString paramTypeStr(pLeaf->Data());

                RedVSILangElement paramType;
                if      (paramTypeStr == kVSIIOElementKeywordBool)   paramType=kLangElementTypeBool;
                else if (paramTypeStr == kVSIIOElementKeywordChar)   paramType=kLangElementTypeChar;
                else if (paramTypeStr == kVSIIOElementKeywordNumber) paramType=kLangElementTypeNumber;
                else if (paramTypeStr == kVSIIOElementKeywordString) paramType=kLangElementTypeString;

                newRoutine->AddParam(paramName, paramType);
            }
            paramIt.Next();
        }
    }

    // code
    RedTmlLeaf* pTmlCode = RedTmlAction::NodeFirstNamedLeaf(cRoutineNode, kVSIIOElementKeywordCode);
    if (pTmlCode == REDNULL)
        cAnalysis.AddErrorEvent("Lib Factory: InputTmlRoutine: Routine has no code");
    else
    {
        RedString c = pTmlCode->Data();

        RedVSITokenBuffer cInputBuffer;
        RedVSILibTokenMap tokenLib;

        int iCreateResult = RedVSITokenFactory::CreateTokens(c, tokenLib.cVSILibTokenMap, cInputBuffer);

        RedString debugText = cInputBuffer.DebugDump();


        if (iCreateResult && !cAnalysis.IsError())
        {
            // Process the code, creating the tree of code objects
            RedVSICmdInterface* pVsiCode = RedVSICmdFactory::RunConstuctionCompetition(cInputBuffer, cAnalysis);

            newRoutine->SetCode(pVsiCode);
        }
    }

    // add or lose the new class
    if (cAnalysis.IsError())
    {
        delete newRoutine;
        newRoutine = REDNULL;
    }

    return newRoutine;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlElement* RedVSILibFactory::OutputTmlClass (const RedString& classname)
{
    // Find the class
    RedVSILibClass* pClass = pLib->FindClass(classname);
    if (pClass == REDNULL) return REDNULL;

    // Create the class node
    RedTmlNode* pClassTml = new RedTmlNode("class");
    pClassTml->CreateChildLeaf("name", pClass->ClassName());

    // Iterate across each routine in the class
    RedVSILibClass::RoutineIteratorType cIt = pClass->GetRoutineIterator();
    cIt.First();
    while ( !cIt.IsDone() )
    {
        // find the routine we want
        RedVSILibRoutine* pCurrRtn = cIt.CurrentItem();

        // get the routine details
        RedString                  cOutName;
        RedVSIStringLangElementMap cOutParamList;
        RedVSICmdInterface*        pOutCode;
        pCurrRtn->GetDetails(cOutName, cOutParamList, pOutCode);

        // Create and name the routine node
        RedTmlNode* pRoutine = new RedTmlNode("routine");
        pRoutine->CreateChildLeaf("name", cOutName);

        // O=convert the params if we have any
        if (cOutParamList.NumItems() > 0)
        {
            RedTmlNode* pParamNode = pRoutine->CreateChildNode("params");

            RedVSIStringLangElementMapIterator paramIt(&cOutParamList);
            paramIt.First();
            while (!paramIt.IsDone())
            {
                RedString         paramName = paramIt.CurrentId();
                RedVSILangElement paramType = paramIt.CurrentData();
                RedVSIIOElement   paramTypeIoElem;
                RedString         paramTypeStr;
                if      (paramType.IsTypeArray())   paramTypeIoElem = RedVSIIOElement::KeywordArray();
                else if (paramType.IsTypeBool())    paramTypeIoElem = RedVSIIOElement::KeywordBool();
                else if (paramType.IsTypeChar())    paramTypeIoElem = RedVSIIOElement::KeywordChar();
                else if (paramType.IsTypeNumber())  paramTypeIoElem = RedVSIIOElement::KeywordNumber();
                else if (paramType.IsTypeString())  paramTypeIoElem = RedVSIIOElement::KeywordString();

                if (cLibMap.cVSILibTokenMap.FindString(paramTypeIoElem, paramTypeStr))
                    pParamNode->CreateChildLeaf(paramName, paramTypeStr);

                paramIt.Next();
            }
        }

        // convert the code into tokens, and then to a string
        RedVSITokenBuffer cTokenBuffer;
        RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pOutCode);
        RedBufferOutput outBuf;
        RedVSICmdSerialiser::TokenBufferToOutputBuffer(cTokenBuffer, cLibMap.cVSILibTokenMap, outBuf);
        pRoutine->CreateChildLeaf("code", outBuf.ExtractData());

        // Add the completed routine into the class
        pClassTml->AddChildNode(pRoutine);

        // Move onto the next class in the library
        cIt.Next();
    }

    return pClassTml;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlElement* RedVSILibFactory::OutputTmlRoutine(const RedString& classname, const RedString& routinename)
{
    RedVSILibClass* pClass = pLib->FindClass(classname);

    RedVSILibClass::RoutineIteratorType cIt = pClass->GetRoutineIterator();
    cIt.First();
    while ( !cIt.IsDone() )
    {
        // find the routine we want
        RedVSILibRoutine* pCurrRtn = cIt.CurrentItem();
        if (pCurrRtn->Name() == routinename)
        {
            // get the routine details
            RedString                  cOutName;
            RedVSIStringLangElementMap cOutParamList;
            RedVSICmdInterface*        pOutCode;
            pCurrRtn->GetDetails(cOutName, cOutParamList, pOutCode);

            // convert the code into tokens
            RedVSITokenBuffer cTokenBuffer;
            RedVSICmdSerialiser::SerialiseCommandChain(cTokenBuffer, pOutCode);

            // turn code tokens into a string

            RedTmlNode* pRoutine = new RedTmlNode("routine");
            pRoutine->CreateChildLeaf("name", cOutName);
        }

        cIt.Next();
    }


    return REDNULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


