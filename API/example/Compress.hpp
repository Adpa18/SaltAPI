//
// Created by wery_a on 09/01/17.
//

#ifndef API_V2_COMPRESS_HPP
#define API_V2_COMPRESS_HPP

#include "Module/IHTTPHandle.hpp"
#include "Module/AModule.hpp"
#include "DllExport.hpp"

extern "C"
{
class EXPORT Compress : public Module::AModule {
public :
    Compress(Module::ICore &core);

    virtual ~Compress();

public :
    bool Zip(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl);
    bool UnZip(HTTP::Request *req, HTTP::Response *res, HTTP::ProcessingList *pl);

public :
    Module::IModule *GetModule(Module::ICore &core) const override;
};
}

#endif //API_V2_COMPRESS_HPP
