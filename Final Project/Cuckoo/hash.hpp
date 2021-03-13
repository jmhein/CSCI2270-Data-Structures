#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <vector>
using namespace std;

struct node
{
    int key;
};

class HashTable
{
    int numElements; // number of elements in table
    int tableSize;  // No. of buckets (linked lists)
    int rehashes;
    node* **table; // Pointer to an array containing buckets
public:
    node* createNode(int key);
    HashTable(int bsize);  // Constructor
    bool insertItem(int key, int n); // inserts a key into hash table
    void deleteItem(int key); // removes a key from a hash table
    unsigned int hashFunctionH(int key); // hash function to map values to key
    unsigned int hashFunctionHPrime(int key); // hash function to map values to key
    int getNumElements();
    double getLoadFactor();
    void printTable();
    void deleteAllNodes();
    bool searchItem(int key);
    int getTableSize();
    void rehash(vector<int> keys);
    int getRehashes();
};

#endif
