//
// Created by wery_a on 18/12/16.
//

#include <sstream>
#include "../../include/Config/Object.hpp"
#include "../../include/Config/Array.hpp"

namespace Config {
    Object::Object() {

    }

    Object::~Object() {
        for (ValueMap::const_iterator it = m_values.begin(); it != m_values.end(); ++it) {
            delete it->second;
        }
    }

    Object::ValueMap    const &Object::getValues() const {
        return m_values;
    };

    Object::ValueMap    const& Object::operator*() const {
        return m_values;
    }

    Value& Object::operator[](std::string const &key) {
        return get(key);
    }

    Value const & Object::operator[](std::string const &key) const {
        return get(key);
    }

    Value &Object::get(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->GetType() == UNKNOWN) {
            throw std::runtime_error("Bad key " + it->first);
        }
        return *it->second;
    }

    char Object::get(std::string const &key, char &rvalue) const {
        rvalue = get(key).GetChar();
        return rvalue;
    }

    int Object::get(std::string const &key, int &rvalue) const {
        rvalue = get(key).GetInt();
        return rvalue;
    }

    float Object::get(std::string const &key, float &rvalue) const {
        rvalue = get(key).GetFloat();
        return rvalue;
    }

    double Object::get(std::string const &key, double &rvalue) const {
        rvalue = get(key).GetDouble();
        return rvalue;
    }

    std::string Object::get(std::string const &key, std::string &rvalue) const {
        rvalue = get(key).GetString();
        return rvalue;
    }

    Array &Object::get(std::string const &key, Array &rvalue) const {
        rvalue = get(key).GetArray();
        return rvalue;
    }

    Object &Object::get(std::string const &key, Object &rvalue) const {
        rvalue = get(key).GetObject();
        return rvalue;
    }

    void Object::push(std::string const &key, Value *value) {
        m_values[key] = value;
    }

    void Object::push(std::string const &key, char value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, int value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, float value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, double value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, std::string const &value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, Array *value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, Object *value) {
        m_values[key] = new Value(value);
    }

    std::string const Object::toString() const {
        std::stringstream   ss;
        ss << "{";
        Object::ValueMap::const_iterator last_it = --m_values.end();
        for (Object::ValueMap::const_iterator it = m_values.begin(); it != m_values.end(); ++it) {
            ss << "\"" << it->first << "\"" << ":" << *(it->second);
            if (it != last_it) {
                ss << ",";
            }
        }
        ss << "}";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Object &object) {
        return os << object.toString();
    }

    std::ostream &operator<<(std::ostream &os, const Object *object) {
        return operator<<(os, *object);
    }
}

