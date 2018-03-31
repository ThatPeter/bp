#include "../Headers/XorModifier.h"
#include "../Headers/Utilities.h"

#include <map>
#include <vector>

namespace FEI {
namespace Cryptosystem {

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
  /*      if (no_linear_eq < 1) // pocet linearnych rovnic (z1 = x1 + x2 .., z2 = ..., ...) by mal byt aspon 1
        {
            throw std::runtime_error("Unable to use xor modifier. Raise the number of linear equations to combine (use 1 or more).");
        }
*/
        std::map<std::string, std::vector<int>> linearEquations; //linearne rovnice z
        for (size_t i = 0; i < m_linearEquationsCount; i++) //instancie linearnych rovnic o no_variables neznamych
        {
            linearEquations["z" + std::to_string(i + 1)] = FEI::Utilities::UtilityModule::RandomVectorGenerator(mq.m_variablesCount + 1);
        }

        std::map<std::string, std::vector<int>> linearCombinations;
        int counter = 0;
        for (auto it = linearEquations.begin(); it != linearEquations.end(); it++) //z1 z2 z3
        {
            for (auto it2 = it; it2 != linearEquations.end(); it2++) // z1 z2 z3...
            {
                linearCombinations[(it->first + it2->first)] = FEI::Utilities::UtilityModule::GetLinearCombination(it->second, it2->second); //add z1z1 z1z2 z2z2 ...
            }
        }

        for (auto it = linearEquations.begin(); it != linearEquations.end(); it++) //add z1 z2 z3
        {
            std::vector<int> toAdd;
            for (size_t i = 0, j = 0; i < mq.m_equations[0].size(); i++)
            {
                if (i < mq.m_equations[0].size() - it->second.size())
                {
                    toAdd.push_back(0);
                }
                else
                {
                    toAdd.push_back(it->second[j]);
                    j++;
                }
            }
            linearCombinations[it->first] = toAdd;
        }

        std::vector<std::vector<int>> quadraticEquations;
        for (size_t i = 0; i < mq.m_equationsCount; i++)
        {
            quadraticEquations.push_back(FEI::Utilities::UtilityModule::RandomQuadraticTermGenerator(linearCombinations)); // push back the newly created quadratic eq's
        }

        // add the newly generated eq's to the old ones
        for (size_t i = 0; i < mq.m_equations.size(); i++)
        {
            mq.m_equations[i] = mq.m_equations[i] + quadraticEquations[i];
        }

        // MQSystem.modifiers.push_back("xor");
    }

} //!Cryptosystem
} //!FEI