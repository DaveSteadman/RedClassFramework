//
//  RedResult.cpp
//
//  Copyright © 2015 Dave Steadman. All rights reserved.
//

#include "RedResult.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator==(const RedResult& lhs, const RedResult& rhs)
{
    if(lhs.iState() == rhs.iState())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool operator!=(const RedResult& lhs, const RedResult& rhs)
{
    if(lhs.iState() != rhs.iState())
        return true;
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red




