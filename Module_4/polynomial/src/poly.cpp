#include "poly.hpp"

#include <sstream>

int Poly::operator[](int exp) const {
    auto it = values_.find(exp);
    return it == values_.end() ? 0 : it->second;
}

Poly operator-(const Poly& a, const Poly& b){
    Poly ret;
    for(Poly::Values::const_reverse_iterator it = a.rbegin(); it != a.rend();it++){
        ret[it->first] = it->second;
    }
    for(Poly::Values::const_reverse_iterator i = b.rbegin(); i != b.rend();i++){
         ret[i->first] = ret[i->first] - i->second;
    }
    return ret;
}

Poly operator-(const Poly& p){
    Poly ret;
    for(Poly::Values::const_reverse_iterator it = p.rbegin(); it != p.rend();it++){
        ret[it->first] = -1*(it->second);
    }
    return ret;
}

Poly& Poly::operator+=(const Poly& b){
    for(auto it = rbegin(); it!=rend();it++){
        values_[it->first] = it->second;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        values_[it->first] = values_[it->first] + it->second;
    }
    return *this;
}
Poly& Poly::operator-=(const Poly& b){
    for(auto it = rbegin(); it!=rend();it++){
        values_[it->first] = it->second;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        values_[it->first] = values_[it->first] - it->second;
    }
    return *this;
}

Poly operator+(const Poly& a, const Poly& b){
    Poly ret;
    for(Poly::Values::const_reverse_iterator it = a.rbegin(); it != a.rend();it++){
        ret[it->first] = it->second;
    }
    for(Poly::Values::const_reverse_iterator it = b.rbegin(); it != b.rend();it++){
         ret[it->first] = ret[it->first] + it->second;
    }
    return ret;
}

bool operator<(const Poly& a, const Poly& b){
    int maxa=0, maxb=0;
    for(auto it=a.rbegin();it!=a.rend();it++){
        maxa++;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        maxb++;
    }
    return maxa<maxb;
}
bool operator>(const Poly& a, const Poly& b){
    int maxa=0, maxb=0;
    for(auto it=a.rbegin();it!=a.rend();it++){
        maxa++;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        maxb++;
    }
    return maxa>maxb;
}
bool operator==(const Poly& a, const Poly& b){
    int maxa=0, maxb=0;
    for(auto it=a.rbegin();it!=a.rend();it++){
        maxa++;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        maxb++;
    }
    return maxa==maxb;
}
bool operator!=(const Poly& a, const Poly& b){
    int maxa=0, maxb=0;
    for(auto it=a.rbegin();it!=a.rend();it++){
        maxa++;
    }
    for(auto it=b.rbegin();it!=b.rend();it++){
        maxb++;
    }
    return maxa!=maxb;
}

std::istream& operator>>(std::istream& is, Poly& p){
    while (!is.eof())
    {
        int mult,exp;
        char ph;
        is>>mult>>ph>>exp;
        p[exp] = mult;
        if(is.peek() == EOF) break;
    }
    return is;
    
}
std::ostream& operator<<(std::ostream& os, const Poly& p){
    for(auto it = p.rbegin(); it!=p.rend();it++){
        if(it->second==0) continue;
        else if(it==p.rbegin() || it->second<=0){
            os << it->second << "x" << it->first;
        } else os<<"+"<<it->second<<"x"<<it->first;
    }
    return os;
}