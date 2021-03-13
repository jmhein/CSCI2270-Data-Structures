#include <iostream>
#include "hash.hpp"

using namespace std;
#define TABLE_SIZE 10009

node* HashTable::createNode(int key, node* next)
{
  node* nw = new node;
  nw->key = key;
  nw->next = next;
  return nw;
}

HashTable::HashTable(int bsize)
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
node* HashTable::searchItem(int key)
{
  int index = hashFunction(key); //Compute the index by using the hash function
  node* curr = table[index]; // set pointer to table at index
  while (curr != NULL) // Search the list at that specific index and return the node if found
  {
    if (curr->key == key)
    {
      return table[index];
    }
    else
    {
      curr = curr->next;
    }
  }
  return curr;
}

//function to insert
void HashTable::insertItem(int key)
{
  int index = hashFunction(key); // find index using hash function
  node* newNode = createNode(key, NULL); // create a new node with the key and insert it in this slot's list
  if (table[index] == NULL) // if there is no value at index
  {
    table[index] = newNode; // set new node to that index
    numElements++;
  }
  else
  {
    newNode->next = table[index]; // point new node to the current head
    table[index] = newNode; // set new node to head at index
    numElements++;
  }
}

// function to delete
void HashTable::deleteItem(int key)
{
  if (searchItem(key)) // check that key is in table
  {
    int index = hashFunction(key); // find index using hash function
    node* pres = table[index]; // set pres to head
    node* prev = NULL; // set prev to NULL
    node* temp = NULL;
    while (pres != NULL && pres->key != key)
    {
      prev = pres;
      pres = pres->next;
    }
    if (prev == NULL)
    {
      temp = pres; // set temp to head
      table[index] = pres->next; // set index to null
      delete temp; // delete
      numElements--;
    }
    else
    {
      prev->next = pres->next;
      delete pres;
      numElements--;
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

// function to calculate load factor
double HashTable::getLoadFactor()
{
  double factor = numElements / (double)tableSize;
  return factor;
}

void HashTable::deleteAllNodes()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    node* ptr = table[i]; // set pointer at head
    node* temp = NULL;
    while (ptr != NULL)
    {
      temp = ptr;
      table[i] = ptr->next;
      ptr = ptr->next;
      delete temp;
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
    while (curr != NULL)
    {
      cout << curr->key;
      if (curr->next != NULL)
      {
        cout << " --> ";
      }
      curr = curr->next;
    }
    cout << endl;
  }
}
