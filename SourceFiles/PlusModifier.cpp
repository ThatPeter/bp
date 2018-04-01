#include "../Headers/PlusModifier.h"
#include "../Headers/Utilities.h"

#include <fstream>

namespace FEI {
namespace CryptoSystem {

    PlusModifier::PlusModifier(int toAddCount)
        : m_toAddCount(toAddCount)
    {

    }

    PlusModifier::~PlusModifier()
    {

    }

    std::string PlusModifier::GetName() const
    {
        return "Plus";
    }

    void PlusModifier::Modify(MQCryptoSystem& mq)
    {
        //appending new equations to the system
        size_t originalEquationsCount = mq.m_polynomialsCount;
        for (size_t i = 0; i < m_toAddCount; i++)
        {
            std::vector<int> eq = FEI::Modules::UtilityModule::RandomVectorGenerator((mq.m_variablesCount * (mq.m_variablesCount + 1)) / 2 + mq.m_variablesCount + 1);
            m_newPolynomials.push_back(eq);
            mq.m_polynomials.push_back(eq);
        }

        mq.m_polynomialsCount = mq.m_polynomials.size();

        for (size_t i = 0; i < originalEquationsCount; i++)
        {
            m_constants.push_back(std::vector<int>());
            for (auto& vec : m_newPolynomials)
            {
                int constant = FEI::Modules::UtilityModule::RandomIntGenerator(1);
                m_constants[i].push_back(constant);
                if (constant)
                {
                    mq.m_polynomials[i] = mq.m_polynomials[i] + vec;
                }
            }
        }
    }

    void PlusModifier::Save(std::string pathname)
    {
        std::ofstream file(pathname);

        /* name */
        file << GetName() << "\n";
        /* number of linear equations */
        file << "Number of polynomials added: " << m_toAddCount << "\n";

        /* equations added to the original ones */
        file << "New polynomials:\n";

        int counter = 0;

        for (auto vector : m_newPolynomials)
        {
            file << "[" << counter << "]" << " = [ ";
            for (auto num : vector)
            {
                file << num << " ";
            }
            file << "]\n";
            counter++;
        }

        /* constants */
        file << "Constants used:\n";

        counter = 0;

        for (auto vector : m_constants)
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

    void PlusModifier::Import(std::string pathname)
    {

    }

} //!Cryptosystem
} //!FEI