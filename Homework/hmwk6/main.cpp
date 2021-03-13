/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    string choice;
    CountryNetwork CountryNet; // Object representing our network of cities.
    while (choice != "5")
    {
      displayMenu();
      getline(cin, choice); // take a menu opton
      int menuChoice = stoi(choice); // convert the `choice` to an integer
      switch (menuChoice)
      {
        case 1:
        {
          CountryNet.loadDefaultSetup();
          CountryNet.printPath();
          break;
        }

        case 2:
        {
          CountryNet.printPath();
          break;
        }

        case 3:
        {
          string newCountry;
          string previous;
          cout << "Enter a new country name:" << endl;
          getline(cin, newCountry);
          cout << "Enter the previous country name (or First):" << endl;
          getline(cin, previous);
          if (previous == "First")
          {
            CountryNet.insertCountry(NULL, newCountry);
            CountryNet.printPath();
          }
          else if (CountryNet.searchNetwork(previous) == NULL)
          {
            while (CountryNet.searchNetwork(previous) == NULL)
            {
              cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
              getline(cin, previous);
              CountryNet.insertCountry(CountryNet.searchNetwork(previous), newCountry);
              CountryNet.printPath();
            }
          }
          else
          {
            CountryNet.insertCountry(CountryNet.searchNetwork(previous), newCountry);
            CountryNet.printPath();
          }
          break;
        }

        case 4:
        {
          string c;
          cout << "Enter a country name:" << endl;
          getline(cin, c);
          CountryNet.deleteCountry(c);
          CountryNet.printPath();
          break;
        }

        case 5:
        {
          CountryNet.reverseEntireNetwork();
          CountryNet.printPath();
          break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
}
