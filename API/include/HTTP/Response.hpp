//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_RESPONSE_HPP
#define API_V2_RESPONSE_HPP

#include "Message.hpp"

namespace HTTP {
    class Request;

    /*! @class Response
     * Representation of HTTP Response
     */
    class Response : public Message {
    public:
        Response();

        virtual ~Response();

    private:
        std::string m_status_msg;
        unsigned int m_status_code;

        Request *m_request;

    public:
        /*! @fn std::string const &GetStatusMsg() const
         *
         * @return Status Message
         */
        std::string const &GetStatusMsg() const;

        /*! @fn unsigned int GetStatusCode() const
         *
         * @return Status Code
         */
        unsigned int GetStatusCode() const;

        /*! @fn Request *GetRequest() const
         *
         * @return Request pointer
         */
        Request *GetRequest() const;

        /*! @fn void SetStatusMsg(std::string const &msg)
         * @brief set message
         * @param msg
         */
        void SetStatusMsg(std::string const &msg);

        /*! @fn void SetStatusCode(unsigned int code)
         * @brief set code
         * @param code
         */
        void SetStatusCode(unsigned int code);

        /*! @fn void SetRequest(Request *request)
         * @brief set Request
         * @param request
         */
        void SetRequest(Request *request);
    };
}

#endif //API_V2_RESPONSE_HPP
