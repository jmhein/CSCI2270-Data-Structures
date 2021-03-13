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
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 ********Add the following six countries, in order, to the network with insertCountry: "United
        States", "Canada", "Brazil", "India", "China", "Austraila"
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
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country* pres = head; // set pointer equal to beginning of Linked List
  if (head == NULL) // check that list is not empty
  {
    cout << "Empty list" << endl;
  }
  else if (searchNetwork(receiver) == NULL) // check that receiver is in the network
  {
    cout << "Country not found" << endl; // if not found - print "Country not found"
  }
  else if (searchNetwork(receiver) == head) // special case: receiver is head
  {
    pres->numberMessages++; // increment num messages
    pres->message = message; // set message
    cout << pres->name << " [# messages received: " << pres->numberMessages << "] received: " << pres->message << endl; // print per directions
  }
  else // if country is found in network
  {
    while (pres != NULL && pres->name != receiver) // set up loop to cycle through the network
    {
      if (pres->next->name == receiver) // increment both pres and next if next
      {
        pres->numberMessages++; // increment num messages
        pres->message = message; // set message
        cout << pres->name << " [# messages received: " << pres->numberMessages << "] received: " << pres->message << endl; // print per directions
        pres->next->numberMessages++;
        pres->next->message = message;
        cout << pres->next->name << " [# messages received: " << pres->next->numberMessages << "] received: " << pres->next->message << endl; // print per directions
        pres = pres->next;
      }
      else
      {
        pres->numberMessages++; // increment num messages
        pres->message = message; // set message
        cout << pres->name << " [# messages received: " << pres->numberMessages << "] received: " << pres->message << endl; // print per directions
        pres = pres->next;
      }
    }
  }
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
