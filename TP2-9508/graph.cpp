#include "graph.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>

void Graph::addVertex(int node) { nodes[node] = {}; }

void Graph::addEdge(int from, int to) {
  this->addIfItsNotIn(from);
  this->addIfItsNotIn(to);
  nodes[from].push_front(to);
}

int Graph::size() { return nodes.size(); }

bool Graph::isIn(int node) { return (nodes.find(node)->first != node); }

void Graph::addIfItsNotIn(int node) {
  if (!this->isIn(node)) {
    this->addVertex(node);
  }
}

void Graph::clear() { nodes.clear(); }

void Graph::connectLast(int to) { this->addEdge(nodes.size() - 1, to); }

void Graph::disconnectNext(int nodo) { nodes[nodo].remove(nodo + 1); }

void Graph::connect(int from, int to) { nodes[from].push_front(to); }

bool Graph::_isCyclic(int start, std::list<int>& found) {
  if (hasBeenFound(start, found)) return true;
  found.push_front(start);
  auto begin = nodes.at(start).begin();
  auto end = nodes.at(start).end();
  if (std::any_of(begin, end,
                  [&found, this](int i) { return this->_isCyclic(i, found); }))
    return true;
  found.remove(start);
  return false;
}

bool Graph::isCyclic() {
  std::list<int> found;
  auto begin = nodes.begin();
  auto end = nodes.end();
  // Lo dejo así por el linter, pero la versión
  // anterior hacía menos accesos a memoria :S
  return std::any_of(begin, end, [&found, this](iterator_t it) {
    return this->_isCyclic(it.first, found);
  });
}

bool Graph::hasBeenFound(int node, std::list<int>& found) {
  return (find(found.begin(), found.end(), node) != found.end());
}

void Graph::dfs(int start, std::list<int>& found) {
  if (hasBeenFound(start, found)) return;
  found.push_front(start);
  for (int& i : nodes[start]) {
    if (!(hasBeenFound(i, found))) {
      Graph::dfs(i, found);
    }
  }
}

bool Graph::hasUnusedInstructions() {
  std::list<int> found;
  if (nodes.size() == 0) return false;
  dfs(1, found);
  return (found.size() != nodes.size());
}
