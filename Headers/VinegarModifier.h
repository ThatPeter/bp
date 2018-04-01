#pragma once

#include "Modifier.h"

namespace FEI {
namespace CryptoSystem {

    class VinegarModifier : public IModifier
    {
    public:
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual void Save(std::string pathname = "VinegarModifier") override;

        /*
        * Unused in this version
        */
        virtual void Import(std::string pathname) override;
    };

} //!Cryptosystem
} //!FEI
