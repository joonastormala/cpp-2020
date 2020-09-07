#pragma once
#include "restricted_ref_counter.hpp"

namespace WeirdMemoryAllocator
{
    template <typename T>
    class RestrictedPtr
    {
    public:
        RestrictedPtr() : data_(nullptr), ptrn("nullptr")
        {
            count_ = new RestrictedRefCounter();
            count_->Increase();
        }
        RestrictedPtr(T *data, std::string name) : data_(data), ptrn(name)
        {
            count_ = new RestrictedRefCounter();
            count_->Increase();
        }
        ~RestrictedPtr()
        {
            if (count_->Decrease() == 0)
            {
                delete data_;
                delete count_;
            }
        }
        RestrictedPtr(RestrictedPtr &rptr)
        {
            if (rptr.count_->Increase())
            {
                data_ = rptr.data_;
                count_ = rptr.count_;
                ptrn = rptr.ptrn;
            }
            else
            {
                throw RestrictedCopyException(rptr.ptrn);
            }
        }
        T &GetData()
        {
            if (data_ == nullptr)
            {
                throw RestrictedNullException(ptrn);
            }
            else
                return *data_;
        }
        T *GetPointer() { return data_; }
        int GetRefCount() { return (*count_).GetCount(); }

        RestrictedPtr &operator=(RestrictedPtr &rptr)
        {
            if (count_->GetCount() == 1)
            {
                delete count_;
            }
            if (rptr.count_->Increase())
            {
                ptrn = rptr.ptrn;
                count_ = rptr.count_;
                data_ = rptr.data_;
                return *this;
            }
            count_ = new RestrictedRefCounter();
            count_->Increase();
            data_ = nullptr;
            ptrn = "nullptr";
            throw RestrictedCopyException(rptr.ptrn);
            return *this;
        }

    private:
        T *data_;
        RestrictedRefCounter *count_;
        std::string ptrn;
    };
} // namespace WeirdMemoryAllocator
/* 
 * Copy your implementation from the last round here (or wait for
 * the example answer to come out and copy that) and wrap it inside a 
 * WeirdMemoryAllocator namespace.
 * 
 * Changes to the class:
 * 
 * Add a new member string to store the use of the RestrictedPtr 
 * and add a new string parameter, which is the use of the pointer, to the 
 * constructor that originally only takes a pointer. Remember to modify
 * copying to also copy the use. If the pointer is automatically set to 
 * a nullptr (i.e. not given in the constructor), the use is "nullptr".
 * 
 * The copy constructor and assigment operators should throw a RestrictedCopyException 
 * if the operations fail (as they in some cases should). When the copying
 * fails, only the exception should be thrown and no changes should be made
 * to the existing pointer.
 * 
 * The GetData function should throw a RestrictedNullException with the use
 * of the RestrictedPtr given to it if the pointer is null.
 * 
 * The class shouldn't leak any memory.
*/
