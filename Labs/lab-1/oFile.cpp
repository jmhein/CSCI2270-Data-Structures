#include <iostream>
#include <fstream>
using namespace std;

int main ()
{
  //File writing
  //Creates instance of ofstream and opens the file
  ofstream oFile ("filename.txt");
  oFile << "Inserted this text into the filename.txt";
  //close the file file
  oFile.colse();
}
