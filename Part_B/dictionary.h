#pragma once
#include <vector>
#include <ostream>

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
    bool lookup(std::string word, int start = 0, int end = 0);
};
