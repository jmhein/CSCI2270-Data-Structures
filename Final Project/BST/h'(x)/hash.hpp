#ifndef HASH_HPP
#define HASH_HPP

#include <string>
using namespace std;

// node for storing item in BST
struct node
{
    int key;
    struct node* left;
    struct node* right;
};

class HashTable
{
    int numElements; // number of elements in table
    int tableSize;  // No. of buckets (linked lists)
    node* *table; // Pointer to an array containing buckets
public:
    node* createNode(int key, node* left, node* right);
    HashTable(int bsize);  // Constructor
    void insertItem(int key); // inserts a key into hash table
    void deleteItem(int key); // removes a key from a hash table
    void deleteAllNodes();
    unsigned int hashFunction(int key); // hash function to map values to key
    int getNumElements();
    double getLoadFactor();
    void printTable(int index);
    bool searchItem(int key);
};

#endif
