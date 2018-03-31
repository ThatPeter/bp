#include "../Headers/Utilities.h"

namespace std {

    vector<int> operator+(vector<int> rhs, vector<int> lhs)
    {
        vector<int> smaller;
        vector<int> bigger;

        if (rhs.size() >= lhs.size())
        {
            smaller = lhs;
            bigger = rhs;
        }
        else
        {
            smaller = rhs;
            bigger = lhs;
        }

        for (size_t i = 0; i < smaller.size(); i++)
        {
            bigger[i] = (bigger[i] + smaller[i]) % 2;
        }

        return bigger;
    }
}

namespace FEI {
namespace Utilities {
    
    int UtilityModule::RandomIntGenerator(std::pair<int, int> range)
    {
        std::random_device rand;
        return (rand() % (range.first + 1)) + range.second;
    }

    int UtilityModule::RandomIntGenerator(int upperbound, int lowerbound)
    {
        std::random_device rand;
        return (rand() % (upperbound + 1)) + lowerbound;
    }

    int UtilityModule::RandomIntGenerator()
    {
        std::random_device rand;
        return rand();
    }

    std::vector<int> UtilityModule::RandomVectorGenerator(size_t size)
    {
        std::vector<int> vector;
        for (size_t i = 0; i < size; i++)
        {
            vector.push_back(RandomIntGenerator(1));
        }
        return vector;
    }

    std::vector<int> UtilityModule::RandomQuadraticTermGenerator(std::map<std::string, std::vector<int>> linear_combinations)
    {
        std::vector<int> quadraticTerm;

        for (auto it = linear_combinations.begin(); it != linear_combinations.end(); it++)
        {
            int condition = RandomIntGenerator(1);
            if (condition != 0)
            {
                quadraticTerm = quadraticTerm + it->second;
            }
        }

        return quadraticTerm;
    }


    inline int UtilityModule::LINEAR_SUM(int i)
    {
        if (i < 0)
        {
            return -1;
        }

        return (i * (i + 1)) / 2;
    }

    inline int UtilityModule::LINEAR_SUM(int from, int to)
    {
        if (from < 0 || from > to)
        {
            return -1;
        }

        return (to * (to + 1)) / 2 - ((from - 1) * (from)) / 2;
    }

    std::vector<int> UtilityModule::GetLinearCombination(std::vector<int> z1, std::vector<int> z2)
    {
        std::vector<int> linearCombination;
        const size_t quadraticVariables = ((z1.size() - 1) * (z2.size())) / 2;

        for (size_t i = 0; i < quadraticVariables + z1.size(); i++) // set the combination variables to 0 by default
        {
            linearCombination.push_back(0);
        }

        //quadratic variables
        for (size_t i = 0; i < z1.size() - 1; i++) //iterate through the first one - dont include the absolute variable
        {
            if (z1[i] != 0) //budeme nasobit len ak je clen v z1 pritomny (moze byt 0*x1 a pod...)
            {
                for (size_t j = 0; j < z2.size() - 1; j++)
                {
                    if (z2[j] != 0) //to iste ako hore, logiku aplikujeme len ak je z2[j] pritomne
                    {
                        // 0 = x1x1, 1 = x1x2, 2 = x2x2, 3 = x1x3, 4 = x2x3, 5 = x3x3, 6 = x1x4, 7 = x2x4, 8 = x3x4, 9 = x4x4, 10 = x1x5, 11 = x2x5, 12 = x3x5, 13 = x4x5, 14 = x5x5
                        // x1x1 x1x2 x1x3 x1x4 x1x5 ... x2x1 x2x2 x2x3 x2x4 x2x5 ... x3x1 x3x2 x3x3 x3x4 x3x5 ... x4x1 x4x2 x4x3 x4x4 x4x5 ... x5x1 x5x2 x5x3 x5x4 x5x5 
                        //  0    1     3   6    10      1     2    4    7   11       3     4    5    8   12       6     7    8    9   13       10    11   12   13  14
                        // 00   01     02  03   04      10    11   12   13  14       20    21   22   23  24       30    31   32   33  34       40    41   42   43  44     

                        int diff = j - i;

                        if (diff == 0)
                        {
                            linearCombination[LINEAR_SUM(i + 1) - 1] = (linearCombination[LINEAR_SUM(i + 1) - 1] + 1) % 2;
                        }
                        if (diff < 0)
                        {
                            linearCombination[LINEAR_SUM(i + 1) - 1 + diff] = (linearCombination[LINEAR_SUM(i + 1) - 1 + diff] + 1) % 2;
                        }
                        if (diff > 0)
                        {
                            linearCombination[LINEAR_SUM(i + 1) - 1 + LINEAR_SUM(i, j) - i] = (linearCombination[LINEAR_SUM(i + 1) - 1 + LINEAR_SUM(i, j) - i] + 1) % 2;
                        }
                    }
                }
            }
        }

        //linear variables                                                    -6 -5 -4 -3 -2 -1
        if (z1[z1.size() - 1] == 1) //(... + 1) *(x1 + x2 + x3 ... 1)         x1 x2 x3 x4 x5 1 
        {                                                              //i=   0  1  2  3  4  5   size = 6
            for (size_t i = 0; i < z2.size(); i++)
            {
                if (z2[i] == 1)
                {
                    linearCombination[linearCombination.size() - z2.size() + i] = (linearCombination[linearCombination.size() - z2.size() + i] + 1) % 2;
                }
            }
        }

        if (z2[z2.size() - 1] == 1)
        {
            for (size_t i = 0; i < z1.size() - 1; i++)
            {
                if (z1[i] == 1)
                {
                    linearCombination[linearCombination.size() - z1.size() + i] = (linearCombination[linearCombination.size() - z1.size() + i] + 1) % 2;
                }
            }
        }

        return linearCombination;
    }
        
} //!Utilities
} //!FEI