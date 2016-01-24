
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedCoreNamespace.h"
#include "RedTmlNamespace.h"

#include "RedVSILib.h"
#include "RedVSILibClass.h"
#include "RedVSILibRoutine.h"
#include "RedVSITokenElementMap.h"
#include "RedVSILibTokenMap.h"
#include "RedVSIErrorCodes.h"

#include "RedVSITokenBuffer.h"
#include "RedVSITokenFactory.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace VSI {

using namespace Red::Core;
using namespace Red::TinyML;

class RedVSILibFactory
{
public:

    RedVSILibFactory(RedVSILib* pNewLib);

    // Add a Tml-Class to library
    void              InputTmlClass  (RedTmlNode  cClassNode,   RedLog& cAnalysis);
    RedVSILibRoutine* InputTmlRoutine(RedTmlNode& cRoutineNode, RedLog& cAnalysis);

    RedTmlElement*    OutputTmlClass  (const RedString& classname);
    RedTmlElement*    OutputTmlRoutine(const RedString& classname, const RedString& routinename);

// attributes

    RedVSILibTokenMap cLibMap;
    RedVSILib*        pLib;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red

