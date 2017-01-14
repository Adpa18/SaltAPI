//
// Created by wery_a on 09/01/17.
//

#include "HelloWorld.hpp"
#include "HTTP/Request.hpp"
#include "HTTP/Response.hpp"
#include "HTTP/ProcessingList.hpp"

HelloWorld::HelloWorld(Module::ICore &core): Module::AModule(core, HTTP, "HelloWorld") {

}

HelloWorld::~HelloWorld() {

}

bool HelloWorld::Handle(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl) {
    res->GetHeader().Add("Content-Type", "text/plain");
    res->SetBody("HelloWorld");
    res->SetStatusCode(200);
    return true;
}

Module::IModule* HelloWorld::GetModule(Module::ICore &core) const {
    return new HelloWorld(core);
}

Module::IModule	*CreateModule(Module::ICore &core) {
	return new HelloWorld(core);
}
