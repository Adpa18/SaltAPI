//
// Created by wery_a on 18/12/16.
//

#ifndef JSONPARSER_ARRAY_HPP
#define JSONPARSER_ARRAY_HPP

#include <vector>
#include "AObject.hpp"
#include "Value.hpp"

namespace Config {
    class Array: public AObject {
    public:
        typedef std::vector<Value*>  ValueList;
        Array();
        virtual ~Array();

    private:
        ValueList   m_array;

    public:
        ValueList   const &getValues() const;

    public:
        ValueList   const &operator*() const;
        Value       &operator[](unsigned int key);
        Value       const &operator[](unsigned int key) const;

    public:
        Value       &get(unsigned int key) const;
        char        get(unsigned int key, char &rvalue) const;
        int         get(unsigned int key, int &rvalue) const;
        float       get(unsigned int key, float &rvalue) const;
        double      get(unsigned int key, double &rvalue) const;
        std::string get(unsigned int key, std::string &rvalue) const;
        Array       &get(unsigned int key, Array &rvalue) const;
        Object      &get(unsigned int key, Object &rvalue) const;

    public:
        void push(Value *value);
        void push(char value);
        void push(int value);
        void push(float value);
        void push(double value);
        void push(std::string const &value);
        void push(Array *value);
        void push(Object *value);

    public:
        std::string const   toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Array &array);
        friend std::ostream& operator<<(std::ostream& os, const Array *array);
    };
}

#endif //JSONPARSER_ARRAY_HPP
