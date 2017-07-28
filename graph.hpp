#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <iostream>
#include <vector>

typedef struct AdjMovieVertex AdjMovieVertex;

/* Graph vertex that includes title, movieId and vertex's
  adjacent vertices */
struct MovieVertex{
  std::string title;
  int totalNumRaters;
  int movieId;
  std::vector<AdjMovieVertex> adj;
  MovieVertex(std::string _title, int _movieId)
  {
    title = _title;
    movieId = _movieId;
    totalNumRaters = 0;
  }
};

/* Vertex's edge with another vertex
    Weight is the number of mutual 5 star raters */
struct AdjMovieVertex{
  MovieVertex * mv;
  int adjNumRaters;
};


class MovieGraph{
public:
  MovieGraph();
  ~MovieGraph();
  /* Insert a vertex into the graph */
  void insertMovieVertex(std::string title, int id);
  /* Insert an edge into the graph */
  void insertMovieEdge(MovieVertex * mv1, MovieVertex * mv2);
  /* find a vertex using its id */
  MovieVertex * findMovieVertexId(int id);
  /* find a vertex using its title */
  MovieVertex * findMovieVertexTitle(std::string title);
  /* print each vertice's id and title */
  void printMovieGraph();
  /* print a vertice's edges and the number of raters in each edge*/
  void printEdges(MovieVertex * mv);
  /* Returns the number of movies in the graph */
  unsigned long int getNumMovies();
  /* Returns the total number of edges created
      does not include additional ratings along ond edge */
  unsigned long int getNumEdges();
  /* Returns the number of 5 star ratings */
  unsigned long int getNumRatings();
  /* Returns the higest rated movie */
  MovieVertex * getHighestRatedMovie();
  /* Prints the title, number of 5 star ratings, and all
      of the adjacent graph vertices */
  void printMovieInfo(std::string title);
  /* Prints all of the adjacent vertices */
  void printAdjs(MovieVertex * mv);
  /* Finds the adjacent vertex with the higest number of
    mutual 5 star raters, recommends a movie based on this statistic*/
  MovieVertex * findSimilar(MovieVertex * mv, int * numSimRaters);
  unsigned long int numUsers;
private:
  std::vector<MovieVertex> vertices;
  unsigned long int numMovies;
  unsigned long int numEdges;
  unsigned long int totalNumRatings;
};

#endif
