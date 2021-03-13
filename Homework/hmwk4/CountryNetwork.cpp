/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  if (head == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  if(head == NULL) //Check if head is Null i.e list is empty
  {
    head = new Country; // create new country
    head->name = countryName; // set country name
    head->numberMessages = 0; // zero messages received
    head->next = NULL; // next node is NULL
    cout << "adding: " << countryName << " (HEAD)" << endl; // print per directions

  }
  else if(previous == NULL) // if list is not empty, look for prev and append our node there
  {
    Country* newCountry = new Country; // create temp Country
    newCountry->name = countryName; // set temp Country country name
    newCountry->numberMessages = 0; // zero messages received
    newCountry->next = head; // point temp country to current head
    head = newCountry; // set new country as the new head
    cout << "adding: " << countryName << " (HEAD)" << endl; // print per directions
  }
  else
  {
    Country* newCountry = new Country; // create temp
    newCountry->name = countryName; // set country name
    newCountry->numberMessages = 0; // zero messages received
    newCountry->next = previous->next; // point temp to where previous was pointing
    previous->next = newCountry; // point previous to new Country
    cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl; // print per directions
  }
}

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName)
{
  Country *pres = head;
  Country *prev = NULL;
  if (head == NULL) // if list is empty
  {
    cout << "Country does not exist." << endl; // cout per directions
  }
  else if (searchNetwork(countryName) == NULL) // if name is not found
  {
    cout << "Country does not exist." << endl; // cout per directions
  }
  else
  {
    while (searchNetwork(countryName)->name != pres->name && pres->next != NULL) // find index / make sure n is within bounds of linked list
    {
        prev = pres; // move pointers
        pres = pres->next;
    }
    if (prev == NULL) // Delete head case
    {
      Country* tempNode = new Country; // create temp
      tempNode = head; // store head
      head = tempNode->next; // reset head to next
      delete tempNode; // delete
    }
    else // Non-head delete case
    {
      prev->next = pres->next; // point previous to node after present
      delete pres; // delete present
    }
  }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  insertCountry(NULL, "United States");
  insertCountry(searchNetwork("United States"), "Canada");
  insertCountry(searchNetwork("Canada"), "Brazil");
  insertCountry(searchNetwork("Brazil"), "India");
  insertCountry(searchNetwork("India"), "China");
  insertCountry(searchNetwork("China"), "Australia");
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country* ptr = head; // set pointer at head
  while (ptr != NULL && ptr->name != countryName) // while name at Country != param and ptr != NULL (ie not at end of list)
  {
    ptr = ptr->next; // move pointer to next node
  }
  return ptr; // return the pointer once the name is found (returns NULL if name is not found)
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  Country* ptr = head; // set pointer at head
  if (head == NULL)
  {
    return;
  }
  else
  {
    while (ptr != NULL) // while ptr != NULL (ie not at end of list)
    {
      cout << "deleting: " << ptr->name << endl;
      ptr = ptr->next;
      Country* tempNode = new Country; // create temp
      tempNode = head; // store head
      head = tempNode->next; // reset head to next
      delete tempNode; // delete
    }
    cout << "Deleted network" << endl;
  }
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n)
 {
   int count = 0;
   Country* pres = head; // pres
   Country* prev = NULL; // prev
   Country* index = NULL; // keep track of where we stop loop
   if (head == NULL)
   {
     cout << "Linked List is Empty" << endl;
   }
   else
   {
     while (pres->next != NULL) // move pointers to tail and get count / set index
     {
       if (n == count)
       {
         index = prev; // set index to previous node (want loop to include index n)
       }
       if (pres->next->next == NULL && n == count + 1) // edge case (n is last element in list)
       {
         index = pres;
       }
       prev = pres; // move pointers
       pres = pres->next;
       count++;
     }
     if (n > count || n < 0) // if n is greater than number of elements in list or negative integer
     {
       cout << "Rotate not possible" << endl;
     }
     else
     {
       Country* front = head; // keep track of head
       while (pres->name != index->name)
       {
         prev->next = pres->next; // point previous to NULL (end)
         pres->next = front; // point tail to front
         head = pres; // reset head
         front = head; // reset front
         prev = NULL; // reset prev
         while (pres->next != NULL) // move pointers back to tail
         {
           prev = pres;
           pres = pres->next;
         }
       }
       cout << "Rotate Complete" << endl;
     }
   }
 }

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork()
{
  Country* pres = head; // pres
  Country* prev = NULL; // prev
  Country* next = NULL; // next
  while (pres != NULL) // traverse list
  {
    next = pres->next; // store next node
    pres->next = prev; // reverse pointer of present
    prev = pres; // move previous
    pres = next; // move present
  }
  head = prev; // reset head
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  Country* ptr = head;
  if (head == NULL)
  {
    cout << "== CURRENT PATH ==" << endl;
    cout << "nothing in path" << endl;
    cout << "===" << endl;
  }
  else
  {
    cout << "== CURRENT PATH ==" << endl;
    while(ptr->next != NULL)
    {
      cout << ptr->name <<" -> ";
      ptr = ptr->next;
    }
    cout << ptr->name <<" -> ";
    cout << "NULL" << endl;
    cout << "===" << endl;
  }
}
