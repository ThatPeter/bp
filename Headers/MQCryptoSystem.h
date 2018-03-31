#pragma once

#include <vector>
#include <string>
#include <list>
#include <memory>

namespace FEI {
namespace Cryptosystem {

    class IModifier;

    typedef std::vector<std::vector<int> > PublicKey;

    struct MQCryptoSystem
    {
        std::string m_galoisField;
        PublicKey m_equations;
        int m_seed;
        std::string m_order;
        std::list<std::shared_ptr<IModifier> > m_modifiers;
        int m_variablesCount;
        int m_equationsCount;

        MQCryptoSystem();

        /*
        * Generates an MQ Cryptosystem of GF(2), seed = 0, reverse lex order, "equations" number of polynomials and "variables" number of variables
        */
        MQCryptoSystem(int equations, int variables); 
        MQCryptoSystem(std::string galoisField, PublicKey equations, std::string order, int seed, int variablesCount, int equationsCount);
        ~MQCryptoSystem();

        virtual void Save(std::string pathname = "mq") const;
        virtual void Import(std::string pathname);
        virtual void Print() const;
    };

} // !Cryptosystem
} // !FEI
