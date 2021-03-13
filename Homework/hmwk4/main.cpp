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
    while (choice != "8")
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

        case 6:
        {
          string c;
          cout << "Enter the count of values to be rotated:" << endl;
          getline(cin, c);
          CountryNet.rotateNetwork(stoi(c));
          CountryNet.printPath();
          break;
        }

        case 7:
        {
          cout << "Network before deletion" << endl;
          CountryNet.printPath();
          CountryNet.deleteEntireNetwork();
          cout << "Network after deletion" << endl;
          CountryNet.printPath();
          break;
        }

        case 8:
        {
          cout << "Quitting... cleaning up path: " << endl;
          CountryNet.printPath();
          CountryNet.deleteEntireNetwork();
          if (CountryNet.isEmpty() == true)
          {
            cout << "Path cleaned" << endl;
          }
          else
          {
            cout << "Error: Path NOT cleaned" << endl;
          }
          break;
        }
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
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
