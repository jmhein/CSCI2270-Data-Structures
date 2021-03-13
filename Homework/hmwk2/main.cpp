#include<iostream>

using namespace std;

void swap(int x, int y);

int main(void)
{
  int a = 1;
  int b = 2;
  swap(a,b);
  cout << a << ", " << b << endl;

  return 0;
}

void swap(int x, int y)
{
  int temp = x;
  x = y;
  y = temp;
}
