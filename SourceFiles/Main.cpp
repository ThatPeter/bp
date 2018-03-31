#include "../Headers/MQCryptoSystem.h"
#include "../Headers/PlusModifier.h"
#include "../Headers/MinusModifier.h"
#include "../Headers/XorModifier.h"

#include <iostream>

int main(int argc, char** argv)
{
    //FEI::Cryptosystem::MQCryptoSystem mq(30,2);
    
    //usage - cesta k suboru, modifikator, parameter, (optional)cesta k suboru na ukladanie

    if (argc < 3 || argc > 4)
    {
        std::cout << "Incorrect usage. In case of need, please use help";
        return 1;
    }

    std::string pathToFile = argv[1];
    std::string modifier = argv[2];
    std::string parameter = argv[3];
    std::string pathToSave = "";

    if(argc == 4) 
    {
        pathToSave = argv[4];
    }

    std::cout << pathToFile << std::endl;
    std::cout << modifier << std::endl;
    std::cout << parameter << std::endl;
    std::cout << pathToSave << std::endl;

    //pri minus modifikatore - pocet rovnic na odobranie
    //pri plus modifikatore - pocet rovnic na pridanie
    //pri xor modifikatore - pocet linearnych rovnic na skombinovanie
    //pri HFE --------------------------------------- ????????????


    /*
    try 
    {
       // mq.Import("ToyExample.txt");
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what();
    }
    /*
    std::shared_ptr<FEI::Cryptosystem::PlusModifier> plusmodifier = std::make_shared<FEI::Cryptosystem::PlusModifier>();
    std::shared_ptr<FEI::Cryptosystem::MinusModifier> minusmodifier = std::make_shared<FEI::Cryptosystem::MinusModifier>();
    std::shared_ptr<FEI::Cryptosystem::XorModifier> xormodifier = std::make_shared<FEI::Cryptosystem::XorModifier>();

    mq.Print();
    xormodifier->Modify(mq);
    mq.Print();
    mq.Save("nfyib.txt");
    */
    return 0;
}