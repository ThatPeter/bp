#include "../Headers/InputManager.h"
#include "../Headers/MQCryptoSystem.h"
#include "../Headers/MinusModifier.h"
#include "../Headers/PlusModifier.h"
#include "../Headers/XorModifier.h"

#include <iostream>
#include <map>
#include <set>

namespace FEI {
namespace Modules {

    void InputManager::DisplayHelp()
    {
        std::cout << "Usage: ./exename\n\nIn case random MQ public key generation use:\n\t-r this option must be accompanied by:\n\t-v [number of variables]\n\t-e [number of polynomials]\n\nIn case of applying modifiers use:\n\t-f [path to file to load]\n\t-m [modifier name]\n\t-p [modifier parameter]\n\n\t-s [save file to path] (OPTIONAL)\n";
    }

    void InputManager::Manage(std::map<std::string, std::string> input)
    {
        std::set<std::string> switches;
        switches.insert("-f");
        switches.insert("-r");
        switches.insert("-v");
        switches.insert("-e");
        switches.insert("-m");
        switches.insert("-p");
        switches.insert("-s");
        switches.insert("-h");

        if (input.size() <= 0)
        {
            throw std::runtime_error("Invalid usage. Use -h for help.");
        }

        std::map<std::string, std::string>::const_iterator inputEnd = input.end();

        if (input.find("-h") != inputEnd || input.find("--help") != inputEnd)
        {
            if (input.size() == 1)
            {
                DisplayHelp();
                return;
            }
            else
            {
                throw std::runtime_error("Invalid usage. Use -h for help.");
            }
        }

        if (input.find("-r") != inputEnd) // -r
        {
            if (input.find("-v") != inputEnd && input.find("-e") != inputEnd) // -e -v
            {
                int polynomials;
                int variables;

                try 
                {
                    polynomials = std::stoi(input.at("-e"));
                    variables = std::stoi(input.at("-v"));
                }
                catch (...)
                {
                    throw std::runtime_error("Invalid usage. Use -h for help.");
                }

                if (polynomials < 1)
                {
                    throw std::runtime_error("Cant create an MQ cryptosystem with " + std::to_string(polynomials) + " polynomials.");
                }

                if (variables < 1)
                {
                    throw std::runtime_error("Cant create an MQ cryptosystem with " + std::to_string(variables) + " variables.");
                }

                FEI::CryptoSystem::MQCryptoSystem mq(polynomials, variables);

                if (input.find("-s") != inputEnd && input.size() == 4) // if -s is defined
                {
                    try 
                    {
                        mq.Save(input.at("-s"));
                    }
                    catch (...)
                    {
                        throw std::runtime_error("Invalid usage. Use -h for help");
                    }
                    return;
                }

                if (input.find("-s") == inputEnd && input.size() == 3) // if -s is not defined
                {
                    mq.Save();
                    return;
                }

                throw std::runtime_error("Invalid usage. Use -h for help");
            }
        }
        
        
        FEI::CryptoSystem::MQCryptoSystem mq;

        if (input.find("-f") == inputEnd || input.find("-m") == inputEnd || input.find("-p") == inputEnd)
        {
            throw std::runtime_error("Invalid usage. Use -h for help.");
        }

        if (input.find("-s") == inputEnd && input.size() != 3)
        {
            throw std::runtime_error("Invalid usage. Use -h for help.");
        }

        if (input.find("-s") != inputEnd && input.size() != 4)
        {
            throw std::runtime_error("Invalid usage. Use -h for help.");
        }

        try 
        {
            mq.Import(input.at("-f"));
        }
        catch (std::runtime_error& e)
        {
            throw;
        }
        catch (...)
        {
            throw std::runtime_error("Invalid usage. Use -h for help");
        }


        std::set<std::string> modifiers;
        modifiers.insert("plus");
        modifiers.insert("minus");
        modifiers.insert("xor");

        if (modifiers.find(input.at("-m")) == modifiers.end())
        {
            throw std::runtime_error("Invalid modifier.");
        }

        if (input.at("-m") == "plus")
        {
            int toAdd = std::stoi(input.at("-p"));

            if (toAdd < 1)
            {
                throw std::runtime_error("Invalid modifier parameter: " + input.at("-p") + ". Number of polynomials to add must be greater than 1.");
            }

            FEI::CryptoSystem::PlusModifier modifier(toAdd);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input.at("-m") == "minus")
        {
            int toRemove = std::stoi(input.at("-p"));

            if (toRemove < 1 || toRemove >= mq.m_polynomials.size())
            {
                throw std::runtime_error("Invalid modifier parameter: " + input.at("-p") + ". Number of polynomials to remove must be in the interval <1, polynomials - 1>.");
            }

            FEI::CryptoSystem::MinusModifier modifier(toRemove);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input.at("-m") == "xor" || input.at("-m") == "i")
        {
            int linearEquations = std::stoi(input.at("-p"));

            if (linearEquations < 1)
            {
                throw std::runtime_error("Invalid modifier parameter: " + input.at("-p") + ". Number of linear equations must be greater than 1.");
            }

            FEI::CryptoSystem::XorModifier modifier(linearEquations);
            modifier.Modify(mq);
            modifier.Save();
        }

        if (input.find("-s") != inputEnd)
        {
            mq.Save(input.at("-s"));
        }
        else
        {
            mq.Save();
        }
    }
   
} //!Modules
} //!FEI