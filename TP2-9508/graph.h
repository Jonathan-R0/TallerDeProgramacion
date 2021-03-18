#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <map>
#include <string>
#include <utility>

typedef std::pair<int, std::list<int>> iterator_t;

class Graph {
 private:
  std::map<int, std::list<int>> nodes;
  int size();
  bool hasBeenFound(int node, std::list<int>& found);
  bool _isCyclic(int start, std::list<int>& found);

 public:
  Graph() {}
  void addVertex(int node);
  bool isIn(int node);
  void addIfItsNotIn(int node);
  void addEdge(int from, int to);
  bool isCyclic();
  void dfs(int start, std::list<int>& found);
  void connect(int from, int to);
  void connectLast(int to);
  bool hasUnusedInstructions();
  void disconnectNext(int nodo);
  void clear();
};

#endif  // GRAPH_H_
