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

#include "RedDataString.h"
#include "RedLogEvent.h"
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef RedDoubleLinkedList<RedLogEvent*>         EventLogListType;
typedef RedDoubleLinkedListIterator<RedLogEvent*> EventLogListItType;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum TELogType { eTimestamped, eEventTypeStamped, eJustText };

// Holds logged information, from text debug statements, info, warnings and
// error messages. Has additional methods to then query the information.
class RedLog
{
public:


    RedLog(void) : containsError(0) { };
    ~RedLog() { Init(); };
    void Init(void) { EventList.DelAll(); containsError=false; };

    void      AddEvent(const RedLogEvent& event);
    void      AddText (const RedDataString& NewText);
    void      AddErrorEvent(const RedDataString& NewText);
    void      AddErrorEvent(const char* NewText) { AddErrorEvent(RedDataString(NewText)); };

    RedDataString AllLoggedText(TELogType eLogType = TELogType::eJustText);

    void      Clear(void) { EventList.DelAll(); containsError = false; };

    // Queries
    //EventLogListType EventsByType();

    unsigned NumEvents(void) const { return EventList.NumItems(); };
    bool     ContainsError(void)   const { return containsError; };

private:

    EventLogListType EventList;
    bool             containsError;
};
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red



