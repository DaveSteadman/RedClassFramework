// -------------------------------------------------------------------------------------------------
// This file is covered by: The MIT License (MIT) Copyright (c) 2022 David G. Steadman
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

#include "RedType.h"
#include "RedDataString.h"
#include "RedLogEvent.h"
#include "RedLog.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddEvent(const RedLogEvent& event)
{
    if (event.EventType() == eErrorEvent)
        containsError = true;

    RedLogEvent* storedEvent = new RedLogEvent(event);

    EventList.AddLast(storedEvent);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddText(const RedDataString& NewText)
{
    RedLogEvent* storedEvent = new RedLogEvent(NewText);

    EventList.AddLast(storedEvent);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddErrorEvent(const RedDataString& NewText)
{
    RedLogEvent* storedEvent = new RedLogEvent(eErrorEvent, NewText);

    EventList.AddLast(storedEvent);
    containsError = true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

RedDataString RedLog::AllLoggedText(void)
{
    RedDataString          outStr;
    EventLogListItType logIt(&EventList);

    logIt.First();
    while (!logIt.IsDone())
    {
        RedLogEvent* pCurrItem = logIt.CurrentItem();

        if      (pCurrItem->EventType() == eErrorEvent)   outStr.Append("Error:   ");
        else if (pCurrItem->EventType() == eWarningEvent) outStr.Append("Warning: ");
        else if (pCurrItem->EventType() == eInfoEvent)    outStr.Append("Info:    ");

        outStr.Append(pCurrItem->Text());
        outStr.Append("\n");

        logIt.Next();
    }

    return outStr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


