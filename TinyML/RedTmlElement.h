
/*
  {{name} qwqwq }
  {{name} "asad }}" }
*/

#pragma once

// Include Namespaces
#include "RedCoreNamespace.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

using namespace Red::Core;

namespace Red {
namespace TinyML {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTmlElement
{
public:
    RedTmlElement(const RedString& initname) { SetName(initname); };

    const RedString Name(void) const { return name;  };
    void            SetName(const RedString& initname) { name = initname; };

    virtual const bool IsLeaf(void) const { return false; };
    virtual const bool IsNode(void) const { return false; };

private:
    RedString name;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red
