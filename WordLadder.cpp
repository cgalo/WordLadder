//
// Created by Carlos Galo on 4/18/20.
//

#include "WordLadder.h"


WordLadder::WordLadder(std::string lexiconFileName, int len)
{
    /* Constructor, parameter(s): string <file>, int <len> of words
     * */

    //First lets read the file
    std::ifstream inFile;                   //Declare an input file stream variable
    inFile.open(lexiconFileName);           //Open the file stream
    if (!inFile)                            //Check if the file was not able to be open
    {
        std::cout << "Error! Unable to open file: " <<  lexiconFileName << std::endl;   //Output error message
        exit(1);                            //Call system to stop
    }   //End of if we couldn't open the file
    else                                    //Else we could open the file
    {
        std::string str;                    //Initiate a string variable to use while reading the file
        while (getline(inFile, str))//While the file still has another line
        {
            if (str.length() == len)        //If the current string is the same length as the parameter
                this->lexicon.insert(str);  //Then we insert it into lexicon set, the dictionary
            else                            //Else the string is not the same len as the one in the parameter
                continue;                   //We continue to the next string in the file
        }   //End of while-loop
        //We get here after reading the entire file
        inFile.close();                     //Close the file after reading through its
    }   //End of else, if we could open the file
}   //End of Constructor for WordLadder

WordLadder::~WordLadder()
{
    /* Destructor for WordLadder, parameter(s): None
     * Notes:
     *  - For garbage collection purposes
     * */

    this->lexicon.erase(this->lexicon.begin(), this->lexicon.end());    //Delete all values in the set  <lexicon>
}   //End of destructor

std::vector<std::string> WordLadder::getMinLadder(std::string start, std::string end)
{
    std::vector<std::string> vector;
    vector.push_back("a");
    return vector;
}   //End of getMinLadder method

void WordLadder::displayResult(std::vector<std::string> sequence)
{

}   //End of displayResult method

int WordLadder::getWordCount()
{
    return lexicon.size();
}   //End of getWordCount

int WordLadder::getHammingDistance(std::string str1, std::string str2)
{
    //Base case the strings have different length, return -1
    if (str1.length() != str2.length())             //If the length of the strings are not equal
        return -1;                                  //Return -1
    else                                            //Else both strings have the same length
    {
        int count = 0;                              //Initiate a count variable
        for (int i = 0; i < str1.length(); i ++)    //Loop through each character in the strings
        {
            if (str1[i] != str2[i])                 //If the current character of each string are different
                count++;                            //Increase the count variable
        }   //End of for-loop
        return count;                               //Return count variable
    }   //End of else, if both strings have the same length
}   //End of getHammingDistance method

