#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>

using namespace std;

/* Classes */
class Vertex {
  private:
    int _Id;
    int _grade;
    vector<Vertex *> _connections;
    int _discoveryTime;
    int _low;
    bool _visited;

  public:
    Vertex() {
      _visited = false;
      _discoveryTime = -1;
      _low = 0;
    }
    ~Vertex() {}

    int getGrade() { return _grade; }

    int getId() { return _Id; }

    void setGrade(int newGrade) { _grade = newGrade; }

    void setId(int id) { _Id = id; }

    int getDiscoveryTime() { return _discoveryTime; }

    int getLow() { return _low; }

    bool isVisited() { return _visited; }

    void setVisited() { _visited = true; }

    void setDiscoveryTime(int disc) { _discoveryTime = disc; }

    void setLow(int low) { _low = low; }

    void addConnections(Vertex *v) { _connections.push_back(v); }

    vector<Vertex *> getAdjacents() { return _connections; }

    bool hasConnection(int id) {
      for (Vertex *v : _connections)
        if (v->getId() == id)
          return true;
      return false;
    }
    
    bool hasChild() { return !(_connections.empty()); }
};

class Graph {
  private:
    int _numVertexes;
    Vertex *_vertexes;

  public:
    Graph() {}
    Graph(int vertexes) {
      _vertexes = new Vertex[vertexes];
      _numVertexes = vertexes;
    }
    ~Graph() { delete _vertexes; }

    int getGrade(int num) { return _vertexes[num].getGrade(); }

    void newVert(int id) {
      int grade = 0;
      if (scanf("%d", &grade) != 1)
        printf("ERRO!\n");
      _vertexes[id].setId(id);
      _vertexes[id].setGrade(grade);
    }

    Vertex *getVertex(int id) { return &_vertexes[id]; }

    int getNumVectors() { return _numVertexes; }

    void addConnection(int id, int idConnection) {
      _vertexes[id].addConnections(&_vertexes[idConnection]);
    }
};

/* Global Variable */

Graph *_g;
vector<int> path;
stack<Vertex *> stackList;
int _time = 0;

/* Functions */

void tarjan(int id, bool visited[]) {
  
  Vertex* vertex = _g->getVertex(id);
  vertex->setDiscoveryTime(++_time);
  vertex->setLow(++_time);
  visited[vertex->getId()] = true;

  stackList.push(vertex);

  vector<Vertex *>::iterator iter;
  for(iter = vertex->getAdjacents().begin(); iter != vertex->getAdjacents().end(); iter++){
    Vertex *v = *iter;

    if(v->getDiscoveryTime() == -1)  // not visited yet
    {
      printf("OIIIIIIII\t");
      tarjan(v->getId(), visited);
      vertex->setLow(min(vertex->getLow(), v->getLow()));
    }

    else if(visited[v->getId()]){
      vertex->setLow(min(vertex->getLow(), v->getDiscoveryTime()));
      printf("SEGUNDO ELSE\t");
      }
  }

  Vertex *w;
  printf("ANTES DO IF E WHILE\t");
  if(vertex->getLow() == vertex->getDiscoveryTime()){
    printf("MESMO ANTES DO WHILE\t");
    while(stackList.top() != vertex){
      printf("ANTES DO W\t");
      w = (Vertex *)stackList.top();
      printf("DEPOIS DO W\t");
      printf("%d\t", w->getId());
      path.push_back(w->getId());
      stackList.pop();
    }
  }
}

void parseCommandLine() {
  int id = 0, idConnection = 0;
  int num_vert = 0, num_edges = 0;

  if (scanf("%d,%d", &num_vert, &num_edges) != 2)
    fprintf(stderr, "Scanf error\n"); //1 linha do input

  if (num_vert < 2)
  {
    fprintf(stderr, "Minimum of students are 2.");
    exit(1);
  }
  else if (num_edges < 1)
  {
    fprintf(stderr, "Minimum connections are 1.");
    exit(1);
  }

  _g = new Graph(num_vert); //Inicialize graph

  for (int i = 1; i <= num_vert; i++) //Set Vertices with grade
    _g->newVert(i - 1);

  for (int i = 1; i <= num_edges; i++) {//Set relations between
    if (scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");
    _g->addConnection(id - 1, idConnection - 1);
  }
}

void max(Vertex *a, Vertex *b) {
  if (a->getGrade() > b->getGrade())
    b->setGrade(a->getGrade());

  if(a->hasConnection(b->getId()) && b->getGrade() > a->getGrade())
    max(b,a);
}

void findPath(int v, bool visited[]) {
  visited[v] = true;
  Vertex *vertex = _g->getVertex(v);
  for (Vertex *adjVertex : vertex->getAdjacents())
  {
    if (!visited[adjVertex->getId()])
      findPath(adjVertex->getId(), visited);
  }
  path.insert(path.begin(), v);
}

void propaga(int v) {
  while ((unsigned) (v + 1) < path.size() && 
  _g->getVertex(path[v])->hasConnection(path[v + 1])){
    max(_g->getVertex(path[v+1]), _g->getVertex(path[v]));
    propaga(v + 1);
  }
  if ((v - 1) >= 0)
    max(_g->getVertex(path[v]), _g->getVertex(path[v-1]));
  path.erase(path.begin() + v);
}




void DFS() {
  bool *visited = new bool[_g->getNumVectors()];

  for (int i = 0; i < _g->getNumVectors(); i++)
    visited[i] = false;

  for (int i = 0; i < _g->getNumVectors(); i++)
    if (!visited[i])
      tarjan(i, visited);

  /* for(auto i: path)
    printf("%d\t", i);
  printf("\n"); */

  /*for (auto i : path)
    printf("%d", i);
  cout << "Elementos" << path.size() << "\n";*/
  for (int i = 0; !path.empty(); i++)
    propaga(0);
}

void output() {
  /* for (auto i : path)
    printf("%d", i);
  cout << "Elementos" << path.size() << "\n"; */
  for (int i = 0; i < _g->getNumVectors(); ++i)
    printf("%d\n", _g->getGrade(i));
}

int main() {
  parseCommandLine();

  DFS();

  output();
  return 0;
}
