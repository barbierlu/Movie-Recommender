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
  numMovies++;
}

void MovieGraph::insertMovieEdge(MovieVertex * mv1, MovieVertex * mv2)
{
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
    (mv1->adj[i].adjNumRaters)++;
    (mv2->adj[j].adjNumRaters)++;
  }
  else // make the new edge
  {
    AdjMovieVertex adj1, adj2;
    adj1.mv = mv2;
    adj1.adjNumRaters = 1;
    adj2.mv = mv1;
    adj2.adjNumRaters = 1;
    mv1->adj.push_back(adj1);
    mv2->adj.push_back(adj2);
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
    std::cout << "Title: "<<mv->title<<std::endl;
    std::cout << "MovieID: " << mv->movieId << std::endl;
    std::cout << "5 star ratings: " << mv->totalNumRaters<<std::endl;
    std::cout << "Linkings "<< mv->adj.size()<< " (total)" << std::endl;
    std::cout << "Linkings above 2 mutual raters:" << std::endl;
    for(int i = 0; i < mv->adj.size();i++)
    {
      if (mv->adj[i].adjNumRaters > 2)
      {
        std::cout << mv->adj[i].mv->title <<
        " (" << mv->adj[i].adjNumRaters << " mutual)"
        <<std::endl;
      }
    }
  }
  else
    printMovieNotFound();
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
  std::cout << "Threshold of 5 muutal ratings of 5 stars" << std::endl;
  for(int i = 0; i < mv->adj.size();i++)
  {
    if (mv->adj[i].adjNumRaters > 4)
    {
      std::cout << mv->adj[i].mv->title << " "
      << mv->adj[i].adjNumRaters << std::endl;
    }
  }
}

MovieVertex * MovieGraph::findSimilar(MovieVertex * mv, int * numSimRaters)
{
  if(mv->adj.size() == 0) return nullptr;

  int hI = 0; // Index of largest number of raters
  for (int i = 0; i < mv->adj.size(); i++)
  {
    if(mv->adj[i].adjNumRaters > mv->adj[hI].adjNumRaters)
      hI = i;
  }
  *numSimRaters = mv->adj[hI].adjNumRaters;
  return mv->adj[hI].mv;
}

unsigned long int MovieGraph::getNumRatings()
{
  return totalNumRatings;
}

MovieVertex * MovieGraph::getHighestRatedMovie()
{
  if (vertices.size() == 0) return nullptr;
  int id = 0;
  for (unsigned int i = 0; i < vertices.size();i++)
  {
    if(vertices[i].totalNumRaters > vertices[id].totalNumRaters)
      id = i;
  }
  return &(vertices[id]);
}

void MovieGraph::printMovieNotFound()
{
  std::cout << "Movie not found" << std::endl;
  std::cout << "Please refer to the Movies.csv file"
  << " for correct movie names. Note: do not inlude"
  << " text in brackets and if a movie's title contains"
  << " 'The' at the beginning, do not follow the .csv's"
  << " convention of putting leading 'The' at the end of"
  << " the title. Please place 'The' at the beginning."
  << std::endl;
}
