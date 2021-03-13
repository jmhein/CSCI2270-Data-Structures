#include <iostream>
#include <cmath>
#include "hash.hpp"

using namespace std;
#define COUNT 10
#define TABLE_SIZE 10009

void printBST(node *currNode, int space)
{
    if (currNode == NULL)
    {
      return;
    }
    space += COUNT; // Increase distance between levels
    printBST(currNode->right, space); // Process right child first

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);
    printBST(currNode->left, space); // Process left child
}

node* addNodeHelper(node* currNode, int key, node* add) // standared add node to BST
{
    if(currNode == NULL)
    {
        return add;
    }
    else if(currNode->key < key)
    {
        currNode->right = addNodeHelper(currNode->right, key, add);
    }
    else if(currNode->key > key)
    {
        currNode->left = addNodeHelper(currNode->left, key, add);
    }
    return currNode;
}

node* searchItemHelper(node* currNode, int key) // standard search in BST
{
  if(currNode == NULL)
      return NULL;

  if(currNode->key == key)
      return currNode;

  if(currNode->key > key)
      return searchItemHelper(currNode->left, key);

  return searchItemHelper(currNode->right, key);
}

// get min value for delete function
node* getMinValueNode (node* currNode)
{
  if(currNode->left == NULL)
  {
    return currNode;
  }
  return getMinValueNode(currNode->left);
}

node* deleteItemHelper(node* currNode, int key) // standard BST delete
{
  if (currNode == NULL)
  {
    return NULL;
  }
  else if (key < currNode->key)
  {
    currNode->left = deleteItemHelper(currNode->left, key);
  }
  else if (key > currNode->key)
  {
    currNode->right = deleteItemHelper(currNode->right, key);
  }
  else // We found the node with the value
  {
    if (currNode->left == NULL && currNode->right == NULL)
    {
      delete currNode;
      return NULL;
    }
    else if (currNode->left == NULL) // Only right child
    {
      node* temp = currNode;
      currNode = currNode->right;
      delete temp;
    }
    else if (currNode->right == NULL) // Only left child
    {
      node* temp = currNode;
      currNode = currNode->left;
      delete temp;
    }
    else // Both left and right child
    {
      node* minN = getMinValueNode(currNode->right); // Replace with Minimum from right subtree
      currNode->key = minN->key;
      currNode->right = deleteItemHelper(currNode->right, minN->key);
    }
  }
return currNode;
}

node* deleteNodesHelper(node* currNode)
{
  if(currNode == NULL)
  {
    return currNode;
  }
  else
  {
    deleteNodesHelper(currNode->left);
    deleteNodesHelper(currNode->right);
    delete currNode;
    currNode = NULL;
  }
  return currNode;
}

node* HashTable::createNode(int key, node* left, node* right)
{
  node* nw = new node;
  nw->key = key;
  nw->left = left;
  nw->right = right;
  return nw;
}

HashTable::HashTable(int bsize)
{
  numElements = 0;
  this->tableSize = bsize;
  table = new node*[tableSize];
  for (int i = 0; i < bsize; i++)
  {
    table[i] = nullptr;
  }

}

// function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
  return (key % tableSize);
}

// function to search
bool HashTable::searchItem(int key)
{
  int index = hashFunction(key); // find index
  node* curr = searchItemHelper(table[index], key); // call helper
  if(curr != NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//function to insert
void HashTable::insertItem(int key)
{
  if (searchItem(key) == false)
  {
    int index = hashFunction(key); // find index using hash function
    node* newNode = createNode(key, NULL, NULL); // create new node
    table[index] = addNodeHelper(table[index], key, newNode); // pass into helper
    numElements++; // increment numElements
  }
  else
  {
    cout << "Duplicate entry" << endl;
  }
}

// function to delete
void HashTable::deleteItem(int key)
{
  if (searchItem(key))
  {
    int index = hashFunction(key);
    if (table[index]->key == key)
    {
      table[index] = deleteItemHelper(table[index], key);
      numElements--;
    }
    else
    {
      deleteItemHelper(table[index], key);
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
  int e = getNumElements();
  for (int i = 0; i < tableSize; i++)
  {
    table[i] = deleteNodesHelper(table[i]);
  }
  for (int i = 0; i < e; i++) // set numElements back to 0
  {
    numElements--;
  }
}

// function to display hash table
void HashTable::printTable(int index)
{
    cout << index << "|| " << endl;
    node* curr = table[index]; // set curr node to index
    printBST(curr, 1); // pass to helper
}
