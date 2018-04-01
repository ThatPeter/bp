#include "../Headers/MinusModifier.h"
#include "../Headers/Utilities.h"

#include <fstream>

namespace FEI {
namespace CryptoSystem {

    MinusModifier::MinusModifier(int toRemoveCount)
        : m_toRemoveCount(toRemoveCount)
    {

    }


    MinusModifier::~MinusModifier()
    {

    }

    std::string MinusModifier::GetName() const
    {
        return "Minus";
    }

    void MinusModifier::Modify(MQCryptoSystem& mq)
    {
        for (size_t i = 0; i < m_toRemoveCount; i++)
        {
            int toErase = FEI::Modules::UtilityModule::RandomIntGenerator(mq.m_polynomials.size() - 1);
            m_removedPolynomials.push_back(*(mq.m_polynomials.begin() + toErase));
            mq.m_polynomials.erase(mq.m_polynomials.begin() + toErase);
        }

        mq.m_polynomialsCount = mq.m_polynomials.size();
    }

    void MinusModifier::Save(std::string pathname)
    {
        std::ofstream file(pathname);

        /* name */
        file << GetName() << "\n";
        /* number of linear equations */
        file << "Number of polynomials removed: " << m_toRemoveCount << "\n";

        /* equations added to the original ones */
        file << "Removed polynomials:\n";

        int counter = 0;

        for (auto vector : m_removedPolynomials)
        {
            file << "[" << counter << "]" << " = [ ";
            for (auto num : vector)
            {
                file << num << " ";
            }
            file << "]\n";
            counter++;
        }

        file.close();
    }

    void MinusModifier::Import(std::string pathname)
    {

    }

} //!Cryptosystem
} //!FEI