
#pragma once

#include "RedType.h"
#include "RedString.h"
#include "RedLogEvent.h"
#include "RedDoubleLinkedList.h"
#include "RedDoubleLinkedListIterator.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace Red {
namespace Core {

    typedef RedDoubleLinkedList<RedLogEvent*>         EventLogListType;
    typedef RedDoubleLinkedListIterator<RedLogEvent*> EventLogListItType;

    /// \Brief Holds logged information, from text debug statements, info, warnings and 
    ///        error messages. Has additional methods to then query the information.
    class RedLog
    {
    public:

        RedLog(void) : containsError(0) { };
        void Init(void) { EventList.DelAll(); containsError=0; };

        void AddEvent(const RedLogEvent& event);
        void AddText (const RedString& NewText);

        void AddErrorEvent(const RedString& NewText);
        void AddErrorEvent(const char* NewText) { AddErrorEvent(RedString(NewText)); };

        // Queries
        //EventLogListType EventsByType();

        const int NumEvents(void) const { return EventList.NumItems(); };
        const int IsError(void)   const { return containsError; };

    private:
        EventLogListType EventList;
        int              containsError;
    };
    
} // Logging
} // Red

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


