#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>

int main(){
  boost::adjacency_list<> graph;
  int noVert = 0;
  int start=0,end=0;
  char choice = 'y';
  
  std::cout<<"Enter the number of Vertices: ";
  std::cin>>noVert;
  while(choice == 'y') {
    std::cout<<"Enter the start and end vertex of the edge: ";
    std::cin>>start>>end;
    boost::add_edge(start,end,graph);
    std::cout<<"Do you want to add another edge(y/n): ";
    std::cin>>choice;
  }

  boost::write_graphviz(std::cout,graph);
  return 0;
}
