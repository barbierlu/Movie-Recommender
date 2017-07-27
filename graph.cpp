#include "graph.hpp"
#include <iostream>
#include <vector>

MovieGraph::MovieGraph()
{
  std::cout << "Graph Initialized" << std::endl;
  numMovies = 0;
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

void MovieGraph::insertMovieEdge(MovieVertex * mv1, int rating1,
  MovieVertex * mv2, int rating2)
{
  // should make both sides of the edges

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
