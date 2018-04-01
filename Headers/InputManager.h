#pragma once

#include <string>
#include <vector>

namespace FEI {
namespace Modules {

    class InputManager
    {
    public:
        virtual void Manage(std::vector<std::string> input);
    };

} //!Modules
} //!FEI