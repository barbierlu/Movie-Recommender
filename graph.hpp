#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <iostream>
#include <vector>

typedef struct AdjMovieVertex AdjMovieVertex;

struct MovieVertex{
  std::string title;
  int totalNumRaters;
  float totalRatings;
  float totalAvgRating;
  int movieId;
  std::vector<AdjMovieVertex> adj;
  MovieVertex(std::string _title, int _movieId)
  {
    title = _title;
    movieId = _movieId;
    totalAvgRating = totalNumRaters = totalRatings = 0;
  }
};

struct AdjMovieVertex{
  MovieVertex * mv;
  int adjNumRaters;
  float adjRatings; // sum of all ratings of common users between vertices
  float adjAvgRating;
};


class MovieGraph{
public:
  MovieGraph();
  ~MovieGraph();
  void insertMovieVertex(std::string title, int id);
  void insertMovieEdge(MovieVertex * mv1, float rating1,
    MovieVertex * mv2, float rating2);
  MovieVertex * findMovieVertexId(int id);
  MovieVertex * findMovieVertexTitle(std::string title);
  void printMovieGraph();
  void printEdges();
  unsigned long int getNumMovies();
  unsigned long int getNumEdges();
  void computeEdgeAvgs();
  void printMovieInfo(std::string title);
  void printAdjs(MovieVertex * mv);
private:
  std::vector<MovieVertex> vertices;
  unsigned long int numMovies;
  unsigned long int numEdges;
  double totalRatings;
  unsigned long int totalNumRatings;
};

#endif
