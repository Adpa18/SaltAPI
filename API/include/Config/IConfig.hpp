//
// Created by wery_a on 11/01/17.
//

#ifndef JSONPARSER_ICONFIG_HPP
#define JSONPARSER_ICONFIG_HPP

#include "Value.hpp"

namespace Config {
    class IConfig {
    public:
        virtual Value       &operator[](std::string const &key) = 0;
        virtual Value       const &operator[](std::string const &key) const = 0;
    };
}

#endif //JSONPARSER_ICONFIG_HPP
