#include<iostream>
#include<string>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include<boost/graph/depth_first_search.hpp>
#include<boost/property_map/property_map.hpp>

struct VertexName {
  char name;
};

std::vector<std::vector<std::string>> words;
std::vector<std::string> word;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,VertexName> bGraph;
typedef bGraph::vertex_descriptor vertex_desc;
typedef bGraph::edge_descriptor edge_desc;
typedef bGraph::adjacency_iterator adjacency_it;

struct vertex_visitor : public boost::default_dfs_visitor {
  bGraph::vertex_descriptor root;
  const int parentRootTerm = 1;
  const int newWordTerm = 2;
  
  void discover_vertex(vertex_desc v, const bGraph& g) {
    if(v < root)
      throw parentRootTerm;
    if( g[v].name == '~') {
      words.push_back(word);
      word.clear();
    } else {
      if(! (v==root))
      word.push_back(std::string(1,g[v].name));
    }
      //std::cout<<g[v].name;
  }
};


class Trie {
  bGraph graph;
  vertex_desc start;
  adjacency_it adjStart, adjEnd;
  vertex_visitor vis;
  
public:
  Trie() {
    boost::add_vertex(graph);
    start = *boost::vertices(graph).first;
    graph[start].name = ' ';
  }
  void addToGraph(const std::string&);
  void printGraph(std::ofstream&);
  std::vector<vertex_desc> search(const std::string& );
  int autofill(const std::string&);
  void dfsautofill(const std::string&);
};

/*********************************************
addToGraph()

This functions reads asks the user to enter a string and stores it in a trie structure.

*/
void Trie::addToGraph(const std::string& str) {
  
  int stringCount = 0;
  int len = str.size();
  
  start = *boost::vertices(graph).first;
  
  while(stringCount < len) { 

    std::tie(adjStart,adjEnd) = boost::adjacent_vertices(start,graph);
    
    if(adjStart == adjEnd) {
      vertex_desc newVertex;
      newVertex = boost::add_vertex(graph);
      boost::add_edge(start,newVertex,graph);
      start = newVertex;
      graph[start].name=(char)str[stringCount];
      ++stringCount;
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
	vertex_desc newVertex;
	newVertex = boost::add_vertex(graph);
	boost::add_edge(start,newVertex,graph);
	start = newVertex;
	graph[start].name=(char)str[stringCount];
	++stringCount;
      }
    }
  }
  vertex_desc newVertex;
  newVertex = boost::add_vertex(graph);
  boost::add_edge(start,newVertex,graph);
  graph[newVertex].name='~';
}

void Trie::printGraph(std::ofstream &file) {
  boost::write_graphviz(file,graph,boost::make_label_writer(boost::get(&VertexName::name,graph)));
}

std::vector<vertex_desc> Trie::search(const std::string& str){

  int i = 0;
  int len = str.size();
  std::vector<vertex_desc> nodes{};
  
  start = *boost::vertices(graph).first;
  while(i<len) {
    std::tie(adjStart,adjEnd) = boost::adjacent_vertices(start,graph);
    if(adjStart == adjEnd) {
      return (std::vector<vertex_desc>{});
    } else {
      int count = 0;
      int nCount = 0;
      for(auto v = adjStart;v!=adjEnd; ++v,++count) {
	if(graph[*v].name == (char)str[i]) {
	  nodes.push_back(*v);
	  start = *v;
	  ++i;
	} else{
	  ++nCount;
	}
      }
      if(nCount == count)
	return (std::vector<vertex_desc>{});
    }
  }
  return nodes;
}

int Trie::autofill(const std::string& str) {
  std::vector<vertex_desc> nodes{};
  vertex_visitor visit;
  nodes = search(str);
  if( nodes.empty() ) {
    return 0;
  }
  visit.root = nodes.back();
  start = nodes.back();
  
  try {
    boost::depth_first_search(graph, boost::visitor(visit).root_vertex(visit.root));
  }
  catch(int e){
    //std::cout<<"\n\nover\n\n";
  }
  if(!(words.empty()) ) {
    for(auto w : words) {
      std::string temp;
      temp = std::accumulate(begin(w),end(w),temp);
      std::cout<<"\n"<<str<<temp;
    }
    std::cout<<"\n";
  }
  return 0;
}

/*
start at a vertex
if visited == 0
  mark its visited as 1;
  find the adjacent vertices
  if no adjacent vertices mark its visited as 2
  if there are adjacent vertices take first pass it to the same function

if visited ==1
  find adjacent vertices
  find adjacent vertex whose visited is !=2

 */

void dfsautofill(const std::string& str) {

}

int main() {
  Trie g;
  char choice = 'y';
  std::vector<vertex_desc> node;
  
  std::string rWord, searchWord;
  std::ofstream myfile;

  std::ifstream wordFile;
  
  wordFile.open("words.txt");
  while ( getline (wordFile,rWord) ) {
    std::cout<<rWord<<"\n";
    g.addToGraph(rWord);
  }
  wordFile.close();
  /*while(choice == 'y') {
      std::cout<<"Enter the word: ";
      std::cin>>rWord;
      g.addToGraph(rWord);
      std::cout<<"Do you want to continue entering words (y/n): ";
      std::cin>>choice;
      }*/

  
  std::cout<<"Enter a string to search: ";
  std::cin>>searchWord;
  node = g.search(searchWord);
  if( node.empty() )
    std::cout<<searchWord<<" not found\n";
  else
    std::cout<<searchWord<<" found\n";

  g.autofill(searchWord);
  myfile.open("sam.dot");
  g.printGraph(myfile);
  myfile.close();  
  return 0;
}

