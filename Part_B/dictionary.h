#pragma once
#include <vector>
#include <ostream>
#include "heap.h"

class dictionary
{
public:
    /* data */
    std::vector<std::string> wordList;
    /* Constructor */
    dictionary();
    /* Destructor */
    //~dictionary();

    /* Methods */
    void readDict(const std::string& file);
    friend std::ostream& operator <<
        (std::ostream& ostr, const dictionary& rhs);
    void sort();
    void qsort(int left = 0, int right = 0);
    void hsort();
    bool lookup(std::string word, int start = 0, int end = 0);
};
