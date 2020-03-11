#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

/* Classes */
class Vertex
{
private:
  int _Id;
  int _grade;
  vector<Vertex *> _connections;

public:
  Vertex() {}
  ~Vertex() {}

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

  vector<Vertex *> getAdjacents()
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
vector<int> path;

/* Functions */

void parseCommandLine()
{
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
  {
    _g->newVert(i - 1);
  }

  for (int i = 1; i <= num_edges; i++) //Set relations between
  {
    if (scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");
    _g->addConnection(id - 1, idConnection - 1);
  }
}

void max(Vertex *a, Vertex *b)
{
  printf("%d\t%d\n", a->getGrade(), b->getGrade());
  if (a->getGrade() > b->getGrade())
    b->setGrade(a->getGrade());
}

void findPath(int v, bool visited[])
{
  visited[v] = true;
  Vertex *vertex = _g->getVertex(v);
  for (Vertex *adjVertex : vertex->getAdjacents())
  {
    if (!visited[adjVertex->getId()])
      findPath(adjVertex->getId(), visited);
  }
  path.insert(path.begin(), v);
}

void propaga(int v = 0)
{
  cout << v << "\n";
  if ((unsigned)v + 1 < path.size())
  {
    //printf("entrou");
    Vertex *vertex = _g->getVertex(path[v]);
    if (vertex->hasConnection(path[v + 1]))
      propaga(v + 1);

    printf("Comparando pai: %d\t com o filho: %d\n", path[v + 1], path[v]);
    max(_g->getVertex(path[v + 1]), _g->getVertex(path[v]));
    printf("Alterações? Pai: %d\n", vertex->getGrade());
    path.erase(path.begin() + v);
    if(path.size() > 1)
      path.resize(path.size() - 1);
  }
}

void DFS()
{
  bool *visited = new bool[_g->getNumVectors()];

  for (int i = 0; i < _g->getNumVectors(); i++)
    visited[i] = false;

  for (int i = 0; i < _g->getNumVectors(); i++)
    if (!visited[i])
      findPath(i, visited);
  propaga();
}

void output()
{
  /* for (auto i: path)
    printf("%d", i);
  cout<<"\n"; */
  for (int i = 0; i < _g->getNumVectors(); ++i)
    printf("%d\n", _g->getGrade(i));
}

int main()
{
  parseCommandLine();

  DFS();

  output();
  return 0;
}
