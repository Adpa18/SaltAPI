//
// Created by wery_a on 22/12/16.
//

#ifndef JSONPARSER_AOBJECT_HPP
#define JSONPARSER_AOBJECT_HPP

#include <string>

namespace Config {
    class Array;
    class Object;
    class AObject {
    public:
        AObject();
        virtual ~AObject();

    public:
        virtual void push(std::string const &key, char value);
        virtual void push(std::string const &key, int value);
        virtual void push(std::string const &key, float value);
        virtual void push(std::string const &key, double value);
        virtual void push(std::string const &key, std::string const &value);
        virtual void push(std::string const &key, Array *value);
        virtual void push(std::string const &key, Object *value);

        virtual void push(char value);
        virtual void push(int value);
        virtual void push(float value);
        virtual void push(double value);
        virtual void push(std::string const &value);
        virtual void push(Array *value);
        virtual void push(Object *value);
    };
}

#endif //JSONPARSER_IOBJECT_HPP
