#ifndef ELEC_AS_CPP_BOOK
#define ELEC_AS_CPP_BOOK

#include <string>
#include <ctime>

struct Date {
    int day;
    int month;
    int year;
    
    // Gets the current date. A function in the Date namespace i.e. called using Date::Today(); an object is not needed
    static Date Today() {
        Date d;
        std::time_t t = time(0);
        struct tm * now = localtime(&t);
        d.day=now->tm_mday;
        d.month=now->tm_mon+1;
        d.year=now->tm_year+1900;
        return d;
    }
};

class Book {
public:
    /* Book:
    * the constructor of the Book class, takes the following parameters:
    *  - the book's name (reference to const string), 
    *  - the book's author (reference to const string), 
    *  - the book's ISBN number (reference to const string) 
    *  - the status of the book, loaned or not (bool), which is by default false
    *  - due date as a Date structure (Date), which is by default 0-0-0
    */ 
    

    /* GetName:
    * returns the Book's name as a string, takes no parameters.
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

    /* GetAuthor:
    * returns the Book's author as a string, takes no parameters. 
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

    /* GetISBN:
    * returns the Book's ISBN as a string, takes no parameters.
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

    /* GetStatus:
    * returns the Book's status as a bool, takes no parameters.
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

    /* GetDueDate:
    * returns the Book's due date, takes no parameters.
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

    /* Loan:
    * sets the due date to current date + 1 month, e.g. loaned on 1.9. => due date 1.10.
    * sets the status to true
    * returns true if loaning was succesful and false if it was not
    * Hint: there is a function Today in the Date struct that returns the current date
    */
    

    /* Restore:
    * sets the due date to 0-0-0
    * sets the status to false
    * returns nothing
    */
    


    /* Print:
    * prints the book's information to the standard output stream.
    * The function takes no parameters and returns nothing. 
    * The output format should be like the following:
Book: <name>, author: <author>, ISBN: <isbn>, loaned <true/false>, due date: <day>.<month>.<year>\n
    * This function should not alter the Book object's state, in other words the function should be const.
    */
    

private:
    std::string name_;
    std::string author_;
    std::string isbn_;
    bool loaned_;
    Date due_date_;
};


#endif
