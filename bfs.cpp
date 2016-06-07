#include<iostream>
#include<fstream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include <queue>

/**
 * This code performs a breadth first search of a given graph
 * It starts from the root node. Reads the adjacent nodes and pushes them to a queue. 
 * From the queue each node is popped out and its adjacent nodes are found and pushed into the queue.
 */

class Graph {
  boost::adjacency_list<> graph;
  boost::adjacency_list<>::vertex_iterator start, end;
  boost::adjacency_list<>::adjacency_iterator adjStart, adjEnd;
  std::queue<boost::adjacency_list<>::adjacency_iterator> q;
  
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
  int vertices = boost::num_vertices(graph);
  bool *visited = new bool[vertices];
  bool flag = 1;
  for(int i = 0;i<vertices;++i)
    visited[i] = 0;
  std::tie(start,end) = boost::vertices(graph);
  auto tempNode = *start;
  do {
    if(!visited[tempNode]) {
      std::tie(adjStart,adjEnd) = boost::adjacent_vertices(tempNode,graph);
      std::cout<<tempNode<<std::endl;
      visited[tempNode] = 1;
      for(auto v = adjStart;v!=adjEnd;++v) {
	q.push(v);
      }
    } else {
      std::cout<<"Already visited\n";
    }
    if(!q.empty()) {
      tempNode = *(q.front());
      q.pop();
      flag=1;
    } else {
      flag = 0;
    }
  }while(flag);
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

    } else {
      std::cout<<"Already visited\n";
    }
    std::cout<<std::endl;
    if(!q.empty()) {
      tempNode = *(q.front());
      q.pop();
      flag=1;
    } else {
      flag = 0;
    }
  }while(flag);
  boost::write_graphviz(std::cout,graph);
  return 0;
}
