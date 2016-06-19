#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>boostGraph;
typedef boostGraph::edge_iterator eIterator;


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

/**

1) take an edge and find num of connected components.
2) remove that edge and again find number of components
3) If the above two numbers are the same then the edge is not a a bridge
4) Proceed untill all edges are checked.
*/

void Graph::findBridge() {

  int numOfComponents = 0;
  std::vector<int> component (boost::num_vertices (graph));
  int numOfCompInGraph = boost::connected_components(graph,&component[0]);

  std::tie(start,end) = boost::edges(graph);
  int numOfEdges = boost::num_edges(graph);
  int edgeIndex = 0;
  auto temp = start;
  
  while(edgeIndex < numOfEdges) {
    auto src = boost::source(*start,graph);
    auto tar = boost::target(*start,graph);
    temp = start;
    start++;
    remove_edge(*temp,graph);
    numOfComponents = boost::connected_components(graph,&component[0]);
    auto edge = add_edge(src,tar,graph);
    if(numOfComponents > numOfCompInGraph) {
      std::cout<<edge.first<<"Is a Bridge\n";
    }
    edgeIndex++;
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
