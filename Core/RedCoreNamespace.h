// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2016 David G. Steadman
// -------------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------------------------------------------------------
// (http://opensource.org/licenses/MIT)
// -------------------------------------------------------------------------------------------------

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
