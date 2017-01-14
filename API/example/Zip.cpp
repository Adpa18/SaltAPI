//
// Created by wery_a on 09/01/17.
//

#include "Zip.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"

Zip::Zip(Module::ICore &core): Module::AModule(core, HTTP, "Zip") {

}

Zip::~Zip() {

}

bool Zip::Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    return true;
}

Module::IModule* Zip::GetModule(Module::ICore &core) const {
    return new Zip(core);
}

Module::IModule	*LoadModule(Module::ICore &core) {
    return new Zip(core);
}