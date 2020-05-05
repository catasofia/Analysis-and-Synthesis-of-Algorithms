#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>

#define NIL -3
#define SUPERMARKET 1
#define CITIZEN 0
#define EMPTY_CROSSROAD -1

using namespace std;

class ResArch;

class Vertex
{
private:
  int _id;
  int height;
  int excess;
  int _type;
  int _avenue;
  int _street;

  list<ResArch *> archs;
  list<ResArch *> backArchs;
  list<ResArch *> neighbours;

public:
  Vertex()
  {
    _id = NIL;
    _type = NIL;
  }
  Vertex(int id, int type)
  {
    _id = id;
    _type = type;
  }

  void addArch(ResArch *arch) { archs.push_back(arch); }

  void addBackArch(ResArch *arch) { backArchs.push_back(arch); }

  /* ResArch* getLessArch(){
      for(ResArch *aux: archs){
        if(aux->getDestinyVertex()->getHeight() < height) neighbours.push_front(aux);
      }

      for(ResArch *aux: backArchs){
        if(aux->getOriginVertex()->getHeight() < height) neighbours.push_front(aux);
      }

      return neighbours[0];
    } */
};

class ResArch
{
private:
  int flux;
  int capacity;
  int destinyVertexCapacity;
  Vertex *originVertex;
  Vertex *destinyVertex;

public:
  ResArch(Vertex *origin, Vertex *destiny)
  {
    flux = 0;
    capacity = 1;
    originVertex = origin;
    destinyVertex = destiny;
  }

  int getCapacity() { return capacity; }

  int getFlux() { return flux; }

  void addFlux(int f)
  {
    flux += f;
    capacity -= f;
  }

  Vertex *getOriginVertex() { return originVertex; }
  Vertex *getDestinyVertex() { return destinyVertex; }
};

class Graph
{
private:
  int _citizens;
  int _supermarkets;
  int _numberVertexes;
  int _avenues;
  int _streets;

  Vertex *_source;
  Vertex *_destiny;
  Vertex *_vertexes;

public:
  Graph(int avenues, int streets)
  {
    _numberVertexes = avenues * streets;
    _vertexes = new Vertex[_numberVertexes];
    _avenues = avenues;
    _streets = streets;
  }

  ~Graph() { delete _vertexes; }

  Vertex *getVertex(int id) { return &_vertexes[id]; }

  void addConnections()
  {
    for (int i = 1; i <= _numberVertexes; i++)
    {
      if (i - 1 % _avenues != 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i - 1]));

      if (i + 1 % _streets != 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i + 1]));

      if (i - _avenues > 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i - _avenues]));

      if (i + _avenues <= _numberVertexes)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i + _avenues]));
    }
  }
};

int maxFlux = 0;
Graph *_g;

void parseCommandLine()
{
  int aven_num = 0, street_num = 0;
  int markets = 0, citizens = 0;

  if (scanf("%d %d", &aven_num, &street_num) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the first line of input

  if (scanf("%d %d", &markets, &citizens) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the second line of input

  if (aven_num < 1)
  {
    fprintf(stderr, "Minimum of avenues is 1.");
    exit(1);
  }

  if (street_num < 1)
  {
    fprintf(stderr, "Minimum of streets is 1.");
    exit(1);
  }

  if (markets < 1)
  {
    fprintf(stderr, "Minimum of markets is 1.");
    exit(1);
  }

  if (citizens < 1)
  {
    fprintf(stderr, "Minimum of citizens is 1.");
    exit(1);
  }

  _g = new Graph(aven_num, street_num);
}

void output()
{
  printf("%d\n", maxFlux);
}

int main()
{
  parseCommandLine();

  output();

  return 0;
}
