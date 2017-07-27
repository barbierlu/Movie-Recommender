#include "graph.hpp"
#include <iostream>
#include <vector>

MovieGraph::MovieGraph()
{
  std::cout << "Graph Initialized" << std::endl;
  numMovies = 0;
  numEdges = 0;
}

MovieGraph::~MovieGraph()
{
  vertices.clear();
  std::cout << "Graph Deleted" << std::endl;
}

void MovieGraph::insertMovieVertex(std::string title, int id)
{
  MovieVertex mv(title, id);
  vertices.push_back(mv);
  // std::cout << title << ". Added" << std::endl;
  numMovies++;
}

void MovieGraph::insertMovieEdge(MovieVertex * mv1, float rating1,
  MovieVertex * mv2, float rating2)
{
  // rating 1 is a new rating
  totalRatings += rating1;
  totalNumRatings++;

  // search to see if the edge already exists
  bool found = false;
  int i,j;
  for (i = 0; i < mv1->adj.size(); i++)
  {
    if(mv1->adj[i].mv == mv2)
    {
      for(j=0; j < mv2->adj.size(); j++)
      {
        found = true;
        break;
      }
      break;
    }
  }
  if (found == true) // edge already exists
  {
    // add to the edges
    (mv1->adj[i].adjNumRaters)++;
    mv1->adj[i].adjRatings += rating2;
    (mv2->adj[j].adjNumRaters)++;
    mv2->adj[j].adjRatings += rating1;
  }
  else // make the new edge
  {
    AdjMovieVertex adj1;
    adj1.mv = mv2;
    adj1.adjNumRaters = 1;
    adj1.adjRatings = rating2;
    AdjMovieVertex adj2;
    adj2.mv = mv1;
    adj2.adjNumRaters = 1;
    adj2.adjRatings = rating1;
    mv1->adj.push_back(adj1);
    mv2->adj.push_back(adj2);
    numEdges++;
  }
}

void computeEdgeAvgs()
{
  int numRaters;
  float ratings;
  for(int i = 0; i < vertices.size(); i++)
  {
    for(int j = 0; j < vertices[i].adj.size(); j++)
    {
      ratings = vertices[i].adj[j].adjRatings;
      numRaters = vertices[i].adj[j].adjNumRaters;
      vertices[i].adj[j].adjAvgRating = ratings / numRaters;
    }
  }
}

void MovieGraph::printMovieGraph()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i].movieId << " "
    << vertices[i].title << "." << std::endl;
  }
}

unsigned long int MovieGraph::getNumMovies()
{
  return numMovies;
}

unsigned long int MovieGraph::getNumEdges()
{
  return numEdges;
}

MovieVertex * MovieGraph::findMovieVertexId(int id)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].movieId == id)
      return &(vertices[i]);
  }
  return nullptr;
}

MovieVertex * MovieGraph::findMovieVertexTitle(std::string title)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].title == title)
      return &(vertices[i]);
  }
  return nullptr;
}
