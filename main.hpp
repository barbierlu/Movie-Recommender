#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>


void displayHelp();
bool openFile(std::ifstream * in, std::string txt);
void processMoviesCSV(std::ifstream * csv);
void askRatingsCSV(std::ifstream * csv);
void askMoviesCSV(std::ifstream * csv);
std::string getCinString();
std::string alterTitleThe(std::string orig);

#endif
