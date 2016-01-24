
#pragma once

namespace Red {
namespace Core {

class RedString;
class RedDataType;

class RedType
{
public:
    virtual void              Init(void) = 0;
    virtual const RedDataType Type(void) const = 0;
    virtual RedType*          Clone(void) const = 0;
    virtual                   ~RedType(void) { };
};

} // Core
} // Red


