//
// Created by wery_a on 09/01/17.
//

#ifndef API_V2_ZIP_HPP
#define API_V2_ZIP_HPP

#include "Module/IHTTPHandle.hpp"
#include "Module/AModule.hpp"
#include "DllExport.hpp"

extern "C"
{
    class EXPORT Zip : public Module::AModule, public Module::IHTTPHandle {
    public :
        Zip(Module::ICore &core);

        virtual ~Zip();

    public :
        bool Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl);

    public :
        Module::IModule *GetModule(Module::ICore &core) const override;
    };

    Module::IModule	*LoadModule(Module::ICore &core);
}

#endif //API_V2_ZIP_HPP
