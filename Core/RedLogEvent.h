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

#include "RedDate.h"
#include "RedTime.h"
#include "RedDataString.h"
#include "RedDataNumber.h"
#include "RedDataActions.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum class TEventLogType {
    eErrorEvent,
    eWarningEvent,
    eInfoEvent
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

class RedLogEvent
{
public:

    // Constructors
    RedLogEvent(const TEventLogType NewLogType)                               : LogType(NewLogType) { SetTimestampNow(); };
    RedLogEvent(const TEventLogType NewLogType, const RedDataString& NewText) : LogType(NewLogType), text(NewText) { SetTimestampNow(); };
    RedLogEvent(const RedDataString& NewText)                                 : LogType(TEventLogType::eInfoEvent), text(NewText) { SetTimestampNow(); };
    RedLogEvent(const RedLogEvent& CurrEvent)                                 : LogType(CurrEvent.LogType), text(CurrEvent.text) { SetTimestampNow(); };

    // Basic Accessors
    void                Init(void)                               { LogType = TEventLogType::eInfoEvent; text.Init(); };
    TEventLogType       EventType(void) const                    { return LogType; };
    
    RedDataString       Text(void)                               { return text; };
    RedDataString       EventTypeText(void)                      { return EventTypeString() + " // " + text; };
    RedDataString       TimestampedText(void)                    { return TimestampString() + " // " + text; };

    void                AppendText(const RedDataString& newText) { text.Append(newText); };
    void                AppendText(const RedDataNumber& newNum)  { text.Append(RedDataActions::StringFromNumber(newNum)); };

    void                Set(const TEventLogType newtype, const RedDataString& newtext) { LogType=newtype; text=newtext; };
    void                SetTimestampNow(void) { cDate = RedDate::Today(); cTime = RedTime::Now(); };



    //void operator =(const RedLogEvent& newVal)      { LogType=newVal.LogType; text=newVal.Text; cDate=newVal.cDate; cTime=newVal.cTime; };

private:

    RedDataString TimestampString(void) 
    { 
        return cDate.EightDigitDateString() + "-" + cTime.SixDigitTimeString(); 
    };

    RedDataString EventTypeString(void)
    {
        if      (LogType == TEventLogType::eErrorEvent)   return "Error";
        else if (LogType == TEventLogType::eWarningEvent) return "Warning";
        else if (LogType == TEventLogType::eInfoEvent)    return "Info";
        return "Unknown";
    };

    RedDate cDate;
    RedTime cTime;
    TEventLogType LogType = TEventLogType::eInfoEvent;
    RedDataString text    = "";
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


