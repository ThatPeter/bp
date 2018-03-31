#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class XorModifier : public IModifier, std::enable_shared_from_this<XorModifier>
    {
    public:
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual std::shared_ptr<XorModifier> GetSharedPtr();
    };

} //!Cryptosystem
} //!FEI
