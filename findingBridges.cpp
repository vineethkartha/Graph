#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>boostGraph;

typedef boostGraph::vertex_iterator vIterator;
typedef boostGraph::edge_iterator eIterator;

typedef boostGraph::vertex_descriptor vDescriptor;
typedef boostGraph::edge_descriptor eDescriptor;


class Graph {
  boostGraph graph;
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
  /**

1) take an edge and find num of connected components.
2) remove that edge and again find number of components
3) If the above two numbers are the same then the edge is not a a bridge
4) Proceed untill all edges are checked.
  */
  int s;
  auto temp = graph;
  std::vector<int> component (boost::num_vertices (temp));
  int origComp = boost::connected_components(graph,&component[0]);
  std::tie(start,end) = boost::edges(temp);
  int n = boost::num_edges(temp);
  int i =0;
  auto ed =start;
  auto t = ed;
  while(i<n) {
    auto src = boost::source(*ed,temp);
    auto tar = boost::target(*ed,temp);
    t = ed;
    ed++;
    remove_edge(*t,temp);
    s = boost::connected_components(temp,&component[0]);
    auto e = add_edge(src,tar,temp);
    if(s>origComp) {
      std::cout<<e.first<<"Is a Bridge\n";
    }
    i++;
  }
}

int main() {
  Graph g;
  std::ofstream myfile;
  g.readGraph();
  g.findBridge();
  myfile.open("sam.dot");
  g.printGraph(myfile);
  myfile.close();  
  return 0;
}
