#include<iostream>


static std::pair<int,int> findMin(int *array, int index,int size) {
  int min = array[index];
  int minInd = index;
  for(int i=index;i<size;++i) {
    if(array[i]<min && array[i]!=0) {
      min = array[i];
      minInd = i;
    }
  }
  return std::make_pair(min,minInd);
}

class AdjacencyMatrix {
private:
  int **adjMat;
  int noOfvertices;
public:
  void createGraph();
  void displayGraph();
  void add_edge(int v1,int v2);
  void del_edge(int v1,int v2);
  void shortestPath();
};

void AdjacencyMatrix::createGraph() {
  std::cout<<"Enter the number of vertices: ";
  std::cin>>noOfvertices;
  adjMat = new int* [noOfvertices];
  for(int i=0;i<noOfvertices;++i) {
    adjMat[i] = new int[noOfvertices];
  }
  std::cout<<"Enter the weight of the connection between each vertex\n";
  for(int i=0;i<noOfvertices;++i){
    for(int j=0;j<noOfvertices;++j) {
      std::cout<<"edge"<<i<<"->"<<j<<": ";
      std::cin>>adjMat[i][j];
    }
  }
}
void AdjacencyMatrix::displayGraph() {
  std::cout<<"\n The Graph is\n";
  for(int i=0;i<noOfvertices;++i){
    for(int j=0;j<noOfvertices;++j) {
      std::cout<<"\nedge"<<i<<"->"<<"j: ";
      std::cout<<adjMat[i][j];
    }
  }
}

void AdjacencyMatrix::shortestPath() {
  int row = 0;
  int index = 0;
  int cost = 0;
  int *tempCost = new int[noOfvertices]();
  while(row < noOfvertices-1) {
    int column = row + 1;
    for(int i=column;i<noOfvertices;++i) {
      if(adjMat[row][i] < tempCost[i] || tempCost[i] ==0)
	tempCost[i] = adjMat[row][i];
    }
    std::pair<int,int> result;
    result = findMin(tempCost, column,noOfvertices);
    cost += result.first;
    row = result.second;
  }
  std::cout<<"Cost of shortest path is : "<<cost<<std::endl;
}

int main() {
  AdjacencyMatrix graph;
  graph.createGraph();
  graph.shortestPath();
  //  graph.displayGraph();
  return 0;
}
