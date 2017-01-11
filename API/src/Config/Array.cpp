//
// Created by wery_a on 22/12/16.
//

#include <sstream>
#include "../../include/Config/Array.hpp"
#include "../../include/Config/Object.hpp"

namespace Config {
    Array::Array() {

    }

    Array::~Array() {
        for (ValueList::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            delete *it;
        }
    }

    Array::ValueList   const& Array::getValues() const {
        return m_array;
    }

    Array::ValueList   const& Array::operator*() const {
        return m_array;
    }

    Value& Array::operator[](unsigned int key) {
        return *m_array[key];
    }

    const Value& Array::operator[](unsigned int key) const {
        return *m_array[key];
    }

    Value& Array::get(unsigned int key) const {
        if (key >= m_array.size() || m_array[key]->GetType() == UNKNOWN) {
            throw std::runtime_error("Bad key " + key);
        }
        return *m_array[key];
    }

    char Array::get(unsigned int key, char &rvalue) const {
        rvalue = get(key).GetChar();
        return rvalue;
    }

    int Array::get(unsigned int key, int &rvalue) const {
        rvalue = get(key).GetInt();
        return rvalue;
    }

    float Array::get(unsigned int key, float &rvalue) const {
        rvalue = get(key).GetFloat();
        return rvalue;
    }

    double Array::get(unsigned int key, double &rvalue) const {
        rvalue = get(key).GetDouble();
        return rvalue;
    }

    std::string Array::get(unsigned int key, std::string &rvalue) const {
        rvalue = get(key).GetString();
        return rvalue;
    }

    Array &Array::get(unsigned int key, Array &rvalue) const {
        rvalue = get(key).GetArray();
        return rvalue;
    }

    Object &Array::get(unsigned int key, Object &rvalue) const {
        rvalue = get(key).GetObject();
        return rvalue;
    }


    void Array::push(Value *value) {
        m_array.push_back(value);
    }

    void Array::push(char value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(int value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(float value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(double value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(std::string const &value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(Array *value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(Object *value) {
        m_array.push_back(new Value(value));
    }

    std::string const Array::toString() const {
        std::stringstream   ss;

        ss << "[";
        Array::ValueList::const_iterator last_it = --m_array.end();
        for (Array::ValueList::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            ss << *(*it);
            if (it != last_it) {
                ss << ",";
            }
        }
        ss << "]";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Array &array) {
        return os << array.toString();
    }

    std::ostream &operator<<(std::ostream &os, const Array *array) {
        return operator<<(os, *array);
    }
}