#include<iostream>
#include<string>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

struct VertexName {
  char name;
};

class Graph {
  boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,VertexName> graph;
  boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,VertexName>::vertex_descriptor start;
  boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,VertexName>::adjacency_iterator adjStart, adjEnd;
  
public:
  Graph() {
    boost::add_vertex(graph);
    start = *boost::vertices(graph).first;
    graph[start].name = ' ';
  }
  void readGraph();
  void printGraph(std::ofstream&);
};

void Graph::readGraph() {
  
  std::string str;
  int stringCount = 0;
  char choice ='y';
  
  while(choice == 'y') {
    stringCount = 0;
    std::cout<<"Enter a string: ";
    std::cin>>str;
    int len = str.size();
    start = *boost::vertices(graph).first;

    while(stringCount<len){ 
      std::tie(adjStart,adjEnd) = boost::adjacent_vertices(start,graph);
      
      if(adjStart == adjEnd) {
	boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,VertexName>::vertex_descriptor newVertex;
	newVertex = boost::add_vertex(graph);
	boost::add_edge(start,newVertex,graph);
	start = newVertex;
	graph[start].name=(char)str[stringCount];
	++stringCount;
	std::cout<<stringCount<<std::endl;
      } else {
	bool flag = 0;
	int count = 0;
	int nodeCount = 0;
	for(auto v = adjStart;v!=adjEnd;++v,++count) {
	  if(graph[*v].name == (char)str[stringCount]) {
	    ++stringCount;
	    start = *v;
	    flag =1;
	    break;
	  } else {
	    nodeCount++;
	  }
	}
	if(nodeCount == count && !flag) {
	  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,VertexName>::vertex_descriptor newVertex;
	  newVertex = boost::add_vertex(graph);
	  boost::add_edge(start,newVertex,graph);
	  start = newVertex;
	  graph[start].name=(char)str[stringCount];
	  ++stringCount;
	}
      }
    }
    std::cout<<"Do you want to enter again: ";
    std::cin>>choice;
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

