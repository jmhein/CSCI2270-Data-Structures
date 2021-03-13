#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////// HELPER FUNCTIONS ///////////////////////////////////////////////////////////////////

LLMovieNode* createNode (int ranking, std::string title, int year, float rating)
{
    LLMovieNode* newNode = new LLMovieNode(ranking, title, year, rating);
    return newNode;
}

TreeNode* getMinValueNode(TreeNode* currNode)
{
  if(currNode->leftChild == NULL)
  {
    return currNode;
  }
  return getMinValueNode(currNode->leftChild);
}


// helper function for printMovieInventory
void printInOrder(TreeNode* ptr) // in-order traversal
{
  if (ptr != NULL )
  {
    printInOrder(ptr->leftChild); // recurse left
    cout << "Movies starting with letter: " << ptr->titleChar << endl; // print TreeNode Letter in alphabetical order
    LLMovieNode* pres = ptr->head; // set pointer to head of Tree
    while (pres != NULL)
    {
      cout << " >> " << pres->title << " " << pres->rating << endl;
      pres = pres->next;
    }
    printInOrder(ptr->rightChild);
  }
}

// helper function for addMovie
void addMovieNode(TreeNode* ptr, int ranking, std::string title, int year, float rating)
{
  char letter = title[0];
  if (letter == ptr->titleChar)
  {
    LLMovieNode* pres = ptr->head; // set pointer to head of LL
    LLMovieNode* prev = NULL;
    if (title < pres->title) // CASE: add node at head
    {
      LLMovieNode* temp = createNode(ranking, title, year, rating);
      temp->next = ptr->head;
      ptr->head = temp;
    }
    else
    {
      while (title > pres->title && pres->next != NULL) // move pointers
      {
        prev = pres;
        pres = pres->next;
      }
      if (pres->next == NULL && title > pres->title) // CASE: add at end
      {
        LLMovieNode* temp = createNode(ranking, title, year, rating);
        pres->next = temp;
      }
      else // CASE: add in middle
      {
        LLMovieNode* temp = createNode(ranking, title, year, rating);
        temp->next = prev->next;
        prev->next = temp;
      }
    }
  }
  else if (ptr->leftChild == NULL && letter < ptr->titleChar) // if pointer left is NULL and letter is less than current title
  {
    ptr->leftChild = new TreeNode; // point left to newMovie
    ptr->leftChild->titleChar = letter;
    ptr->leftChild->parent = ptr;
    ptr->leftChild->head = createNode(ranking, title, year, rating);
  }
  else if (ptr->rightChild == NULL && letter > ptr->titleChar) // if pointer right is NULL and title is greater than current title
  {
    ptr->rightChild = new TreeNode; // point left to newMovie
    ptr->rightChild->titleChar = letter;
    ptr->rightChild->parent = ptr;
    ptr->rightChild->head = createNode(ranking, title, year, rating); // point right to new Movie
  }
  else if (letter < ptr->titleChar) // if we arent at a leaf and title is less than current title
  {
    addMovieNode(ptr->leftChild, ranking, title, year, rating); // recurse left
  }
  else if (letter > ptr->titleChar) // if we arent at a leaf and title is greater than current title
  {
    addMovieNode(ptr->rightChild, ranking, title, year, rating); // recurse right
  }
}

TreeNode* deleteTreeNode(TreeNode *currNode, char letter)
{
  if(currNode == NULL)
  {
    return NULL;
  }
  else if (letter < currNode->titleChar)
  {
    currNode->leftChild = deleteTreeNode(currNode->leftChild, letter);
  }
  else if (letter > currNode->titleChar)
  {
    currNode->rightChild = deleteTreeNode(currNode->rightChild, letter);
  }
  else// We found the node with the value
  {
    if (currNode->head == NULL)
    {
      if(currNode->leftChild == NULL && currNode->rightChild == NULL)
      {
        delete currNode;
        return NULL;
      }
      else if (currNode->leftChild == NULL)
      {
        TreeNode* temp = currNode;
        currNode = currNode->rightChild;
        free(temp);
      }
      else if(currNode->rightChild == NULL)
      {
        TreeNode* temp = currNode;
        currNode = currNode->leftChild;
        free(temp);
      }
      else
      {
        TreeNode* minN = getMinValueNode(currNode->rightChild);
        currNode->head = minN->head;
        currNode->titleChar = minN->titleChar;
        minN->head = NULL;
        currNode->rightChild = deleteTreeNode(currNode->rightChild, minN->titleChar);
      }
    }
  }
return NULL;
}

void deleteMovieNode (TreeNode* ptr, string title)
{
  char letter = title[0];
  if (letter == ptr->titleChar && ptr->head->next == NULL) // CASE: delete tree with right child
  {
    LLMovieNode* temp = ptr->head; // create temp
    ptr->head = NULL; // reset head to next
    delete temp; // delete
  }
  else if (letter == ptr->titleChar && ptr->head->next != NULL)
  {
    LLMovieNode* pres = ptr->head;
    LLMovieNode* prev = NULL;
    while (title != pres->title)
    {
      prev = pres;
      pres = pres->next;
    }
    if (prev == NULL) // delete head case
    {
      LLMovieNode* temp = ptr->head; // create temp
      ptr->head = temp->next; // reset head to next
      delete temp; // delete
    }
    else
    {
      prev->next = pres->next;
      delete pres;
    }
  }
  else if (letter < ptr->titleChar) // if we arent at a leaf and title is less than current title
  {
    deleteMovieNode(ptr->leftChild, title); // recurse left
  }
  else if (letter > ptr->titleChar) // if we arent at a leaf and title is greater than current title
  {
    deleteMovieNode(ptr->rightChild, title); // recurse right
  }

}

void destroyMovieNodes(TreeNode* currNode)
{
  if(currNode != NULL)
  {
    destroyMovieNodes(currNode->leftChild);
    destroyMovieNodes(currNode->rightChild);
    LLMovieNode* ptr = currNode->head; // set pointer at head
    if (currNode->head == NULL)
    {
      delete currNode;
    }
    else
    {
      while (ptr != NULL) // while ptr != NULL (ie not at end of list)
      {
        LLMovieNode* toDelete = ptr; // create temp
        ptr = ptr->next;
        delete toDelete; // delete
      }
    }
  }
}

void destroyTreeNodes(TreeNode* currNode)
{
  if(currNode!=NULL)
  {
      destroyTreeNodes(currNode->leftChild);
      destroyTreeNodes(currNode->rightChild);
      delete currNode;
      currNode = NULL;
  }
}

////////////////////////////////////////////// CLASS FUNCTIONS ////////////////////////////////////////////////////////////////////

MovieTree::MovieTree()
{
  root = NULL;
}

MovieTree::~MovieTree()
{
  destroyMovieNodes(root);
  destroyTreeNodes(root);
}

void MovieTree::printMovieInventory()
{
  printInOrder(root);
}

void MovieTree::addMovie(int ranking, std::string title, int year, float rating)
{
  if (root == NULL)
  {
    root = new TreeNode;
    root->titleChar = title[0];
    root->head = createNode(ranking, title, year, rating);
  }
  else
  {
    addMovieNode(root, ranking, title, year, rating);
  }
}

void MovieTree::deleteMovie(std::string title)
{
  if (root == NULL)
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
  }
  else
  {
    deleteMovieNode(root, title);
    root=deleteTreeNode(root, title[0]);
  }
}
