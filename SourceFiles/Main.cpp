#include "../Headers/InputManager.h"

#include <iostream>
#include <string>

//#include <vector>

int main(int argc, char** argv)
{
   // int argc = 5;
   // std::vector<std::string> argv;

   // argv.push_back("");
    /*-----------------------*/ 
    //argv.push_back("help");           //uncomment for help test
    /*-----------------------
    argv.push_back("random");         //uncomment for random mq creation;
    argv.push_back("5");              //m
    argv.push_back("5");              //n
    argv.push_back("file.txt");       //save - optional
    -----------------------
    argv.push_back("file.txt");       //uncomment for modifier application
    argv.push_back("xore");            //modifier name
    argv.push_back("2");              //modifier parameter
    argv.push_back("xor.txt");        //save - optional
    -----------------------*/
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

    std::vector<std::string> input;
    for (int i = 0; i < argc; i++)
    {
        input.push_back(argv[i]);
    }

    FEI::Modules::InputManager im;
    try
    {
        im.Manage(input);
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Runtime error: " << e.what() << "\n";
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "Invalid argument: " << e.what() << "\n";
    }

    return 0;
}
