#include "../Headers/MQCryptosystem.h"
#include "../Headers/Utilities.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

namespace FEI {
namespace Cryptosystem {

    MQCryptoSystem::MQCryptoSystem(std::string galoisField, PublicKey equations, std::string order, int seed, int variablesCount, int equationsCount)
        : m_galoisField(galoisField)
        , m_equations(equations)
        , m_order(order)
        , m_seed(seed)
        , m_equationsCount(equationsCount)
        , m_variablesCount(variablesCount)
    {

    }

    MQCryptoSystem::MQCryptoSystem(int equations, int variables)
        : m_equationsCount(equations)
        , m_variablesCount(variables)
        , m_order("Order : graded reverse lex order")
        , m_seed(0)
        , m_galoisField("Galois Field : GF(2)")
    {
        for (size_t i = 0; i < equations; i++)
        {
            m_equations.push_back(FEI::Utilities::UtilityModule::RandomVectorGenerator((variables * (variables + 1) / 2) + variables + 1));
        }
    }

    MQCryptoSystem::MQCryptoSystem()
    {

    }

    MQCryptoSystem::~MQCryptoSystem()
    {

    }

    void MQCryptoSystem::Save(std::string pathname) const
    {
        std::ofstream file(pathname);

        file << m_galoisField << "\n";
        file << "Number of variables (n) : " << m_variablesCount << "\n";
        file << "Number of polynomials (m) : " << m_equationsCount << "\n";
        file << "Seed : " << m_seed << "\n";
        file << m_order << "\n";
        file << "\n*********************\n";

        int counter = 0;
        for (auto vector : m_equations)
        {
            for (auto num : vector)
            {
                file << num << " ";
            }
            file << ";";
            if (counter != m_equations.size() - 1)
            {
                file << std::endl;
            }
        }
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
        m_equationsCount = std::stoi(std::regex_replace(line, std::regex(R"([\D])"), ""));

        std::getline(inputFile, line);          //seed
        m_seed = std::stoi(std::regex_replace(line, std::regex(R"([\D])"), ""));

        std::getline(inputFile, m_order);       //order

        std::getline(inputFile, line);          //empty
        std::getline(inputFile, line);          //dots

        std::vector<int> values;
    
        int counter = 0;
                                                
        while (std::getline(inputFile, line))   //equations
        {
            m_equations.push_back(std::vector<int>());
            std::stringstream stream(line);

            int n;
            while (stream >> n)
            {
                m_equations[counter].push_back(n);
            }
            counter++;
        }
    }


    void MQCryptoSystem::Print() const
    {
        std::cout << m_galoisField << "\n";
        std::cout << "Number of variables (n) : " << m_variablesCount << "\n";
        std::cout << "Number of polynomials (m) : " << m_equationsCount << "\n";
        std::cout << "Seed : " << m_seed << "\n";
        std::cout << m_order << "\n";
        std::cout << "\n*********************\n";

        for (auto vector : m_equations)
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