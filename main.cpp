///////////////////////////////////////////////////////////////////////////////
// Project#3
// Word Search: Part A
// Written by:
// James Napier:                                      napier.j@northeastern.edu
// Julia Rasmussen:                                rasmussen.j@northeastern.edu
// Samuel Sheehan:                                   sheehan.s@northeastern.edu
//
// Main program file for homework 3a. Contains declarations for
//
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>        // only need this if case matters

#include "dictionary.h"
#include "grid.h"
#include "d_except.h"
#include "d_matrix.h"

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
    ifstream fin;
    string path = file;
    fin.open(path.c_str());
    if (!fin)
    {
        // error handling
        cout << "Houston, we have a problem" << endl;
    }

    string element;
    while (fin >> element)
    {
        // transform(element.begin(), element.end(), element.begin(), ::tolower);  // only need this if case matters
        wordList.push_back(element);
    }
    fin.close();
}

/*
* Overrides the print operator for the dictionary object.
* ostr: output stream ostr, the output stream to print to. 
* rhs: dictionary to print out.
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
            cout << "Swapping " << wordList[i] << " and " << wordList[pos] << endl;
            swap = wordList[i];
            wordList[i] = wordList[pos];
            wordList[pos] = swap;
        }
    }

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
    ifstream fin;
    fin.open(path.c_str());
    if (!fin)
    {
        // error handling
        cout << "Houston, we have a problem" << endl;
    }
    int size;
    string element;

    getline(fin, element);

    size = stoi(element.substr(0, 2));
    matrix<string> newMat(size, size);
    letters = newMat;

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
*/
int grid::getLength()
{
    return letters.rows();
}

/*
* Gets the letter at given index.
* r: int r, the row to search.
* c: int c, the col to search.
*/
string grid::getLetterAt(int r, int c)
{
    return letters[r][c];
}

/*
* Gets all possible rows on grid from which words can be found.
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
// Global Functions
//=============================================================================
#pragma region func

/*
* Gets all possible words on each row from the given matrix.
* minLength: the minimum length of a possible word.
* n: the length of each row.
* allFullRows: the matrix to search for words from. 
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
void findMatches(grid& searchGrid, const dictionary& searchDictionary)
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
    for (string word : allWords)
    {
        cout << word << " ";
    }
}

/*
* Searches for all words from grid and dictionary files. 
*/
void search()
{
    //sort the dictionary file.
    string dPath = "../Dictionary.txt"; //for visual studio code project
    //string dPath = "Dictionary" //for regular implementation

    dictionary dict;
    dict.readDict(dPath);
    //dict.sort();

    cout << "\nFinished Sorting\n";

    //identify the grid to search for words
    string grid_file_name;
    cout << "Please enter the file name for your grid: \n";
    cin >> grid_file_name;

    //initialize the grid object, then print it out
    grid newGrid(grid_file_name);
    cout << newGrid;

    findMatches(newGrid, dict);
}

#pragma endregion func
//=============================================================================
int main()
{
    /*
    dictionary dict;
    string temp = "Dictionary";
    dict.readDict(temp);
    dict.sort();
    cout << temp << endl;
    */
    search();
}
