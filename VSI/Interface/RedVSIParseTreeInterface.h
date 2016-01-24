
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSIContextInterface.h"
#include "RedVSILangElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

class RedVSIParseTreeInterface 
{
public:

    virtual void                    CalcResult(RedVSIContextInterface* pContext) =0;
    virtual const RedVSILangElement Type(void) const =0;
    virtual                         ~RedVSIParseTreeInterface(void) { };
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


