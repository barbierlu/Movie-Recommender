#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <iostream>
#include <vector>

typedef struct AdjMovieVertex AdjMovieVertex;

struct MovieVertex{
  std::string title;
  int totalNumRaters;
  int totalRatings;
  int totalAvgRating;
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
  int adjNumRatings;
  int adjAvgRating;
};


class MovieGraph{
public:
  MovieGraph();
  ~MovieGraph();
  void insertMovieVertex(std::string title, int id);
  void insertMovieEdge(MovieVertex * mv1, int rating1,
    MovieVertex * mv2, int rating2);
  void printMovieGraph();
  unsigned long int getNumMovies();
private:
  std::vector<MovieVertex> vertices;
  unsigned long int numMovies;
};

#endif
