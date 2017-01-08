//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_AMODULELOADER_HPP
#define API_V2_AMODULELOADER_HPP

#include <map>
#include "IModuleLoader.hpp"

class AModuleLoader: public IModuleLoader {
public:
    AModuleLoader();
    virtual ~AModuleLoader();

protected:
    std::map<std::string, Module::IModule *>    m_modules;

public:
    IModuleLoader   *Load(std::string const &path) override;
    bool            Unload(Module::IModule *module) override;
    bool            IsLoaded(std::string const &name) const override;
    bool            IsLoaded(Module::IModule::Type type) const override;
};

#endif //API_V2_AMODULELOADER_HPP
