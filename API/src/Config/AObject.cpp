//
// Created by wery_a on 22/12/16.
//

#include <stdexcept>
#include "../../include/Config/AObject.hpp"

namespace Config {
    AObject::AObject() {

    }


    AObject::~AObject() {

    }

    void AObject::push(std::string const &, char) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &, int) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &, float) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &, double) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &key, std::string const &value) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &, Array *) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &, Object *) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(char) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(int) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(float) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(double) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(std::string const &value) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(Array *) {
        throw std::runtime_error("Not Inplemented for this type");
    }

    void AObject::push(Object *) {
        throw std::runtime_error("Not Inplemented for this type");
    }
}