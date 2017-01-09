//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_PROCESSINGLIST_HPP
#define API_V2_PROCESSINGLIST_HPP

#include <list>

namespace HTTP {
    class Request;

    class Response;

    class ProcessingList;

    /*! @typedef EventFunction
     * type of an event function
     */
    typedef bool (*EventFunction)(Request *req, Response *res, ProcessingList *pl);

    class ProcessingList {
    public:
        ProcessingList();

        virtual ~ProcessingList();

    private:
        std::list<EventFunction *> m_events;

    public:
        /*! @fn bool pop();
         * @brief pop first elem
         * @return
         */
        bool pop();

        /*! @fn EventFunction *top()
         *
         * @return first elem
         */
        EventFunction *top();

        /*! EventFunction *bottom()
         *
         * @returnlast elem
         */
        EventFunction *bottom();

        /*! @fn bool push(EventFunction *eventFunction)
         * @brief push back eventFunction
         * @param eventFunction
         * @return
         */
        bool push(EventFunction *eventFunction);

        /*! @fn bool pushBefore(EventFunction *eventFunction, EventFunction *ref)
         * @brief push eventFunction before ref pointer
         * @param eventFunction
         * @param ref
         * @return
         */
        bool pushBefore(EventFunction *eventFunction, EventFunction *ref);

        /*! @fn bool pushBefore(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref)
         * @brief push eventFunction before iterator
         * @param eventFunction
         * @param ref
         * @return
         */
        bool pushBefore(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref);

        /*! @fn bool pushAfter(EventFunction *eventFunction, EventFunction *ref)
        * @brief push eventFunction after ref pointer
        * @param eventFunction
        * @param ref
        * @return
        */
        bool pushAfter(EventFunction *eventFunction, EventFunction *ref);

        /*! @fn bool pushAfter(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref)
        * @brief push eventFunction after iterator
        * @param eventFunction
        * @param ref
        * @return
        */
        bool pushAfter(EventFunction *eventFunction, std::list<EventFunction *>::const_iterator ref);

        /*! @fn bool next() const
         * @brief pop current event and call next event
         * @return
         */
        bool next(Request *req, Response *res);
    };
}

#endif //API_V2_PROCESSINGLIST_HPP
