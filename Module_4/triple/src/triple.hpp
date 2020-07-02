#ifndef TRIPLE_H
#define TRIPLE_H
/* Add include guards here */
#include <iostream>
#include <cstdlib>
/* Class: Triple
 * -------------
 * The template class Triple is a container class, which holds three values.
 * All of the values can be of different type. All of the values should be
 * private.
 *
 * The constructor of the class takes three const references to values as a
 * parameter. The parameters are in order, in other words, after construction
 * the first parameter should be accessible through the public member function
 * First, the second parameter through the public member function Second, and
 * the third through the public member function Third. 
 *
 * The default empty constructor should also work.
 *
 * The Triple class should also support the copy constructor, and assignment
 * operations.
 */
 template<typename T1, typename T2, typename T3>
 class Triple {
     public:
        Triple(const T1& a, const T2& b, const T3& c) : a_(a), b_(b), c_(c) { }
        const T1& First() const { return a_; }
        const T2& Second() const { return b_; }
        const T3& Third() const { return c_; }

        Triple &operator=(const Triple &t){
            a_ = t.First();
            b_ = t.Second();
            c_ = t.Third();
            return *this;
        }
        Triple(const Triple&t){
            a_ = t.First();
            b_ = t.Second();
            c_ = t.Third();
        }

     private:
        T1 a_;
        T2 b_;
        T3 c_;
    };

/* Public member functions:
 * ------------------------
 * The Triple class has three public member functions, which are used to
 * access the stored elements. All three should work with const instances
 * of Triple.
 *
 * Function: First
 * The function takes no parameters.
 * The function returns a const reference to the first value of the triple.
 *
 * Function: Second
 * The function takes no parameters.
 * The function returns a const reference to the second value of the triple.
 *
 * Function: Third
 * The function takes no parameters.
 * The function returns a const reference to the third value of the triple.
 */

/* Non-member functions:
 * ---------------------
 * Function: IsHomogenous
 * The function is a non-member function that takes a Triple as a parameter.
 * The function returns a boolean value indicating whether the triple is
 * homogenous or not. A triple is homogenous if all of its three values are of
 * the same type.
 * Hint: specialisation can help you here.
 */
template<typename T>
bool IsHomogenous(const Triple<T,T,T>){
    return true;
}
template<typename A, typename B, typename C>
bool IsHomogenous(const Triple<A,B,C>){
    return false;
}

template<typename A, typename B, typename C>
    bool operator==(const Triple<A,B,C>& f, const Triple<A,B,C>& s) {
        return (f.First() == s.First() && f.Second() == s.Second() && f.Third() == s.Third());
    }
template<typename A, typename B, typename C>
    bool operator!=(const Triple<A,B,C>& f, const Triple<A,B,C>& s) {
        return !(f==s);
    }
template<typename A, typename B, typename C>
    std::ostream &operator<<(std::ostream& os, const Triple<A,B,C>& t){
        os << "[" << t.First() << "," << t.Second() << "," << t.Third() << "]";
        return os;
    }
/* Operator overloads:
 * -------------------
 * The triple class should support the following operators:
 *
 * Assignment operator, =
 * The default functionality should do here.
 *
 * Equality operator, ==
 * You can assume that all the values in the triple can be compared by the
 * == -operator. Two triples are equal if the corresponding values in both
 * of the triples are equal.
 *
 * Inequality operator, !=
 * You can assume that all the values in the triple can be compared by the
 * != -operator. Two triples are inequal if even one corresponding value in
 * the triples is different.
 *
 * The output stream operator, <<
 * You can assume that all the values in the triple support the << -operator.
 * The triple should be printed to the output stream in the following format: 
[<first value>, <second value>, <third value>]
 * Note that there is NO new line at the end of the output.
 */

/* Remember the endif here to close the header guards */

#endif