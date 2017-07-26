#include <iostream>


struct MovieVertex{
  std::string title;
  int totalNumRaters;
  int totalRatings;
  int totalAvgRating;
  std::vector<AdjMovieVertex> adj;
  MovieVertex(std::string _title, int rating)
  {
    numRaters = 1;
    ratings = avgRating = rating;
    title = _title;
  }
}

struct AdjMovieVertex{
  MovieVertex * mv;
  int adjNumRaters;
  int adjNumRatings;
  int adjAvgRating;
}


class MovieGraph{
public:
  MovieGraph();
  ~MovieGraph();
  void insertMovieVertex(std::string title);
  void insertMovieEdge(MovieVertex * mv1, int rating1,
    MovieVertex * mv2, int rating2);
  void printMovieGraph();
private:
  std::vector<MovieVertex> vertices;
}
