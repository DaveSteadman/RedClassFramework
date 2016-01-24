
#include "RedCoreNamespace.h"
#include "RedTmlNamespace.h"

#include "RedTmlNode.h"
#include "RedTmlElement.h"

namespace Red {
namespace TinyML {

using namespace Red::Core;
using namespace Red::TinyML;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlNode* RedTmlNode::CreateChildNode(const RedString& NewName)
{
    RedTmlNode* pNewNode = new RedTmlNode(NewName);
    this->nodelist.AddLast((RedTmlElement*)pNewNode);

    return (RedTmlNode*)pNewNode;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedTmlLeaf* RedTmlNode::CreateChildLeaf(const RedString& NewName, const RedString& NewData)
{
    RedTmlLeaf *NewLeaf = new RedTmlLeaf(NewName, NewData);

    if (NewLeaf)
    {
        this->nodelist.AddLast((RedTmlElement*)NewLeaf);
        return NewLeaf;
    }

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // TinyML
} // Red


