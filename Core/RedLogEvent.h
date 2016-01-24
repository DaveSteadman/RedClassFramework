
#pragma once

#include "RedType.h"
#include "RedString.h"
#include "RedNumber.h"

namespace Red {
namespace Core {

    typedef enum TEventLogType {
        eErrorEvent,
        eWarningEvent,
        eInfoEvent,
        eUndefinedEvent
    } TEventLogType;

    class RedLogEvent
    {
    public:

        // Constructors
        RedLogEvent(const TEventLogType NewLogType)                           : LogType(NewLogType) {};
        RedLogEvent(const TEventLogType NewLogType, const RedString& NewText) : LogType(NewLogType), text(NewText) {};
        RedLogEvent(const RedString& NewText)                                 : LogType(eUndefinedEvent), text(NewText) {};
        RedLogEvent(const RedLogEvent& CurrEvent)                             : LogType(CurrEvent.LogType), text(CurrEvent.text) {};

        // Basic Accessors
        void                Init(void)                       { LogType = eInfoEvent; text.Init(); };
        const TEventLogType EventType(void) const            { return LogType; };
        const RedString     Text(void) const                 { return text; };
        void                Append(const RedString& newText) { text.Append(newText); };
        void                Append(const RedNumber& newNum)  { text.Append(newNum.DecimalString()); };

    private:
        TEventLogType LogType;
        RedString     text;
    };

} // Core
} // Red


