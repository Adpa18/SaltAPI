//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_ICORE_HPP
#define API_V2_ICORE_HPP

#include <vector>
#include "IModule.hpp"

class IModuleLoader;
class IConfig;

namespace Module {

    /*! @class ICore
     * Interface representing a module core
     */
    class ICore {
    public:
        /*! @fn bool Run(std::vector<std::string> const &opts, IModuleLoader *moduleLoader)
         *
         * @param opts arguments from main
         * @param moduleLoader pointer on moduleLoader
         * @return
         */
        virtual bool Run(std::vector<std::string> const &opts, IModuleLoader *moduleLoader) = 0;

        /*! @fn IConfig const &GetConfig() const
         *
         * @return const reference on Config
         */
        virtual IConfig const &GetConfig() const = 0;

    public:
        /*! @fn IModule *Get(std::string const &name) const
         * @brief Get the module by name from the list in ModuleLoader
         * @param name of the module
         * @return pointer on the module founded
         */
        virtual IModule *Get(std::string const &name) const = 0;

        /*! @fn IModule *Get(IModule::Type) const
        * @brief Get the module by Type from the list in ModuleLoader
        * @param type of the module
        * @return pointer on the module founded
        */
        virtual IModule *Get(IModule::Type type) const = 0;
    };
}
#endif //API_V2_ICORE_HPP
