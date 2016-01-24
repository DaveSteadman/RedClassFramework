
#include "RedVSIIOElement.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedVSIIOElement::Init(void) 
{
    eType = eDefaultInvalid; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsLocationKeyword(void) const
{
    if (IsKeywordAttribute()) return 1;
    if (IsKeywordStack())     return 1;
    if (IsKeywordHeap())      return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsTypeKeyword(void) const
{
    if (IsKeywordArray())  return 1;
    if (IsKeywordBool())   return 1;
    if (IsKeywordChar())   return 1;
    if (IsKeywordNumber()) return 1;
    if (IsKeywordString()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsCommandKeyword(void) const
{  
    if (IsKeywordNew())     return 1;
    if (IsKeywordLet())     return 1;
    if (IsKeywordIf())      return 1;
    if (IsKeywordElse())    return 1;
    if (IsKeywordEndif())   return 1;
    if (IsKeywordWhile())   return 1;
    if (IsKeywordLoop())    return 1;
    if (IsKeywordEndloop()) return 1;
    if (IsKeywordReturn())  return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsLibraryKeyword(void) const
{
    if (IsKeywordName())    return 1;
    if (IsKeywordClass())   return 1;
    if (IsKeywordRoutine()) return 1;
    if (IsKeywordParams())  return 1;
    if (IsKeywordParent())  return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsOperatorSymbol(void) const
{
    if (IsAssignOpSymbol())      return 1;
    if (IsLogicOpSymbol())       return 1;
    if (IsBinaryLogicOpSymbol()) return 1;
    if (IsCompareOpSymbol())     return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsAssignOpSymbol(void) const
{
    if (IsSymbolAssignDivide())   return 1;
    if (IsSymbolAssignEqual())    return 1;
    if (IsSymbolAssignMinus())    return 1;
    if (IsSymbolAssignMultiply()) return 1;
    if (IsSymbolAssignPlus())     return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsLogicOpSymbol(void) const
{
    if (IsSymbolLogicAnd()) return 1;
    if (IsSymbolLogicOr())  return 1;
    if (IsSymbolLogicNot()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsBinaryLogicOpSymbol(void) const
{
    if (IsSymbolLogicAnd()) return 1;
    if (IsSymbolLogicOr())  return 1;

    return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsCompareOpSymbol(void) const
{
    if (IsSymbolCompareEqual())       return 1;
    if (IsSymbolCompareNotEqual())    return 1;
    if (IsSymbolCompareLessThan())    return 1;
    if (IsSymbolCompareGreaterThan()) return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsBinaryOpSymbol(void) const
{
    if (IsSymbolAssignDivide())       return 1;
    if (IsSymbolAssignEqual())        return 1;
    if (IsSymbolAssignMinus())        return 1;
    if (IsSymbolAssignMultiply())     return 1;
    if (IsSymbolAssignPlus())         return 1;

    if (IsSymbolCompareEqual())       return 1;
    if (IsSymbolCompareNotEqual())    return 1;
    if (IsSymbolCompareLessThan())    return 1;
    if (IsSymbolCompareGreaterThan()) return 1;

    if (IsSymbolLogicAnd())           return 1;
    if (IsSymbolLogicOr())            return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int RedVSIIOElement::IsSeparatorSymbol(void) const
{
    if (IsSymbolStringContent()) return 1;
    if (IsSymbolOpenBracket())   return 1;
    if (IsSymbolCloseBracket())  return 1;
    if (IsSymbolComma())         return 1;
    if (IsSymbolPeriod())        return 1;
    if (IsSymbolDoubleColon())   return 1;

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedVSIIOElement& lhs, const RedVSIIOElement& rhs)
{
    if(lhs.iElem() == rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedVSIIOElement& lhs, const RedVSIIOElement& rhs)
{
    if(lhs.iElem() != rhs.iElem())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
