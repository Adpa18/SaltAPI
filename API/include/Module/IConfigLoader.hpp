//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_ICONFIGLOADER_HPP
#define API_V2_ICONFIGLOADER_HPP

#include <string>

/*! @class IConfig
 * @brief This class is for the config
 * It's use to store a pointer of the config in the Core
 * You have to dynamic_cast your IConfig pointer to your Config class
 * @example IConfigClass The config is JSON::Object, JSON::Object inherit from IConfig
 * @example usage dynamic_cast<JSON::Object>(config_ptr)
 *
 */
class IConfig {};

namespace Module {
    /*! @class IConfigLoader
     * Interface of class that call default config and parser config
     */
    class IConfigLoader {
    public:
        /*! @fn IConfig *LoadConfig(std::string const &path)
         * @brief LoadConfig from file
         * @param path of the module
         * @return pointer on IConfig
         */
        virtual IConfig *LoadConfig(std::string const &path) = 0;
    };
}

#endif //API_V2_ICONFIGLOADER_HPP
