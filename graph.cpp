#include "graph.hpp"
#include <iostream>

MovieGraph::MovieGraph()
{
  std::cout << "Graph Initialized" << std::endl;
}

MovieGraph::~MovieGraph()
{
  vertices.erase(vertices.begin(), vertices.end());
}

MovieGraph::insertMovieEdge(std::string title, int rating)
{
  MovieVertex * mv = new MovieVertex(title, rating);
}
