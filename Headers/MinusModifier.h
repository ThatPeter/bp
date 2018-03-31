#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class MinusModifier : public IModifier, std::enable_shared_from_this<MinusModifier>
    {
    private:
        int m_toRemoveCount;
    public:
        MinusModifier(int toRemove);
        ~MinusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual std::shared_ptr<MinusModifier> GetSharedPtr();
    };

} //!Cryptosystem
} //!FEI
