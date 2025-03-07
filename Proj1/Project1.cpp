#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>

#define NIL -1 

using namespace std;

/* Classes */
class Vertex {
  private:
    int _id;
    int _grade;
    list<Vertex *> _connections;

  public:
    int getGrade() { return _grade; }

    int getId() { return _id; }

    void setGrade(int newGrade) { _grade = newGrade; }

    void setId(int id) { _id = id; }

    void addConnections(Vertex *v) { _connections.push_back(v); }

    list<Vertex *> getAdjacents() { return _connections; }

    bool hasConnection(int id);

    bool hasConnections() { return !_connections.empty(); }
};

class Graph {
  private:
    int _numVertexes;
    Vertex *_vertexes;
    
  public:
    Graph(int vertexes) {
      _vertexes = new Vertex[vertexes];
      _numVertexes = vertexes;
    }

    ~Graph() { delete _vertexes; }

    void newVert(int id);

    int getGrade(int num) { return _vertexes[num].getGrade(); }

    Vertex *getVertex(int id) { return &_vertexes[id]; }

    int getNumVectors() { return _numVertexes; }

    void addConnection(int id, int idConnection) {
      _vertexes[id].addConnections(&_vertexes[idConnection]);
    }

    void tarjan();  //O(V)
    void sccThreatment(list<int> sccList);  //O(V+E)
    void tarjanVisit(int i, int* dTime, int* low, list<int> *stackL);  //O(V+E)
};

/* Global Variable */
Graph *_g;

/* Class Functions*/
bool Vertex::hasConnection(int id){
  for (Vertex *v : _connections)
    if (v->getId() == id)
      return true;
  return false;
}

void Graph::newVert(int id){
  int grade = 0;
  if (scanf("%d", &grade) != 1)
    printf("ERRO!\n");
  _vertexes[id].setId(id);
  _vertexes[id].setGrade(grade);
}

bool contains(list<int> *lst, int id){
  for(auto it = lst->begin(); it != lst->end(); ++it)
		if (*it == id) return true;
  return false;
}

void Graph::sccThreatment(list<int> sccList){
  Vertex *v = getVertex(*sccList.begin());
  
  if(sccList.size() == 1 && !v->hasConnections())
    return;

  else if(sccList.size() == 1 && v->hasConnections()){        
    for(auto it: v->getAdjacents()) //O(E)
      v->setGrade(max(it->getGrade(),v->getGrade()));
    return;
  }

  else{
    int max = v->getGrade();
    for(int i: sccList){    //O(V+E)
      if(getGrade(i) > max)
        max = getGrade(i);

      for(Vertex* v: getVertex(i)->getAdjacents())
        if(v->getGrade() > max)
          max = v->getGrade();
    }

    for(int i: sccList)  //O(V)
      if(getGrade(i) < max)
        getVertex(i)->setGrade(max);
  }
}

void Graph::tarjanVisit(int u, int* dTime, int* low,list<int> *stackL){  //O(V+E)
  static int visited = 0;
  dTime[u] = low[u] = visited++;
  stackL->push_front(u);
  for(auto v: _g->getVertex(u)->getAdjacents()){  
    int vert = v->getId();
  
    if (dTime[vert]==NIL || contains(stackL,vert)){
      if (dTime[vert] == NIL)
        tarjanVisit(vert,dTime,low,stackL);
      low[u] = min(low[u], low[vert]);
    }
  }

  int v=0;
  list<int> Scc;
  if (dTime[u] == low[u]){
    do{
      v = stackL->front();
      Scc.push_back(v);
      stackL->erase(stackL->begin());
    } while (u!=v);
  sccThreatment(Scc);
  Scc.clear();
  }
}

void Graph::tarjan(){
  int *dTime = new int[_numVertexes];
  int *low = new int[_numVertexes];
  list<int> *stackL = new list<int>(); 

  for(int i=0; i<_numVertexes;i++)
    dTime[i] = NIL, low[i] = NIL;

  for(int i=0; i<_numVertexes;i++)
    if (dTime[i] == NIL)
      tarjanVisit(i,dTime,low,stackL);
}


void parseCommandLine() {
  int id = 0, idConnection = 0;
  int num_vert = 0, num_edges = 0;

  if (scanf("%d,%d", &num_vert, &num_edges) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the first line of input

  if (num_vert < 2){
    fprintf(stderr, "Minimum of students are 2.");
    exit(1);
  }
  else if (num_edges < 1){
    fprintf(stderr, "Minimum connections are 1.");
    exit(1);
  }
  
  _g = new Graph(num_vert); //Inicialize graph

  for (int i = 1; i <= num_vert; i++) //Set Vertices with grade
    _g->newVert(i - 1);

  for (int i = 1; i <= num_edges; i++) {  //Set relations between vertexes
    if (scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");
    _g->addConnection(id - 1, idConnection - 1);
  }
}

void output() {
  for (int i = 0; i < _g->getNumVectors(); ++i)
    printf("%d\n", _g->getGrade(i));
}

int main() {
  parseCommandLine();

  _g->tarjan();
  
  output();

  return 0;
}