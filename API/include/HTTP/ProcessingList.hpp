//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_PROCESSINGLIST_HPP
#define API_V2_PROCESSINGLIST_HPP

#include <list>
#include <functional>

namespace HTTP {
    class Request;

    class Response;

    class ProcessingList;

    /*! @typedef EventFunction
     * type of an event function
     */
//    typedef bool (EventFunction)(Request *req, Response *res, ProcessingList *pl);
    typedef std::function<bool(Request *req, Response *res, ProcessingList *pl)> EventFunction;

    typedef std::list<EventFunction>    EventFunctionList;

    class ProcessingList {
    public:
        ProcessingList();

        virtual ~ProcessingList();

    private:
        EventFunctionList m_events;

    public:
        /*! @fn bool pop();
         * @brief pop first elem
         * @return
         */
        bool pop();

        /*! @fn EventFunction begin()
         *
         * @return first iterator
         */
        EventFunctionList::iterator begin();

        /*! EventFunction *bottom()
         *
         * @return last iterator
         */
        EventFunctionList::iterator end();

        /*! @fn EventFunctionList::iterator push(EventFunction eventFunction)
         * @brief push back eventFunction
         * @param eventFunction
         * @return
         */
        EventFunctionList::iterator push(EventFunction eventFunction);


        /*! @fn EventFunctionList::iterator pushBefore(EventFunction eventFunction, EventFunctionList::const_iterator ref)
         * @brief push eventFunction before iterator
         * @param eventFunction
         * @param ref
         * @return iterator of new eventFunction
         */
        EventFunctionList::iterator pushBefore(EventFunction eventFunction, EventFunctionList::const_iterator ref);

        /*! @fn EventFunctionList::iterator pushAfter(EventFunction eventFunction, EventFunctionList::const_iterator ref)
        * @brief push eventFunction after iterator
        * @param eventFunction
        * @param ref
        * @return iterator of new eventFunction
        */
        EventFunctionList::iterator pushAfter(EventFunction eventFunction, EventFunctionList::const_iterator ref);

        /*! @fn bool next() const
         * @brief pop current event and call next event
         * @return iterator of new eventFunction
         */
        bool next(Request *req, Response *res);
    };
}

#endif //API_V2_PROCESSINGLIST_HPP
