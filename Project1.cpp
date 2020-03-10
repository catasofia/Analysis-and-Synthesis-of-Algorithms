#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>

using namespace std;

#define WHITE -1
#define GRAY 0
#define BLACK 1

/* Classes */
class Vertex
{
private:
  int _Id;
  int _grade;
  list<Vertex *> _connections;

public:
  Vertex() {}
  ~Vertex()
  {
  }

  int getGrade()
  {
    return _grade;
  }

  int getId()
  {
    return _Id;
  }

  void setGrade(int newGrade)
  {
    _grade = newGrade;
  }

  void setId(int id)
  {
    _Id = id;
  }

  void addConnections(Vertex *v)
  {
    _connections.push_back(v);
  }

  list<Vertex *> getAdjacents()
  {
    return _connections;
  }

  bool hasConnection(int id)
  {
    for (Vertex *v : _connections)
    {
      if (v->getId() == id)
        return true;
    }
    return false;
  }
};

class Graph
{
private:
  int _numVertexes;
  Vertex *_vertexes;

public:
  Graph() {}
  Graph(int vertexes)
  {
    _vertexes = new Vertex[vertexes];
    _numVertexes = vertexes;
  }
  ~Graph()
  {
    delete _vertexes;
  }

  int getGrade(int num)
  {
    return _vertexes[num].getGrade();
  }

  void newVert(int id)
  {
    int grade = 0;
    if (scanf("%d", &grade) != 1)
      printf("ERRO!\n");
    _vertexes[id].setId(id);
    _vertexes[id].setGrade(grade);
  }

  Vertex *getVertex(int id)
  {
    return &_vertexes[id];
  }

  int getNumVectors()
  {
    return _numVertexes;
  }

  void addConnection(int id, int idConnection)
  {
    _vertexes[id].addConnections(&_vertexes[idConnection]);
  }
};

/* Global Variable */

Graph *_g;
list<int> *path;

/* Functions */

void parseCommandLine()
{
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

  _g = new Graph(num_vert);

  for (int i = 1; i <= num_vert; i++)
  {
    _g->newVert(i - 1);
    //printf("%d\n", _g->getGrade(i));
  }

  int id = 0;
  int idConnection = 0;
  for (int i = 1; i <= num_edges; i++)
  {
    if (scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");
    _g->addConnection(id - 1, idConnection - 1);
  }
}

void max(Vertex *a, Vertex *b)
{
  if (a->getGrade() > b->getGrade())
    b->setGrade(a->getGrade());
}

void DFSUtil(int v, bool visited[])
{
  visited[v] = true;
  Vertex *vertex = _g->getVertex(v);
  for (Vertex *adjVertex : vertex->getAdjacents())
  {
    if (!visited[adjVertex->getId()])
      DFSUtil(adjVertex->getId(), visited);
  }
  path->push_front(v);
  path->pop_back();
}

void DFSUtil_u(int v, bool visited[])
{
  visited[v] = true;
  Vertex *vertex = _g->getVertex(v);

  if (v + 1 < _g->getNumVectors())
  {
    int a;
    a = path[v + 1];
    if (!visited[a] && vertex->hasConnection(a))
      DFSUtil_u(a, visited);
    max(_g->getVertex(a, vertex);
  }
  printf("saiu %d", v);

  path->remove(v);
}

void DFS()
{
  bool *visited = new bool[_g->getNumVectors()];
  for (int i = 0; i < _g->getNumVectors(); i++)
    visited[i] = false;

  for (int i = 0; i < _g->getNumVectors(); i++)
    if (!visited[i])
      DFSUtil(i, visited);

  for (int i = 0; i < _g->getNumVectors(); i++)
  {
    visited[i] = false;
  }


  for (int i = 0; i < _g->getNumVectors(); i++)
    if (!visited[i])
      DFSUtil_u(i, visited);
}

void findPath()
{
  path = new list<int>(_g->getNumVectors());
  //cout<<_g->getNumVectors()<<"\n";
  DFS();
}

void output()
{
  int i = 0;
  for (i = 0; i < _g->getNumVectors(); ++i)
    printf("%d\n", _g->getGrade(i));
}

int main()
{
  parseCommandLine();

  //DFS();
  findPath();

  output();
  return 0;
}
