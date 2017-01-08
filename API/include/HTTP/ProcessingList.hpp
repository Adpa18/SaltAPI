//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_PROCESSINGLIST_HPP
#define API_V2_PROCESSINGLIST_HPP

#include <list>

namespace HTTP {
    class Request;

    class Response;

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

        /*! @fn bool pushBefore(EventFunction *eventFunction)
         * @brief push before eventFunction pointer
         * @param eventFunction
         * @return
         */
        bool pushBefore(EventFunction *eventFunction);

        /*! @fn bool pushBefore(std::list<EventFunction *>::const_iterator it)
         * @brief push before iterator
         * @param it
         * @return
         */
        bool pushBefore(std::list<EventFunction *>::const_iterator it);

        /*! @fn bool pushAfter(EventFunction *eventFunction)
        * @brief push after eventFunction pointer
        * @param eventFunction
        * @return
        */
        bool pushAfter(EventFunction *eventFunction);

        /*! @fn bool pushAfter(std::list<EventFunction *>::const_iterator it)
        * @brief push after iterator
        * @param it
        * @return
        */
        bool pushAfter(std::list<EventFunction *>::const_iterator it);
    };
}

#endif //API_V2_PROCESSINGLIST_HPP
