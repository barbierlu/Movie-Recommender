/*
  Luke Barbier
  Final Project
  Montero Quesada
*/

#include <iostream>
#include <fstream>
#include "main.hpp"
using namespace std;

std:: string getCinString()
{
  // Concatenation technique to get multiword cin strings
  std::string title1, title2;
  cin >> title1;
  getline(cin, title2);
  return title1 + title2;
}

void askMoviesCSV(ifstream * csv)
{
  cout << "Please enter the Movies.csv file:" << endl;
  openFile(csv, getCinString());
}

void askRatingsCSV(ifstream * csv)
{
  cout << "Please enter the Ratings.csv file:" << endl;
  openFile(csv, getCinString());
}

void displayHelp()
{
  cout << "This program recommends movies by analyzing significant data"
  << " in the form of two files 'Movies.csv' and 'Ratings.csv'. These large"
  << " files can be downloaded from https://grouplens.org/datasets/movielens/"
  << ". Simply enter a movie to receive a recommendation with the information"
  << " regarding the recommended movie." << endl;
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

void processMoviesCSV(ifstream * csv)
{
  string s, prev;
  int id;
  string title = "";

  getline(*csv, s, ',');
  if (s != "movieId")
  {
    cout << "invalid Movies.csv file." << endl;
    return;
  }
  getline(*csv, s, ',');
  getline(*csv, s, '\n');

  while(true)
  {
    // ID
    getline(*csv, s, ',');
    if(s == prev || s=="")
      break;
    cout << "id: "<<s<<endl;
    id = stoi(s);
    // Title
    getline(*csv, title, ',');
    getline(*csv, s, '\n');
    cout << "Adding: " << id << " " << title << endl;
    prev = s;
  }
}

int main(int argc, char * argv[])
{
  if(argc != 1)
    displayHelp();
  ifstream ratings;
  ifstream movies;
  askMoviesCSV(&movies);
  //askRatingsCSV(&ratings);
  processMoviesCSV(&movies);
  cout << "finished." << endl;

  return 0;
}
