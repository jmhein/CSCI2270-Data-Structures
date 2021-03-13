// CSCI 2270 Fall 2019
// Author: Jeremy Hein

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

struct Park
{
  string parkname;
  string state;
  int area;
};

// Initialize functions
void addPark(Park parks[], string parkname, string state, int area, int length);
void printList(const Park parks[], int length);
int split(string sentence, char delim, string mySplits[], int length);

int main (int argc, char *argv[])
{
  Park myParks[100]; // initilize array of Park structs
  int numEntries = 0; // counter for size of parks array
  string inFile = argv[1]; // set input filename equal to command line input
  string outFile = argv[2]; // set output filename equal to command line input
  string minimum_area = argv[3];
  ifstream myfile; // create input stream
  ofstream output;
  string line = ""; // initializ line variable
  string tempString = "";
  string temp_array[10];
  myfile.open(inFile); //open my input file
  if (myfile.is_open()) // check if file opened successfully
  {
     while(getline(myfile, line)) // while getline function returns true
     {
         if (line != "") // if line is not empty
         {
           split (line, ',', temp_array, 3);
           {
             addPark(myParks,temp_array[0],temp_array[1],stoi(temp_array[2]),numEntries);
           }
           numEntries++;
         }
     }
     myfile.close();
     printList(myParks, numEntries);
  }
  else
  {
      cout << "Failed to open the file." << endl;
  }
  output.open(outFile);
  if (output.is_open())
  {
    for (int i = 0; i < numEntries; i++)
    {
      if (myParks[i].area > stoi(minimum_area))
      {
        output << myParks[i].parkname << "," << myParks[i].state << "," << myParks[i].area << endl;
      }
    }
    output.close();
  }
}

// function definition for addPark
void addPark(Park parks[], string parkname, string state, int area, int length)
{
  Park localPark;
  localPark.parkname = parkname;
  localPark.state = state;
  localPark.area = area;
  parks[length] = localPark;
}

// function definition for printList
void printList(const Park parks[], int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << endl;
  }
}

int split(string sentence, char delim, string mySplits[], int length) // Write function below
{
    int count = 0; // initilize count variable
    string word = ""; // temp string to hold word
    sentence = sentence + delim; // adds delim to end of string in order to pick up last word in sentence
    for (int i = 0; i < sentence.length(); i++)
    {
        if (count < length)
        {
            if (sentence[i] == delim) // if character at index i = delim
            {
                if (word.length() > 0) // check if word length is greater than 0
                {
                    mySplits[count] = word; // if true, print word
                    count ++; // count plus 1
                }
                word = "";
            }
            else
            {
            word = word + sentence[i]; // if character is not = to delim, word = previous characters + character at index #
            }
        }
        else
        {
            return -1;
        }
    }
}
