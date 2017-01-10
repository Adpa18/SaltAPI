//
// Created by wery_a on 09/01/17.
//

#ifndef API_V2_ADDEVENT_HPP
#define API_V2_ADDEVENT_HPP

#include "Module/IHTTPHandle.hpp"
#include "Module/AModule.hpp"
#include "DllExport.hpp"

extern "C"
{
class EXPORT AddEvent : public Module::IHTTPHandle, public Module::AModule {
public:
    AddEvent(Module::ICore &core);

    virtual ~AddEvent();

public:
    bool Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl);

public:
    Module::IModule *GetModule(Module::ICore &core) const override;
};
}

#endif //API_V2_ADDEVENT_HPP
