#include <algorithm>
#include <iostream>
#include <vector>

class Solver {
 public:
  Solver(size_t vertexNum, size_t edgeNum)
      : vertexNum(vertexNum), edgeNum(edgeNum) {}

  // builds solution tree
  void Solve() {
    // 0 - no edge, 1 - common edge, 2 - edge with artifact
    std::vector<std::vector<int>> graph(vertexNum);
    for (size_t i = 0; i < vertexNum; i++) {
      graph[i].resize(vertexNum, 0);
    }
    Init(graph);

    std::vector<Edge> bridges = FindBridges(graph);
    for (auto e : bridges) {
      graph[e.u][e.v] = 0;
      graph[e.v][e.u] = 0;
    }

    size_t numOfComponents = 0;
    std::vector<bool> used(vertexNum, false);
    component.resize(vertexNum, 0);
    for (size_t i = 0; i < vertexNum; i++) {
      if (!used[i]) {
        ConnectedComponentDFS(i, numOfComponents, used, component, graph);
        ++numOfComponents;
      }
    }

    // build tree where vertices are components of graph and edges are bridges
    tree.resize(numOfComponents);
    for (size_t i = 0; i < numOfComponents; i++) {
      tree[i].resize(numOfComponents, 0);
    }
    for (auto e : bridges) {
      if (e.hasArtifact) {
        tree[component[e.u]][component[e.v]] = 2;
        tree[component[e.v]][component[e.u]] = 2;
      } else {
        tree[component[e.u]][component[e.v]] = 1;
        tree[component[e.v]][component[e.u]] = 1;
      }
    }

    compHasArtifact.resize(numOfComponents, false);
    for (size_t i = 0; i < vertexNum; i++) {
      for (size_t j = 0; j < vertexNum; j++) {
        if (graph[i][j] == 2) {
          compHasArtifact[component[i]] = true;
        }
      }
    }
  }

  // returns result for specific pair of vertices using solution tree
  bool GetResult(size_t startVert, size_t endVert) {
    std::vector<bool> hasArtifactOnWayTo(tree.size(), false);
    hasArtifactOnWayTo[component[startVert]] =
        compHasArtifact[component[startVert]];

    std::vector<bool> used(tree.size(), false);
    FindArtifactsDFS(component[startVert], used, hasArtifactOnWayTo);
    return hasArtifactOnWayTo[component[endVert]];
  }

 private:
  size_t vertexNum;
  size_t edgeNum;

  std::vector<std::vector<int>> tree;
  std::vector<size_t> component;
  std::vector<bool> compHasArtifact;

  void Init(std::vector<std::vector<int>>& graph) {
    for (size_t i = 0; i < edgeNum; i++) {
      size_t x = 0, y = 0, z = 0;
      std::cin >> x >> y >> z;
      if (z) {
        graph[x - 1][y - 1] = 2;
        graph[y - 1][x - 1] = 2;
      } else {
        graph[x - 1][y - 1] = 1;
        graph[y - 1][x - 1] = 1;
      }
    }
  }

  struct Edge {
    size_t u;
    size_t v;
    bool hasArtifact;

    Edge(size_t u, size_t v, bool haasArtifact)
        : v(v), u(u), hasArtifact(haasArtifact) {}
  };
  int time = 0;
  std::vector<Edge> FindBridges(std::vector<std::vector<int>>& graph) {
    std::vector<bool> used(vertexNum, false);
    std::vector<int> inTime(vertexNum, 0);
    std::vector<int> upEarliest(vertexNum, 0);
    std::vector<Edge> bridges;
    for (size_t i = 0; i < vertexNum; i++) {
      if (!used[i]) {
        BridgesDFS(i, -1, used, inTime, upEarliest, bridges, graph);
      }
    }

    return bridges;
  }

  void BridgesDFS(size_t from, size_t par, std::vector<bool>& used,
                  std::vector<int>& inTime, std::vector<int>& upEarliest,
                  std::vector<Edge>& bridges,
                  std::vector<std::vector<int>>& graph) {
    used[from] = true;
    inTime[from] = time;
    ++time;
    upEarliest[from] = inTime[from];

    for (size_t to = 0; to < vertexNum; to++) {
      if (!graph[from][to] || to == par) {
        continue;
      }
      if (used[to]) {
        upEarliest[from] = std::min(upEarliest[from], inTime[to]);
      } else {
        BridgesDFS(to, from, used, inTime, upEarliest, bridges, graph);
        upEarliest[from] = std::min(upEarliest[from], upEarliest[to]);
        if (inTime[from] < upEarliest[to]) {
          bridges.push_back(Edge(from, to, graph[from][to] == 2));
        }
      }
    }
  }

  void ConnectedComponentDFS(size_t v, size_t comp, std::vector<bool>& used,
                             std::vector<size_t>& component,
                             std::vector<std::vector<int>>& graph) {
    component[v] = comp;
    used[v] = true;
    for (size_t to = 0; to < vertexNum; to++) {
      if (graph[v][to] && !used[to]) {
        ConnectedComponentDFS(to, comp, used, component, graph);
      }
    }
  }

  void FindArtifactsDFS(size_t v, std::vector<bool>& used,
                        std::vector<bool>& hasArtifactOnWayTo) {
    used[v] = true;
    for (size_t to = 0; to < tree.size(); to++) {
      if (tree[v][to] && !used[to]) {
        if (hasArtifactOnWayTo[v] || tree[v][to] == 2 || compHasArtifact[to]) {
          hasArtifactOnWayTo[to] = true;
        }
        FindArtifactsDFS(to, used, hasArtifactOnWayTo);
      }
    }
  }
};

int main() {
  size_t vertexNum = 0;
  size_t edgeNum = 0;
  std::cin >> vertexNum >> edgeNum;
  Solver slv(vertexNum, edgeNum);
  slv.Solve();

  size_t startVert = 0;
  size_t endVert = 0;
  std::cin >> startVert >> endVert;
  if (slv.GetResult(startVert - 1, endVert - 1)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}