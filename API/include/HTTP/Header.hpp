//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_HEADER_HPP
#define API_V2_HEADER_HPP

#include <string>
#include <map>

namespace HTTP {
    class Header {
    public:
        Header();
        virtual ~Header();
    private:
        std::map<std::string, std::string> m_headers;

    public:
        std::string const &Get(std::string const &key) const;

        void Set(std::string const &key, std::string const &value);

        void Add(std::string const &key, std::string const &value);

        void Del(std::string const &key);

    };
}

#endif //API_V2_HEADER_HPP
