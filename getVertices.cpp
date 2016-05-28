#include<iostream>
#include<boost/graph/adjacency_list.hpp>

int main() {
  boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> graph;

  enum {A,B,C,D};
  boost::add_edge(A,B,graph);
  boost::add_edge(A,C,graph);
  boost::add_edge(A,D,graph);

  boost::adjacency_list<>::vertex_iterator start,end;
  std::tie(start,end) = boost::vertices(graph);

  for(auto v = start;v!=end;++v) {
    std::cout<<*v<<"\n";
  }
  return 0;
}
