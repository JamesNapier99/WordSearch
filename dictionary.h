#pragma once
#include <vector>
#include <ostream>

class dictionary
{
private:
    /* data */
    std::vector<std::string> wordList;
public:
    /* Constructor */
    dictionary();
    /* Destructor */
    //~dictionary();

    /* Methods */
    void readDict(const std::string& file);
    friend std::ostream& operator << 
        (std::ostream& ostr, const dictionary& rhs);
    void sort();
    void lookup();  // placeholder, probs need to be something different
};
