#include<iostream>
#include<ostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include<boost/graph/breadth_first_search.hpp>

class custom_visitor : public boost::default_bfs_visitor {
public:
  template<typename Vertex,typename Graph>
  void discover_verted(Vertex v,const Graph &g) const {
    std::cout<<v<<std::endl;
  }
};

class Graph {
  boost::adjacency_list<> graph;
  boost::adjacency_list<>::vertex_iterator start, end;
  custom_visitor vis;
  
public:
  void readGraph();
  void printGraph(std::ofstream&);
  void bfs();
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

void Graph::bfs() {
  boost::breadth_first_search(graph,boost::vertex(0,graph),boost::visitor(vis));
}
int main() {
  Graph g;
  std::ofstream myfile;
  myfile.open("sam.dot");
  g.readGraph();
  g.bfs();
  g.printGraph(myfile);
  myfile.close();
  return 0;
}

