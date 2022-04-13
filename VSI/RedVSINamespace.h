// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 Dave Steadman
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

// Commands
#include "RedVSICmdFactory.h"
#include "RedVSICmdSerialiser.h"
#include "RedVSICmdLet.h"
#include "RedVSICmdLog.h"
#include "RedVSICmdIf.h"
#include "RedVSICmdNew.h"
#include "RedVSICmdReturn.h"
#include "RedVSICmdWhile.h"

// Context
#include "RedVSIContextFactory.h"
#include "RedVSIContextBase.h"
#include "RedVSIContextRoutine.h"
#include "RedVSIParseStackTraverser.h"

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
#include "RedTokenPredefType.h"
#include "RedTokenType.h"

// Interface
#include "RedVSICmd.h"
#include "RedVSIContextRoutine.h"
#include "RedVSIParseTreeinterface.h"
#include "RedVSIRoutineCallInterface.h"

// IO
#include "RedToken.h"
#include "RedTokenBuffer.h"
#include "RedTokenPredefMap.h"
#include "RedTokenFactory.h"

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

// Shell
#include "RedVSIShell.h"
