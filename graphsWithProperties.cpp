/**
 * This code demonstrates how Vertices can have properties in the Boost graph.
 * Here is use the bundled properties. Which is the easiest way to assign properties to vertices and edges.
 * Refere: http://www.boost.org/doc/libs/1_55_0/libs/graph/doc/bundles.html
 */

#include<iostream>
#include<string>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

struct VertexName {
  char name;
};

class Graph {
  boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,VertexName> graph;
  boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,VertexName>::vertex_descriptor start;
  
public:
  void readGraph();
  void printGraph(std::ofstream&);
};

void Graph::readGraph() {
  
  std::string str;
  std::cout<<"Enter a string: ";
  std::cin>>str;
  int len = str.size();
  // here I leave the first vertex with blank properties. This is because I will be using the code later to implement trie.
  boost::add_vertex(graph);
  start = *boost::vertices(graph).first;
  graph[start].name = ' ';
  for(int i=1;i<=len;++i) {
    ++start;
    boost::add_edge(i-1,i,graph);
    graph[start].name = (char)str[i-1];
  }
}

void Graph::printGraph(std::ofstream &file) {
  boost::write_graphviz(file,graph,boost::make_label_writer(boost::get(&VertexName::name,graph)));
}


int main() {
  Graph g;
  std::ofstream myfile;
  myfile.open("sam.dot");
  g.readGraph();
  g.printGraph(myfile);
  myfile.close();
  return 0;
}

