#include "GraphBase.hpp"
#include <string>
#include <vector>
#include <map>
#include <iterator>

class Edge {
  public:
    std::string v1;
      std::string v2;
      unsigned long w;
      Edge();
      friend class Graph;
};

class Graph : GraphBase {
  private:
    Edge* e = new Edge;
    int N;

  public: // Most of the ADTs used in the code are declared here
  std::vector<std::string> vertex_vector;
  std::vector<std::string>::iterator itr;
  std::vector<Edge*> edge_vector;
  std::vector<Edge*>::iterator itr2;
  std::map<std::string, size_t> minDistance;
  std::map<std::string, size_t>::iterator itr3;
  std::map<std::string, std::string> visited;
  Graph();
  ~Graph();
  void addVertex(std::string label);
  void removeVertex(std::string label);
  void addEdge(std::string label1, std::string label2, unsigned long weight);
  void removeEdge(std::string label1, std::string label2);
  unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};