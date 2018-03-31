#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class VinegarModifier : public IModifier
    {
    public:
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
    };

} //!Cryptosystem
} //!FEI
