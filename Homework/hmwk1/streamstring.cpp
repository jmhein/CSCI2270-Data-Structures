#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string input = "abc,def,ghi";
istringstream ss(input);
string token;
int main (int argc, char *argv[])
{
  while(getline(ss, token, ',')) {
      cout << token << '\n';
  }
}
