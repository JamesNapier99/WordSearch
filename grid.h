#pragma once
#include "d_matrix.h"
#include "dictionary.h"

class grid
{
private:
    /* data */
    matrix<std::string> letters;
public:
    /* Constructor */
    grid(const string& path);
    /* Destructor */
    //~grid();

    /* Methods */
    friend void findMatches(const dictionary& dict, const grid& letters);
    friend std::ostream& operator <<
        (std::ostream& ostr, const grid& rhs);
};
