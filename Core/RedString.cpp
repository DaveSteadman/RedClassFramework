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

#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "RedString.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int  RedString::AllocIncr  = 16;
char RedString::chInitChar = '\0';

// ============================================================================
// Construction
// ============================================================================

RedString::RedString(void)
{
    // define the size with no length and a default allocation
    Len    = 0;
    Siz    = AllocIncr;

    // create the characters
    Txt    = new char[Siz];
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString::RedString(const RedString& Str)
{
    // Setup the user length and allocarted size of the string
    Len = Str.Len;
    Siz = Str.Siz;

    // allocate the new char array
    Txt = new char[Siz];

    // copy all the old string characters in the new one
    memcpy(Txt, Str.Txt, Siz);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString::RedString(const char* Cstr)
{
    // Read the length of the input string and tack on space for the \0 terminator.
    Len = (unsigned)strlen(Cstr) + 1;

    // Setup the user length and allocarted size of the string
    Siz = ((Len + AllocIncr - 1) / AllocIncr) * AllocIncr;

    // allocate the new char array
    Txt = new char[Siz];

    // copy the old string characters in the new one
    memcpy(Txt, Cstr, Len);

    // initialise the unused characters
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString::RedString(char FillCh, int Count)
{
    // set up the new size, ensuring the size is a multiple of the 
    // allocation size
    Siz = ((Count + AllocIncr - 1) / AllocIncr) * AllocIncr;
    Len = Count;

    // create the characters and call an error on failure
    Txt = new char[Siz];

    // Copy across the characters
    memset(Txt, FillCh, Len);

    // initialise the unused characters
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString::~RedString()
{
     delete[] Txt;
}

// ============================================================================
// Assignments
// ============================================================================

void RedString::Empty(void)
{
    // Delete the allocated string
    if (Txt)
    {
        delete[] Txt;
        Txt = 0;
    }

    // define a new allocated string
    Len    = 0;
    Siz    = AllocIncr;

    // create the characters
    Txt    = new char[Siz];
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::SetChar(const int Pos, const char chNewChar)
{
    if ( (Pos>=0) && (Pos<Len) )
        Txt[Pos] = chNewChar;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Set(const char* pText)
{
    // Assign the new properties
    Len = (unsigned)strlen(pText);
    Siz = (Len/AllocIncr)*AllocIncr + AllocIncr;

    // delete the old text
    delete Txt;

    // create the new sized text
    Txt = new char[Siz];

    // copy the characters across
    memcpy(Txt, pText, Len);
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Set(const RedString& Str)
{
    // Assign the new properties
    Len = Str.Len;
    Siz = Str.Siz;

    // delete the old text
    delete Txt;

    // create the new sized text
    Txt = new char[Siz];

    // copy the characters across
    memcpy(Txt,Str.Txt,Len);
    InitUnsetChars();   
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Delete(const unsigned Pos, const unsigned Count)
{
    unsigned CopyPos;
    unsigned delpos = Pos;

    if (delpos > Len)
        return;

    CopyPos = delpos + Count;

    if (CopyPos >= Len)
    {
        Txt[delpos] = 0;
    }
    else
    {
        while (CopyPos <= Len)
        {
            Txt[delpos] = Txt[CopyPos];
            ++delpos;
            ++CopyPos;
        }
    }
    Len -= Count;

    Shrink();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Insert(const unsigned Pos, char Ch)
{
    char* Temp;

    // check the position is in-bounds
    if (Pos>Len)
        return;

    // if we need to expand the string to accomodate the new character
    if (Len == Siz)
    {
        // create the new string
        Siz += AllocIncr;
        Temp = new char[Siz];

        // copy the Chars across and initialise the unused ones
        memcpy(Temp, Txt, Len);
        InitUnsetChars();

        // tidy up the memory allocation
        delete[] Txt;
        Txt = Temp;
    }

    // we have room and we need to shuffle characters along
    if (Pos < Len)
    {
        for (int Col = Len + 1; Col > Pos; --Col)
            Txt[Col] = Txt[Col-1];
    }

    // finally assign the new character and increase the string length
    Txt[Pos] = Ch;
    ++Len;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Insert(const unsigned Pos, const char* Str)
{
    RedString TempStr(Str);

    Insert(Pos, TempStr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Insert(const unsigned Pos, const RedString& Str)
{
    unsigned SLen = Str.Len;
    unsigned insertPos = Pos;

    if (SLen > 0)
    {
        // Iterate through the new string, adding each character to this one.
        for (int I = 0; I < SLen; ++I)
        {
            char ch = Str.Txt[I];

            // Strip any \0 characters from the insert string
            if (ch != '\0')
                Insert(insertPos, ch);
            ++insertPos;
        }
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(const RedString& Str)
{
    Append(Str.Txt);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(const char* pText)
{
    // Determine the new string size
    unsigned long NewLen = strlen(Txt) + strlen(pText) + 1;

    // Create teh new char array
    char* pNewText = new char[NewLen];

    // copy data into the new array
    snprintf(pNewText, NewLen, "%s%s", Txt, pText);

    // delete the existing txt
    delete[] Txt;

    // Setup the new values
    Txt = pNewText;
    Siz = (unsigned)NewLen;
    Len = (unsigned)NewLen;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(const char ch)
{
    // Determine the new string size
    unsigned long NewLen = strlen(Txt) + 1 + 1;

    // Create teh new char array
    char* pNewText = new char[NewLen];

    // copy data into the new array
    snprintf(pNewText, NewLen, "%s%c", Txt, ch);

    // delete the existing txt
    delete[] Txt;

    // Setup the new values
    Txt = pNewText;
    Siz = (unsigned)NewLen;
    Len = (unsigned)NewLen;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(RedChar ch)
{
    Append((const char)ch.Char());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(const int num)
{
    char numchars[16];
    snprintf(numchars, 16, "%d", num);

    Append(numchars);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Append(const unsigned num)
{
    char numchars[16];
    snprintf(numchars, 16, "%u", num);

    Append(numchars);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::DelFirstChar(void)
{
    this->Delete(0, 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::DelLastChar(void)
{
    this->Delete(this->Length(), 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::StripChar(const RedChar& ch)
{
	// New char array the same as existing, as new string is guaranteed to be same or shorter
	char     strippedStr[Len];
	unsigned currStrippedStrIndex = 0;

	// Loop through the chars
	for (unsigned currCharIndex = 0; currCharIndex<Len; currCharIndex++)
	{
		if (Txt[currCharIndex] != ch)
		{
			strippedStr[currStrippedStrIndex] = Txt[currCharIndex];
			currStrippedStrIndex++;
		}
	}

	// Append a \0
	strippedStr[currStrippedStrIndex] = '\0';

	// Delete the existing text and assign the new string
	unsigned strippedStrLen = currStrippedStrIndex;
	delete Txt;
	Txt = new char[strippedStrLen];
	memcpy(Txt, strippedStr, strippedStrLen);
	Len = strippedStrLen;
	Siz = strippedStrLen;
}

// ============================================================================
// Queries
// ============================================================================

const char RedString::CharAtPos(const unsigned iPos) const
{
    // if the Pos is out of bounds, return a null character.
    if (iPos >= Len)
        return '\0';

    return Txt[iPos];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const unsigned RedString::NumLines(void) const
{
    unsigned NumLines = 0;

    for (unsigned i=0; i<Len; i++)
    {
        // account for the first line if we have a valid char
        if ( (NumLines == 0) && ( Txt[i] != '\0' ) )
            NumLines = 1;

        if ( Txt[i] == '\n' )
            NumLines++;
    }

    return NumLines;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedString::LineAtNum(const unsigned LineNum, RedString& Line) const
{
    unsigned iLineStartIndex, iLineLength, iCurrIndex;
    unsigned iOnLine;

    // initialise the return value
    Line = "";

    // initialise the working values
    iLineLength     = 0;
    iCurrIndex      = 0; 
    iOnLine         = 1;

    // Lines are indexed as we would want to see a position marker, from 1.
    // check we have enough lines to fullfill operation
    if (LineNum > NumLines())
        return false;

    // Loop to the first character of the line we need
    while (iOnLine < LineNum)
    {
        if ( Txt[iCurrIndex] == '\n' )
            iOnLine++;

         iCurrIndex++;
    }

    // mark the start of the line
    iLineStartIndex = iCurrIndex;

    // loop to the end of the line
    while ( (iCurrIndex<Len) && (Txt[iCurrIndex]!='\n') )
    {
        iCurrIndex++;
        iLineLength++;
    }

    // use the inbuilt routine to retrieve the section of line
    Line = SubStr(iLineStartIndex, iLineLength);

    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::SubStr(const unsigned Start, const unsigned Count) const
{
    RedString TempStr;
    unsigned iCurrIndex = Start;
    unsigned realCount = Count;

    // crop the string if it would be too long
    if (realCount>Len)
        realCount = Len;
    
    for (unsigned i=0; i<realCount; i++)
    {
        TempStr += Txt[iCurrIndex];
        iCurrIndex++;
    }

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::StringFromPos(const unsigned iPos) const
{
    return SubStr(iPos, Len-iPos);
}

// ============================================================================
// Complex Operations
// ============================================================================

RedString::StrCompVal RedString::Compare(const RedString& Str, RedString::StrCompMode Case) const
{
    unsigned Index, MaxIndex;
    char Ch1, Ch2;

    // return quick result if one of the strings is empty
    if (Len == 0)
    {
        if (Str.Len == 0)
            return SC_EQUAL;
        else
            return SC_LESS;
    }
    else
    {
        if (Str.Len == 0)
            return SC_GREATER;
    }

    // determine the last point we need to compare to 
    MaxIndex = Len > Str.Len ? Len : Str.Len;

    // compare the strings
    for (Index = 0; Index < MaxIndex; Index++)
    {
        // acquire the characters
        if (Case == SM_IGNORE_CASE)
        {
            Ch1 = toupper(Txt[Index]);
            Ch2 = toupper(Str.Txt[Index]);
        }
        else
        {
            Ch1 = Txt[Index];
            Ch2 = Str.Txt[Index];
        }

        // compare the characters, if different return the less/greater value 
        // based on the difference in the last character.
        if (Ch1 != Ch2)
        {
            if (Ch1 < Ch2)
                return SC_LESS;
            else
                return SC_GREATER;
        }
    }

    // no differences found, so return an equals value
    return SC_EQUAL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::ToUpper(void)
{
    RedString TempStr = *this;

    for (unsigned Pos = 0; Pos < Len; ++Pos)
        TempStr.Txt[Pos] = toupper(TempStr.Txt[Pos]);

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::ToLower(void)
{
    RedString TempStr = *this;

    for (unsigned Pos = 0; Pos < Len; ++Pos)
        TempStr.Txt[Pos] = tolower(TempStr.Txt[Pos]);

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedString::IsCharInString(char ch) const
{
    for (unsigned Pos = 0; Pos < Len; ++Pos)
    {
        if (Txt[Pos] == ch)
            return 1;
    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedString::IsAlphaNumeric(void) const
{
    RedChar RedChar;
    for (unsigned iPos = 0; iPos < Len; ++iPos)
    {
        RedChar = CharObjAtPos(iPos);

        if (!RedChar.IsAlphaNumeric())
            return 0;
    }
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedString::IsEqualTo(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_EQUAL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const bool RedString::IsEqualTo(const char* Str) const
{
    RedString temp(Str);
    return (Compare(temp, SM_CASE_SENSITIVE) == SC_EQUAL);
}

// ============================================================================
// Operators
// ============================================================================

void RedString::operator =(const char* chStr)
{
    // Assign the new properties
    Len = (unsigned)strlen(chStr);
    Siz = (Len/AllocIncr)*AllocIncr + AllocIncr;

    // delete the old text
    delete[] Txt;

    // create the new sized text
    Txt = new char[Siz];

    // copy the characters across
    memcpy(Txt, chStr, Len);
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::operator =(const RedChar& cChr)
{
    Empty();
    Insert(0, cChr.Char());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::operator =(const RedString& Str)
{
    // Assign the new properties
    Len = Str.Len;
    Siz = Str.Siz;

    // delete the old text
    delete[] Txt;

    // create the new sized text
    Txt = new char[Siz];

    // copy the characters across
    memcpy(Txt,Str.Txt,Len);
    
    // Initialise unused characters
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

char RedString::operator [](int Pos) const
{
    if ( (Pos<0) || (Pos>=Len) )
        return chInitChar;

    return Txt[Pos];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma mark - Comparison Operators
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator <(const RedString Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_LESS);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator <=(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) != SC_LESS);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator >(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_GREATER);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator >=(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_GREATER);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator ==(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_EQUAL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator ==(const char* Str) const
{
    // if the strings are different lengths, fail.
    if (strlen(Str) != Len)
        return 0;

    // compare each character, fail if any difference is found
    for (unsigned i=0; i<Len; i++)
    {
        if (Txt[i] != Str[i])
            return 0;
    }

    // return success, nothing failed to match
    return 1;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::operator !=(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) != SC_EQUAL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// concatenation methods
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString operator +(const RedString& Str1, const RedString& Str2)
{
    RedString retStr = Str1;
    retStr.Append(Str2);

    return retStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString operator +(const RedString& Str, const RedChar ch)
{
    RedString RetStr = Str;
    RetStr.Append(ch);
    return RetStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// ============================================================================
// Test Routines
// ============================================================================

void RedString::DebugDump(void)
{
    printf("{{Siz}%d}", Siz);
    printf("{{Len}%d}", Len);
    printf("{{Txt}\"%s\"}\n", Txt);
}

// ============================================================================
// Private Operations
// ============================================================================

void RedString::InitUnsetChars(void)
{
    // initialise the unset Chars
    for (unsigned i=Len; i<Siz; i++)
        Txt[i] = chInitChar;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Shrink()
{
    char* Temp;

    if ((Siz - Len) > AllocIncr)
    {
        Siz  = ((Len + AllocIncr - 1) / AllocIncr) * AllocIncr;

        Temp = new char[Siz];

        memcpy(Temp,Txt,Len);
        delete[] Txt;
        Txt  = Temp;
    }
    InitUnsetChars();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red

