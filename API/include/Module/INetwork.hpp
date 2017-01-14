//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_INETWORK_HPP
#define API_V2_INETWORK_HPP

namespace HTTP {
    class Request;

    class Response;

    class ProcessingList;
}

namespace Module {
    /*! @class INetwork
     * Interface for network
     */
    class INetwork {
    public:
        /*! @fn bool Start(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl)
         *
         * @param req the default request from the core
         * @param res the default response from the core
         * @param pl the default processsingList from the core
         * @return
         */
        virtual bool Start(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) = 0;

        /*! @fn void Poll()
         * @brief this function is used to handle client just one time and return just before
         * @return void
         */
        virtual void Poll() = 0;

        /*! @fn void Run()
         * @brief this function is used to handle client and never return
         * @return
         */
        virtual void Run() = 0;
    };
}

#endif //API_V2_INETWORK_HPP
