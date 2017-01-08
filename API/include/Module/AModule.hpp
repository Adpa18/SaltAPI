//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_AMODULE_HPP
#define API_V2_AMODULE_HPP

#include "IModule.hpp"

namespace Module {
    class ICore;

    class AModule : public IModule {
    public:
        AModule(ICore &core);

        virtual ~AModule();

    protected:
        ICore &m_core;
        std::string m_name;
        Type m_type;

    public:
        std::string const &GetName() const override;

        Type GetType() const override;

    public:
        bool Load() override;

        bool Unload() override;

    public:
        virtual IModule *GetModule(ICore &core) const override;
    };
}

#endif //API_V2_AMODULE_HPP
