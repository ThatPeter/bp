#include "../Headers/PlusModifier.h"
#include "../Headers/Utilities.h"

namespace FEI {
namespace Cryptosystem {

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
        /*if(eq_to_add < 1)
        {
            throw std::runtime_error("Plus modifier failed: the number of equations to add is too low!");
            return;
        }*/

        //appending new equations to the system
        std::vector<std::vector<int>> newEquations;
        size_t originalEquationsCount = mq.m_equationsCount;
        for (size_t i = 0; i < m_toAddCount; i++)
        {
            std::vector<int> eq = FEI::Utilities::UtilityModule::RandomVectorGenerator((mq.m_variablesCount * (mq.m_variablesCount + 1)) / 2 + mq.m_variablesCount + 1);
            newEquations.push_back(eq);
            mq.m_equations.push_back(eq);
        }

        mq.m_equationsCount = mq.m_equations.size();

        // adding the equations to the old ones
        {
            for (size_t i = 0; i < originalEquationsCount; i++)
            {
                for (auto& vec : newEquations)
                {
                    int constant = FEI::Utilities::UtilityModule::RandomIntGenerator(1);
                    if (constant)
                    {
                        mq.m_equations[i] = mq.m_equations[i] + vec;
                    }
                }
            }
        }
    }

} //!Cryptosystem
} //!FEI