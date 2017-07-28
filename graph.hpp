#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <iostream>
#include <vector>

typedef struct AdjMovieVertex AdjMovieVertex;

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

struct AdjMovieVertex{
  MovieVertex * mv;
  int adjNumRaters;
};


class MovieGraph{
public:
  MovieGraph();
  ~MovieGraph();
  void insertMovieVertex(std::string title, int id);
  void insertMovieEdge(MovieVertex * mv1, MovieVertex * mv2);
  MovieVertex * findMovieVertexId(int id);
  MovieVertex * findMovieVertexTitle(std::string title);
  void printMovieGraph();
  void printEdges(MovieVertex * mv);
  unsigned long int getNumMovies();
  unsigned long int getNumEdges();
  unsigned long int getNumRatings();
  MovieVertex * getHighestRatedMovie();
  void computeEdgeAvgs();
  void printMovieInfo(std::string title);
  void printAdjs(MovieVertex * mv);
  unsigned long int numUsers;
  MovieVertex * findSimilar(MovieVertex * mv, int * numSimRaters);
private:
  std::vector<MovieVertex> vertices;
  unsigned long int numMovies;
  unsigned long int numEdges;
  unsigned long int totalNumRatings;
};

#endif
