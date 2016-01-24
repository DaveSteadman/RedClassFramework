
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

#include "RedVSIParseTreeInterface.h"
#include "RedVSIContextInterface.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSIParseTreeVal : public RedVSIParseTreeInterface
{
public:

    RedVSIParseTreeVal(void)                      { Init(); };
    RedVSIParseTreeVal(RedVariant cNewVal)        { SetValue(cNewVal); };

    // Inherited RedType
    void                    Init(void)            { cVal.Init(); };
    const RedVSILangElement Type(void) const      { return RedVSILangElement::ParseValue(); };
	
    // Query
    const RedVariant Value(void) const            { return cVal;  };
    void             SetValue(RedVariant& cInVal) { cVal = cInVal; };

    // Inherited RedVSIParseTreeInterface
    void CalcResult(RedVSIContextInterface* pContext);

private:
    RedVariant cVal;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red


