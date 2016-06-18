#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graphviz.hpp>


typedef boost::adjacency_list<> graph;
typedef graph::vertex_iterator vIterator;
typedef graph::edge_iterator eIterator;

class custom_visitor:public default_dfs_visitor {
  int count;
public:
  void custom_visitor() {
    count = 0;
  }
  void discover_vertex(vDescriptor v, const graph&g) {
    ++count;
  }
  int getCount() const{
    return count;
  }
};

class Graph {
  graph G;
  eIterator start,end;

public:
  void readGraph();
  void printGraph(std::ofstream&);
  void findBridge();
};

void Graph::readGraph() {
  char choice = 'y';
  int startV=0,endV=0;

  while(choice == 'y') {
    std::cout<<"Enter the start and end vertex of the edge: ";
    std::cin>>startV>>endV;
    boost::add_edge(startV,endV,graph);
    std::cout<<"Do you want to add another edge(y/n): ";
    std::cin>>choice;
  }
}

void Graph::printGraph(std::ofstream &file) {
  boost::write_graphviz(file,graph);
}

void Graph::findBridge() {

}

int main() {

  return 0;
}
