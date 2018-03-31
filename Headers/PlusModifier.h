#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class PlusModifier : public IModifier
    {
    private:
        int m_toAddCount;
    public:
        PlusModifier(int toAdd);
        ~PlusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
    };

} //!Cryptosystem
} //!FEI
