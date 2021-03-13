// CSCI 2270 Fall 2019
// Author: Jeremy Hein

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

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

int main (int argc, char *argv[])
{
  Park myParks[100]; // initilize array of Park structs
  int numEntries = 0; // counter for size of parks array
  string inFile = argv[1]; // set input filename equal to command line input
  string outFile = argv[2]; // set output filename equal to command line input
  ifstream myfile; // create input stream
  string line = ""; // initializ line variable
  string tempString = "";
  vector<string> tokens;
  myfile.open(inFile); //open my input file
  if (myfile.is_open()) // check if file opened successfully
  {
     while(getline(myfile, line)) // while getline function returns true
     {
         if (line != "") // if line is not empty
         {
           stringstream ss(line);
           while (getline(ss,tempString,','))
           {
             toekns.push_back(tempString);
             addPark(myParks,tokens[0],tokens[1],stoi(tokens[2],numEntries))
           }
           numEntries++;
         }
         /*for (int i = 0; i < numEntries; i++)
         {
           if ( ) // output file
         }*/
     }
     printList(myParks, numEntries);
  }
  else
  {
      cout << "Failed to open the file." << endl;
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
