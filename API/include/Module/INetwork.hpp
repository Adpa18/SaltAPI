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
        /*! @fn bool Raise(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl)
         *
         * @param req the default request from the core
         * @param res the default response from the core
         * @param pl the default processsingList from the core
         * @return
         */
        virtual bool Raise(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) = 0;

        /*! @fn bool OnRequest()
         * @brief this function is called when a request is received
         * @return
         */
        virtual bool OnRequest() = 0;

        /*! @fn bool Send(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl)
         *
         * @param req the request from the previous module
         * @param res the response from the previous module
         * @param pl the processsingList from the previous module
         * @return
         */
        virtual bool Send(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) = 0;
    };
}

#endif //API_V2_INETWORK_HPP
