
#pragma once

// Commands
#include "RedVSICmdFactory.h"
#include "RedVSICmdSerialiser.h"
#include "RedVSICmdExpr.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdWhile.h"

// Context
#include "RedVSIContextFactory.h"
#include "RedVSIContextRoutine.h"
#include "RedVSIContextThread.h"
//#include "RedVSIContextStackTraverser.h"

// Collections
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"
#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

// Definitions
#include "RedVSICollections.h"
#include "RedVSIErrorCodes.h"
#include "RedVSILangElement.h"
#include "RedVSIIOElement.h"
#include "RedVSIObject.h"
#include "RedVSITokenType.h"

// Interface
#include "RedVSICmdInterface.h"
#include "RedVSIContextInterface.h"
#include "RedVSILibRoutineInterface.h"
#include "RedVSIParseTreeinterface.h"
#include "RedVSIRoutineCallInterface.h"

// IO
#include "RedVSIToken.h"
#include "RedVSITokenBuffer.h"
#include "RedVSITokenElementMap.h"
#include "RedVSITokenFactory.h"

// Lib
#include "RedVSILib.h"
#include "RedVSILibClass.h"
#include "RedVSILibfactory.h"
#include "RedVSILibRoutine.h"

// Parse
#include "RedVSIParseFactory.h"
#include "RedVSIParseSerialiser.h"
#include "RedVSIParseTreeBinaryOp.h"
#include "RedVSIParseTreeCall.h"
#include "RedVSIParseTreeUnaryOp.h"
#include "RedVSIParseTreeVal.h"
#include "RedVSIParseTreeVar.h"

