//
//  RedDataType.cpp
//
//  Created by Dave Steadman on 11/08/2015.
//  Copyright © 2015 Dave Steadman. All rights reserved.
//

#include "RedDataType.h"
#include "RedString.h"

namespace Red {
namespace Core {

bool operator==(const RedDataType& lhs, const RedDataType& rhs)
{
    if (lhs.iState() == rhs.iState())
        return true;
    return false;
}

bool operator!=(const RedDataType& lhs, const RedDataType& rhs)
{
    if (lhs.iState() != rhs.iState())
        return true;
    return false;
}

} // Core
} // Red




