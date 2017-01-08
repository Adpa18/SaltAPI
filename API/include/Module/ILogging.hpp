//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_ILOGGING_HPP
#define API_V2_ILOGGING_HPP

#include <string>

namespace Module {
    /*! @class ILogging
     * Interface for logging system
     */
    class ILogging {
    public:
        /*! @enum
         * Log Type
         */
        enum Type {
            Emergency,
            Alert,
            Critic,
            Error,
            Warning,
            Notice,
            Info,
            Debug
        };

        /*! @fn void Log(std::string const &msg, Type type = Type::Info) const
         *
         * @param msg to log
         * @param type of log
         */
        virtual void Log(std::string const &msg, Type type = Type::Info) const = 0;

    };
}

#endif //API_V2_ILOGGING_HPP
