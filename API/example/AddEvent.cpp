//
// Created by wery_a on 09/01/17.
//

#include <functional>
#include "AddEvent.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"
#include "Module/ACore.hpp"

AddEvent::AddEvent(Module::ICore &core): Module::AModule(core, HTTP, "AddEvent") {

}

AddEvent::~AddEvent() {

}

bool AddEvent::Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    Module::IHTTPHandle *zipModule = dynamic_cast<Module::IHTTPHandle*>(m_core.Get("Zip"));
    Module::IHTTPHandle *unzipModule = dynamic_cast<Module::IHTTPHandle*>(m_core.Get("UnZip"));

    pl->pushAfter(std::bind(&Module::IHTTPHandle::Handle, zipModule, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), pl->begin());
    pl->pushBefore(std::bind(&Module::IHTTPHandle::Handle, unzipModule, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), pl->end());

    res->GetHeader().Add("Content-Type", "text/plain");
    res->SetBody("AddEvent");
    res->SetStatusCode(200);
    return true;
}

Module::IModule* AddEvent::GetModule(Module::ICore &core) const {
    return new AddEvent(core);
}

Module::IModule	*LoadModule(Module::ICore &core) {
    return new AddEvent(core);
}