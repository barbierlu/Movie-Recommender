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

/* Insert a vertex into the graph */
void MovieGraph::insertMovieVertex(std::string title, int id)
{
  MovieVertex mv(title, id); // make a temp copy to add to vector
  vertices.push_back(mv);
  numMovies++;
}

/* Insert an edge into the graph */
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
  if (found) // edge already exists
  {
    (mv1->adj[i].adjNumRaters)++;
    (mv2->adj[j].adjNumRaters)++;
  }
  else // make the new edge
  {
    AdjMovieVertex adj1, adj2; // temp copies to add to vector
    adj1.mv = mv2;
    adj1.adjNumRaters = 1;
    adj2.mv = mv1;
    adj2.adjNumRaters = 1;
    mv1->adj.push_back(adj1);
    mv2->adj.push_back(adj2);
    numEdges++;
  }
}

/* Prints all of the adjacent vertices */
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

/* Prints the title, number of 5 star ratings, and all
  of the adjacent graph vertices */
void MovieGraph::printMovieInfo(std::string title)
{
  MovieVertex * mv = findMovieVertexTitle(title);
  if(mv != nullptr)
  {
    std::cout << "Title: "<<mv->title<<std::endl;
    std::cout << "MovieID: " << mv->movieId << std::endl;
    std::cout << "5 star ratings: " << mv->totalNumRaters<<std::endl;
    std::cout << "5 star different movie Linkings: "<< mv->adj.size()<< std::endl;
    std::cout << "5 star Linkings with more than 2 mutual raters below" << std::endl;
    for(int i = 0; i < mv->adj.size();i++) // print links to mv
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

/* print each vertice's id and title */
void MovieGraph::printMovieGraph()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i].movieId << " "
    << vertices[i].title << "." << std::endl;
  }
}

/* Returns the number of movies in the graph */
unsigned long int MovieGraph::getNumMovies()
{
  return numMovies;
}

/* Returns the total number of edges created
    does not include additional ratings along ond edge */
unsigned long int MovieGraph::getNumEdges()
{
  return numEdges;
}

/* Returns the number of 5 star ratings */
unsigned long int MovieGraph::getNumRatings()
{
  return totalNumRatings;
}

/* find a vertex using its id */
MovieVertex * MovieGraph::findMovieVertexId(int id)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].movieId == id)
      return &(vertices[i]);
  }
  return nullptr;
}

/* find a vertex using its title */
MovieVertex * MovieGraph::findMovieVertexTitle(std::string title)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].title == title)
      return &(vertices[i]);
  }
  return nullptr;
}

/* print a vertice's edges and the number of raters in each edge*/
void MovieGraph::printEdges(MovieVertex * mv)
{
  std::cout << mv->title << "'s Connections:" << std::endl;
  std::cout << "Threshold of 5 muutal ratings of 5 stars" << std::endl;
  for(int i = 0; i < mv->adj.size();i++)
  {
    if (mv->adj[i].adjNumRaters > 4)
    {
      std::cout << mv->adj[i].mv->title << " ("
      << mv->adj[i].adjNumRaters << ", 5 star raters)"
      << std::endl;
    }
  }
}

/* Finds the adjacent vertex with the higest number of
  mutual 5 star raters, recommends a movie based on this statistic*/
MovieVertex * MovieGraph::findSimilar(MovieVertex * mv, int * numSimRaters)
{
  if(mv->adj.size() == 0) return nullptr;

  int hI = 0; // highest index, index of largest number of raters
  for (int i = 0; i < mv->adj.size(); i++)
  {
    if(mv->adj[i].adjNumRaters > mv->adj[hI].adjNumRaters)
      hI = i;
  }
  *numSimRaters = mv->adj[hI].adjNumRaters;
  return mv->adj[hI].mv;
}

/* Returns the higest rated movie */
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

/* Informs user that movie was not found and gives
information to guide proper title syntax */
void MovieGraph::printMovieNotFound()
{
  std::cout << "Movie not found" << std::endl;
  std::cout << "Please refer to the Movies.csv file"
  << " for correct movie names. Note: do not inlude"
  << " the last date in parenthesis but do include"
  << " all other info in paranthesis."
  << " If a movie's title normally contains"
  << " 'The' at the beginning, keep it in the natural order with"
  << " 'The' at the beginning."
  << std::endl;
}
