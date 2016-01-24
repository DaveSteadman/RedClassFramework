
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "RedString.h"

namespace Red {
namespace Core {

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
    Len = (int)strlen(Cstr) + 1;

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
    Len = (int)strlen(pText);
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

void RedString::Delete(int Pos, int Count)
{
    int CopyPos;

    if (Pos > Len)
        return;

    CopyPos = Pos + Count;

    if (CopyPos >= Len)
    {
        Txt[Pos] = 0;
    }
    else
    {
        while (CopyPos <= Len)
        {
            Txt[Pos] = Txt[CopyPos];
            ++Pos;
            ++CopyPos;
        }
    }
    Len -= Count;

    Shrink();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Insert(int Pos, char Ch)
{
    char* Temp;

    // check the position is in-bounds
    if ( (Pos<0) || (Pos>Len) )
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
        delete Txt;
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

void RedString::Insert(int Pos, const char* Str)
{
    RedString TempStr(Str);

    Insert(Pos, TempStr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedString::Insert(int Pos, const RedString& Str)
{
    int  SLen = Str.Len;

    if (SLen > 0)
    {
        // Iterate through the new string, adding each character to this one.
        for (int I = 0; I < SLen; ++I)
        {
            char ch = Str.Txt[I];

            // Strip any \0 characters from the insert string
            if (ch != '\0')
                Insert(Pos, ch);
            ++Pos;
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
    delete Txt;

    // Setup the new values
    Txt = pNewText;
    Siz = (int)NewLen;
    Len = (int)NewLen;
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
    delete Txt;

    // Setup the new values
    Txt = pNewText;
    Siz = (int)NewLen;
    Len = (int)NewLen;
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

// ============================================================================
// Queries
// ============================================================================

const char RedString::CharAtPos(int iPos) const
{
    // if the Pos is out of bounds, return a null character.
    if ( ( iPos >= Len ) || ( iPos < 0 ) )
        return '\0';

    return Txt[iPos];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::NumLines(void) const
{
    int iNumLines = 0;

    for (int i=0; i<Len; i++)
    {
        // account for the first line if we have a valid char
        if ( (iNumLines == 0) && ( Txt[i] != '\0' ) )
            iNumLines = 1;

        if ( Txt[i] == '\n' )
            iNumLines++;
    }

    return iNumLines;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::LineAtNum(int iLineNum, RedString& Line) const
{
    int iLineStartIndex, iLineLength, iCurrIndex;
    int iOnLine;

    // initialise the return value
    Line = "";

    // initialise the working values
    iLineLength     = 0;
    iCurrIndex      = 0; 
    iOnLine         = 1;

    // Lines are indexed as we would want to see a position marker, from 1.
    if (iLineNum < 1)
        return 0;
    // check we have enough lines to fullfill operation
    if (iLineNum > NumLines() )
        return 0;

    // Loop to the first character of the line we need
    while (iOnLine < iLineNum)
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

    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::SubStr(int Start, int Count) const
{
    RedString TempStr;
    int iCurrIndex = Start;
    
    // crop the string if it would be too long
    if (Count>Len) Count = Len;
    
    for (int i=0; i<Count; i++)
    {
        TempStr += Txt[iCurrIndex];
        iCurrIndex++;
    }

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::StringFromPos(int iPos) const
{
    return SubStr(iPos, Len-iPos);
}

// ============================================================================
// Complex Operations
// ============================================================================

RedString::StrCompVal RedString::Compare(const RedString& Str, RedString::StrCompMode Case) const
{
    int Index, MaxIndex;
    char Ch1, Ch2;

    // return quick result if one of the strings is empty
    if (Len == 0)
        if (Str.Len == 0)
            return SC_EQUAL;
        else
            return SC_LESS;
    else
        if (Str.Len == 0)
            return SC_GREATER;

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

    for (int Pos = 0; Pos < Len; ++Pos)
        TempStr.Txt[Pos] = toupper(TempStr.Txt[Pos]);

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedString RedString::ToLower(void)
{
    RedString TempStr = *this;

    for (int Pos = 0; Pos < Len; ++Pos)
        TempStr.Txt[Pos] = tolower(TempStr.Txt[Pos]);

    return TempStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::IsCharInString(char ch) const
{
    for (int Pos = 0; Pos < Len; ++Pos)
    {
        if (Txt[Pos] == ch)
            return 1;
    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::IsAlphaNumeric(void) const
{
    RedChar RedChar;
    for (int iPos = 0; iPos < Len; ++iPos)
    {
        RedChar = CharObjAtPos(iPos);

        if (!RedChar.IsAlphaNumeric())
            return 0;
    }
    return 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::IsEqualTo(const RedString& Str) const
{
    return (Compare(Str, SM_CASE_SENSITIVE) == SC_EQUAL);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedString::IsEqualTo(const char* Str) const
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
    Len = (int)strlen(chStr);
    Siz = (Len/AllocIncr)*AllocIncr + AllocIncr;

    // delete the old text
    delete Txt;

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
// Operators: Comparison 
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
    for (int i=0; i<Len; i++)
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
    for (int i=Len; i<Siz; i++)
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

} // Core
} // Red

