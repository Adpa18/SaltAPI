//
// Created by wery_a on 09/01/17.
//

#include "Module/ACore.hpp"

namespace Module {
    ACore::ACore(ICore &core, std::string const &name): AModule(*this, Core, name) {

    }

    ACore::~ACore() {

    }

    bool ACore::Run(std::vector<std::string> const &opts, IModuleLoader *moduleLoader) {
        m_moduleLoader = moduleLoader;
        // TODO load module
        return true;
    }

    IConfig const& ACore::GetConfig() const {
        return *m_config;
    }

    IModule* ACore::Get(std::string const &name) const {
        return m_moduleLoader->Get(name);
    }

    IModule* ACore::Get(IModule::Type type) const {
        return m_moduleLoader->Get(type);
    }

    IModule* ACore::GetModule(ICore &core) const {
        return new ACore(core, "Core");
    }
}