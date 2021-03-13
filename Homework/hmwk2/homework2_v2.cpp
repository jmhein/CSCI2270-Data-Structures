// CSCI 2270 Fall 2019
// Author: Jeremy Hein

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct wordItem
{
  string word;
  int count;
};

// Initialize functions
void getStopWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void swap_by_pointers(wordItem *n1, wordItem *n2);
void printNext10(wordItem uniqueWords[], int n, int totalNumWords);
void resize(wordItem *&arrayPtr, int &capacity, int numEntries);

int main (int argc, char *argv[])
{
  if (argc != 4)
	{
    cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
	}
  else
  {
    int n = atoi(argv[1]);
    int capacity = 100;
    wordItem *arrayPtr;
    arrayPtr = new wordItem[capacity];
    string stopWords[50];
    getStopWords(argv[3], stopWords);
    int arrayDouble = 0;  // counter for number of times array has doubled
    int numEntries = 0;
    ifstream myfile; // create input stream
    string line = ""; // initializ line variable
    string word = "";
    int flag = -1;
    myfile.open(argv[2]); //open my input file
    if (myfile.is_open()) // check if file opened successfully
    {
       while(getline(myfile, line)) // while getline function returns true
       {
         stringstream ss(line);
         while(getline(ss, word, ' '))
         {
           if (isStopWord(word, stopWords) == false)
           {
             if (numEntries == 0)
             {
               arrayPtr[numEntries].word = word;
               numEntries++;
             }
             else
             {
               for (int i = 0; i < numEntries; i++)
               {
                 if (arrayPtr[i].word == word)
                 {
                   arrayPtr[i].count++;
                   flag = i;
                 }
               }
               if (flag < 0)
               {
                 if (numEntries == capacity)
                 {
                   resize(arrayPtr, capacity, numEntries);
                   arrayPtr[numEntries].word = word;
                   arrayPtr[numEntries].count = 1;
                   numEntries++;
                   arrayDouble++;
                 }
                 else
                 {
                   arrayPtr[numEntries].word = word;
                   arrayPtr[numEntries].count = 1;
                   numEntries++;
                 }
               }
             }
             flag = -1; // reset flag
           }
         }
       }
     }
     myfile.close();
     arraySort(arrayPtr, numEntries);
     cout << "Array doubled: " << arrayDouble << endl;
     cout << "#" << endl;
     cout << "Unique non-common words: " << numEntries << endl;
     cout << "#" << endl;
     cout << "Total non-common words: " << getTotalNumberNonStopWords(arrayPtr, numEntries) << endl;
     cout << "#" << endl;
     cout << "Probability of next 10 words from rank " << n << endl;
     cout << "---------------------------------------" << endl;
     printNext10(arrayPtr, n, getTotalNumberNonStopWords(arrayPtr, numEntries));
  }
}

///////////////////////// FUNCTION DEFINITION FOR getStopWords //////////////////////////////////
void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  ifstream myfile; // create input stream
  string line = ""; // initializ line variable
  int index = 0; // index counter
  myfile.open(ignoreWordFileName); // open my file
  if (myfile.is_open()) // check if file opened successfully
  {
     while(getline(myfile, line)) // while getline function returns true
     {
         if (line != "") // if line is not empty
         {
           ignoreWords[index] = line; // add line to array at index
           index++; // increment index
         }
     }
  }
  else // if file did not open successfully
  {
      cout << "Failed to open " << ignoreWordFileName << endl;
  }
  myfile.close(); // close my file
}

///////////////////////// FUNCTION DEFINITION FOR isStopWord //////////////////////////////////////////////
bool isStopWord(string word, string ignoreWords[])
{
  int flag = -1; // int tracker
  for (int i = 0; i < 50; i++)
  {
    if (word == ignoreWords[i]) // check if word is in array
      {
        flag = i; // if true, set flag equal to index i
      }
  }
  if (flag >= 0) // if flag is set
  {
    return true; // word is in array
  }
  else
  {
    return false; // if not, word is not in array
  }
}

///////////////////////// FUNCTION DEFINITION FOR getTotalNumberNonStopWords //////////////////////////////////
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
  int totalWords = 0; // counter variable
  for (int i = 0; i <  length; i++)
  {
    totalWords = totalWords + uniqueWords[i].count; // add count at index i to total
  }
  return totalWords; // return total
}

///////////////////////// FUNCTION DEFINITION FOR arraySort ///////////////////////////////////////////////////
void arraySort(wordItem uniqueWords[], int length)
{
  for (int i = 0; i < length; i++) // starting at index 0
  {
    for (int k = i; k < length; k++) // nested loop starting at index i
    {
      if (uniqueWords[k].count > uniqueWords[i].count) // if there is an element with higher count than index i
      {
        swap_by_pointers(&uniqueWords[i], &uniqueWords[k]); // swap the two elements
      }
    }
  }
}

///////////////////////// FUNCTION DEFINITION FOR swap by pointers ////////////////////////////////////////
void swap_by_pointers(wordItem *n1, wordItem *n2)
{
  wordItem temp; // temp variable
  temp = *n1; // temp = first element
  *n1 = *n2; // first element equals second element
  *n2 = temp; // second element equals first element (thus the swap)
}

///////////////////////// FUNCTION DEFINITION FOR printNext10 /////////////////////////////////////////////
void printNext10(wordItem uniqueWords[], int n, int totalNumWords)
{
  wordItem tempArray[10];  // temp array to store next 10 Elements
  int k = 0;
  for (int i = n; i < n + 10; i++) // pass elements from uniqueWords to tempArray
  {
    tempArray[k] = uniqueWords[i];
    k++;
  }
  arraySort(tempArray, 10); // sort tempArray
  for (int i = 0; i < 10; i++)
  {
    cout << fixed << setprecision(4); // set precision to 4 decimal places
    cout << (float) tempArray[i].count / totalNumWords << " - " << tempArray[i].word << endl; // print
  }
}


void resize(wordItem *&arrayPtr, int &capacity, int numEntries)
{
	int newCapacity = capacity * 2;
	wordItem *newArray = new wordItem[newCapacity];
	for (int i = 0; i < numEntries; i++)
	{
		newArray[i] = arrayPtr[i];
	}
	delete [] arrayPtr;
	arrayPtr = newArray;
	capacity = newCapacity;
}
