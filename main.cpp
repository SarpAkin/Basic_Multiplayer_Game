#include <iostream>

#include "src/shared/vectorBinarySearch.h"

int main()
{
    std::vector<std::pair<int, int>> vec;
    vec.emplace_back(0,5);
    vec.emplace_back(8,9);
    vec.emplace_back(15,1);
    std::cout << findIndVec(vec,9) << '\n';
}