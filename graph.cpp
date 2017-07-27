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
  for (int i = 0; i < vertices.size(); i++)
  {
    vertices[i].adj.clear();
  }
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
  // std::cout << "insertingEdge" << std::endl;
  // std::cout << "mv1:"<<mv1->title<<std::endl;
  // std::cout << "mv2:"<<mv2->title<<std::endl;
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
    std::cout << "edge already exists"<<std::endl;
    (mv1->adj[i].adjNumRaters)++;
    mv1->adj[i].adjRatings += rating2;
    (mv2->adj[j].adjNumRaters)++;
    mv2->adj[j].adjRatings += rating1;
  }
  else // make the new edge
  {
    // std::cout << "Creating New Edges" << std::endl;
    AdjMovieVertex adj1, adj2;
    adj1.mv = mv2;
    adj1.adjNumRaters = 1;
    adj1.adjRatings = rating2;
    adj1.adjAvgRating = 0;
    adj2.mv = mv1;
    adj2.adjNumRaters = 1;
    adj2.adjRatings = rating1;
    adj2.adjAvgRating = 0;
    // std::cout << mv1->title<<" empty? " << mv1->adj.empty() << std::endl;
    // std::cout << mv2->title<<" empty? " << mv2->adj.empty() << std::endl;
    mv1->adj.push_back(adj1);
    mv2->adj.push_back(adj2);
    // std::cout << mv1->title << " linked: "<<mv1->adj.back().mv->title << std::endl;
    // std::cout << mv2->title << " linked: "<<mv2->adj.back().mv->title << std::endl;
    // if(mv1->adj.size() == 1)
    //   std::cout << mv1->title << " first adj:" << mv1->adj[0].mv->title << std::endl;
    numEdges++;
  }

}

void MovieGraph::printAdjs(MovieVertex * mv)
{
  std::cout << "**Printing Linkages of " << mv->title <<
  " ("<<mv->adj.size()<<")"<<std::endl;
  for(int i = 0; i < mv->adj.size(); i++)
  {
    std::cout << mv->title<<" linked to "<<mv->adj[i].mv->title << std::endl;
  }
  std::cout << "Ending linkage printing**"<<std::endl;
}

void MovieGraph::computeEdgeAvgs()
{
  std::cout << "Computing Avgs on edges"<<std::endl;
  int numRaters;
  float ratings;
  for(int i = 0; i < vertices.size(); i++)
  {
    std::cout << "Avg of "<<vertices[i].title<<":"<<std::endl;
    for(int j = 0; j < vertices[i].adj.size(); j++)
    {
      std::cout << vertices[i].adj[j].mv->title<<" ";
      ratings = vertices[i].adj[j].adjRatings;
      numRaters = vertices[i].adj[j].adjNumRaters;
      vertices[i].adj[j].adjAvgRating = ratings / numRaters;
      std::cout << vertices[i].adj[j].adjAvgRating << std::endl;
    }
  }
}

void MovieGraph::printMovieInfo(std::string title)
{
  MovieVertex * mv = findMovieVertexTitle(title);
  std::cout << "Title:"<<mv->title<<" "<<mv->movieId<<std::endl;
  std::cout << "totalNumRaters: " << mv->totalNumRaters<<std::endl;
  std::cout << "totalRatings: " << mv->totalRatings<<std::endl;
  std::cout << "totalAvgRating: " << mv->totalAvgRating<<std::endl;
  std::cout << "Linkings: "<< mv->adj.size()<<std::endl;
  for(int i = 0; i < mv->adj.size();i++)
  {
    std::cout << mv->adj[i].mv->title <<
    " (N:" << mv->adj[i].adjNumRaters <<
    " R:" << mv->adj[i].adjRatings <<
    " A:" << mv->adj[i].adjAvgRating << ")"<<std::endl;
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

void MovieGraph::printEdges()
{
  std::cout << std::endl << std::endl << "Printing Movie Graph Edges"
  <<std::endl<<std::endl;
  for(int i = 0; i < vertices.size(); i++)
  {
    std::cout << std::endl << vertices[i].title
    << " V: "<< vertices[i].adj.size() <<std::endl;
    for(int j = 0; j < vertices[i].adj.size();j++)
    {
      std::cout << vertices[i].adj[j].mv->title << std::endl;
    }
  }
}
