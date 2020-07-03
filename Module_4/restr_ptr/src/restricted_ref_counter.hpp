#pragma once

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
