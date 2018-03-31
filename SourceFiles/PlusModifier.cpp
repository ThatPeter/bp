#include "../Headers/PlusModifier.h"
#include "../Headers/Utilities.h"

namespace FEI {
namespace Cryptosystem {

    std::string PlusModifier::GetName() const
    {
        return "Plus";
    }

    void PlusModifier::Modify(MQCryptoSystem& mq)
    {
        int eq_to_add = 5;
        if(eq_to_add < 1)
        {
            throw std::runtime_error("Plus modifier failed: the number of equations to add is too low!");
            return;
        }

        //appending new equations to the system
        std::vector<std::vector<int>> newEquations;
        size_t original_num_eq = mq.m_equationsCount;
        for (size_t i = 0; i < eq_to_add; i++)
        {
            std::vector<int> eq = FEI::Utilities::UtilityModule::RandomVectorGenerator((mq.m_variablesCount * (mq.m_variablesCount + 1)) / 2 + mq.m_variablesCount + 1);
            newEquations.push_back(eq);
            mq.m_equations.push_back(eq);
        }

        mq.m_equationsCount = mq.m_equations.size();

        // adding the equations to the old ones
        {
            for (size_t i = 0; i < original_num_eq; i++)
            {
                for (auto& vec : newEquations)
                {
                    int constant = FEI::Utilities::UtilityModule::RandomIntGenerator(1);
                    if (constant)
                    {
                        for (size_t j = 0; j < vec.size(); j++)
                        {
                            mq.m_equations[i][j] = (mq.m_equations[i][j] + vec[j]) % 2;
                        }
                    }
                }
            }
        }

       // mq.m_modifiers.push_back(GetSharedPtr());
    }

    std::shared_ptr<PlusModifier> PlusModifier::GetSharedPtr()
    {
        return shared_from_this();
    }
    
} //!Cryptosystem
} //!FEI