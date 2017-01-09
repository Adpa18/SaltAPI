//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_REQUEST_HPP
#define API_V2_REQUEST_HPP

#include "Message.hpp"

namespace HTTP {
    class Response;

    /*! @class Request
     * Representation of HTTP Request
     */
    class Request : public Message {
    public:
        Request();

        virtual ~Request();

    private:
        std::string m_method;
        std::string m_url;

        Response *m_response;

    public:
        /*! @fn std::string const &GetMethod() const
         *
         * @return method
         */
        std::string const &GetMethod() const;

        /*! @fn std::string const &GetURL() const
         *
         * @return URL
         */
        std::string const &GetURL() const;

        /*! @fn Response *GetResponse() const
         *
         * @return Response pointer
         */
        Response *GetResponse() const;

    public:
        /*! @fn void SetMethod(std::string const &method)
         * @brief set Method
         * @param method
         */
        void SetMethod(std::string const &method);

        /*! @fn void SetURL(std::string const &url)
         * @brief set URL
         * @param url
         */
        void SetURL(std::string const &url);

        /*! @fn void SetResponse(Response *response)
         * @brief set Response
         * @param response
         */
        void SetResponse(Response *response);
    };
}

#endif //API_V2_REQUEST_HPP
