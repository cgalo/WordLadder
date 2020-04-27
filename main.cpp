/*
 * Author: Carlos Galo
 * Created On: 4/18/2020
 * Program: WordLadder
 * Class: Non-Linear Data Structures
 * File: main.cpp
 *  - CLI menu
 * */

#include <iostream>
#include "WordLadder.h"

using namespace std;

void toUpper(std::string* word);                    //Declaring the toUpper function

int main(int argc, char** argv) {
    //Argv0 = WordLadder.exe
    //1 = Name of the file containing the dictionary to use, aka file.txt
    //2 = first word in the ladder
    //3 = last word in the ladder
    //WordLadder file.txt clash clown

    if (argc <= 3)                          //We need at least 3 arguments in the CLI
        cout << "Error! Missing more arguments with command" << endl;
    else                                    //Else the user provided 3 arguments
    {
        string firstWord    = argv[2];      //Save the 'first word' value from the cmd
        string lastWord     = argv[3];      //Save the 'last word' value from the cmd
        if (firstWord.length() == lastWord.length()) //If the first word and last word in the ladder are the same length
        {
            toUpper(&firstWord);            //Convert the firstWord string to upper case
            toUpper(&lastWord);             //Convert the lastWord string to upper case
            WordLadder* wl = new WordLadder(argv[1], firstWord.length());
            if (wl->getWordCount() == 0)    //If no words were found, in the file, with the given length, output error
                cout << "Error! No words were found with the length of: " << firstWord << ", " <<  lastWord << endl;
            else                            //Else we found words with the desired length in the file
                wl->displayResult(wl->getMinLadder(firstWord,lastWord));
            delete wl;                      //Perform garbage collection on the WordLadder object
        }   //End of if the firstWord and lastWord have the same length
        else                                    //Else first & last word sizes do not match
            cout << "Error! Your first & last word values are not the same length" << std::endl;  //Output error message
    }   //End of else, if the user passed at least 3 arguments w/ the cmd
    return 0;
}   //End of main function


void toUpper (std::string* word)
{
    /* toUpper function, parameter(s): string <word>
     * Objective: Convert given string <word> into upper case
     * */

    for (auto & c: *word) c = toupper(c);
}   //End of toUpper function