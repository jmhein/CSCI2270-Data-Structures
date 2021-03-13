#ifndef HASH_HPP
#define HASH_HPP

#include <string>
using namespace std;

struct node
{
    int key;
};

class HashTable
{
    int numElements; // number of elements in table
    int tableSize;  // No. of buckets (linked lists)
    node* *table; // Pointer to an array containing buckets
    node* createNode(int key);
public:
    HashTable(int bsize);  // Constructor
    void insertItem(int key); // inserts a key into hash table
    void deleteItem(int key); // removes a key from a hash table
    unsigned int hashFunction(int key); // hash function to map values to key
    int getNumElements();
    double getLoadFactor();
    void printTable();
    void deleteAllNodes();
    bool searchItem(int key);
    int generateRandoms();
};

#endif
