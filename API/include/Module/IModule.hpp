//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_IMODULE_HPP
#define API_V2_IMODULE_HPP

#include <string>

/*! @namespace Module
 * Namespace for all Modules
 *
 */
namespace Module {
    class ICore;

    /*! @class IModule
     * Interface representing a module
     */
    class IModule {
    public:
        /*! @enum Type
         * Type of a module
         */
        enum Type {
            Core,
            Logging,
            ConfigLoader,
            Network,
            FileServe,
            ModuleHandler
        };

    public:
        /*! @fn std::string const &GetName() const
         *
         * @return name of the module
         */
        virtual std::string const &GetName() const = 0;

        /*! @fn Type GetType() const
         *
         * @return type of the module
         */
        virtual Type GetType() const = 0;

    public:
        /*! @fn bool Load()
         * @brief Method for futur use
         * @return true if everything is ok
         */
        virtual bool Load() = 0;

        /*! bool Unload()
         * @brief Method for futur use
         * @return true if everything is ok
         */
        virtual bool Unload() = 0;

    public:
        /*! @fn IModule *GetModule(ICore &core) const
         * @brief The function return an instance of the module
         * @param core
         * @return pointer on module instance
         */
        virtual IModule *GetModule(ICore &core) const = 0;
    };

}

#endif //API_V2_IMODULE_HPP
