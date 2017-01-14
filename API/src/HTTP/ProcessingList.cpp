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

    EventFunctionList::iterator ProcessingList::begin() {
        return m_events.begin();
    }

    EventFunctionList::iterator ProcessingList::end() {
        return m_events.end();
    }

    EventFunctionList::iterator ProcessingList::push(EventFunction eventFunction) {
        m_events.push_back(eventFunction);
        return m_events.end();
    }

    EventFunctionList::iterator ProcessingList::pushBefore(EventFunction eventFunction, EventFunctionList::const_iterator ref) {
        return m_events.insert(ref, eventFunction);
    }


    EventFunctionList::iterator ProcessingList::pushAfter(EventFunction eventFunction, EventFunctionList::const_iterator ref) {
        return m_events.insert(++ref, eventFunction);
    }

    bool ProcessingList::next(Request *req, Response *res) {
        pop();
        (*begin())(req, res, this);
    }
}