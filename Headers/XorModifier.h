#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class XorModifier : public IModifier
    {
    private:
        int m_linearEquationsCount;
    public:
        XorModifier(int linearEquations);
        ~XorModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
    };

} //!Cryptosystem
} //!FEI
