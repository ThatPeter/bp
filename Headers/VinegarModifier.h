#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class VinegarModifier : public IModifier, std::enable_shared_from_this<IModifier>
    {
    public:
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual std::shared_ptr<IModifier> GetSharedPtr();
    };

} //!Cryptosystem
} //!FEI