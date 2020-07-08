// copy your implementation from the last round here (if you had one and used it)
// and wrap it inside a WeirdMemoryAllocator namespace
#pragma once

namespace WeirdMemoryAllocator
{
    const int kMaxReferenceCount = 3;

    class RestrictedRefCounter
    {
    public:
        RestrictedRefCounter() : count_(0) {}

        bool Increase()
        {
            if (count_ < kMaxReferenceCount)
            {
                count_++;
                return true;
            }
            return false;
        }

        int Decrease() { return --count_; }
        int GetCount() { return count_; }

    private:
        int count_;
    };
} // namespace WeirdMemoryAllocator