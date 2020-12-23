#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <iostream>

class Message
{
public:
    std::vector<char> data;
public:
    Message() = default;

    template <typename T>
    void push_back(T& item)
    {
        if(std::is_trivially_copyable<T>())
        {
            data.insert(data.end(),(char*)&item,(char*)&item + sizeof(T));
        }
        else
        {
            throw std::exception(std::string("This item isn't serializable! ") + typeid(T).name());
        }
    }

    template<typename T>
    T pop_front()
    {
        T tmp = *(T*)data.data();
        data.erase(data.begin(),data.begin() + sizeof(T));

        return tmp;
    }
    
};

#endif