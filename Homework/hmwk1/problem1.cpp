// CSCI 2270 Fall 2019
// Author: Jeremy Hein

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Initialize "insertIntoSortedArray" function with stated arguements
int insertIntoSortedArray(int myArray[], int numEntries, int newValue);

int main (int argc, char *argv[])
{
  int sortedArray[100]; // sorted array size 100, per directions
  int numEntries = 0; // counter for size of sorted array
  string fileName = argv[1]; // set filename equal to command line input
  ifstream myfile; // create input stream
  string line = ""; // initializ line variable
  myfile.open(fileName); //open my file
  if (myfile.is_open()) // check if file opened successfully
  {
     while(getline(myfile, line)) // while getline function returns true
     {
         if (line != "") // if line is not empty
         {
           insertIntoSortedArray(sortedArray,numEntries,stoi(line)); // insert line into sorted array
           numEntries++;
         }
         for (int i = 0; i < numEntries; i++)
         {
           if (numEntries == 1)
           {
             cout << sortedArray[i];
           }
           else
           {
             if (i < numEntries - 1)
             {
               cout << sortedArray[i] << ",";
             }
             if (i == numEntries - 1)
             {
               cout << sortedArray[i];
             }
           }
         }
         cout << endl;
     }
  }
  else
  {
      cout << "Failed to open the file." << endl;
  }
}

// function definition
int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
  int tempArray[100];
  int index = -1;
  int count = numEntries;
  if (numEntries == 0)
  {
    myArray[0] = newValue;
  }
  for (int i = 0; i < numEntries; i++) // copy elements from original array intro temp
  {
    tempArray[i] = myArray[i]; // pass my array elements into tempArray
  }
  for (int i = 0; i < numEntries; i++) // find index # to add new element
  {
    if (newValue <= myArray[0]) // check if lowest value
    {
      myArray[0] = newValue;
      index = 0;
    }
    else if (newValue > myArray[numEntries - 1])
    {
      myArray[numEntries] = newValue;
    }
    else if (newValue > myArray[i] && newValue <= myArray[i + 1] ) // checks where to insert new values
    {
      myArray[i + 1] = newValue;
      index = i + 1;
    }
  }
  if (index >= 0)
  {
    for (int i = numEntries; i > index; i--)
    {
      myArray[i] = tempArray[i - 1];
    }
  }
  count++;
  return count;
}
