
// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedTinyMLFileIO.h"

using namespace Red::Core;

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedDataChar kOpenBracket  = '{';
static const RedDataChar kCloseBracket = '}';

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Top Level IO
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedTinyMLFileIO::CreateTinyMLFromFile(const RedDataString& filepath)
{
    // Check the file exists to open
    if (!RedIOHandler::FileExists(filepath))
        return NULL;

    // Open the file and copy into input buffer
    RedBufferInput iB;
    if (RedIOHandler::InputBufferFromFile(filepath, iB) == kResultFail)
        return NULL;

    // Parse the file to create TML Element
    RedTinyMLElement* pTmlElement = RedTinyMLFileIO::CreateTinyML(iB);

    return pTmlElement;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedResult RedTinyMLFileIO::CreateFileFromTinyML(const RedTinyMLElement* tmlElement, const RedDataString& filepath, const TESerialiseType writeStyle)
{
    // Check node is not null
    if (tmlElement == NULL)
        return kResultFail;

    // Write the validated tml node to the buffer
    RedBufferOutput outBuf;
    RedTinyMLFileIO::SerialiseCore(outBuf, tmlElement, writeStyle);

    // Final newline for asthetics
    outBuf.WriteNewLine();

    // Write buffer to file
    if (RedIOHandler::OutputBufferToFile(filepath, outBuf) != kResultSuccess)
        return kResultFail;

    return kResultSuccess;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedTinyMLFileIO::CreateTinyML(const RedDataString& inputStr)
{
    RedBufferInput inputBuf(inputStr);

    return RedTinyMLFileIO::CreateTinyML(inputBuf);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedTinyMLFileIO::CreateTinyML(RedBufferInput& inputBuf)
{
    RedTinyMLElement* retTml = NULL;

    if ( ReadTmlElement(inputBuf, &retTml) )
        return retTml;

    return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTinyMLElement* RedTinyMLFileIO::CreateTinyML(RedDataRecord& inputRec)
{
    return NULL;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedTinyMLFileIO::SerialiseCore(RedBufferOutput& outputBuf, const RedTinyMLElement* topTmlNode, const TESerialiseType eMode)
{
    outputBuf.Append(kOpenBracket);

    // write name
    outputBuf.Append(kOpenBracket);
    outputBuf.Append(topTmlNode->Name());
    outputBuf.Append(kCloseBracket);

    if (topTmlNode->IsNode())
    {
        RedTinyMLNode* pCurrNode = (RedTinyMLNode*)topTmlNode;

        RedTinyMLNode::TmlNodeListItType ListIt = pCurrNode->NodeIterator();

        if (eMode == eLinedIndentedContent) outputBuf.IncreaseIndent();

        while (!ListIt.IsDone())
        {
            RedTinyMLElement* nextElem = ListIt.CurrentItem();

            if (eMode == eLinedIndentedContent) outputBuf.WriteNewLineWithIndent();

            RedTinyMLFileIO::SerialiseCore(outputBuf, nextElem, eMode);

            ListIt.Next();
        }

        if (eMode == eLinedIndentedContent)
        {
            outputBuf.DecreaseIndent();
            outputBuf.WriteNewLineWithIndent();
        }
    }
    else if (topTmlNode->IsLeaf())
    {
        RedTinyMLLeaf* pCurrLeaf = (RedTinyMLLeaf*)topTmlNode;
        if (pCurrLeaf->Data().NumLines() > 1)
        {
            outputBuf.IncreaseIndent();
            outputBuf.AppendIndented(pCurrLeaf->Data());
            outputBuf.DecreaseIndent();
            outputBuf.WriteNewLineWithIndent();
        }
        else
        {
            outputBuf.Append(pCurrLeaf->Data());
        }
    }

    outputBuf.Append(kCloseBracket);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Private
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTinyMLFileIO::ReadName(RedBufferInput& inputBuf, RedDataString& outputName)
{
    RedDataChar ch;
    outputName.Empty();

    // Second bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != kOpenBracket) return false;
    if (ch.IsEOF())   return false;

    // Read name
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;
    while (ch != kCloseBracket)
    {
        outputName.Append(ch);
        ch = inputBuf.GetNextChar();
        if (ch.IsEOF()) return false;
    }

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTinyMLFileIO::ReadContent(RedBufferInput& inputBuf, RedDataString& outputContent)
{
    bool EndOfContentFound = false;
    RedDataString levelChars;

    // Initialse the return data
    outputContent.Empty();

    // Skip whitespace
    RedDataChar ch = inputBuf.PreviewNextNonWhitespaceChar();
    if (ch.IsEOF()) return false;

    // Loop until EOF or unquoted close bracket
    while(!EndOfContentFound)
    {
        RedDataChar ch = inputBuf.GetNextChar();

        // Check for obvious invalid characters
        if (ch.IsEOF()) return false;

        // Check for a quote level changes, appending and deleting the latest quote character from a list.
        // Offers some basic robustness against quotes in strings.
        if ((ch.IsQuote()) && (ch != levelChars.LastChar())) levelChars.Append(ch);
        if ((ch.IsQuote()) && (ch == levelChars.LastChar())) levelChars.DelLastChar();

        // check for final close bracket
        if ( (ch == kCloseBracket) && (levelChars.IsEmpty()) )
        {
            inputBuf.UngetChar();
            return true;
        }
        else
        {
            outputContent.Append(ch);
        }
    }

    // Default error return value
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool RedTinyMLFileIO::ReadTmlElement(RedBufferInput& inputBuf, RedTinyMLElement** newTml)
{
    RedDataChar   ch;
    RedDataString leafname;

    // Opening bracket
    ch = inputBuf.GetNextNonWhitespaceChar();
    if (ch != kOpenBracket) return false;
    if (ch.IsEOF())         return false;
    
    // Read the name
    if ( !RedTinyMLFileIO::ReadName(inputBuf, leafname) ) return false;

    // If the next character is {, its a collection
    ch = inputBuf.PreviewNextNonWhitespaceChar();

    if (ch == kOpenBracket)
    {
        RedTinyMLNode* newNode = new RedTinyMLNode(leafname);

        // Move onto the next non-whitespace character
        ch = inputBuf.PreviewNextNonWhitespaceChar();

        // Check we are starting the object correctly.
        if (ch != kOpenBracket)
        {
            delete newNode;
            return false;
        }

        // Iterate across the Tml entries
        while (ch == kOpenBracket)
        {
            RedTinyMLElement* newChildNode;
            
            if (RedTinyMLFileIO::ReadTmlElement(inputBuf, &newChildNode) )
                newNode->NodeList()->AddLast(newChildNode);

             ch = inputBuf.PreviewNextNonWhitespaceChar();
        }

        // Read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == kCloseBracket)
        {
            *newTml = dynamic_cast<RedTinyMLElement*>(newNode);
            return true;
        }
        else
        {
            delete newNode;
            return false;
        }
    }
    else
    {
        RedDataString   leafdata;
        RedTinyMLLeaf* newLeaf;

        // Attempt to read the content
        if (!RedTinyMLFileIO::ReadContent(inputBuf, leafdata))
            return false;

        // Read bracket to close statement
        ch = inputBuf.GetNextNonWhitespaceChar();
        if (ch == kCloseBracket)
        {
            // All read, construct returned object
            newLeaf = new RedTinyMLLeaf(leafname, leafdata);

            *newTml = dynamic_cast<RedTinyMLElement*>(newLeaf);
            return true;
        }
    }

    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
