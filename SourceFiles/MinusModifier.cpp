#include "../Headers/MinusModifier.h"
#include "../Headers/Utilities.h"

namespace FEI {
namespace Cryptosystem {

    std::string MinusModifier::GetName() const
    {
        return "Minus";
    }

    void MinusModifier::Modify(MQCryptoSystem& mq)
    {
        int n_eq_to_erase = 3;

        if (n_eq_to_erase >= mq.m_equationsCount || n_eq_to_erase < 1)
        {
            throw std::runtime_error("Minus modifier failed: the number of equations to erase is either too low or too high!");
        }

        for (size_t i = 0; i < n_eq_to_erase; i++)
        {
            mq.m_equations.erase(mq.m_equations.begin() + FEI::Utilities::UtilityModule::RandomIntGenerator(mq.m_equations.size() - 1));
        }

        mq.m_equationsCount -= 3;

        // mq.modifiers.push_back("minus");
    }

    std::shared_ptr<MinusModifier> MinusModifier::GetSharedPtr()
    {
        return shared_from_this();
    }

} //!Cryptosystem
} //!FEI