
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"

namespace Red {
namespace VSI {

using namespace Red::Core;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static const RedString kClassname = "classname";

class RedVSIObject : public RedRecord
{
public:

    RedVSIObject(void);
    //RedVSIObject(RedString& cNewClassName) { Add(kClassname, &cNewClassName); };

    const RedString Classname(void) { RedString r = "TBD"; return r; };

    // Operators
    void operator =(const RedVSIObject cNewVal);   

private:

    // Attributes
    RedString classname;
    RedRecord Attribs;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red
