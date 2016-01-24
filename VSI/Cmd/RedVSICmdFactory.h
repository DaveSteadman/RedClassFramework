
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "RedVSICmdInterface.h"
#include "RedVSITokenBuffer.h"
#include "RedLog.h"
#include "RedVSIContextInterface.h"
#include "RedVSIErrorCodes.h"

namespace Red {
namespace VSI {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Class to create all the command classes.
// The construction code was taken out of the command classes to allow them to 
// focus on their core functionality of performing commands. Additional processing 
// will use SetDetails/GetDetails on each of the commands and dal with their
// own domain (such as GUI or serialisation).
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedVSICmdFactory
{
public:

    static RedVSICmdInterface* RunConstuctionCompetition(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);

private:

    static int                 EOFComp   (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);

    static RedVSICmdInterface* CallComp  (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
    static RedVSICmdInterface* ExprComp  (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
	static RedVSICmdInterface* IfComp    (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
	static RedVSICmdInterface* NewComp   (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
    static RedVSICmdInterface* ReturnComp(RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
    static RedVSICmdInterface* WhileComp (RedVSITokenBuffer& cInputBuffer, RedLog& RedLog);
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // VSI
} // Red
