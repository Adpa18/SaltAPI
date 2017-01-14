//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_IMODULELOADER_HPP
#define API_V2_IMODULELOADER_HPP

#include "Module/IModule.hpp"

/*! @class IModuleLoader
 * Interface for module Loader
 */
class IModuleLoader {
public:
    virtual ~IModuleLoader() {}
    
    /*! @fn Module::IModule *Load(std::string const &path)
     * @brief load module by path
     * @param path
     * @return loaded module
     */
    virtual Module::IModule *Load(std::string const &path) = 0;

    /*! @fn bool Unload(Module::IModule *module)
     *  @brief unload module by pointer
     * @param module
     * @return
     */
    virtual bool Unload(Module::IModule *module) = 0;

    /*! @fn bool IsLoaded(std::string const &name) const
     * @brief check if module is loaded by name
     * @param name
     * @return is module loaded
     */
    virtual bool IsLoaded(std::string const &name) const = 0;

    /*! @fn bool IsLoaded(Module::IModule::Type type) const
     * @brief check if module is loaded by type
     * @param type
     * @return is module loaded
     */
    virtual bool IsLoaded(Module::IModule::Type type) const = 0;

public:
    /*! @fn Module::IModule *Get(std::string const &name) const
     *
     * @param name
     * @return module got by name
     */
    virtual Module::IModule *Get(std::string const &name) const = 0;

    /*! @fn Module::IModule *Get(Module::IModule::Type) const
     *
     * @return module got by type
     */
    virtual Module::IModule *Get(Module::IModule::Type) const = 0;

};

#endif //API_V2_IMODULELOADER_HPP
