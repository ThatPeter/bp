#pragma once

#include <string>
#include <map>

namespace FEI {
namespace Modules {

    class InputManager
    {
    private:
        void DisplayHelp();
    public:
        virtual void Manage(std::map<std::string, std::string> input);
    };

} //!Modules
} //!FEI