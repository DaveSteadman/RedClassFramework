
/*
  {{name} qwqwq }
  {{name} "asad }}" }
*/

#pragma once

// Include Namespaces
#include "RedCoreNamespace.h"

namespace Red {
namespace TinyML {

using namespace Red::Core;

class RedTmlElement;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTmlLeaf : public RedTmlElement
{
public:
    RedTmlLeaf(RedString NewName, RedString NewData) : RedTmlElement(NewName) { data = NewData; };

    // Override: RedTmlElement
    const bool IsLeaf(void) const { return true; };

    const RedString Data(void)                        { return data; };
    void            SetData(const RedString& NewData) { data = NewData; };

private:
    RedString data;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red


