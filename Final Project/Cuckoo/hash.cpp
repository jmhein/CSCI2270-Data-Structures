#include <iostream>
#include <cmath>
#include <vector>
#include "hash.hpp"

using namespace std;

//given a number n, determine if it is prime
bool isPrime(int n)
{
  for (int i = 2; i <= n/2; i++) //loop from 2 to n/2 to check for factors
  {
    if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
        return false;
  }
  return true;
}

//given a number n, find the next closest prime number above n
int findNextPrime(int n)
{
  int nextPrime = n;
  bool found = false;
  while (!found) //loop continuously until isPrime returns true for a number above n
  {
    nextPrime++;
    if (isPrime(nextPrime))
        found = true;
  }
  return nextPrime;
}

node* HashTable::createNode(int key) // helper function to create new node
{
  node* nw = new node;
  nw->key = key;
  return nw;
}

HashTable::HashTable(int bsize) // construct 2D table
{
  numElements = 0;
  rehashes = 0;
  this->tableSize = bsize;
  table = new node**[tableSize];
  for (int i = 0; i < bsize; i++)
  {
    table[i] = new node*[2];
  }
  for (int i = 0; i < bsize; i++) // column 1 refers to table 1 - column 2 refers to table 2
  {
    for (int j = 0; j < 2; j++)
    {
      table[i][j] = nullptr;
    }
  }
}

// function to calculate hash function h(x)
unsigned int HashTable::hashFunctionH(int key)
{
  return (key % tableSize);
}

// function to calculate hash function h'(x)
unsigned int HashTable::hashFunctionHPrime(int key)
{
  double x = key / tableSize;
  double f = floor(x);
  return (int)f % tableSize;
}

//function to search
bool HashTable::searchItem(int key)
{
  int indexH = hashFunctionH(key); // run key through first hash function
  int indexHPrime = hashFunctionHPrime(key); // run key through first hash function
  if (table[indexH][0] == NULL) // first check it null
  {
    return false;
  }
  else if (table[indexH][0]->key == key) // then check key at first location
  {
    return true;
  }
  else if (table[indexHPrime][1] == NULL)
  {
    return false;
  }
  else if (table[indexHPrime][1]->key == key)
  {
    return true;
  }
}

void HashTable::rehash(vector<int> keys)
{
  int cap = tableSize; // old capacity
  int newCap = findNextPrime(cap); // new capacity
  int r = rehashes; // old number of times rehashed

  // initialize a new hash table with new capacity
  node* **newTable = new node**[newCap];
  for (int i = 0; i < newCap; i++)
  {
    newTable[i] = new node*[2];
  }
  for (int i = 0; i < newCap; i++) // column 1 refers to table 1 - column 2 refers to table 2
  {
    for (int j = 0; j < 2; j++)
    {
      newTable[i][j] = nullptr;
    }
  }

  //delete the old table
  for (int i = 0; i < cap; i++)
    delete[] table[i];
  delete[] table;

  // reset table
  table = newTable;
  tableSize = newCap;
  numElements = 0;
  rehashes = r + 1;

  // insert items back into table
  for (int i = 0; i < keys.size(); i++)
  {
    node* newNode = createNode(keys[i]); // create a new node to be inserted
    int indexH = hashFunctionH(keys[i]); // run key through first hash function
    int indexHPrime = hashFunctionHPrime(keys[i]); // run key through second hash function
    int displacements = 0; // record number of items displaced
    if (table[indexH][0] == NULL || table[indexH][0]->key == -1) // if first index is available
    {
      table[indexH][0] = newNode; // set node equal to first
      numElements++;
    }
    else if (table[indexHPrime][1] == NULL || table[indexHPrime][1]->key == -1) // if second index is available
    {
      table[indexHPrime][1] = newNode; // set node equal to second
      numElements++;
    }
    else // if neither slot is available
    {
      node* temp = table[indexH][0]; // store element in first location
      node* d = NULL;
      table[indexH][0] = newNode; // set newNode to first location
      numElements++; // increment numElements
      while (displacements < tableSize + 1)
      {
        displacements++; // track number of times we have displaced an element
        indexHPrime = hashFunctionHPrime(temp->key); // reset alternate location
        if (table[indexHPrime][1] == NULL || table[indexHPrime][1]->key == -1) // if alternate slot empty
        {
          table[indexHPrime][1] = temp; // set the alternate location to temp
          break;
        }
        else // if alternate slot is not empty
        {
          d = table[indexHPrime][1]; // store item in alternate slot
          table[indexHPrime][1] = temp; // place temp into alternate slot
          temp = d; // reset temp to displaced item
          indexH = hashFunctionH(temp->key); // reset alternate location
          if (table[indexH][0] == NULL || table[indexH][0]->key == -1)
          {
            table[indexH][0] = temp;
            break;
          }
        }
      }
    }
  }
}

//function to insert
bool HashTable::insertItem(int key, int n)
{
  if (searchItem(key) == false) // check that key is not duplicate
  {
    node* newNode = createNode(key); // create a new node to be inserted
    int indexH = hashFunctionH(key); // run key through first hash function
    int indexHPrime = hashFunctionHPrime(key); // run key through second hash function
    int displacements = 0; // record number of items displaced
    if (table[indexH][0] == NULL || table[indexH][0]->key == -1) // if first index is available
    {
      table[indexH][0] = newNode; // set node equal to first
      numElements++;
      return true;
    }
    else if (table[indexHPrime][1] == NULL || table[indexHPrime][1]->key == -1) // if second index is available
    {
      table[indexHPrime][1] = newNode; // set node equal to second
      numElements++;
      return true;
    }
    else // if neither slot is available
    {
      node* temp = table[indexH][0]; // store element in first location
      node* d = NULL;
      table[indexH][0] = newNode; // set newNode to first location
      numElements++; // increment numElements
      while (displacements < n + 1)
      {
        displacements++; // track number of times we have displaced an element
        indexHPrime = hashFunctionHPrime(temp->key); // reset alternate location
        if (table[indexHPrime][1] == NULL || table[indexHPrime][1]->key == -1) // if alternate slot empty
        {
          table[indexHPrime][1] = temp; // set the alternate location to temp
          return true;
        }
        else // if alternate slot is not empty
        {
          d = table[indexHPrime][1]; // store item in alternate slot
          table[indexHPrime][1] = temp; // place temp into alternate slot
          temp = d; // reset temp to displaced item
          indexH = hashFunctionH(temp->key); // reset alternate location
          if (table[indexH][0] == NULL || table[indexH][0]->key == -1)
          {
            table[indexH][0] = temp;
            return true;
          }
        }
      }
      if (displacements >= n+1)
      {
        return false;
      }
    }
  }
}

// function to delete
void HashTable::deleteItem(int key)
{
  if (searchItem(key) == true)
  {
    int indexH = hashFunctionH(key); // run key through first hash function
    int indexHPrime = hashFunctionHPrime(key); // run key through first hash function
    if (table[indexH][0]->key == key) // check first location
    {
      table[indexH][0]->key = -1;
      numElements--;
    }
    else if (table[indexHPrime][1]->key == key) // check second location
    {
      table[indexHPrime][1]->key = -1;
      numElements--;
    }
    else // if key is not in one of the possible locations
    {
      cout << "You shouldn't be seeing this" << endl;
    }
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

// funtion to return numer of times rehashed
int HashTable::getRehashes()
{
  return rehashes;
}

// funtion to return numer of table size
int HashTable::getTableSize()
{
  return tableSize;
}

// function to calculate load factor
double HashTable::getLoadFactor()
{
  double factor = numElements / (double)tableSize;
  return factor;
}

void HashTable::deleteAllNodes()
{
  int originalSize = 10009; // TO BE UPDATED

  // initialize a new hash table with original table size
  node* **newTable = new node**[originalSize];
  for (int i = 0; i < originalSize; i++)
  {
    newTable[i] = new node*[2];
  }
  for (int i = 0; i < originalSize; i++) // column 1 refers to table 1 - column 2 refers to table 2
  {
    for (int j = 0; j < 2; j++)
    {
      newTable[i][j] = nullptr;
    }
  }

  //delete the old table
  for (int i = 0; i < tableSize; i++)
    delete[] table[i];
  delete[] table;

  // reset table
  table = newTable;
  tableSize = originalSize;
  numElements = 0;
  rehashes = 0;
}

// function to display hash table
void HashTable::printTable()
{
  for (int i = 0; i < tableSize; i++)
  {
    cout << i << "|| ";
    for (int j = 0; j < 2; j++)
    {
      node* curr = table[i][j];
      if (curr != NULL && j == 0)
      {
        cout << curr->key << "   || ";
      }
      else if (curr == NULL && j == 0)
      {
        cout << "empty" << "   || ";
      }
      else if (curr != NULL && j == 1)
      {
        cout << curr->key;
      }
      else
      {
        cout << "empty";
      }
    }
    cout << endl;
  }
}
