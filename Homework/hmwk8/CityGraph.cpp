#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// helper traverse function
void DFTraversal(vertex *n)
{
  n->visited = true;
  for (int x = 0; x < (int)n->adj.size(); x++)
  {
    if (n->adj[x].v->visited == false)
    {
      DFTraversal(n->adj[x].v);
    }
  }
}

void colorGraph(vertex *n)
{
  n->visited = true;
  string c1 = "green";
  string c2 = "red";
  if (n->color == " ")
  {
    n ->color = c1;
  }
  for (int x = 0; x < (int)n->adj.size(); x++)
  {
    if (n->adj[x].v->visited == false)
    {
      if (n->color == c1)
      {
        n->adj[x].v->color = c2;
      }
      else
      {
        n->adj[x].v->color = c1;
      }
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
void Graph::addEdge(string n1, string n2)
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
          av.v = vertices[j]; // set equal to vertices at index j
          vertices[i]->adj.push_back(av); // push to vector of adj verticies for i
          //another vertex for edge in other direction
          adjVertex av2; // create adjVertex varialbe
          av2.v = vertices[i]; // set equal to verticies at index i
          vertices[j]->adj.push_back(av2); // push to vector of adj vertices for j
        }
      }
    }
  }
}

//prints all edges
void Graph::displayEdges()
{
  for (int i = 0; i < (int)vertices.size(); i++) //loop through all vertices
  {
    cout << vertices[i]->name << " --> "; // print name of vertice at index i
    for (int j = 0; j < (int)vertices[i]->adj.size(); j++) // loop through all adjacents
    {
      cout << vertices[i]->adj[j].v->name << " "; // print name of all adjacents
    }
    cout << endl;
  }
}

// traverses graph in breadth first fashion
void Graph::breadthFirstTraverse(string sourceVertex)
{
  vertex *vStart;
  for(int i = 0; i < (int)vertices.size(); i++) // find the starting vertex
  {
      if(vertices[i]->name == sourceVertex)
      {
          vStart = vertices[i];
      }
  }
  vStart->visited = true; // mark starting vertex as visited
  queue<vertex*> q; // Use the queue to keep track of visited vertices
  q.push(vStart); // Enqueue the source vertex
  vertex *n;
  cout << "Starting vertex (root): " << vStart->name << "-> "; // print per directions
  // standard BFS
  while(!q.empty())
  {
    n = q.front();
    q.pop();
    for( int x = 0; x < (int)n->adj.size(); x++ ) // go to all the adjacent vertices of n
    {
      if (n->adj[x].v->visited == false) // check if adjacent has been visited
      {
        n->adj[x].v->visited = true; // mark as visited
        q.push(n->adj[x].v); // enqueue adjacent
        n->adj[x].v->distance = n->distance + 1; // update distance
        cout << n->adj[x].v->name <<"("<< n->adj[x].v->distance <<")"<< " "; // print per directions
      }
    }
  }
}

int Graph::getConnectedComponents()
{
  int components = 0;
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    if (vertices[i]->visited == false)
    {
      DFTraversal(vertices[i]);
      components++;
    }
  }
  return components;
}

bool Graph::checkBipartite()
{
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    if (vertices[i]->visited == false)
    {
      colorGraph(vertices[i]);
    }
  }
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    for (int j = 0; j < (int)vertices[i]->adj.size(); j++) // loop through all adjacents
    {
      if (vertices[i]->color == vertices[i]->adj[j].v->color)
      {
        return false;
      }
    }
  }
  return true;
}
