/*
 * Author: Carlos Galo
 * Created On: 4/18/2020
 * Program: WordLadder
 * Class: Non-Linear Data Structures
 * File: WordLadder.cpp
 *  - This is the source file for the WordLadder class
 * */

#include "WordLadder.h"


WordLadder::WordLadder(std::string lexiconFileName, int len)
{
    /* Constructor, parameter(s): string <file>, int <len> of words
     * */

    std::ifstream inFile;                   //Declare an input file stream variable
    inFile.open(lexiconFileName );           //Open the file stream
    if (!inFile)                            //Check if the file was not able to be open
    {
        std::cout << "Error! Unable to open file: " <<  lexiconFileName << std::endl;   //Output error message
        exit(1);                            //Call system to stop
    }   //End of if we couldn't open the file
    else                                    //Else we could open the file
    {
        std::string str;                    //Initiate a string variable to use while reading the file
        while (std::getline(inFile, str))
        {
            str.pop_back();                 //Remove the end of line delimiter at the end of the string
            if (str.length() == len)        //If the string's length is the length we are looking for
                this->lexicon.insert(str);  //Then insert the string into our dictionary <lexicon>
        }   //End of while-loop, finished traversing each line in the file
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
    /* Returns a minimum-length word ladder from start to end. If multiple minimum-length
     * word ladders exist, no guarantee is made regarding which one is returned. If no word
     * ladder exists, this method returns an empty list.
     * Breadth-first search must be used to implement this method.
     *  start    the starting word
     *  end      the ending word
     *  returns  a minimum length word ladder from start to end
     * */

    //First we initiate the list, and vectors, needed for this method
    std::vector <std::string> ladder;                       //Initiate a vector, ladder, to return at the end
    std::vector <std::string> wordsSeen;                    //List of words seen
    std::vector <std::string> predecessor;                  //Keep track of the predecessors
    std::list   <std::string> queue;                        //Initiate a queue, type list

    if (!isWord(end))                                       //If the 'end' word is not in the lexicon
        return ladder;                                      //Return empty ladder

    //Start by inserting the 'start' string into the queue and wordSeen, and empty string as predecessor
    queue.push_back(start);                                 //Insert the 'start' string into the queue
    wordsSeen.push_back(start);                             //Insert the 'start' string into wordsSeen
    predecessor.push_back("");                              //Insert an empty string as predecessor to the start string

    while (!queue.empty())                                  //While the queue is not empty
    {
        std::string QFront = queue.front();                 //Get the most recent item in the queue and save it as QFront
        std::set <std::string> neighbors = getNeighbors(QFront);    //Get the neighbors of string 'QFront'
        queue.pop_front();                                  //Remove the top of the queue, as we already got its neighbors
        for (const auto& neighbor: neighbors)               //Loop through each element in neighbors set
        {
            int seenResult = findInVector(wordsSeen, neighbor);     //Check if we've seen the current neighbor
            if (seenResult == -1)                           //If we have NOT seen the current neighbor
            {
                if (neighbor == end)                        //If the current neighbor is the end of the ladder
                {
                    wordsSeen.push_back(neighbor);          //Insert the neighbor into wordsSeen
                    predecessor.push_back(QFront);          //Insert QFront into predecessors

                    ladder.push_back(end);                  //Insert the 'end' string into the ladder
                    std:: string lastInsert = end;          //Remember the last word inserted into the ladder

                    while (!predecessor.empty())
                    {
                        std::string pred = predecessor.back();  //Get the last element in the list
                        predecessor.pop_back();                 //Remove the element from the list
                        std::string word = ladder[0];           //Get the top element in the ladder

                        if (pred.empty())                        //If we have reached the first empty predecessor inserted
                            break;                              //Then break out of the loop
                        else                                    //Else it's NOT an empty string
                        {
                            //We want to check if the last predecessor is a predecessor to our 'str'
                            std::vector <std::string> tempLadder = ladder;
                            tempLadder.insert(tempLadder.begin(), pred);
                            if (isWordLadder(tempLadder))
                                ladder = tempLadder;
                            else
                                continue;
                        }   //End of else, if it's not an empty string
                    }   //End of while-loop
                    return ladder;                          //Return the final ladder
                }   //End of the current neighbor is the end of the ladder
                else                                        //Else the word is not the 'end' of the ladder
                {                                           //We need to insert it at least to the wordsSeen
                    predecessor.push_back(QFront);          //Insert current QFront to the list of predecessors
                    wordsSeen.push_back(neighbor);          //Insert neighbor to the list of wordsSeen
                    wordsSeen.push_back(QFront);            //Insert QFront to the list of wordSeen
                    queue.push_back(neighbor);              //Insert current neighbor to the queue
                }   //End of else, if the word is not the 'end' of the ladder
            }   //End of if we have NOT seen the current neighbor
            else                                            //Else we have seen the current neighbor before
                continue;                                   //We just continue to the next string in the queuea
        }   //End of for-loop, looping through each element in neighbors set
    }   //End of while-loop, loop until the queue is empty
    return ladder;                                          //Return empty ladder
}   //End of getMinLadder method

void WordLadder::displayResult(std::vector<std::string> sequence)
{
   if (sequence.empty())    //If the sequence vector is empty
       std::cout << "Word Ladder is empty - No Solution" << std::endl;
   else                     //Else the sequence vector is NOT empty
   {
       std::cout << "A Shortest Word Ladder is: ";
       //Output each value of the sequence
       for (const auto & S : sequence)
           std::cout << S << " ";
   }    //End of else, if the sequence vector is not empty
}   //End of displayResult method

int WordLadder::getWordCount()
{
    /* getWordCount public method, parameter(s): None
     * Objective: Return the size of the global set variable, lexicon
     * */

    return lexicon.size();
}   //End of getWordCount

int WordLadder::getHammingDistance(std::string str1, std::string str2)
{
    /* getHammingDistance private method, parameter(s): string <str1>, string <str2>
     * Objective: Return the total hamming distance of the given strings
     * Notes:
     *  - If the length of the two strings are not the same then the method returns -1
     *  - Hamming Distance is the number of position which the corresponding symbol is different
     * */

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

int WordLadder::findInVector(std::vector<std::string> vec, std::string word)
{
    /* findInVector private method, parameter(s): vector (string) <vec>, string <word>
     * Objective: Search string in vector, return index location of the string in the vector
     * Notes:
     *  - If string is not found then return -1
     * */

    for (int index = 0; index < vec.size(); index++)
    {
        if (vec[index] == word)
            return index;
    }   //End of for-loop
    return -1;
}   //End of findInVector method

std::set<std::string> WordLadder::getNeighbors(std::string word)
{
    std::set<std::string> neighbors;                    //Initiate an empty set of strings called neighbors
    for (const auto& elem: lexicon)                     //Loop through each element in our dictionary, lexicon
    {
        std::string str = elem;
        int hamDist = getHammingDistance(elem, word);   //Get the hamming distance between the two words
        if (hamDist == 1)                               //If the distance is 1
        {
            neighbors.insert(str);                      //Then we insert it to our neighbor set
        }
        else                                            //Else the distance is not 1
            continue;                                   //We continue through the loop
    }   //End of for-loop

    return neighbors;                                   //Return the final list of neighbors
}   //End of getNeighbors method

bool WordLadder::isWord(std::string str)
{
    /* isWord private method, parameter(s): string <str>
     * Objective: Check if the given string is part of the lexicon (dictionary)
     * Notes:
     *  - Return true if it's in the lexicon, otherwise return false
     * */

    return lexicon.find(str) != lexicon.end();

}   //End of isWord

bool WordLadder::isWordLadder(std::vector<std::string> sequence)
{

    for (int i = 0; i < sequence.size(); i++)
    {
        if (i == sequence.size()-1)   //If we reached the last element
            break;                  //Then we leave the loop as there is nothing to compare anymore
        else                        //Else are not in the last element of the vector sequence
        {
            std::string word = sequence[i];         //Save the current element of the sequence as variable word
            std::string nextWord = sequence[i+1];   //Save the next word in sequence as variable nextWord
            std::set <std::string> neighbors = getNeighbors(word);  //Get all neighbors for our current word

            //Check if the neighbors set contains the 'nextWord' in it
            if (neighbors.find(nextWord) != neighbors.end())    //If 'nextWord' is in the neighbors set
                continue;                                       //Continue to the next element in the sequence set
            else                                                //Else 'nextWord' is NOT in the neighbors set
                return false;                                   //Return false, this means this is not a valid ladder
        }   //End of else
    }   //End of for-loop
    //If we get here then we got to the last word in the sequence and we never returned false
    return true;
}   //End of isWordLadder