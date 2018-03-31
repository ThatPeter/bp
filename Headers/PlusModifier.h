#pragma once

#include "Modifier.h"

namespace FEI {
namespace Cryptosystem {

    class PlusModifier : public IModifier, std::enable_shared_from_this<PlusModifier>
    {
    private:
        int m_toAddCount;
    public:
        PlusModifier(int toAdd);
        ~PlusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual std::shared_ptr<PlusModifier> GetSharedPtr();
    };

} //!Cryptosystem
} //!FEI
