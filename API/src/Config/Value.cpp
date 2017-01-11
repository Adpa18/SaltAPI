//
// Created by wery_a on 23/12/16.
//

#include <sstream>
#include "../../include/Config/Value.hpp"
#include "../../include/Config/Array.hpp"
#include "../../include/Config/Object.hpp"

namespace Config {
    Value::~Value() {
        deleteValue();
    }

    void Value::deleteValue() {
        switch (m_type) {
            case STRING:
                delete m_value.s;
                break;
            case ARRAY:
                delete m_value.array;
                break;
            case OBJECT:
                delete m_value.object;
                break;
            default:
                break;
        }
    }

    Value::Value(char value) {
        m_type = CHAR;
        this->m_value.c = value;
    }

    Value::Value(int value) {
        m_type = INT;
        this->m_value.i = value;
    }

    Value::Value(float value) {
        m_type = FLOAT;
        this->m_value.f = value;
    }

    Value::Value(double value) {
        m_type = DOUBLE;
        this->m_value.d = value;
    }

    Value::Value(std::string value) {
        m_type = STRING;
        this->m_value.s = new std::string(value);
    }

    Value::Value(Array *value) {
        m_type = ARRAY;
        this->m_value.array = value;
    }

    Value::Value(Object *value) {
        m_type = OBJECT;
        this->m_value.object = value;
    }

    Value   &Value::operator=(char value) {
        deleteValue();
        m_type = CHAR;
        this->m_value.c = value;
        return *this;
    }

    Value   &Value::operator=(int value) {
        deleteValue();
        m_type = INT;
        this->m_value.i = value;
        return *this;
    }

    Value   &Value::operator=(float value) {
        deleteValue();
        m_type = FLOAT;
        this->m_value.f = value;
        return *this;
    }

    Value   &Value::operator=(double value) {
        deleteValue();
        m_type = DOUBLE;
        this->m_value.d = value;
        return *this;
    }

    Value   &Value::operator=(std::string value) {
        deleteValue();
        m_type = STRING;
        this->m_value.s = new std::string(value);
        return *this;
    }

    Value   &Value::operator=(Array *value) {
        deleteValue();
        m_type = ARRAY;
        this->m_value.array = value;
        return *this;
    }

    Value   &Value::operator=(Object *value) {
        deleteValue();
        m_type = OBJECT;
        this->m_value.object = value;
        return *this;
    }

    ValueType Value::GetType() const {
        return m_type;
    }

    char Value::GetChar() const {
        if (m_type != CHAR) {
            throw std::runtime_error("Bad type, Cannot get char");
        }
        return m_value.c;
    }

    int Value::GetInt() const {
        if (m_type != INT) {
            throw std::runtime_error("Bad type, Cannot get int");
        }
        return m_value.i;
    }

    float Value::GetFloat() const {
        if (m_type != FLOAT) {
            throw std::runtime_error("Bad type, Cannot get float");
        }
        return m_value.f;
    }

    double Value::GetDouble() const {
        if (m_type != DOUBLE) {
            throw std::runtime_error("Bad type, Cannot get double");
        }
        return m_value.d;
    }

    std::string &Value::GetString() const {
        if (m_type != STRING) {
            throw std::runtime_error("Bad type, Cannot get string");
        }
        return *m_value.s;
    }

    Array &Value::GetArray() const {
        if (m_type != ARRAY) {
            throw std::runtime_error("Bad type, Cannot get Array");
        }
        return *m_value.array;
    }

    Object &Value::GetObject() const {
        if (m_type != OBJECT) {
            throw std::runtime_error("Bad type, Cannot get Object");
        }
        return *m_value.object;
    }

    std::string const Value::toString() const {
        std::stringstream ss;

        switch (m_type) {
            case CHAR:
                ss << m_value.c;
                break;
            case INT:
                ss << m_value.i;
                break;
            case FLOAT:
                ss << m_value.f;
                break;
            case DOUBLE:
                ss << m_value.d;
                break;
            case STRING:
                ss << "\"" << *(m_value.s) << "\"";
                break;
            case ARRAY:
                ss << *(m_value.array);
                break;
            case OBJECT:
                ss << *(m_value.object);
                break;
            default:
                throw std::runtime_error("Bad Type");
        }
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Value &value) {
        return os << value.toString();
    }
    std::ostream &operator<<(std::ostream &os, const Value *value) {
        return operator<<(os, *value);
    }

}