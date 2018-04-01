#pragma once

#include "Modifier.h"
#include <map>
#include <string>
#include <vector>

namespace FEI {
namespace CryptoSystem {

    class XorModifier : public IModifier
    {
    private:
        int m_linearEquationsCount;
        std::map<std::string, std::vector<int>> m_linearEquations;      //linear equations e.g. : z1, z2, .... , zn
        std::vector<std::vector<int>> m_polynomials;                    //quadratic equations - random linear combinations combined (e.g. z1 + z1z2 + z1z1 + z2z4 ...)
        std::map<std::string, std::vector<int>> m_linearCombinations;   //linear combinations of all z's (z1, z2, z1z1, z1z2, z2z2, z2z3, z2z4...)
    public:
        XorModifier(int linearEquations);
        ~XorModifier();
        virtual std::string GetName() const override;
        virtual void Modify(MQCryptoSystem& mq) override; 
        virtual void Save(std::string pathname = "XorModifier") override;

        /*
        * Unused in this version
        */
        virtual void Import(std::string pathname) override;
    };

} //!Cryptosystem
} //!FEI
