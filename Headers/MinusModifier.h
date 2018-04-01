#pragma once

#include "Modifier.h"
#include <vector>
#include <string>

namespace FEI {
namespace CryptoSystem {

    class MinusModifier : public IModifier
    {
    private:
        int m_toRemoveCount;
        std::vector<std::vector<int>> m_removedPolynomials;
    public:
        MinusModifier(int toRemove);
        ~MinusModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override; 
        virtual void Save(std::string pathname = "MinusModifier") override;

        /*
        * Unused in this version
        */
        virtual void Import(std::string pathname) override;
    };

} //!Cryptosystem
} //!FEI
