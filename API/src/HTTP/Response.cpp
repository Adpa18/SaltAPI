//
// Created by wery_a on 09/01/17.
//

#include "HTTP/Response.hpp"

namespace HTTP {
    Response::Response() {

    }

    Response::~Response() {

    }

    std::string const& Response::GetStatusMsg() const {
        return m_status_msg;
    }

    unsigned int Response::GetStatusCode() const {
        return m_status_code;
    }

    Request* Response::GetRequest() const {
        return m_request;
    }

    void Response::SetStatusMsg(std::string const &msg) {
        m_status_msg = msg;
    }

    void Response::SetStatusCode(unsigned int code) {
        m_status_code = code;
    }

    void Response::SetRequest(Request *request) {
        m_request = request;
    }
}