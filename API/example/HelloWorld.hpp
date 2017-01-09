//
// Created by wery_a on 09/01/17.
//

#ifndef API_V2_HELLOWORLD_HPP
#define API_V2_HELLOWORLD_HPP

#include "Module/IHTTPHandle.hpp"
#include "Module/AModule.hpp"
#include "DllExport.hpp"

extern "C"
{
    class EXPORT HelloWorld : public Module::IHTTPHandle, public Module::AModule
    {
    public:
        HelloWorld(Module::ICore &core);

        virtual ~HelloWorld();

    public:
        bool Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl);

    public:
        Module::IModule *GetModule(Module::ICore &core) const override;
    };
}

#endif //API_V2_HELLOWORLD_HPP
