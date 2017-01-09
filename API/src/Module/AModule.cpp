//
// Created by wery_a on 09/01/17.
//

#include "Module/AModule.hpp"

namespace Module {
    AModule::AModule(ICore &core, Type type, std::string const &name)
            : m_core(core), m_type(type), m_name(name) {

    }

    AModule::~AModule() {

    }

    std::string const &AModule::GetName() const {
        return m_name;
    }

    IModule::Type AModule::GetType() const {
        return m_type;
    }

    bool AModule::Load() {

    }

    bool AModule::Unload() {

    }

    IModule *AModule::GetModule(ICore &core) const {
        return new AModule(core, Default, "Module");
    }
}