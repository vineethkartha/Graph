#include<iostream>
#include<boost/graph/adjacency_list.hpp>

int main() {
  boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS> graph;
  enum {A,B,C,D};
  boost::add_edge(A,B,graph);
  boost::add_edge(A,C,graph);
  boost::add_edge(A,D,graph);
  boost::add_edge(B,D,graph);

  boost::adjacency_list<>::edge_iterator start,end;
  std::tie(start,end) = boost::edges(graph);
  for(auto ed = start;ed!=end;++ed) {
    std::cout<<*ed<<"\n";
  }
  return 0;
}
