/*
  Luke Barbier
  Final Project
  Montero Quesada
*/

#include <iostream>
#include <fstream>
#include "main.hpp"
using namespace std;

std::string getCinString()
{
  // Concatenation technique to get multiword cin strings
  std::string title1, title2;
  cin >> title1;
  getline(cin, title2);
  return title1 + title2;
}

int mainMenuSelect(void)
{
  int sel = 0;
  while(true)
  {
    std::cout << "======Main Menu======" << std::endl;
    std::cout << "1. Find a movie" << std::endl;
    std::cout << "2. Rent a movie" << std::endl;
    std::cout << "3. Print the inventory" << std::endl;
    std::cout << "4. Delete a movie" << std::endl;
    std::cout << "5. Count the movies" << std::endl;
    std::cout << "6. Count the longest path" << std::endl;
    std::cout << "7. Quit" << std::endl;
    std::cin >> sel;
    if(sel > 0 && sel < 8)
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

// function that moves 'The' to the front of the title
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

void processMoviesCSV(ifstream * csv)
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
    cout << "Adding: " << id << " " << title<<"." << endl;
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

  switch(mainMenuSelect())
  {
    case 1: //cout << "Find Movie" << endl;
      findMov(tree);
      break;
    case 2: //cout << "Rent Movie" << endl;
      rentMov(tree);
      break;
    case 3: //cout << "Print Inventory" << endl;
      tree->printInv();
      break;
    case 4: //cout << "Delete Movie" << endl;
      deleteMovie(tree);
      break;
    case 5: //cout << "Count Movies" << endl;
      cout << "Tree contains: "<<tree->countMovies()
       << " movies."<<endl;
      break;
    case 6: //cout << "Count Longest Path" << endl;
      cout << "Longest Path: " << tree->countLongestPath() << endl;
      break;
    case 7: //cout << "Quiting" << endl;
      on = false;
      break;
    default: cout << "Unrecognized Input" << endl;
      break;
  }
  cout << "Goodbye!" << endl;
  // delete rbTree and Movie Graph
  return 0;
}
