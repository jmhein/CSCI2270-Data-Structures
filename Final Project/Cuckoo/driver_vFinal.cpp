// Driver program
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <vector>
#include "hash.hpp"
using namespace std;
#define TABLE_SIZE 10009

void displayMenu();

int main (int argc, char *argv[])
{
  srand(time(NULL));
  if (argc != 2)
  {
  cout << "Usage: test <inputfilename.txt>" << endl;
  }
  HashTable ht(TABLE_SIZE); // create instance of hash table
  ifstream myfile; // create input stream
  string line = ""; // initializ line variable
  LARGE_INTEGER frequency;
  LARGE_INTEGER startTime, endTime, totalTime;
  string choice;
  while (choice != "7")
  {
    displayMenu();
    getline(cin, choice); // take a menu opton
    int menuChoice = stoi(choice); // convert the `choice` to an integer
    switch (menuChoice)
    {
      case 1:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 0.1) // while getline function returns true && load factor is less than 0.1
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Size of hash table: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 0.1
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 0.1: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 0.1
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getNumElements());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 0.1: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 0.1
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 0.1: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
      break;
      }
      case 2:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 0.2) // while getline function returns true && load factor is less than 0.2
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Size of hash table: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 0.2
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 0.2: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 0.2
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getNumElements());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 0.2: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 0.2
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 0.2: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
      break;
      }
      case 3:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 0.5) // while getline function returns true && load factor is less than 0.5
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              cout << ht.getTableSize() << endl;
              cout << myKeys.size() << endl;
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Table Size: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 0.5
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 0.5: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 0.5
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getTableSize());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 0.5: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 0.5
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 0.5: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
      break;
      }
      case 4:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 0.7) // while getline function returns true && load factor is less than 0.7
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              cout << ht.getTableSize() << endl;
              cout << myKeys.size() << endl;
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Size of hash table: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 0.7
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 0.1: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 0.7
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getNumElements());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 0.7: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 0.7
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 0.7: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
      break;
      }
      case 5:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 0.9) // while getline function returns true && load factor is less than 0.9
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              cout << ht.getTableSize() << endl;
              cout << myKeys.size() << endl;
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Size of hash table: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 0.9
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 0.9: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 0.9
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getNumElements());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 0.9: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 0.9
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 0.9: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
      break;
      }
      case 6:
      {
        vector<int> myKeys;
        myfile.open(argv[1]); //open my input file
        if (myfile.is_open()) // check if file opened successfully
        {
          while(getline(myfile, line, ',') && ht.getLoadFactor() < 1.0) // while getline function returns true && load factor is less than 1.0
          {
            if (ht.insertItem(stoi(line), ht.getTableSize()) == true) // if we can insert the item
            {
              if (ht.searchItem(stoi(line)) == true)
              {
                myKeys.push_back(stoi(line)); // add to my keys
              }
            }
            else // if not, rehash
            {
              ht.rehash(myKeys);
            }
          }
        }
        else
        {
          cout << "File did not open successfully" << endl;
        }
        myfile.close();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Load factor of hash table: " << ht.getLoadFactor() << endl;
        cout << "Size of hash table: " << ht.getTableSize() << endl;
        cout << "Number of times rehashed: " << ht.getRehashes() << endl;
        cout << endl;

        // generate randoms (no duplicates) within hash table
        int randoms[100];
        for (int i = 0; i < 100; i++)
        {
          bool check; //variable to check or number is already used
          int n; //variable to store the number in
          do
          {
          n = myKeys[rand() % ht.getNumElements()];
          check = true; //check or number is already used:
          for (int j = 0; j < i; j++)
              if (n == randoms[j]) //if number is already used
              {
                  check = false; //set check to false
                  break; //no need to check the other elements of value[]
              }
          } while (!check); //loop until new, unique number is found
          randoms[i] = n; //store the generated number in the array
        }

        // time for deleting 100 elements with load factor of 1.0
        cout << "Deleting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.deleteItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to delete 100 elements with load factor of 1.0: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for inserting 100 elements with load factor of 1.0
        cout << "Inserting 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.insertItem(randoms[i], ht.getNumElements());
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to insert 100 elements with load factor of 1.0: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        // time for searching 100 elements with load factor of 1.0
        cout << "Searching for 100 elements" << endl;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&startTime);
        for (int i = 0; i < 100; i++)
        {
          ht.searchItem(randoms[i]);
        }
        QueryPerformanceCounter(&endTime);
        totalTime.QuadPart = ((endTime.QuadPart - startTime.QuadPart) * 1e6) / frequency.QuadPart;
        //1e9 is nanoseconds, 1e6 microseconds, 1e3 is milliseconds
        //the multiplier is what changes the form of measurement, which are listed above.
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << "Time to search 100 elements with load factor of 1.0: " << endl;
        cout << "Total microseconds: " << totalTime.QuadPart << endl;
        cout << "Avg. microseconds: " << totalTime.QuadPart/100.0 << endl;
        cout << endl;

        cout << "Deleting all elements" << endl;
        ht.deleteAllNodes();
        cout << "Items in hash table: " << ht.getNumElements() << endl;
        cout << endl;
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
  cout << "======Main Menu======" << endl;
  cout << "1. Time with load factor of 0.1" << endl;
  cout << "2. Time with load factor of 0.2" << endl;
  cout << "3. Time with load factor of 0.5" << endl;
  cout << "4. Time with load factor of 0.7" << endl;
  cout << "5. Time with load factor of 0.9" << endl;
  cout << "6. Time with load factor of 1.0" << endl;
  cout << "7. Quit" << endl;
}
