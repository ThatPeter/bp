#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class MinusModifier : public IModifier
    {
    private:
        int m_toRemoveCount;
    public:
        MinusModifier(int toRemove);
        ~MinusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
    };

} //!Cryptosystem
} //!FEI
