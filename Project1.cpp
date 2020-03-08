#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

//GLOBAL VARIABLES
int *vertices; //a.k.a alunos inscritos
int *edges;    //a.k.a as conexões, n utilizado agr

void parse()
{
  int num_vert = 0, num_edges = 0;
  scanf("%d, %d", &num_vert, &num_edges); //1 linha do input

  if (num_vert < 2)
  {
    printf("Minimum of students are 2.");
    exit(1);
  }
  else if (num_edges < 1)
  {
    printf("Minimum connections are 1.");
    exit(1);
  }

  vertices = new int[num_vert];
  for (int i = 0; i < num_vert; i++)
  {
    scanf("%d", &vertices[i]);
    //printf("%d",vertices[i]);
  }
}

class Vertex{
  private:
    int _id;
    int _parentId;
    int _grade;
    list<Vertex> _connections;   // antecessores ou predecessores

  public:
    Vertex(int id, int parentId, int grade){
      _id = id;
      _parentId = parentId;
      _grade = grade;
    }

    int getGrade(){
      return _grade;
    }

    void addConnection(Vertex connection){
      _connections.push_back(connection);
    }
};

class Graph{
  private:
    Vertex *_vertexes;

  public:
    Graph(){
      _vertexes = NULL;
    }

  void createGraph(){
    /* _vertexes = new Vertex[vertices];
    for(int i = 0; i < edges; i++){
      //criar as conexões através da função addConnection da class vertex
    } */
  }
};

int main()
{
  parse();
  return 0;
}