//
// Created by wery_a on 09/01/17.
//

#include "Compress.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"

Compress::Compress(Module::ICore &core): Module::AModule(core, HTTP, "Compress") {

}

Compress::~Compress() {

}

bool Compress::Zip(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    return true;
}

bool Compress::UnZip(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    return true;
}

Module::IModule* Compress::GetModule(Module::ICore &core) const {
    return new Compress(core);
}