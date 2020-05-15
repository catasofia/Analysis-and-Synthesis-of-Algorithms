#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <climits>


#define NIL -3
#define SUPERMARKET 1
#define CITIZEN 2
#define EMPTY_CROSSROAD -1
#define LIV_IN_SUPER -2
#define SOURCE_ID 0

int DESTINY_ID;


using namespace std;
class Vertex;
class ResArch;
class Graph;

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

class Vertex
{
private:
  int _id;
  int height;
  int excess;
  int _type;
  int _avenue;
  int _street;
  bool ocupied;

  list<ResArch *> archs;
  /*list<ResArch *> backArchs;
  list<ResArch *> neighbours;*/

public:
  Vertex()
  {
    _id = NIL;
    _type = NIL;
  }
  Vertex(int id)
  {
    _id = id;
  }
  Vertex(int id, int type)
  {
    _id = id;
    _type = type;
    height = 0;
    excess = 0;
  }

  void setId(int id) { _id = id; }

  void setHeight(int h) {height = h;}

  int getHeight() {return height;}

  void setExcess(int e) {excess += e;}

  int getExcess() {return excess;}

  void setType(int type){
    if(type == SUPERMARKET) _type = LIV_IN_SUPER;
  }
  
  int getId() { return _id; }
  
  void addArch(ResArch *arch) { archs.push_back(arch); }
  
  list<ResArch *> getArch() { 
    return archs;
    /* for(ResArch *aux: archs){
      
      printf("%d\t%d\t%d\n",_id, aux->getOriginVertex()->getId(), aux->getDestinyVertex()->getId()); 

  } */}

  /*void addBackArch(ResArch *arch) { backArchs.push_back(arch); }*/
 
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
    _avenues = avenues;
    _streets = streets;
    _numberVertexes = avenues * streets;
    _vertexes = new Vertex[_numberVertexes];
    _source = new Vertex(0);
    DESTINY_ID = _numberVertexes + 1;
    _destiny = new Vertex(DESTINY_ID);
    
    addConnections();
  }

  ~Graph() { delete _vertexes; }

  Vertex *getVertex(int id) { return &_vertexes[id - 1]; }

  int getNumberVertexes(){return _numberVertexes;}

  void newVert(int id);

  void addConnections()
  {
    for (int i = 0; i < _numberVertexes; i++)
    {
      if (i - _avenues >= 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i - _avenues]));
      if ((i)% _avenues != 0 && (i)% _streets != 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i - 1]));

      if ((i+1)%_streets != 0 && (i+1)%_avenues != 0)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i + 1]));

      if (i + _avenues <= _numberVertexes - 1)
        _vertexes[i].addArch(new ResArch(&_vertexes[i], &_vertexes[i + _avenues]));
    }
  }
};

void Graph::newVert(int id){
  _vertexes[id - 1].setId(id);
}

int maxFlux = 0;
Graph *_g;
list<Vertex *> queue;

void parseCommandLine()
{
  int aven_num = 0, street_num = 0;
  int markets = 0, citizens = 0;

  if (scanf("%d %d", &aven_num, &street_num) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the first line of input

  if (scanf("%d %d", &markets, &citizens) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the second line of input

  int coordX = 0, coordY = 0;
  for(int i = 0; i < markets; i++){        //reads the location of supermarkets
		scanf("%d %d", &coordX, &coordY);
		_g->getVertex(coordY + (coordX - 1) * aven_num)->setType(SUPERMARKET);
    _g->getVertex(coordY + (coordX - 1) * aven_num)->addArch(new ResArch(_g->getVertex(coordY + (coordX - 1) * aven_num), _g->getVertex(DESTINY_ID)));
	}
	
	for(int i = 0; i < citizens; i++){       //reads the location of citizens
		scanf("%d %d",&coordX, &coordY);
		_g->getVertex(coordY + (coordX - 1) * aven_num)->setType(CITIZEN);
    _g->getVertex(SOURCE_ID)->addArch(new ResArch(_g->getVertex(SOURCE_ID), _g->getVertex(coordY + (coordX - 1) * aven_num)));
    _g->getVertex(coordY + (coordX - 1) * aven_num)->addArch(new ResArch(_g->getVertex(coordY + (coordX - 1) * aven_num), _g->getVertex(SOURCE_ID)));
  }


  /*if (aven_num < 1)
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
  }*/

  _g = new Graph(aven_num, street_num);
  for(int i = 1; i <= aven_num*street_num; i++)
    _g->newVert(i);

  for(int i = 1; i <= 9; i++)
    _g->getVertex(i)->getArch();

}

void InitializePreFlow(){
  _g->getVertex(SOURCE_ID)->setHeight(_g->getNumberVertexes() + 2);
  
  for(ResArch *arch : _g->getVertex(SOURCE_ID)->getArch()){
    arch->addFlux(1);
    arch->getDestinyVertex()->setExcess(1);
    _g->getVertex(SOURCE_ID)->setExcess(-1);
  }
}

void relabel(Vertex *v){
  int min = INT_MAX;
  for(ResArch *arch : v->getArch()){
    if (arch->getCapacity() > 0 && arch->getDestinyVertex()->getHeight() < min)
      min = arch->getDestinyVertex()->getHeight();
  }
  v->setHeight(1 + min);
  queue.push_front(v);


}


void pushRelab(ResArch *arch){
  int d = 0;
  Vertex *u = arch->getOriginVertex();
  Vertex *v = arch->getDestinyVertex();
  
  d = min(u->getExcess(), arch->getCapacity());
  arch->addFlux(d);


  u->setExcess(-d);
  v->setExcess(d);
}



void output()
{
  printf("%d\n", maxFlux);
}

int main()
{
  parseCommandLine();


  
  /*output();*/



  return 0;
}
