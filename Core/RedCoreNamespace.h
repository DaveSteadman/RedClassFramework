
#pragma once

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// The Core namespace is exactly that, the core classes which are re-used throughout the rest of the
// system. Everything is prefixed Red* to differentiate it from other class frameworks a compiler
// may pick up.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Fundamental Elements
#include "RedType.h"
#include "RedDataType.h"
#include "RedCoreConsts.h"

// Core Types
#include "RedBoolean.h"
#include "RedChar.h"
#include "RedNumber.h"
#include "RedString.h"

// Wrappers
#include "RedRecord.h"
#include "RedVariant.h"
#include "RedSmartPtr.h"

// Collections
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"
#include "RedLinkedList.h"
#include "RedLinkedListIterator.h"
#include "RedMapList.h"
#include "RedMapListIterator.h"

// Derived Collections
#include "RedQueueFIFO.h"
#include "RedStackLIFO.h"

// Time
#include "RedDate.h"
#include "RedDateSpan.h"
#include "RedTime.h"
#include "RedTimeSpan.h"

// IO
#include "RedBufferPos.h"
#include "RedBufferInput.h"
#include "RedBufferOutput.h"
#include "RedIOHandler.h"

// Event Logging
#include "RedResult.h"
#include "RedLogEvent.h"
#include "RedLog.h"
