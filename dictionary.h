#pragma once
#include <vector>
#include <ostream>

class dictionary
{
private:

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
    int lookup(std::string word,int start, int end);};
