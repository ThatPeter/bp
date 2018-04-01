#pragma once

#include "IOService.h"
#include <string>
#include "MQCryptoSystem.h"

namespace FEI {
namespace CryptoSystem {

    class IModifier : public FEI::Modules::IOService
    {
    public:
        virtual std::string GetName() const = 0;
        virtual void Modify(MQCryptoSystem& mq) = 0;
    };

} //!Cryptosystem
} //!FEI