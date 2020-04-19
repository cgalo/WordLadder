/*
 * Author: Carlos Galo
 * Created On: 4/18/2020
 * Program: WordLadder
 * Class: Non-Linear Data Structures
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

    if (argc <= 3)                  //We need at least 3 arguments in the CLI
        cout << "Error! Missing more arguments with command" << endl;
    else                            //Else the user provided 3 arguments
    {
        string firstWord    = argv[2];  //Save the 'first word' value from the cmd
        string lastWord     = argv[3];  //Save the 'last word' value from the cmd
        if (firstWord.length() == lastWord.length()) //If the first word and last word in the ladder are the same length
        {
            toUpper(&firstWord);         //Convert the firstWord string to upper case
            toUpper(&lastWord);          //Convert the lastWord string to upper case

            cout << "First Word: " << firstWord << endl;
            cout << "Last Word: "  << lastWord << endl;
            std:: cout << "File name: " << argv[1] << endl;
            WordLadder* wl = new WordLadder(argv[1], firstWord.length());
            std::cout << "Size: " << wl->getWordCount() << std::endl;
            delete wl;

        }   //End of if the firstWord and lastWord have the same length
        else                                    //Else first & last word sizes do not match
            cout << "Error! Your first & last word values are not the same length" << std::endl;  //Output error message
    }   //End of else, if the user passed at least 3 arguments w/ the cmd

    return 0;
}   //End of main function


void toUpper (std::string* word)
{
    //Function takes pointer/reference of a string and converts it into uppercase
    for (auto & c: *word) c = toupper(c);
}   //End of toUpper function