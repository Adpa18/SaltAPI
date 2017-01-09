//
// Created by wery_a on 09/01/17.
//

#ifndef API_V2_IHTTPHANDLE_HPP
#define API_V2_IHTTPHANDLE_HPP

namespace HTTP {
    class Request;

    class Response;

    class ProcessingList;
}

namespace Module {
    /*! @class IHTTPHandle
     * Interface for all HTTP modules
     * @example Module (HTTP Parser, HTTP Validator, HTTP Inspector)
     */
    class IHTTPHandle {
    public:
        /*! @fn bool Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl)
         *
         * @param req the request from the previous module
         * @param res the response from the previous module
         * @param pl the processsingList from the previous module
         * @return
         */
        virtual bool Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) = 0;
    };
}

#endif //API_V2_IHTTPHANDLE_HPP
