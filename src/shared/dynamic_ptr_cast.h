#ifndef DYNAMIC_PTR_CAST_H
#define DYNAMIC_PTR_CAST_H

#include <memory>


template<typename T0,typename T1>
std::unique_ptr<T0> dynamic_ptr_cast(std::unique_ptr<T1>& ptr)
{
    T0* c_ptr = dynamic_cast<T0*>(ptr.get());
    if(c_ptr)
    {
        ptr.release();
        return std::unique_ptr<T0>(c_ptr);
    }
    return std::unique_ptr<T0>(nullptr);
}

template<typename T0,typename T1>
std::unique_ptr<T0> dynamic_ptr_cast(std::unique_ptr<T1>&& ptr)
{
    T0* c_ptr = dynamic_cast<T0*>(ptr.get());
    if(c_ptr)
    {
        ptr.release();
        return std::unique_ptr<T0>(c_ptr);
    }
    return std::unique_ptr<T0>(nullptr);
}

#endif
