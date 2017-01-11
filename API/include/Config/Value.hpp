//
// Created by wery_a on 18/12/16.
//

#ifndef JSONPARSER_VALUE_HPP
#define JSONPARSER_VALUE_HPP

#include <string>
#include <ostream>

namespace Config {
    class Object;
    class Array;
    enum ValueType {
        UNKNOWN = 0,
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        STRING,
        ARRAY,
        OBJECT
    };
    union ValueValue {
        char    c;
        int     i;
        float   f;
        double  d;
        std::string *s;
        Array       *array;
        Object      *object;
    };

    class Value {
    public:
        Value(char value);
        Value(int value);
        Value(float value);
        Value(double value);
        Value(std::string value);
        Value(Array *value);
        Value(Object *value);

        Value&operator=(char value);
        Value&operator=(int value);
        Value&operator=(float value);
        Value&operator=(double value);
        Value&operator=(std::string value);
        Value&operator=(Array *value);
        Value&operator=(Object *value);

        ~Value();
        void    deleteValue();

    private:
        ValueType   m_type;
        ValueValue  m_value;

    public:
        ValueType   GetType() const;
        char        GetChar() const;
        int         GetInt() const;
        float       GetFloat() const;
        double      GetDouble() const;
        std::string &GetString() const;
        Array       &GetArray() const;
        Object      &GetObject() const;

    public:
        std::string const   toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Value &value);
        friend std::ostream& operator<<(std::ostream& os, const Value *value);
    };
}


#endif //JSONPARSER_VALUE_HPP
