#pragma once

#include <string>
#include "MQCryptoSystem.h"

namespace FEI {
namespace Cryptosystem {

    class IModifier
    {
    public:
        virtual std::string GetName() const = 0;
        virtual void Modify(MQCryptoSystem& mq) = 0;
    };

} //!Cryptosystem
} //!FEI