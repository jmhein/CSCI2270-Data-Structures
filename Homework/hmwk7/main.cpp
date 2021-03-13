
#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
// you may include more libraries as needed

using namespace std;

void displayMenu();
int split(string sentence, char delim, string mySplits[], int length);

int main(int argc, char* argv[])
{

  string inFile = argv[1];
  MovieTree myMovies;
  string temp_array[4];
  ifstream myfile; // create input stream
  string line = ""; // initializ line variable
  myfile.open(inFile); //open my input file
  if (myfile.is_open()) // check if file opened successfully
  {
     while(getline(myfile, line)) // while getline function returns true
     {
         if (line != "") // if line is not empty
         {
           split (line, ',', temp_array, 4);
           {
             myMovies.addMovie(stoi(temp_array[0]), temp_array[1], stoi(temp_array[2]), stoi(temp_array[3]));
           }
         }
     }
     myfile.close();
   }
   
   string choice;
  while (choice != "3")
  {
    displayMenu();
    getline(cin, choice); // take a menu opton
    menuChoice = stoi(choice); // convert the `choice` to an integer
    switch (menuChoice)
    {
      case 1:
      {
        myMovies.printMovieInventory();
        break;
      }
      case 2:
      {
        string title;
        cout << "Enter a movie title:" << endl;
        getline(cin, title); // take a menu opton
        myMovies.deleteMovie(title);
        break;
      }
      case 3:
      {
        cout << "Goodbye!" << endl;
        break;
      }
  }

}
  return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;
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
