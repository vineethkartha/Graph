#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

int main() {
  boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;
  enum {A,B,C,D,E};
  boost::add_edge(A,B,graph);
  boost::add_edge(A,C,graph);
  boost::add_edge(B,D,graph);
  boost::add_edge(B,E,graph);
  boost::add_edge(C,D,graph);
  boost::add_edge(C,E,graph);
  boost::add_edge(D,E,graph);
  boost::add_edge(B,B,graph);
  boost::add_edge(E,B,graph);

  boost::write_graphviz(std::cout,graph);
  return 0;
}
