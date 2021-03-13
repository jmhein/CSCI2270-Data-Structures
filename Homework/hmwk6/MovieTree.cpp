#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST

// same as add node but with pointer parameter for recursion
void findLeaf(MovieNode* ptr, int ranking, string title, int year, float rating)
{
  if (ptr->left == NULL && title < ptr->title) // if pointer left is NULL and title is less than current title
  {
    ptr->left = new MovieNode(ranking, title, year, rating); // point left to newMovie
  }
  else if (ptr->right == NULL && title > ptr->title) // if pointer right is NULL and title is greater than current title
  {
    ptr->right = new MovieNode(ranking, title, year, rating); // point right to new Movie
  }
  else if (title < ptr->title) // if we arent at a leaf and title is less than current title
  {
    findLeaf(ptr->left, ranking, title, year, rating); // recurse left
  }
  else if (title > ptr->title) // if we arent at a leaf and title is greater than current title
  {
    findLeaf(ptr->right, ranking, title, year, rating); // recurse right
  }
}

// same as print inventory but with pointer parameter for recursion
void printInOrder(MovieNode* ptr)
{
  if (ptr != NULL )
  {
    printInOrder(ptr->left);
    cout << "Movie: " << ptr->title << " " << ptr->rating << endl;
    printInOrder(ptr->right);
  }
}

// same as find movide but with pointer parameter for recursion
MovieNode* searchTree(MovieNode* currNode, string title)
{
  if(currNode == NULL)
      return NULL;

  if(currNode->title == title)
      return currNode;

  if(currNode->title > title)
      return searchTree(currNode->left, title);

  return searchTree(currNode->right, title);
}

void queryTree(MovieNode* currNode, float rating, int year)
{
  if(currNode != NULL)
  {
    if(currNode->rating >= rating && currNode->year >= year)
    {
      cout << currNode->title << "(" << currNode->year << ") " << currNode->rating << endl;
    }
    queryTree(currNode->left, rating, year);
    queryTree(currNode->right, rating, year);
  }
}

int countNodes(MovieNode* currNode)
{
  int c =  1;             //Node itself should be counted
  if (currNode == NULL)
        return 0;
  else
  {
      c += countNodes(currNode->left);
      c += countNodes(currNode->right);
      return c;
  }
}

float getfullTotal(MovieNode* currNode)
{
  float r = 0;             //Node itself should be counted
  if (currNode == NULL)
        return 0;
  else
  {
      r = currNode->rating;
      r += getfullTotal(currNode->left);
      r += getfullTotal(currNode->right);
      return r;
  }
}

void destroyNode(MovieNode* currNode)
{
  if(currNode!=NULL)
  {
      destroyNode(currNode->left);
      destroyNode(currNode->right);

      delete currNode;
      currNode = NULL;
  }
}

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  destroyNode(root);
}

void MovieTree::printMovieInventory()
{
   if (root == NULL)
   {
     cout << "Tree is Empty. Cannot print" << endl;
   }
   else
   {
     printInOrder(root);
   }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  if (root == NULL)
  {
    root = new MovieNode(ranking, title, year, rating);
  }
  else
  {
    findLeaf(root, ranking, title, year, rating);
  }
}

void MovieTree::findMovie(string title)
{
  MovieNode* ptr = searchTree(root, title);
  if (ptr != NULL)
  {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << ptr->ranking << endl;
    cout << "Title :" << ptr->title << endl;
    cout << "Year :" << ptr->year << endl;
    cout << "rating :" << ptr->rating << endl;
  }
  else
  {
    cout << "Movie not found." << endl;
  }
}


void MovieTree::queryMovies(float rating, int year)
{
  if (root == NULL)
  {
    cout << "Tree is Empty. Cannot query Movies" << endl;
  }
  else
  {
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    queryTree(root, rating, year);
  }
}

void MovieTree::averageRating()
{
  if (root == NULL)
  {
    cout << "Average rating:0.0" << endl;
  }
  else
  {
    float total = getfullTotal(root);
    int count = countNodes(root);
    cout << "Average rating:" << total/count << endl;
  }
}
