#pragma once

#include <string>

namespace FEI {
namespace Modules {

    class IOService
    {
    public:
        virtual void Import(std::string pathname) = 0;
        virtual void Save(std::string pathname) = 0;
    };

} //!Module
} //!FEI