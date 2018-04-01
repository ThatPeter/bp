#include "../Headers/MQCryptoSystem.h"
#include "../Headers/Utilities.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

namespace FEI {
namespace CryptoSystem {

    MQCryptoSystem::MQCryptoSystem(std::string galoisField, PublicKey equations, std::string order, int seed, int variablesCount, int polynomialsCount)
        : m_galoisField(galoisField)
        , m_polynomials(equations)
        , m_order(order)
        , m_seed(seed)
        , m_polynomialsCount(polynomialsCount)
        , m_variablesCount(variablesCount)
    {

    }

    MQCryptoSystem::MQCryptoSystem(int equations, int variables)
        : m_polynomialsCount(equations)
        , m_variablesCount(variables)
        , m_order("Order : graded reverse lex order")
        , m_seed(0)
        , m_galoisField("Galois Field : GF(2)")
    {
        for (size_t i = 0; i < equations; i++)
        {
            m_polynomials.push_back(FEI::Modules::UtilityModule::RandomVectorGenerator((variables * (variables + 1) / 2) + variables + 1));
        }
    }

    MQCryptoSystem::MQCryptoSystem()
    {

    }

    MQCryptoSystem::~MQCryptoSystem()
    {

    }

    void MQCryptoSystem::Save(std::string pathname)
    {
        std::ofstream file(pathname);

        file << m_galoisField << "\n";
        file << "Number of variables (n) : " << m_variablesCount << "\n";
        file << "Number of polynomials (m) : " << m_polynomialsCount << "\n";
        file << "Seed : " << m_seed << "\n";
        file << m_order << "\n";
        file << "\n*********************\n";

        int counter = 0;
        for (auto vector : m_polynomials)
        {
            for (auto num : vector)
            {
                file << num << " ";
            }
            file << ";";
            if (counter < m_polynomials.size() - 1)
            {
                file << std::endl;
            }
            counter++;
        }

        file.close();
    }

    void MQCryptoSystem::Import(std::string pathname)
    {
        std::ifstream inputFile(pathname); 

        if (!inputFile.is_open()) 
        {
            throw std::runtime_error("Failed to open file");
        }
        
        std::string line;

        std::getline(inputFile, m_galoisField); //GF

        std::getline(inputFile, line);          //n
        m_variablesCount = std::stoi(std::regex_replace(line, std::regex(R"([\D])"), ""));
        
        std::getline(inputFile, line);          //m
        m_polynomialsCount = std::stoi(std::regex_replace(line, std::regex(R"([\D])"), ""));

        std::getline(inputFile, line);          //seed
        m_seed = std::stoi(std::regex_replace(line, std::regex(R"([\D])"), ""));

        std::getline(inputFile, m_order);       //order

        std::getline(inputFile, line);          //empty
        std::getline(inputFile, line);          //dots

        std::vector<int> values;
    
        int counter = 0;
                                                
        while (std::getline(inputFile, line))   //equations
        {
            m_polynomials.push_back(std::vector<int>());
            std::stringstream stream(line);

            int n;
            while (stream >> n)
            {
                m_polynomials[counter].push_back(n);
            }
            counter++;
        }

        inputFile.close();
    }


    void MQCryptoSystem::Print() const
    {
        std::cout << m_galoisField << "\n";
        std::cout << "Number of variables (n) : " << m_variablesCount << "\n";
        std::cout << "Number of polynomials (m) : " << m_polynomialsCount << "\n";
        std::cout << "Seed : " << m_seed << "\n";
        std::cout << m_order << "\n";
        std::cout << "\n*********************\n";

        for (auto vector : m_polynomials)
        {
            for (auto num : vector)
            {
                std::cout << num << " ";
            }
            std::cout << ";" << std::endl;
        }
    }

} // !Cryptosystem
} // !FEI