#pragma once
#include "restricted_ptr.hpp"

using namespace WeirdMemoryAllocator;
template <typename T>
RestrictedPtr<T> MakeRestricted(T *pntr)
{
    return RestrictedPtr(pntr, "RestrictedPtr instance");
}
template <typename T>
std::ostream &operator<<(std::ostream &os, RestrictedPtr<T> &rpntr)
{
    try
    {
        os << rpntr.GetData() << std::endl;
    }
    catch (RestrictedPtrException &ex)
    {
        os << ex.GetError() << std::endl;
    }
    return os;
}
template <typename T>
RestrictedPtr<T> CopyRestricted(RestrictedPtr<T> &rpntr)
{
    RestrictedPtr<T> temp;
    try
    {
        temp = rpntr;
        return temp;
    }
    catch (RestrictedPtrException &ex)
    {

        std::cout << ex.GetError() << std::endl;
        return temp;
    }
}

/* TODO:
 *
 * MakeRestricted: a template function that takes any type of
 * pointer as a parameter and returns a RestrictedPtr holding
 * that pointer with the use set to "RestrictedPtr instance".
 * 
 * CopyRestricted: a template function that takes a reference to
 * a RestrictedPtr as a parameter and returns a copy of it. If
 * the copying fails, prints the error in the exception to
 * standard output with a newline appended and returns a
 * default constructed RestrictedPtr.
 *
 * operator<<: a template function that takes in a ostream 
 * reference and a RestrictedPtr reference, prints the object
 * pointed to by the pointer to the stream using the << operator 
 * and returns a reference to the stream. If the pointer is null,
 * prints the return value of GetError of the exception thrown by 
 * GetData instead.
*/
