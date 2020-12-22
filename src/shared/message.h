#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>

class Message
{
private:
    std::vector<char> data;
public:
    Message() = default;

    template <typename T>
    void push_back(T& item)
    {
        if(std::is_trivially_copyable<T>)
        {
            data.insert((char*)&item,(char*)&item + sizeof(T));
        }
        else
        {
            throw std::exception("This item isn't serializable!");
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