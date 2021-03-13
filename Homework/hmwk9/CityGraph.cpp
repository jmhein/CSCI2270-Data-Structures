#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void DFTraversal(vertex *n)
{
  n->visited = true; // mark as visited
  cout<< n->name << " --> "; // print name
  for (int x = 0; x < (int)n->adj.size(); x++)
  {
    if (n->adj[x].v->visited == false)
    {
      DFTraversal(n->adj[x].v);
    }
  }
}

// function to add a Vertex
void Graph::addVertex (string name)
{
  bool found = false; // flag to check if name is already added
  for (int i = 0; i < (int)vertices.size(); i++) // loop through verticies
  {
    if (vertices[i]->name == name)
    {
      found = true; // set flag is name is found
    }
  }
  if (found == false) // if name is not already in vector
  {
    vertex *v = new vertex; // allocate memory for new vertex
    v->name = name; // set name
    vertices.push_back(v);
  }
}

// function to add edge between two vertices
void Graph::addEdge(string n1, string n2, int num)
{
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    if(vertices[i]->name == n1) // find name of 1st parameter
    {
      for(int j = 0; j < (int)vertices.size(); j++)
      {
        if(vertices[j]->name == n2 && i != j) // find name of 2nd parameter
        {
          adjVertex av; // create adjVertex variable
          av.weight = num;
          av.v = vertices[j]; // set equal to vertices at index j
          vertices[i]->adj.push_back(av); // push to vector of adj verticies for i
          //another vertex for edge in other direction
          adjVertex av2; // create adjVertex varialbe
          av2.weight = num;
          av2.v = vertices[i]; // set equal to verticies at index i
          vertices[j]->adj.push_back(av2); // push to vector of adj vertices for j
        }
      }
    }
  }
}

void Graph::depthFirstTraversal(string sourceVertex)
{
  vertex* n;
  for (int i = 0; i < (int)vertices.size(); i++) // find soucre vertex
  {
    if (vertices[i]->name == sourceVertex)
    {
      n = vertices[i];
    }
  }
  DFTraversal(n); // pass to helper function
  cout << "Done"; // cout done at end
}

vertex* Graph::DijkstraAlgorithm(string start, string end)
{
  vertex *vStart; // store starting vertex
  for(int i = 0; i < (int)vertices.size(); i++) // find starting vertex
  {
      if(vertices[i]->name == start)
      {
          vStart = vertices[i];
      }
  }
  vector<vertex*> solved; // vector to store solved vertices
  vStart->visited = true; // mark as solved
  solved.push_back(vStart); // push start into solved
  vertex* temp;
  bool found = false;
  int distance = 0;
  int compare = 0;
  if ((int)vStart->adj.size() > 0)
  {
    compare = vStart->adj[0].weight;
  }
  while (found == false)
  {
    for (int i = 0; i < (int)solved.size(); i++) // loop through all solved vertices
    {
      for (int j = 0; j < (int)solved[i]->adj.size(); j++) // loop through all adjacents
      {
        if (solved[i]->adj[j].v->visited == false) // check if adjacent vertex has been solved
        {
          solved[i]->adj[j].v->distance = solved[i]->distance + solved[i]->adj[j].weight; // update distance to weight plus distance of parent
          if (solved[i]->adj[j].v->distance <= compare)
          {
            temp = solved[i]->adj[j].v;
            temp->pred = solved[i];
          }
          if (temp->name == end)
          {
            found = true;
          }
        }
      }
    }
    temp->visited = true;
    distance = distance + temp->distance;
    compare = distance;
    solved.push_back(temp);
  }
  return temp;
}

void Graph::shortestpath(string start, string end)
{
  vertex *vEnd; // store ending vertex
  for(int i = 0; i < (int)vertices.size(); i++) // find ending vertex
  {
      if(vertices[i]->name == end)
      {
          vEnd = vertices[i];
      }
  }
  vector<vertex*> solved; // vector to store vertices
  while (vEnd != NULL) // push all vertices into vector
  {
    solved.push_back(vEnd);
    vEnd = vEnd->pred;
  }
  for (int i = (int)solved.size() - 1; i >= 0; i--) // start loop at end of vector
  {
    cout << solved[i]->name << " ";
  }
}
