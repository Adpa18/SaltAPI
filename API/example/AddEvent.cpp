//
// Created by wery_a on 09/01/17.
//

#include <functional>
#include "AddEvent.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"
#include "Module/ACore.hpp"
#include "Compress.hpp"

AddEvent::AddEvent(Module::ICore &core): Module::AModule(core, HTTP, "AddEvent") {

}

AddEvent::~AddEvent() {

}

bool AddEvent::Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    Compress *compressModule = dynamic_cast<Compress*>(m_core.Get("Compress"));

    pl->pushAfter(std::bind(&Compress::UnZip, compressModule, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                  pl->begin());
    pl->pushBefore(std::bind(&Compress::Zip, compressModule, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), pl->end());

    res->GetHeader().Add("Content-Type", "text/plain");
    res->SetBody("AddEvent");
    res->SetStatusCode(200);
    return true;
}

Module::IModule* AddEvent::GetModule(Module::ICore &core) const {
    return new AddEvent(core);
}