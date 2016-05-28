#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

int main(){
  boost::adjacency_list<>graph;
  // creating the vertices
  boost::adjacency_list<>::vertex_descriptor v1 = boost::add_vertex(graph);
  boost::adjacency_list<>::vertex_descriptor v2 = boost::add_vertex(graph);
  boost::adjacency_list<>::vertex_descriptor v3 = boost::add_vertex(graph);
  boost::adjacency_list<>::vertex_descriptor v4 = boost::add_vertex(graph);
  //creating an edges
  boost::add_edge(v1,v2,graph);
  boost::add_edge(v2,v3,graph);
  boost::add_edge(v3,v4,graph);
  boost::add_edge(v4,v1,graph);
  boost::write_graphviz(std::cout,graph);
  return 0;
}
