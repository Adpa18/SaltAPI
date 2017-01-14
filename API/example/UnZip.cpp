//
// Created by wery_a on 09/01/17.
//

#include "UnZip.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"

UnZip::UnZip(Module::ICore &core): Module::AModule(core, HTTP, "UnZip") {

}

UnZip::~UnZip() {

}

bool UnZip::Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    return true;
}

Module::IModule* UnZip::GetModule(Module::ICore &core) const {
    return new UnZip(core);
}

Module::IModule	*LoadModule(Module::ICore &core) {
    return new UnZip(core);
}