#include "../Headers/MQCryptoSystem.h"
#include "../Headers/PlusModifier.h"
#include "../Headers/MinusModifier.h"
#include "../Headers/XorModifier.h"

#include <iostream>
#include <string>

int main(/*int argc, char** argv*/)
{
    //FEI::Cryptosystem::MQCryptoSystem mq(30,2);
    
    //usage - cesta k suboru, modifikator, parameter, (optional)cesta k suboru na ukladanie

    int argc = 4;
    
    std::vector<std::string> argv;

    argv.push_back("");

    argv.push_back("random");

    argv.push_back("5");

    argv.push_back("5");

    if (argc == 2)
    {
	    std::string input(argv[1]);

	    if (input == "help")
	    {
	        std::cout << "Usage: ./Name [path to file] [modifier name] [modifier parameter] [(optional) path to save the file to (default = \"mq\")]\n";
            std::cout << "or ./Name random [number of polynomials] [number of variables] [(optional) path to save the file to (default = \"mq\")] to generate an MQ cryptosystem with random equations\n";
            return 0;
	    }
    }

    if (argc < 4 || argc > 5)
    {
        std::cout << "Incorrect usage. In case of need, please use \"help\"!\n";
        return 1;
    }

    std::vector<std::string> strings;
    for(int i = 0; i < argc; i++) 
    {
	    strings.push_back(argv[i]);
    }

    if (strings[1] == "random")
    {
        FEI::Cryptosystem::MQCryptoSystem mq(std::stoi(strings[2]), std::stoi(strings[3]));
        if (argc == 5)
        {
            mq.Save(strings[4]);
        }
        else
        {
            mq.Save();
        }
        return 0;
    }

    FEI::Cryptosystem::MQCryptoSystem mq;
    mq.Import(strings[1]);
    
    if (strings[2] == "plus")
    {
        std::shared_ptr<FEI::Cryptosystem::PlusModifier> modifier = std::make_shared<FEI::Cryptosystem::PlusModifier>(stoi(strings[3]));
    } 
    if (strings[2] == "minus")
    {
        std::shared_ptr<FEI::Cryptosystem::MinusModifier> modifier = std::make_shared<FEI::Cryptosystem::MinusModifier>(stoi(strings[3]));
    } 
    if (strings[2] == "xor")
    {
        std::shared_ptr<FEI::Cryptosystem::XorModifier> modifier = std::make_shared<FEI::Cryptosystem::XorModifier>(stoi(strings[3]));
    }

    if (argc == 5)
    {
        mq.Save(strings[4]);
    }
    else
    {
        mq.Save();
    }



    /*
    for(auto s : strings)
        std::cout << s << "\n"; */

/*
    std::string pathToFile(argv[1]);
    std::string modifier(argv[2]);
    std::string parameter(argv[3]);
    std::string pathToSave = "";

    if(argc == 4) 
    {
        pathToSave = std::string(argv[4]);
    }

    std::cout << pathToFile << std::endl;
    std::cout << modifier << std::endl;
    std::cout << parameter << std::endl;
    std::cout << pathToSave << std::endl; */

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
