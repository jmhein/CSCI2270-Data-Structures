// CSCI 2270 Fall 2019
// Author: Jeremy Hein

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Park
{
  string parkname;
  string state;
  int area;
};

// Initialize functions
void addPark(Park parks[], string parkname, string state, int area, int length);


int main (int argc, char *argv[])
{

}

// function definition
void addPark(Park parks[], string parkname, string state, int area, int length)
{
  Park localPark;
  localPark.parkname = parkname;
  localPark.state = state;
  localPark.area = area;
  parks[length] = localPark;
}
