#include<iostream>
#include<fstream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

class Graph {
  boost::adjacency_list<>graph;
  boost::adjacency_list<>::vertex_iterator start, end;
  boost::adjacency_list<>::adjacency_iterator adjStart, adjEnd;
  bool *visited;
  
public:
  void readGraph();
  void printGraph(std::ofstream&);
  int getRoot();
  bool *getVisited();
  void dfs(int, bool*);
  
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
  
  int vertices = boost::num_vertices(graph);
  visited = new bool[vertices];
  for(int i=0;i<vertices;++i)
    visited[i] = 0;
}

void Graph::printGraph(std::ofstream &file) {
  boost::write_graphviz(file,graph);
}

int Graph::getRoot() {
  std::tie(start,end) = boost::vertices(graph);
  return *start;
}

bool* Graph::getVisited() {
  return visited;
}
void Graph::dfs(int node,bool *visited) {

  std::cout<<node<<std::endl;
  visited[node] = 1;
std::tie(adjStart,adjEnd) = boost::adjacent_vertices(node,graph);
 for(auto v = adjStart;v!=adjEnd;++v) {
   if(!visited[*v]) {
     dfs(*v,visited);
   }
 }
}

int main() {
  Graph g;
  int root;
  bool *vis;
  std::ofstream myfile;
  myfile.open("sam.dot");
  g.readGraph();
  root = g.getRoot();
  vis = g.getVisited();
  g.dfs(root,vis);
  myfile.close();
  return 0;
}
