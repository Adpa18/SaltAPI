//
// Created by wery_a on 09/01/17.
//

#include <algorithm>
#include "HTTP/ProcessingList.hpp"

namespace HTTP {
    ProcessingList::ProcessingList() {

    }

    ProcessingList::~ProcessingList() {

    }

    bool ProcessingList::pop() {
        m_events.pop_front();
    }

    EventFunction *ProcessingList::top() {
        return m_events.front();
    }

    EventFunction *ProcessingList::bottom() {
        return m_events.back();
    }

    bool ProcessingList::push(EventFunction *eventFunction) {
        m_events.push_back(eventFunction);
        return true;
    }

    bool ProcessingList::pushBefore(EventFunction *eventFunction, EventFunction *ref) {
        std::list<EventFunction *>::const_iterator pos = std::find(m_events.begin(), m_events.end(), ref);
        if (pos == m_events.end()) {
            return false;
        }
        pushBefore(eventFunction, pos);
        return true;
    }

    bool ProcessingList::pushBefore(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref) {
        m_events.insert(ref, eventFunction);
        return true;
    }

    bool ProcessingList::pushAfter(EventFunction *eventFunction, EventFunction *ref) {
        std::list<EventFunction *>::const_iterator pos = std::find(m_events.begin(), m_events.end(), ref);
        if (pos == m_events.end()) {
            return false;
        }
        pushAfter(eventFunction, pos);
        return true;
    }

    bool ProcessingList::pushAfter(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref) {
        m_events.insert(++ref, eventFunction);
        return true;
    }

    bool ProcessingList::next(Request *req, Response *res) {
        pop();
        (*top())(req, res, this);
    }
}