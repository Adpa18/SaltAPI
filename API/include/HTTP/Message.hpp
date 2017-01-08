//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_MESSAGE_HPP
#define API_V2_MESSAGE_HPP

#include "Header.hpp"

class CommunicationSession;

/*! @namespace HTTP
 * Namespace for HTTP Communication
 */
namespace HTTP {
    /*! @class Message
     * Representation of a HTTP Message
     */
    class Message {
    public:
        Message();

        virtual ~Message();

    protected:
        unsigned char m_http_version_major;
        unsigned char m_http_version_minor;

        Header m_header;

        char *m_body;

        int m_content_length;

        CommunicationSession *m_communicationSession;

    public:
        /*! @fn Header &GetHeader() const
         *
         * @return Header reference
         */
        Header &GetHeader() const;

        /*! @fn char *Body() const
         *
         * @return body
         */
        char *Body() const;

        /*! @fn std::string GetHTTPVersion() const
         * @example "HTTP/1.1"
         * @return HTTP Version
         */
        std::string GetHTTPVersion() const;

        /*! @fn void setHTTPVersion(unsigned char major, unsigned char minor)
         * @brief set version of HTTP
         * @param major
         * @param minor
         */
        void setHTTPVersion(unsigned char major, unsigned char minor);

        /*! @fn CommunicationSession *GetSocket() const
         *
         * @return pointer on socket
         */
        CommunicationSession *GetSocket() const;

    };
}
#endif //API_V2_MESSAGE_HPP
