#include "graph.hpp"
#include <iostream>
#include <vector>

MovieGraph::MovieGraph()
{
  std::cout << "Graph Initialized" << std::endl;
  numMovies = 0;
  numEdges = 0;
  numUsers = 0;
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

void MovieGraph::insertMovieEdge(MovieVertex * mv1, MovieVertex * mv2)
{
  // std::cout << "insertingEdge" << std::endl;
  // std::cout << "mv1:"<<mv1->title<<std::endl;
  // std::cout << "mv2:"<<mv2->title<<std::endl;
  // rating 1 is a new rating
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
    // std::cout << "edge already exists"<<std::endl;
    (mv1->adj[i].adjNumRaters)++;
    (mv2->adj[j].adjNumRaters)++;
  }
  else // make the new edge
  {
    // std::cout << "Creating New Edges" << std::endl;
    AdjMovieVertex adj1, adj2;
    adj1.mv = mv2;
    adj1.adjNumRaters = 1;
    adj2.mv = mv1;
    adj2.adjNumRaters = 1;
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

void MovieGraph::printMovieInfo(std::string title)
{
  MovieVertex * mv = findMovieVertexTitle(title);
  if(mv != nullptr)
  {
    std::cout << "Title:"<<mv->title<<" "<<mv->movieId<<std::endl;
    std::cout << "totalNumRaters: " << mv->totalNumRaters<<std::endl;
    std::cout << "Linkings: "<< mv->adj.size()<<std::endl;
    for(int i = 0; i < mv->adj.size();i++)
    {
      if (mv->adj[i].adjNumRaters > 2)
      {
        std::cout << mv->adj[i].mv->title <<
        " (N: " << mv->adj[i].adjNumRaters << ")"
        <<std::endl;
      }
    }
  }
  else
    std::cout << "Movie not found" << std::endl;
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

void MovieGraph::printEdges(MovieVertex * mv)
{
  std::cout << mv->title << "'s Connections:" << std::endl;
  for(int i = 0; i < mv->adj.size();i++)
  {
    std::cout << mv->adj[i].mv->title << " "
    << mv->adj[i].adjNumRaters << std::endl;
  }
}

MovieVertex * MovieGraph::findSimilar(MovieVertex * mv, int * numSimRaters)
{
  if(mv->adj.size() == 0) return nullptr;

  int hI = 0; // Index of largest number of raters
  for (int i = 0; i < mv->adj.size(); i++)
  {
    if(mv->adj[hI].adjNumRaters > mv->adj[i].adjNumRaters)
      hI = i;
  }
  *numSimRaters = mv->adj[hI].adjNumRaters;
  return mv->adj[hI].mv;
}

unsigned long int MovieGraph::getNumRatings()
{
  return totalNumRatings;
}
