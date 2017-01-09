//
// Created by wery_a on 09/01/17.
//

#include "HTTP/Request.hpp"

namespace HTTP {
    Request::Request() {

    }

    Request::~Request() {

    }

    std::string const& Request::GetMethod() const {
        return m_method;
    }

    std::string const& Request::GetURL() const {
        return m_url;
    }

    Response* Request::GetResponse() const {
        return m_response;
    }

    void Request::SetMethod(std::string const &method) {
        m_method = method;
    }

    void Request::SetURL(std::string const &url) {
        m_url = url;
    }

    void Request::SetResponse(Response *response) {
        m_response = response;
    }
}