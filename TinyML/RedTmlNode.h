
/*
  {{name} qwqwq }
  {{name} "asad }}" }
*/

#pragma once

// Include Namespaces
#include "RedCoreNamespace.h"

#include "RedTmlElement.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

using namespace Red::Core;

namespace Red {
namespace TinyML {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedTmlNode : public RedTmlElement
{
public:

    typedef RedDoubleLinkedList<RedTmlElement*>         TmlNodeListType;
    typedef RedDoubleLinkedListIterator<RedTmlElement*> TmlNodeListItType;

    // Constructor
    RedTmlNode(const RedString& NewName) : RedTmlElement(NewName) { nodelist.Init(); };

    // Basic Queries
    const bool     IsNode(void)           const { return true; };
    const unsigned NodeElementCount(void) const { return nodelist.NumItems(); };

    // List an list-iterator accessors
    TmlNodeListType*  NodeList(void)     { return &nodelist; };
    TmlNodeListItType NodeIterator(void) { return TmlNodeListItType(&nodelist); };

    // Create child elements within the tree and return a pointer to them
    RedTmlNode*    CreateChildNode (const RedString& NewName);
    RedTmlLeaf*    CreateChildLeaf (const RedString& NewName, const RedString& NewData);

    // Add new child nodes without cloning
    void AddChildNode (RedTmlNode* pNewNode) { nodelist.AddLast((RedTmlElement*)pNewNode); };
    void AddChildLeaf (RedTmlLeaf* pNewLeaf) { nodelist.AddLast((RedTmlElement*)pNewLeaf); };

private:
    TmlNodeListType nodelist;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red


