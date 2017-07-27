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
    std::cout << "2. Print movie list" << std::endl;
    std::cout << "3. Print connection list" << std::endl;
    std::cout << "4. See statistics" << std::endl;
      // Num raters, num movies, avg rating,
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
  << " in the form of two files 'Movies.csv' and 'Ratings.csv'. These large"
  << " files can be downloaded from https://grouplens.org/datasets/movielens/"
  << ". Simply enter a movie to receive a recommendation with the information"
  << " regarding the recommended movie." << endl;
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
    // cout << "has The!" << endl;
    size_t pos = orig.rfind('T');
    string check = orig.substr(0, pos-2);
    // cout <<"check:"<< check << "." << endl;
    string concat = "The " + check;
    // cout <<"concat:"<<concat<<"."<<endl;
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
  // cout << "s:" << s << endl;

  while(true)
    {
    getline(*csv, s, '\n');
    if(s == prev || s=="") // check for last line
      break;
    // if(counter++ == 122)
    //   break;
    // Id
    s1 = s.substr(0, s.find(','));
    id = stoi(s1);
    // cout << "id:" << id <<"."<< endl;
    // title
    size_t firstComma = s.find(',') + 1;
    s2 = s.substr(firstComma, s.rfind(',')-firstComma);
    if(s2.at(0) != '\"')
    {
      title = s2.substr(0, s2.size()-7);
      // cout << "s2:" << s2 <<"."<< endl;
      // cout << "title:"<<title<<"."<<endl;
    }
    else
    {
      // cout << "quotations" << endl;
      title = s2.substr(1, s2.size()-9);
      // cout << "s2:" << s2 <<"."<< endl;
      // cout << "title:"<<title<<"."<<endl;
    }
    title = alterTitleThe(title);
    // cout << "Adding: " << id << " " << title<<"." << endl;
    graph->insertMovieVertex(title, id);
    prev = s;
  }
}

bool processRatingsCSV(MovieGraph * graph, ifstream * csv)
{
  int counter = 0;
  string s,s1,s2,prev; // helper parsing strings

  string rating_s, movieId_s, userId_s;
  int movieId, userId, prevUserId=-1;
  float rating;

  bool sameUser = false;

  // other movies the user has rated
  vector<MovieVertex> userOtherVertices;
  vector<float> userOtherRatings;

  getline(*csv, s); // disregard first line
  cout << "s:"<<s<<endl;
  while(true)
    {
    getline(*csv, s, '\n');
    cout << "s:"<<s<<endl;
    if(s == prev || s=="") // check for last line
      break;
    if(counter++ == 10) // 7,3 (1000)
      break;
    s1 = s.substr(0, s.rfind(','));
    rating_s = s1.substr(s1.rfind(',')+1);
    s2 = s1.substr(0, s1.rfind(','));
    movieId_s = s2.substr(s2.rfind(',')+1);
    userId_s = s2.substr(0, s2.rfind(','));
    userId = stoi(userId_s);
    movieId = stoi(movieId_s);
    rating = stof(rating_s);
    cout << userId << " " << movieId << " "
    << rating << "." << endl;

    MovieVertex * mv = graph->findMovieVertexId(movieId);
    if(mv == nullptr)
    {
      cout << "[ERROR] " << movieId << " not found."<<endl;
      return false;
    }
    cout << userId << " rated "<<mv->title <<"."<< endl;

    if(prevUserId == userId)
    {
      sameUser = true;
      cout << "same user" <<endl;
    }
    else
    {
      sameUser = false;
      cout << "new user" << endl;
    }

    if (sameUser) // link that movie to all the other ones
    {
      for (int i = 0; i < userOtherVertices.size(); i++)
      {
        graph->insertMovieEdge(mv, rating,
          &(userOtherVertices[i]), userOtherRatings[i]);
        cout << "linked:" << mv->title <<". to:"<<
          userOtherVertices[i].title<<"."<<endl;
      }
      userOtherVertices.push_back(*mv);
      userOtherRatings.push_back(rating);
    }
    else
    { // delete vectors
      userOtherVertices.clear();
      userOtherRatings.clear();
      cout << "deleted vectors:"<<
      userOtherVertices.empty()<<" "<<
      userOtherRatings.empty()<<endl;
      userOtherVertices.push_back(*mv);
      userOtherRatings.push_back(rating);
    }
    prev = s;
    prevUserId = userId;
  }
  // graph->computeEdgeAvgs();
  return true;
}

void printStats(MovieGraph * graph)
{
  cout << "Number of Movies: " << graph->getNumMovies() << endl;
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
  processMoviesCSV(graph, &movies);
  bool rv = processRatingsCSV(graph, &ratings);
  if (rv == false) {graph->~MovieGraph(); return -1;}
  cout << "finished." << endl;
  bool on = true;
  while(on)
  {
    switch(mainMenuSelect())
    {
      case 1:
        break;
      case 2: cout << "Printing Graph" << endl;
        graph->printMovieGraph();
        break;
      case 3:
        graph->printEdges();
        break;
      case 4:
        printStats(graph);
        break;
      case 5:
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
