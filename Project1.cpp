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

  Vertex* getVertex(int id)
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
    max(adjVertex, vertex);
  }
}

void DFS()
{
  bool *visited = new bool[_g->getNumVectors()];
  for (int i = 0; i < _g->getNumVectors(); i++)
    visited[i] = false;

  for (int i = 0; i < _g->getNumVectors(); i++)
    if (!visited[i]) DFSUtil(i, visited);
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

  DFS();

  output();
  return 0;
}
