#include "../Headers/XorModifier.h"
#include "../Headers/Utilities.h"

#include <map>
#include <vector>
#include <fstream>

namespace FEI {
namespace CryptoSystem {

    XorModifier::XorModifier(int linearEquationsCount)
        : m_linearEquationsCount(linearEquationsCount)
    {

    }

    XorModifier::~XorModifier()
    {

    }

    std::string XorModifier::GetName() const
    {
        return "Xor";
    }

    void XorModifier::Modify(MQCryptoSystem& mq)
    {
        for (size_t i = 0; i < m_linearEquationsCount; i++) //instancie linearnych rovnic o no_variables neznamych
        {
            m_linearEquations["z" + std::to_string(i + 1)] = FEI::Modules::UtilityModule::RandomVectorGenerator(mq.m_variablesCount + 1);
        }

        int counter = 0;
        for (auto it = m_linearEquations.begin(); it != m_linearEquations.end(); it++) //z1 z2 z3
        {
            for (auto it2 = it; it2 != m_linearEquations.end(); it2++) // z1 z2 z3...
            {
                m_linearCombinations[(it->first + it2->first)] = FEI::Modules::UtilityModule::GetLinearCombination(it->second, it2->second); //add z1z1 z1z2 z2z2 ...
            }
        }

        for (auto it = m_linearEquations.begin(); it != m_linearEquations.end(); it++) //add z1 z2 z3
        {
            std::vector<int> toAdd;
            for (size_t i = 0, j = 0; i < mq.m_polynomials[0].size(); i++)
            {
                if (i < mq.m_polynomials[0].size() - it->second.size())
                {
                    toAdd.push_back(0);
                }
                else
                {
                    toAdd.push_back(it->second[j]);
                    j++;
                }
            }
            m_linearCombinations[it->first] = toAdd;
        }

        for (size_t i = 0; i < mq.m_polynomialsCount; i++)
        {
            m_polynomials.push_back(FEI::Modules::UtilityModule::RandomQuadraticTermGenerator(m_linearCombinations)); // push back the newly created quadratic eq's
        }

        // add the newly generated eq's to the old ones
        for (size_t i = 0; i < mq.m_polynomials.size(); i++)
        {
            mq.m_polynomials[i] = mq.m_polynomials[i] + m_polynomials[i];
        }

        // MQSystem.modifiers.push_back("xor");
    }

    void XorModifier::Save(std::string pathname)
    {
        std::ofstream file(pathname);

        /* name */
        file << GetName() << "\n";
        /* number of linear equations */
        file << "Number of linear equations used: " << m_linearEquationsCount << "\n";

        /* concrete linear combinations */
        file << "Linear equations:\n";
        for (auto keys : m_linearCombinations)
        {
            file << keys.first << " = [ ";
            for (auto num : keys.second)
            {
                file << num << " ";
            }
            file << "]\n";
        }

        /* equations added to the original ones */
        file << "Polynomials used:\n";

        int counter = 0;

        for (auto vector : m_polynomials)
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

    void XorModifier::Import(std::string pathname)
    {

    }

} //!Cryptosystem
} //!FEI