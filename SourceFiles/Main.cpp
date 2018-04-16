#include "../Headers/InputManager.h"

#include <iostream>
#include <string>
#include <map>

#include <vector>

int main(int argc, char** argv)
{
    //-------------------------------------------
  /*  int argc;
    std::vector<std::string> argv;

    argv.push_back("exefile name");
        argv.push_back("-h"); */
   /* argv.push_back("-r");
    
    argv.push_back("-v");
    argv.push_back("10");

    argv.push_back("-e");
    argv.push_back("10");

    argv.push_back("-s");           THIS BLOCK IS PRESENT FOR TESTING PURPOSES ONLY AND WILL BE REMOVED 
    argv.push_back("rand");*///     IMMEDIATELY UPON A FINAL RELEASE VERSION       
    /*
    argv.push_back("-f");
    argv.push_back("rand");

    argv.push_back("-m");
    argv.push_back("plus");

    argv.push_back("-p");
    argv.push_back("1");

    argv.push_back("-s");
    argv.push_back("r"); 

    argc = argv.size();
    */
    //----------------------------------------------
    std::map<std::string, std::string> input;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == "-r" || argv[i] == "-h")
        {
            input[argv[i]] = "";
        }
        else 
        {
            if (i + 1 < argc)
            {
                input[argv[i]] = argv[i + 1];
                i++;
            }
            else
            {
                std::cout << "Invalid usage. Use -h for help.\n";
                return 1;
            }
        }
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
