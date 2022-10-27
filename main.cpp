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
dictionary::dictionary() {};    // placeholder

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
        transform(element.begin(), element.end(), element.begin(), ::tolower);  // only need this if case matters
        wordList.push_back(element);
    }
    fin.close();
}

ostream& operator << (ostream& ostr, const dictionary& rhs)
{
    int size = rhs.wordList.size();
    for (int i = 0; i < size; i++)
    {
        cout << rhs.wordList[i] << endl;
    }
    return ostr;
}

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

#pragma endregion Grid
//=============================================================================
// Global Functions
//=============================================================================
#pragma region func
void findMatches(const grid& searchGrid, const dictionary& searchDictionary)
{

}

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