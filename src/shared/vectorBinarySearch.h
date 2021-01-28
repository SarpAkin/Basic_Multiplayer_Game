#include <vector>

template<typename T>
T* findIndVec(std::vector<std::pair<int, T>>& vec, int id)
{
    if(!vec.size())//check if the vectors size is greater than 0
        return nullptr;
    int rangeBegin = 0;
    int rangeEnd = vec.size() - 1;
    while (rangeBegin < rangeEnd)
    {
        int mid = (rangeEnd + rangeBegin) >> 1;//dive by 2

        if (vec[mid].first < id)
            rangeBegin = mid + 1;
        else if (vec[mid].first > id)
            rangeEnd = mid - 1;
        else // if vec[mid].fist isn't greater or lesser than id its equal to id
            return &(vec[mid].second);
    }
    //Chech the begining or the ending of the vector
    if(vec[rangeBegin].first == id)
        return &(vec[rangeBegin].second);
    return nullptr;
}