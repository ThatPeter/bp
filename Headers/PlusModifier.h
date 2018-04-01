#pragma once

#include "Modifier.h"
#include <string>
#include <vector>

namespace FEI {
namespace CryptoSystem {

    class PlusModifier : public IModifier
    {
    private:
        int m_toAddCount;
        std::vector<std::vector<int>> m_newPolynomials;
        std::vector<std::vector<int>> m_constants;
    public:
        PlusModifier(int toAdd);
        ~PlusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override;
        virtual void Save(std::string pathname = "PlusModifier") override;

        /*
        * Unused in this version
        */
        virtual void Import(std::string pathname) override;
    };

} //!Cryptosystem
} //!FEI
