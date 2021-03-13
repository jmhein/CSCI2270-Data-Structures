#include "LinkedList.h"

using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey)
{
  if(head == NULL) //Check if head is Null i.e list is empty
  {
    head = new Node;
    head->key = newKey;
    head->next = NULL;
  }
  else if(prev == NULL) // if list is not empty, look for prev and append our node there
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head;
      head = newNode;
  }
  else
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;
  }
}


// TODO: SILVER PROBLEM
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n)
{
  bool isDeleted = false;
  if(head == NULL)
  {
    cout<< "List is already empty"<<endl;
    return isDeleted;
  }
  if (n == 0) // Special case to delete the head
  {
    Node* tempNode = new Node;
    tempNode = head;
    head = tempNode->next;
    delete tempNode;
    isDeleted = true;
  }
  else
  {
    Node *pres = head;
  	Node *prev = NULL;
    int count = 0;
    while (count < n && pres->next != NULL) // find index / make sure n is within bounds of linked list
    {
      if (count < n)
      {
        prev = pres; // move pointers
        pres = pres->next;
        count++; // increment count
      }
    }
    if (count == n) // check that we found a correct index - if so, delete
    {
      prev->next = pres->next;
      delete pres;
      count++;
      isDeleted = true;
    }
  }
  return isDeleted;
}

// TODO: GOLD PROBLEM
// Swap the first and last nodes (don't just swap the values)
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;
    if(head == NULL) // check if empty
    {
        cout << "List is empty. Cannot swap" << endl;
        return false;
    }
    else
    {
      Node *pres = head;
      Node *prev = NULL;
      while(pres->next != nullptr) // find last node
      {
        prev = pres;
        pres = pres->next;
      }
      pres->next = head->next; // point last to head->next
      head->next = nullptr; // point first to last->next
      prev->next = head; // point previous to new last
      head = pres; // reset head
    }
    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}
