#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include <queue>

int main(){
  boost::adjacency_list<> graph;
  boost::adjacency_list<>::vertex_iterator start, end;
  boost::adjacency_list<>::adjacency_iterator adjStart, adjEnd;

  std::queue<boost::adjacency_list<>::vertex_iterator> q;
  int startV=0,endV=0;
  char choice = 'y';
  
  while(choice == 'y') {
    std::cout<<"Enter the start and end vertex of the edge: ";
    std::cin>>startV>>endV;
    boost::add_edge(startV,endV,graph);
    std::cout<<"Do you want to add another edge(y/n): ";
    std::cin>>choice;
  }
  std::tie(start,end) = boost::vertices(graph);
  auto tempNode = start;
  while(tempNode != end) {
    std::tie(adjStart,adjEnd) = boost::adjacent_vertices(*tempNode,graph);

    std::cout<<*tempNode<<std::endl;

    for(auto v = adjStart;v!=adjEnd;++v) {
      std::cout<<*v<<std::endl;
      //q.push(graph[*v]); 
    }
    break;
    //tempNode = q.front();
    //q.pop();
  }
  boost::write_graphviz(std::cout,graph);
  return 0;
}
