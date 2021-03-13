/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[])
{
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
        string n;
        string m;
        cout << "Enter name of the country to receive the message:" << endl;
        getline(cin, n);
        cout << "Enter the message to send:" << endl;
        getline(cin, m);
        cout << endl;
        CountryNet.transmitMsg(n, m);
        break;

      }

      case 4:
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

      case 5:
      {
        cout << "Quitting..." << endl;
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
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
