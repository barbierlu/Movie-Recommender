#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include "graph.hpp"

struct MovieNode
{
  std::string title;
  MovieVertex * mv;
  MovieNode * p;
  MovieNode * l;
  MovieNode * r;
}

class RBTree
{
public:
  RBTree();
  ~RBTree();
  void print(); // print the rb tree
  void add(); // add a movie to the rb tree
  int count(); // count the longest path
private:
  MovieVertex * root;

};

#endif
