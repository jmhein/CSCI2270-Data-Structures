#include "RPNCalculator.hpp"
#include <iostream>

using namespace std;

RPNCalculator::RPNCalculator() // constructor
{
  stackHead = NULL; // set stackHead to null
}

RPNCalculator::~RPNCalculator() // destructor
{
  while(!isEmpty())
      pop();
}

bool RPNCalculator::isEmpty()
{
  return (stackHead == NULL);
}

void RPNCalculator::push(float num) // push
{
  Operand* nn = new Operand; // create new node
  nn->next = stackHead; // point to current stackHead
  nn->number = num; // set number to input parameters
  stackHead = nn; // reset stack head
}

void RPNCalculator::pop() // pop
{
  if(!isEmpty()) // check that list is not empty
  {
    Operand* temp = stackHead; // set temp to stackHead
    stackHead = stackHead->next; // reset stackHead
    delete temp; // delete the node
  }
  else
  {
    cout << "Stack empty, cannot pop an item." << endl; // print per directions if empty
  }
}

Operand* RPNCalculator::peek()
{
  if (isEmpty()) // check if empty
  {
    cout <<  "Stack empty, cannot peek." << endl; // print per directions
    return NULL; // return null
  }
  else
  {
    return getStackHead(); // return stack head (top)
  }
}

bool RPNCalculator::compute(std::string symbol)
{
  float x;
  float y;
  if (symbol != "+" && symbol != "*") // check that symbol is valid
  {
    cout << "err: invalid operation" << endl;
    return false;
  }
  if (!isEmpty()) // if list isn't empty
  {
    x = peek()->number; // x = top
    pop();
    if (!isEmpty()) // if list is still not empty
    {
      y = peek()->number; // y = top
      pop();
    }
    else
    {
      push(x); // push x back
      cout << "err: not enough operands" << endl; // print error
      return false;
    }
  }
  else
  {
    cout << "err: not enough operands" << endl;
    return false;
  }
  if (symbol == "+")
  {
    push(x+y);
    return true;
  }
  else
  {
    push(x*y);
    return true;
  }
}
