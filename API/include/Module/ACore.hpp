//
// Created by wery_a on 07/01/17.
//

#ifndef API_V2_ACORE_HPP
#define API_V2_ACORE_HPP

#include "AModule.hpp"
#include "ICore.hpp"
#include "IModuleLoader.hpp"

namespace Module {
    class IConfigLoader;

    class ILogging;

    class INetwork;

    class IFileServe;

    class ACore : public ICore, public AModule {
    public:
        ACore(ICore &core);

        virtual ~ACore();

    protected:
        IModuleLoader *m_moduleLoader = nullptr;
        IConfigLoader *m_configLoader = nullptr;
        ILogging *m_logging = nullptr;
        INetwork *m_network = nullptr;
        IFileServe *m_fileServe = nullptr;

        IConfig *m_config = nullptr;
    protected:


    public:
        bool Run(std::vector<std::string> const &opts, IModuleLoader *moduleLoader) override;

        IConfig const &GetConfig() const override;

    public:
        IModule *Get(std::string const &name) const override;

        IModule *Get(IModule::Type) const override;

        template<class T>
        T *Get() const override {
            return m_moduleLoader->Get<T>();
        }

    public:
        virtual IModule *GetModule(ICore &core) const override;
    };
}
#endif //API_V2_ACORE_HPP
