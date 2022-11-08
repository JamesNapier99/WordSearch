///////////////////////////////////////////////////////////////////////////////
// Project#3
// Word Search: Part B
// Written by:
// James Napier:                                      napier.j@northeastern.edu
// Julia Rasmussen:                                rasmussen.j@northeastern.edu
// Samuel Sheehan:                                   sheehan.s@northeastern.edu
//
// Main program file for homework 3b.
//
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>

#include "dictionary.h"
#include "grid.h"
#include "d_except.h"
#include "d_matrix.h"
#include "heap.h"

using namespace std;

//=============================================================================
// Dictionary Methods
//=============================================================================
#pragma region Dictionary

/*
* Initializes the dictionary object.
*/
dictionary::dictionary() {};    // placeholder

/*
* Reads file and inputs into dictionary object.
* file: string of path of the file to read.
*/
void dictionary::readDict(const string& file)
{
    //opens dictionary file from given file path
    ifstream fin;
    string path = file;
    fin.open(path.c_str());

    //throw error if file not found.
    if (!fin)
    {
        // error handling
        cout << "Houston, we have a problem" << endl;
    }

    //traverse dictionary file and append each word to wordList.
    string element;
    while (fin >> element)
    {
        // transform(element.begin(), element.end(), element.begin(), ::tolower);  // only need this if case matters
        wordList.push_back(element);
    }
    fin.close();
}

/*
* Overrides the print operatorD for the dictionary object.
* ostr: output stream ostr, the output stream to print to.
* rhs: dictionary to print out.
* returns ostream with the printed dictionary.
*/
ostream& operator << (ostream& ostr, const dictionary& rhs)
{
    int size = rhs.wordList.size();
    for (int i = 0; i < size; i++)
    {
        cout << rhs.wordList[i] << endl;
    }
    return ostr;
}

/*
* Sorts all words in the dictionary object alphabetically.
*/
void dictionary::sort()
{
    string swap;
    for (int i = 0; i < wordList.size() - 2; i++)
    {
        cout << i << " of " << wordList.size() << "\n";
        int pos = i;
        for (int j = i + 1; j < wordList.size() - 1; j++)
        {
            if (wordList[pos] > wordList[j])
            {
                pos = j;
            }
        }
        if (pos != i)
        {
            //cout << "Swapping " << wordList[i] << " and " << wordList[pos] << endl;
            swap = wordList[i];
            wordList[i] = wordList[pos];
            wordList[pos] = swap;
        }
    }
}

void dictionary::qsort(int left, int right)
/*
* Sorts all words in the dictionary object using Quick Sort
*/
{
    if (right == 0)
    {
        right = wordList.size();
    }
    if (left < right)
    {
        /* Begin Partitioning*/
        string x = wordList[right];
        int i = left - 1;
        for (int j = left; j < right; j++)
        {
            if (wordList[j].compare(x) <= 0)    // based on compare outcomes
            {
                i += 1;
                string temp = wordList[j];
                wordList[j] = wordList[i];
                wordList[i] = temp;
            }
        }
        wordList[right] = wordList[i + 1];
        wordList[i + 1] = x;
        /* End Partitioning */
        qsort(left, i);
        qsort(i + 2, right);
    }
}

void dictionary::hsort()
/*
* Sorts all words in the dictionary object using Quick Sort
*/
{
    heap<string> dictionary_heap;
    dictionary_heap.initializeMaxHeap(wordList);
    dictionary_heap.heapsort();
}

/*
* Checks if a word is in the dictionary, returns 0 if not.
* word: string to check for within dictionary.
* start: int index to start to look for word in.
* end: int index to end to look for word in.
* return bool of 1 if word is within dictionary, and 0 if not.
*/
bool dictionary::lookup(string word, int start, int end)
{
    bool val = false;
    int mid = int((end + start) / 2);

    //if at last possible case that word can still be at mid, check.
    if (start == end)
    {
        if (wordList[mid].compare(word) == 0)
        {
            return true;
        }
    }

    //if out of bounds, return false.
    else if (start > end)
    {
        return false;
    }

    //check if word is in mid.
    else if (wordList[mid].compare(word) == 0)
        return true;

    //check if word is larger than mid alphabetically.
    else if (wordList[mid].compare(word) < 0)
        return lookup(word, mid + 1, end);

    //check if word is smaller than mid alphabetically.
    else if (wordList[mid].compare(word) > 0)
        return lookup(word, start, mid - 1);

    //else return false
    return val;
}
#pragma endregion Dictionary
//=============================================================================
// Grid Methods
//=============================================================================
#pragma region Grid

/*
* Initializes the grid object from a given file.
* path: string that gives the path of the file to initialize the grid object from.
*/
grid::grid(const string& path)
{
    //opens the file given with the path input.
    ifstream fin;
    fin.open(path.c_str());

    //throws error if file not found.
    if (!fin)
    {
        // error handling
        cout << "Houston, we have a problem" << endl;
    }

    int size;
    string element;

    //get first line and determine the size from it.
    getline(fin, element);

    size = stoi(element.substr(0, 2));
    matrix<string> newMat(size, size);
    letters = newMat;

    //traverse file and append each element to letters matrix.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fin >> letters[i][j];
        }
    }
}

/*
* Overrides the print operator for the grid object.
* ostr: output stream ostr, the output stream to print to.
* rhs: grid to print out.
* returns ostream with printed grid object.
*/
ostream& operator << (ostream& ostr, const grid& rhs)
{
    for (int i = 0; i < rhs.letters.rows(); i++)
    {
        for (int j = 0; j < rhs.letters.cols(); j++)
        {
            cout << rhs.letters[i][j] << " ";
        }
        cout << "\n";
    }
    return ostr;
}

/*
* Gets the length of the grid object.
* returns the integer length of the letters object within grid.
*/
int grid::getLength()
{
    return letters.rows();
}

/*
* Gets all possible rows on grid from which words can be found.
* returns matrix with all possible rows to check.
*/
matrix<string> grid::getFullRows()
{
    int n = getLength();
    matrix<string> allFullRows(4 * n, n);

    //get all possible n-length rows that could hold words within them
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //get all horizontal rows
            allFullRows[i][j] = letters[i][j];

            //get all vertical rows
            allFullRows[i + n][j] = letters[j][i];

            //get first horizontal row
            int checkR = i + j;
            if (checkR >= n)
            {
                checkR = checkR - n;
            }
            allFullRows[i + 2 * n][j] = letters[checkR][j];

            //second horizontal row
            checkR = i - j;
            if (checkR < 0)
            {
                checkR = checkR + n;
            }
            allFullRows[i + 3 * n][j] = letters[checkR][j];
        }
    }

    //return all full rows
    return allFullRows;
}

#pragma endregion Grid
//=============================================================================
// Grid Methods
//=============================================================================
#pragma region Heap
template <class T>

T heap<T>::getItem(const int& n)
{
    return Heap[n];
}

template <class T>
int heap<T>::parent(const int& n)
{
    if (n < Heap.size() && n >= 0)
    {
        return floor(n / 2);
    }
    else
    {
        return -1;
    }
}

template <class T>
int heap<T>::left(const int& n)
{
    if (n < Heap.size() && n >= 0)
    {
        return 2 * n;
    }
    else
    {
        return -1;
    }
}

template <class T>
int heap<T>::right(const int& n)
{
    if (n < Heap.size())
    {
        return 2 * n + 1;
    }
    else
    {
        return -1;
    }
}
// Not sure if this works
template <class T>
heap<T>::heap()
{
    vector<T> placeholder;
    Heap = placeholder;
}

template <class T>
void heap<T>::initializeMaxHeap(const vector<T>& list)
{
    Heap = list;
}


template <class T>
void heap<T>::buildMaxHeap()
{
    heap_size = Heap.length();
    for (int i = floor(heap_size / 2); i > 0; i--)
    {
        maxHeapify(i);
    }
}

template <class T>
void heap<T>::maxHeapify(int& i)
{
    int l = Heap.left(i);
    int r = Heap.right(i);
    int largest;
    if (l <= heap_size && Heap[l] > Heap[i])
    {
        largest = l;
    }
    else
    {
        largest = r;
    }   // end if
    if (r <= heap_size && Heap[r] > Heap[largest])
    {
        largest = r;
    }   // end if
    if (largest != i)
    {
        T biggest = Heap[largest];
        Heap[largest] = Heap[i];
        Heap[i] = biggest;
    }
}

template <class T>
void heap<T>::heapsort()
{
    heap_size = Heap.size();
    while (heap_size >= 2)
    {
        maxHeapify(1); //idk how to make this an & int input
        T temp = Heap[1];
        Heap[1] = Heap[heap_size];
        Heap[heap_size] = temp;
        heap_size -= 1;
    }
}
#pragma endregion Heap
//=============================================================================
// Global Functions
//=============================================================================
#pragma region func

/*
* Gets all possible words on each row from the given matrix.
* minLength: the minimum length of a possible word.
* n: the length of each row.
* allFullRows: the matrix to search for words from.
* returns vector with all possible words stored in it.
*/
vector<string> allPossibleWords(int minLength, int n, matrix<string> allFullRows)
{
    vector<string> allWords;
    for (int i = 0; i < 4 * n; i++)
    {
        //now on row i, need all words within i.
        for (int j = 0; j < n; j++) //iterate through all starting letters
        {
            //iterate through all possible lengths
            for (int length = minLength; length < n; length++)
            {
                string word = "";
                //construct word of given length from starting letter
                for (int lengthi = 0; lengthi < length; lengthi++)
                {
                    int rValue = j + lengthi;
                    if (rValue >= n)
                    {
                        rValue = rValue - n;
                    }
                    word = word + allFullRows[i][rValue];
                }

                //after having constructed word, append it to list of words
                allWords.push_back(word);
            }
        }
    }
    return allWords;
}

/*
* Finds all possible words from given grid.
* searchGrid: the grid to search.
* searchDictionary: the dictionary to compare possible words to.
*/
void findMatches(grid& searchGrid, dictionary& searchDictionary)
{
    int n = searchGrid.getLength();
    matrix<string> allFullRows(4 * n, n);
    allFullRows = searchGrid.getFullRows();

    //print the allFullRows matrix, to show which rows have been found (can be commented out)
    for (int i = 0; i < 4 * n; i++)
    {
        if (i % n == 0)
        {
            cout << "\n";
        }
        for (int j = 0; j < n; j++)
        {
            cout << allFullRows[i][j] << " ";
        }
        cout << "\n";
    }

    //find all possible words in allFullRows
    int minLength = 5;
    vector<string> allWords = allPossibleWords(minLength, n, allFullRows);

    //print all words found in allWords
    cout << "Words Found: \n";
    for (string word : allWords)
    {
        //check if the word from allWords is within the given dictionary, if so, print it.
        if (searchDictionary.lookup(word, 0, searchDictionary.wordList.size() - 1))
        {
            cout << word << "\n";
        }
    }
}

/*
* Searches for all words from grid and dictionary files.
* selectionType: integer that indicates sorting type (1-selection sort, 2-heap sort, 3-quick sort)
*/
void search(int selectionType)
{
    //identify the dictionary to search for words
    string dict_file_name;
    cout << "Please enter the file name for your dictionary: \n";
    cin >> dict_file_name;

    //sort the dictionary file, depending on int selectionType.
    dictionary dict;
    dict.readDict(dict_file_name);

    //selection sort
    if (selectionType == 1)
    {
        dict.sort();
    }
    //heap sort
    else if (selectionType == 2)
    {
        dict.hsort();
    }
    //quick sort
    else
    {
        dict.qsort();
    }

    cout << "\nFinished Sorting the Dictionary!\n";

    /*
    //identify the grid to search for words
    string grid_file_name;
    cout << "Please enter the file name for your grid: \n";
    cin >> grid_file_name;

    //initialize the grid object, then print it out
    grid newGrid(grid_file_name);
    cout << newGrid;

    //find all possible words from the grid
    findMatches(newGrid, dict);
    */
}

#pragma endregion func
//=============================================================================
int main()
{
    //get sort type
    bool sort_defined = false;
    int sort_type_input;
    cout << "The dictionary will be sorted with the following input: \n";
    cout << "1 - Selection Sort\n";
    cout << "2 - Heap Sort\n";
    cout << "3 - Quick Sort\n";
    while (!sort_defined)
    {
        cout << "How do you want to sort the dictionary? \n";
        cin >> sort_type_input;
        if ((sort_type_input == 1) || (sort_type_input == 2) || (sort_type_input == 3))
        {
            sort_defined = true;
        }
        else
        {
            cout << "Please enter a valid input. \n";
        }
    }

    //start search function.
    search(sort_type_input);
}
