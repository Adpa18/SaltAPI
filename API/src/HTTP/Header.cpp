//
// Created by wery_a on 09/01/17.
//

#include "HTTP/Header.hpp"

namespace HTTP {
    Header::Header() {

    }

    Header::~Header() {

    }

    std::string const &Header::Get(std::string const &key) const {
        std::map<std::string, std::string>::const_iterator it = m_headers.find(key);
        return it->second;
    }

    void Header::Set(std::string const &key, std::string const &value) {
        if (m_headers.find(key) == m_headers.end()) {
            // TODO warning key doesn't exist
        }
        m_headers[key] = value;
    }

    void Header::Add(std::string const &key, std::string const &value) {
        if (m_headers.find(key) != m_headers.end()) {
            // TODO warning already exist
        }
        m_headers[key] = value;
    }

    void Header::Del(std::string const &key) {
        if (m_headers.find(key) == m_headers.end()) {
            // TODO warning key doesn't exist
        }
        m_headers.erase(key);
    }
}