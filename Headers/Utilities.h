#pragma once

#include <random>
#include <vector>
#include <map>

namespace std {
    vector<int> operator +(vector<int> rhs, vector<int> lhs);
}

namespace FEI {
namespace Utilities {

    class UtilityModule
    {
    public:
        static int RandomIntGenerator(std::pair<int, int> range);
        static int RandomIntGenerator(int upperbound, int lowerbound = 0);
        static int RandomIntGenerator();
        static std::vector<int> RandomVectorGenerator(size_t size);
        static std::vector<int> RandomQuadraticTermGenerator(std::map<std::string, std::vector<int>> linear_combinations);
        static inline int LINEAR_SUM(int i);
        static inline int LINEAR_SUM(int from, int to);
        static std::vector<int> GetLinearCombination(std::vector<int> z1, std::vector<int> z2);
    };

} //!Utilities
} //!FEI