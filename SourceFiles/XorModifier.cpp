#include "../Headers/XorModifier.h"
#include "../Headers/Utilities.h"

#include <map>
#include <vector>

namespace FEI {
namespace Cryptosystem {

    std::string XorModifier::GetName() const
    {
        return "Xor";
    }

    void XorModifier::Modify(MQCryptoSystem& mq)
    {
        int no_linear_eq = 3;

        if (no_linear_eq < 1) // pocet linearnych rovnic (z1 = x1 + x2 .., z2 = ..., ...) by mal byt aspon 1
        {
            throw std::runtime_error("Unable to use xor modifier. Raise the number of linear equations to combine (use 1 or more).");
        }

        std::map<std::string, std::vector<int>> linear_equations; //linearne rovnice z
        for (size_t i = 0; i < no_linear_eq; i++) //instancie linearnych rovnic o no_variables neznamych
        {
            linear_equations["z" + std::to_string(i + 1)] = FEI::Utilities::UtilityModule::RandomVectorGenerator(mq.m_variablesCount + 1);
        }

        std::map<std::string, std::vector<int>> linear_combinations;
        int counter = 0;
        for (auto it = linear_equations.begin(); it != linear_equations.end(); it++) //z1 z2 z3
        {
            for (auto it2 = it; it2 != linear_equations.end(); it2++) // z1 z2 z3...
            {
                linear_combinations[(it->first + it2->first)] = FEI::Utilities::UtilityModule::GetLinearCombination(it->second, it2->second); //add z1z1 z1z2 z2z2 ...
            }
        }

        for (auto it = linear_equations.begin(); it != linear_equations.end(); it++) //add z1 z2 z3
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
            linear_combinations[it->first] = toAdd;
        }

        std::vector<std::vector<int>> quadratic_equations;
        for (size_t i = 0; i < mq.m_equationsCount; i++)
        {
            quadratic_equations.push_back(FEI::Utilities::UtilityModule::RandomQuadraticTermGenerator(linear_combinations)); // push back the newly created quadratic eq's
        }

        // add the newly generated eq's to the old ones
        for (size_t i = 0; i < mq.m_equations.size(); i++)
        {
            mq.m_equations[i] = mq.m_equations[i] + quadratic_equations[i];
        }

        // MQSystem.modifiers.push_back("xor");
    }

    std::shared_ptr<XorModifier> XorModifier::GetSharedPtr()
    {
        return shared_from_this();
    }

} //!Cryptosystem
} //!FEI