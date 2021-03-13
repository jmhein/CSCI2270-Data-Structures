#include <iostream>
#include "hash.hpp"

using namespace std;

node* HashTable::createNode(int key) // create node
{
  node* nw = new node;
  nw->key = key;
  return nw;
}

HashTable::HashTable(int bsize) // constructor
{
  numElements = 0;
  this->tableSize = bsize;
  table = new node*[tableSize];
  for (int i = 0; i < bsize; i++)
      table[i] = nullptr;
}

// function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
  return (key % tableSize);
}

//function to search
bool HashTable::searchItem(int key)
{
  int index = hashFunction(key); // Compute the index by using the hash function
  int original = index; // store original index value
  int count = 0; // counter to track if we've cycled through the entire table
  node* curr = table[index]; // set pointer to table at index
  while (curr->key != key && count == 0) // find key in table
  {
    if (index < tableSize - 1) // if we haven't reached end of table
    {
      index++; // increment the index
      curr = table[index]; // reset curr
    }
    else // if we have reached the end of the table
    {
      index = 0; // start at the beginnning
      curr = table[index]; // reset curr
    }
    if (index == original) // if we reach our original index
    {
      count++; // flag count and exit loop
    }
  }
  if (count == 0)
  {
    return true;
  }
  else
  {
    cout << "Key not found." << endl;
    return false;
  }
}

//function to insert
void HashTable::insertItem(int key)
{
  int index = hashFunction(key); // find index using hash function
  int count = 0;
  int original = index;
  while (table[index] != NULL && table[index]->key != -1 && count == 0)
  {
    if (index < tableSize - 1)
    {
      index++;
    }
    else
    {
      index = 0;
    }
    if (index == original)
    {
      count++;
    }
  }
  if (count == 0 && table[index] == NULL) // only allocate new node if index is null
  {
    table[index] = createNode(key);
    numElements++;
  }
  else if (count == 0 && table[index]->key == -1) // if node is not null - reset key
  {
    table[index]->key = key;
    numElements++;
  }
  else
  {
    cout << "Table is full. Cannot insert." << endl;
  }
}

// function to delete
void HashTable::deleteItem(int key)
{
  if (searchItem(key)) // check that key is in table
  {
    int index = hashFunction(key); // find index using hash function
    node* curr = table[index]; //
    while (curr->key != key) // find key in table
    {
      if (index < tableSize - 1) // if we haven't reached end of table
      {
        index++; // increment the index
        curr = table[index]; // reset curr
      }
      else // if we have reached the end of the table
      {
        index = 0; // start at the beginnning
        curr = table[index]; // reset curr
      }
    }
    table[index]->key = -1; // mark as deleted but available for reuse
    numElements--; // decrease numElements
  }
  else
  {
    cout << "Key not found" << endl;
  }
}

// funtion to return numElements
int HashTable::getNumElements()
{
  return numElements;
}

// function to calculate load factor
double HashTable::getLoadFactor()
{
  double factor = numElements / (double)tableSize;
  return factor;
}

void HashTable::deleteAllNodes()
{
  for (int i = 0; i < tableSize; i++)
  {
    if (table[i] != NULL && table[i]->key != -1)
    {
      table[i]->key = -1; // mark as deleted but available for reuse
      numElements--;
    }
  }
}

// function to display hash table
void HashTable::printTable()
{
  for (int i = 0; i < tableSize; i++)
  {
    cout << i << "|| ";
    node* curr = table[i];
    if (curr != NULL)
    {
      cout << curr->key;
    }
    cout << endl;
  }
}

int HashTable::generateRandoms()
{
  int index = rand() % 10009;
  int randoms = table[index]->key;
  return randoms;
}
