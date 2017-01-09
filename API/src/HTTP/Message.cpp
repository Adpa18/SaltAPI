//
// Created by wery_a on 09/01/17.
//

#include <sstream>
#include <cstring>
#include "HTTP/Message.hpp"

namespace HTTP {
    Message::Message() {

    }

    Message::~Message() {
        delete m_body;
    }

    Header &Message::GetHeader() {
        return m_header;
    }

    char *const Message::GetBody() const {
        return m_body;
    }

    std::string Message::GetHTTPVersion() const {
        std::ostringstream oss;

        oss << "HTTP/" << m_http_version_major << "." << m_http_version_minor;
        return oss.str();
    }

    void Message::SetHTTPVersion(unsigned char major, unsigned char minor) {
        m_http_version_major = major;
        m_http_version_minor = minor;
    }

    void Message::SetBody(std::string const &body) {
        SetBody(body.c_str(), body.length());
    }

    void Message::SetBody(const char *body, unsigned long size) {
        if (m_body) {
            delete m_body;
        }
        m_body = new char[size];
        std::memcpy(m_body, body, size);
    }

    CommunicationSession *Message::GetSocket() const {
        return m_communicationSession;
    }
}