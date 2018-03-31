#include "../Headers/MinusModifier.h"
#include "../Headers/Utilities.h"

namespace FEI {
namespace Cryptosystem {

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
     /*   if (n_eq_to_erase >= mq.m_equationsCount || n_eq_to_erase < 1)
        {
            throw std::runtime_error("Minus modifier failed: the number of equations to erase is either too low or too high!");
        }*/

        for (size_t i = 0; i < m_toRemoveCount; i++)
        {
            mq.m_equations.erase(mq.m_equations.begin() + FEI::Utilities::UtilityModule::RandomIntGenerator(mq.m_equations.size() - 1));
        }

        mq.m_equationsCount -= 3;
    }

    std::shared_ptr<MinusModifier> MinusModifier::GetSharedPtr()
    {
        return shared_from_this();
    }

} //!Cryptosystem
} //!FEI