// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);
    node* curr = table[index];

    //TODO: Search the list at that specific index and return the node if found
    while (curr != NULL)
    {
      if (table[index]->key == key)
      {
        return table[index];
      }
      else
      {
        curr = curr->next;
      }
    }
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        int index = hashFunction(key);
        node* newNode = createNode(key, NULL);
        // create a new node with the key and insert it in this slot's list
        if (table[index] == NULL)
        {
          table[index] = newNode;
        }
        else
        {
          newNode->next = table[index];
          table[index] = newNode;
        }
     }
    else
    {
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }
    return true;
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << "|| ";
        //TODO
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
