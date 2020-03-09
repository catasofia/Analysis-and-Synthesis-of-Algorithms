#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

#define WHITE -1
#define GRAY 0
#define BLACK 1

/* Classes */
class Vertex
{
private:
  int _parentId;
  int _grade;

public:
  Vertex() {}

  Vertex(int grade)
  {
    _grade = grade;
  }

  int getGrade()
  {
    return _grade;
  }

  void setGrade(int newGrade)
  {
    _grade = newGrade;
  }
};

class Graph
{
private:
  Vertex *_vertexes;
  list<Vertex> *_connections;

public:
  Graph() {}
  Graph(int vertexes)
  {
    _vertexes = new Vertex[vertexes];
    _connections = new list<Vertex>[vertexes];
  }

  int getGrade(int num)
  {
    return _vertexes[num].getGrade();
  }

  void newVert(int id)
  {
    int grade = 0;
    if (scanf("%d", &grade) != 0)
      printf("ERRO!\n");
    _vertexes[id].setGrade(grade);
  }
};

/* Global Variable */

Graph *_g;

/* Functions */

void parse()
{
  int num_vert = 0, num_edges = 0;
  if (scanf("%d, %d", &num_vert, &num_edges) != 0)
    printf("ERRO\n"); //1 linha do input

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

  for (int i = 0; i < num_vert; i++)
  {
    _g->newVert(i);
    printf("%d\n", _g->getGrade(i));
  }
}

int main()
{
  parse();
  return 0;
}