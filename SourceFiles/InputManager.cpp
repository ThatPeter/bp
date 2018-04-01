#include "../Headers/InputManager.h"
#include "../Headers/MQCryptoSystem.h"
#include "../Headers/MinusModifier.h"
#include "../Headers/PlusModifier.h"
#include "../Headers/XorModifier.h"

#include <iostream>
#include <map>

namespace FEI {
namespace Modules {

    //argc = input.size()
    void InputManager::Manage(std::vector<std::string> input)
    {
        //in case we want to generate a random cryptosystem
        if (input[1] == "random")
        {
            int polynomials = std::stoi(input[2]);
            int variables = std::stoi(input[3]);

            if (polynomials < 1)
            {
                throw std::runtime_error("Cant create an MQ cryptosystem with " + input[2] + " polynomials.");
            }

            if (variables < 1)
            {
                throw std::runtime_error("Cant create an MQ cryptosystem with " + input[3] + " variables.");
            }

            FEI::CryptoSystem::MQCryptoSystem mq(polynomials, variables);
            if (input.size() == 5)
            {
                mq.Save(input[4]); //saving with the given path and name
            }
            else
            {
                mq.Save(); //default saving to the exe directory
            }
            return;
        }

        FEI::CryptoSystem::MQCryptoSystem mq;

        try 
        {
            mq.Import(input[1]);
        }
        catch (std::runtime_error& e)
        {
            throw;
        }

        std::map<std::string, std::string> modifiers;
        modifiers["plus"] = "plus";
        modifiers["minus"] = "minus";
        modifiers["xor"] = "xor";

        if (modifiers.find(input[2]) == modifiers.end())
        {
            throw std::runtime_error("Invalid modifier.");
        }

        if (input[2] == "plus")
        {
            int toAdd = std::stoi(input[3]);

            if (toAdd < 1)
            {
                throw std::runtime_error("Invalid modifier parameter: " + input[3] + ". Number of polynomials to add must be greater than 1.");
            }

            FEI::CryptoSystem::PlusModifier modifier(toAdd);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input[2] == "minus")
        {
            int toRemove = std::stoi(input[3]);

            if (toRemove < 1 || toRemove >= mq.m_polynomials.size())
            {
                throw std::runtime_error("Invalid modifier parameter: " + input[3] + ". Number of polynomials to remove must be in the interval <1, polynomials - 1>.");
            }

            FEI::CryptoSystem::MinusModifier modifier(toRemove);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input[2] == "xor")
        {
            int linearEquations = std::stoi(input[3]);

            if (linearEquations < 1)
            {
                throw std::runtime_error("Invalid modifier parameter: " + input[3] + ". Number of linear equations must be greater than 1.");
            }

            FEI::CryptoSystem::XorModifier modifier(linearEquations);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input.size() == 5)
        {
            mq.Save(input[4]);
        }
        else
        {
            mq.Save();
        }
    }
   
} //!Modules
} //!FEI