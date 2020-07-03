#pragma once

#include "restricted_ref_counter.hpp"

template <typename T>
class RestrictedPtr
{
public:
    RestrictedPtr() : data_(nullptr)
    {
        count_ = new RestrictedRefCounter();
        count_->Increase();
    }
    RestrictedPtr(T *data) : data_(data)
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
        }
        else
        {
            data_ = nullptr;
            count_ = new RestrictedRefCounter();
            count_->Increase();
        }
    }
    T &GetData() { return *data_; }
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
            count_ = rptr.count_;
            data_ = rptr.data_;
            return *this;
        }
        count_ = new RestrictedRefCounter();
        count_->Increase();
        data_ = nullptr;
        return *this;
    }

private:
    T *data_;
    RestrictedRefCounter *count_;
};
/*
    Implement a class RestrictedPtr that holds a pointer of any type with at least the following members:
        - default constructor (takes no parameters)
        - constructor with a raw pointer parameter
        - copy constructor
        - destructor
        - copy assignment operator
        - function GetData that takes no parameters and returns the data the raw pointer refers to.
            The data returned should be such that modifying it modifies the data the pointer refers to.
        - function GetPointer that takes no parameters and returns the raw pointer
        - function GetRefCount that takes no parameters and returns an int with the reference count
    
    At any time the objects should keep track of how many references there are to a pointer
    and not allow more than 3 references. If the reference count drops to 0, the referenced
    pointer's memory should be released. If the reference count is already 3 when copying,
    the copier should set it's pointer to nullptr and reference count to 1.
    NOTE: GetPointer, GetData and GetRefCount are needed for the tests to run
*/
