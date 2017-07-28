/*
  Luke Barbier
  Final Project
  Montero Quesada
*/

#include <iostream>
#include <fstream>
#include "graph.hpp"
using namespace std;

std::string getCinString()
{
  // Concatenation technique to get multiword cin strings
  std::string str1, str2;
  cin >> str1;
  getline(cin, str2);
  return str1 + str2;
}


bool openFile(ifstream * in, string txt)
{
  in->open(txt);
  if(!in->is_open())
  {
    cout << "Error reading input file" << endl;
    cout << "Name of file: "<< txt << endl;
    return false;
  }
  return true;
}

int mainMenuSelect(void)
{
  int sel = 0;
  while(true)
  {
    std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Recommend a movie" << std::endl;
    std::cout << "2. Print all movies" << std::endl;
    std::cout << "3. Print a movie's connections" << std::endl;
    std::cout << "4. See list's statistics" << std::endl;
    std::cout << "5. See a movie's info" << std::endl;
    std::cout << "6. Quit" << std::endl;
    std::cin >> sel;
    if(sel > 0 && sel < 7)
      return sel;
    else
      std::cout << std::endl <<"***** Invalid Input *****"
        << std::endl << std::endl;
  }
}

void askMoviesCSV(ifstream * csv)
{
  cout << "Please enter the Movies.csv file:" << endl;
  // openFile(csv, getCinString());
  openFile(csv, "Movies.csv");
}

void askRatingsCSV(ifstream * csv)
{
  cout << "Please enter the Ratings.csv file:" << endl;
  // openFile(csv, getCinString());
  openFile(csv, "Ratings.csv");
}

void displayHelp()
{
  cout << "This program recommends movies by analyzing significant data"
  << " in the form of two files 'Movies.csv' and 'Ratings.csv'. Only"
  << " 5 star ratings are considered. Recommendations are chosen based"
  << " on the greatest number of mutual 5 star ratings. For example, if"
  << " a user inputs 'Movie A' as their favorite movie and 100 people from"
  << " the Ratings.csv file gave Movie A and Move B 5 stars and 30 people also"
  << " gave Movie A and Movie C 5 stars, then the program would recommend"
  << " Movie B." << std::endl
  << "These large files can be downloaded from"
  << " https://grouplens.org/datasets/movielens/"
  << ". Please read the README for more information." << std::endl << std::endl;
}

// function that moves 'The' to the front of the movie's title
string alterTitleThe(string orig)
{
  if(orig.size() < 4) // check if too short for 'The'
    return orig;
  // check if Title ends in 'The'
  if (orig.at(orig.size()-3) == 'T' &&
      orig.at(orig.size()-2) == 'h' &&
      orig.at(orig.size()-1) == 'e')
  {
    size_t pos = orig.rfind('T');
    string check = orig.substr(0, pos-2);
    string concat = "The " + check;
    return concat;
  }
  else
    return orig;
}

void processMoviesCSV(MovieGraph * graph, ifstream * csv)
{
  string s,s1,s2, prev="";
  int id, counter=0;
  string title;

  getline(*csv, s);

  while(true)
    {
    getline(*csv, s, '\n');
    if(s == prev || s=="") // check for last line
      break;
    // Id
    s1 = s.substr(0, s.find(','));
    id = stoi(s1);
    // title
    size_t firstComma = s.find(',') + 1;
    s2 = s.substr(firstComma, s.rfind(',')-firstComma);
    if(s2.at(0) != '\"')
    {
      title = s2.substr(0, s2.size()-7);
    }
    else
    {
      title = s2.substr(1, s2.size()-9);
    }
    title = alterTitleThe(title);
    graph->insertMovieVertex(title, id);
    prev = s;
  }
}

bool processRatingsCSV(MovieGraph * graph, ifstream * csv, int numRaters)
{
  int counter = 0;
  string s,s1,s2,prev; // helper parsing strings

  string rating_s, movieId_s, userId_s;
  int movieId, userId, prevUserId=-1;
  float rating;

  bool sameUser = false;

  // other movies the user has rated
  vector<MovieVertex*> userOtherVertices;

  getline(*csv, s); // disregard first line
  while(true)
    {
    getline(*csv, s, '\n');
    if(s == prev || s=="") // check for last line
      break;
    if(counter == numRaters) // user's inputted number of users to analyze
      break;
    s1 = s.substr(0, s.rfind(','));
    rating_s = s1.substr(s1.rfind(',')+1);
    s2 = s1.substr(0, s1.rfind(','));
    movieId_s = s2.substr(s2.rfind(',')+1);
    userId_s = s2.substr(0, s2.rfind(','));
    userId = stoi(userId_s);
    movieId = stoi(movieId_s);
    rating = stof(rating_s);

    MovieVertex * mv = graph->findMovieVertexId(movieId);
    if(mv == nullptr)
    {
      cout << "[ERROR] " << movieId << " not found."<<endl;
      return false;
    }

    if(prevUserId == userId)
    {
      sameUser = true;
    }
    else
    {
      sameUser = false;
      cout << "new user " << userId << endl;
      graph->numUsers++;
      counter++;
    }

    if(rating == 5.0)
    {
      mv->totalNumRaters++;
    }

    if (sameUser && rating == 5.0) // link that movie to all the other ones
    {
      for (int i = 0; i < userOtherVertices.size(); i++)
      {
        graph->insertMovieEdge(mv, userOtherVertices[i]);
      }
      userOtherVertices.push_back(mv);
    }
    else
    {
      userOtherVertices.clear();
      if(rating == 5.0)
      {
        userOtherVertices.push_back(mv);
      }
    }
    prev = s;
    prevUserId = userId;
  }
  return true;
}

void printStats(MovieGraph * graph)
{
  cout << "Number of Movies: " << graph->getNumMovies() << endl;
  cout << "Number of Edges: " << graph->getNumEdges() << endl;
  cout << "Number of Ratings: " << graph->getNumRatings() << endl;
  cout << "Highest Rated Movie: " << graph->getHighestRatedMovie() << endl;
}

void printMovieInfo(MovieGraph * g)
{
  cout << "Enter Movie Title" << endl;
  g->printMovieInfo(getCinString());
}

void recommendMovie(MovieGraph * g)
{
  cout << "Enter your favorite movie" << endl;
  MovieVertex * mv = g->findMovieVertexTitle(getCinString());
  if(mv == nullptr)
  {
    cout << "Movie not found" << endl;
    return;
  }
  int numSimRaters = 0;
  MovieVertex * rec = g->findSimilar(mv, &numSimRaters);
  cout << "Recommended Movie: " << rec->title <<
  ", number of common 5 star ratings: "<< numSimRaters
  << endl;
}

int askNumRatings()
{
  cout << "Enter number of users to analyze (1 - 138493)"<<
   "or enter 'all'" << endl;
  string s = getCinString();
  if(s == "all")
    return 138493;
  else
  {
    return stoi(s);
  }
}

int main(int argc, char * argv[])
{
  if(argc != 1)
    displayHelp();
  ifstream ratings;
  ifstream movies;
  askMoviesCSV(&movies);
  askRatingsCSV(&ratings);
  MovieGraph * graph = new MovieGraph();
  int numRaters = askNumRatings();
  processMoviesCSV(graph, &movies);
  bool rv = processRatingsCSV(graph, &ratings, numRaters);
  if (rv == false) {graph->~MovieGraph(); return -1;}
  cout << "finished." << endl;
  MovieVertex * mv;
  bool on = true;
  while(on)
  {
    switch(mainMenuSelect())
    {
      case 1:
        recommendMovie(graph);
        break;
      case 2: cout << "Printing Graph" << endl;
        graph->printMovieGraph();
        break;
      case 3:
        cout << "Enter Movie Title to see its connections" << endl;
        mv = graph->findMovieVertexTitle(getCinString());
        graph->printEdges(mv);
        break;
      case 4:
        printStats(graph);
        break;
      case 5:
        printMovieInfo(graph);
        break;
      case 6:
        on = false;
        break;
      default: cout << "Unrecognized Input" << endl;
        break;
    }
  }
  cout << "Goodbye!" << endl;
  graph->~MovieGraph();
  return 0;
}
