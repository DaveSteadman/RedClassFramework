
#include "RedType.h"
#include "RedString.h"
#include "RedLogEvent.h"
#include "RedLog.h"

namespace Red {
namespace Core {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddEvent(const RedLogEvent& event)
{
    if (event.EventType() == eErrorEvent)
        containsError = 1;

    RedLogEvent* storedEvent = new RedLogEvent(event);

    EventList.AddLast(storedEvent);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddText(const RedString& NewText)
{
    RedLogEvent* storedEvent = new RedLogEvent(NewText);

    EventList.AddLast(storedEvent);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void RedLog::AddErrorEvent(const RedString& NewText)
{
    RedLogEvent* storedEvent = new RedLogEvent(eErrorEvent, NewText);

    EventList.AddLast(storedEvent);
    containsError = 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // Core
} // Red


