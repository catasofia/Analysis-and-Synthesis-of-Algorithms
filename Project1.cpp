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
  int _parentId;
  int _grade;
  list<Vertex *> _connections;

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

  void addConnections(Vertex *v){
    _connections.push_back(v);
    list<Vertex *>::iterator it;
    for (it = _connections.begin(); it != _connections.end(); ++it) {
      printf("grade: %d ", (*it)->getGrade());
    }
  }
};

class Graph
{
private:
  Vertex *_vertexes;
  

public:
  Graph() {}
  Graph(int vertexes)
  {
    _vertexes = new Vertex[vertexes];
    //_connections = new list<Vertex>[vertexes];
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
    _vertexes[id].setGrade(grade);
  }

  Vertex getVertex(int id){
    return _vertexes[id];
  }

  void addConnection(int id, int idConnection){
    _vertexes[id].addConnections(&_vertexes[idConnection]);
    //this->getVertex(id).addConnections(&(this->getVertex(idConnection)));
  }

};

/* Global Variable */

Graph *_g;

/* Functions */

void parse()
{
  int num_vert = 0, num_edges = 0;
  if (scanf("%d, %d", &num_vert, &num_edges) != 2)
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
    _g->newVert(i);
    printf("%d\n", _g->getGrade(i));
  }

  int id = 0;
  int idConnection = 0;
  for(int i = 1; i <= num_edges; i++){
    if(scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");  
    _g->addConnection(id, idConnection);


  }
}

int main()
{
  parse();
  return 0;
}