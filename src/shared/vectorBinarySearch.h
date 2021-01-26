#include <vector>

template<typename T>
T* findIndVec(std::vector<std::pair<int, T>> vec, int id)
{
    int rangeBegin = 0;
    int rangeEnd = vec.size() - 1;
    int index = rangeEnd / 2;
    while (vec[index].first != id)
    {
        int oldindex = index;
        if (vec[index].first < id)
        {
            rangeBegin = index;
            index += (rangeEnd - index) >> 1;
        }
        else
        {
            rangeEnd = index;
            index -= (index - rangeBegin) >> 1;
        }

        if(oldindex == index)
        {
            return nullptr;
        }
    }
    return &(vec[index].second);
}