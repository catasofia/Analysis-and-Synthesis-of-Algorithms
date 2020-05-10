#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <queue>
#include <climits>

using namespace std;
#define NIL -1
#define SOURCE_ID 0
int DESTINY_ID;

enum Type{
  none, supermarket, citizen, both
};

/*  Pre-load Class's*/
class Graph;
class Vertex;
class ResArch;

/*  Global Variables  */
Graph* _g;


class ResArch{
private:
  int flux,capacity;
  Vertex *originVertex;
  Vertex *destinyVertex;

public:
  ResArch(Vertex *origin, Vertex *destiny){
    originVertex = origin;
    destinyVertex = destiny;
    flux=0;
    capacity=1;
  }
  Vertex *getOriginVertex() { return originVertex; }
  Vertex *getDestinyVertex() { return destinyVertex; }
  void addFlux(int nFlux){ flux += nFlux; }
  void resetFlux() {flux = 0;}
  int getCapacity(){ return capacity; }
};

class Vertex{
private:
  int _id;
  int _level;
  int _excess;
  bool _ocupied;
  Type _type;
  list<ResArch *> archs;
  list<ResArch *> back_archs;
  list<ResArch *> lower_height;


public:
  Vertex(){
    _id = NIL;
    _type = none;
    _level=_excess=0;
    _ocupied = false;
  }

  int getId() { return _id; }

  Type getType() { return _type; }

  void setId(int id) { _id = id; }

  void setType(Type ntype) {
    if (_type==none)  _type = ntype;
    else  _type = both;
  }

  void addArch(Vertex* destiny) {
    ResArch* narch = new ResArch(this, destiny);
    archs.push_back(narch);
    lower_height.push_back(narch);
    narch = new ResArch(destiny, this);
    back_archs.push_back(narch);
  }

  void updateLowerVertex(){
    for(ResArch * edge : archs){
      if(edge->getDestinyVertex()->getLevel() < _level)
        lower_height.push_back(edge);
    }

    for(ResArch * edge : back_archs){
      if(edge->getDestinyVertex()->getLevel() < _level)
        lower_height.push_back(edge);
    }
  }

  ResArch* getLowerH(){
    ResArch *minEdge = NULL;
    for(ResArch *edge : lower_height){
      int min = edge->getOriginVertex()->getLevel();
      if(edge->getDestinyVertex()->getLevel() < min ){
        //printf("%d\t%d\n", edge->getDestinyVertex()->getId(),edge->getDestinyVertex()->getLevel());
        minEdge = edge;
        min = edge->getDestinyVertex()->getLevel();
      }
    }
    return minEdge;
   }

  list<ResArch *> getArch() { return archs; }

  list<ResArch *> getBackArch() { return back_archs; }

  void setExcess(int nExcess){ _excess += nExcess;}

  int getExcess(){ return _excess;}

  void setHeight(int height) { _level = height; }

  int getLevel(){ return _level; }

  void changeOcupied(){ _ocupied = !_ocupied; }

  bool isOcupied() { return _ocupied; }

  bool inBackEdges(ResArch *edge){
    for (ResArch *temp : back_archs){
      if (temp == edge) return true;
    }
    return false;
  }

  /* void printCon(){
    for (ResArch *edge : archs){
      printf("%d\t%d\n", _id, edge->getDestinyVertex()->getId());
    }
  } */

};

class Graph{
private:
  int _avenues, _streets, _numberVertexes;
  Vertex *_vertexes;

public:
  Graph(int avenues, int streets){
    _avenues = avenues;
    _streets = streets;
    _numberVertexes = avenues * streets;

    _vertexes = new Vertex[_numberVertexes+1];

    DESTINY_ID = _numberVertexes+1;

    addConnections();
    setOrigin_Destiny();
  }

  ~Graph() { delete _vertexes; }

  Vertex *getVertex(int id) { return &_vertexes[id]; }

  Vertex *getVertex(int x, int y) { return getVertex(x + (y - 1) * _avenues); }

  Vertex *getSource(){ return getVertex(SOURCE_ID);}

  Vertex *getVertexList(){ return _vertexes; }

  void addConnections();

  int getSize(){ return _numberVertexes+2; }

  void setOrigin_Destiny(){
    getVertex(SOURCE_ID)->setId(SOURCE_ID);
    getVertex(DESTINY_ID)->setId(_numberVertexes+1);
  }

  void newMarket(int x, int y){
    Vertex* t = getVertex(DESTINY_ID);
    Vertex* aux = getVertex(x,y);
    aux->setType(supermarket);
    aux->addArch(t);
  }

  void newCitizen(int x, int y){
    Vertex* s = getVertex(SOURCE_ID);
    Vertex* aux = getVertex(x,y);
    aux->setType(citizen);
    s->addArch(aux);
    //aux->addArch(s);
  }
};

void Graph::addConnections(){
  for (int i = 1; i <= _numberVertexes; i++){
    _vertexes[i].setId(i);
    if (i - _avenues > 0)
      _vertexes[i].addArch(getVertex(i - _avenues));
    if ((i-1)%/* _streets */ _avenues != 0)
      _vertexes[i].addArch(getVertex(i - 1));
    if (i% /* _streets */ _avenues  != 0)
      _vertexes[i].addArch(getVertex(i + 1));
    if (i + _avenues <= _numberVertexes)
      _vertexes[i].addArch(getVertex(i + _avenues));
  }
}

void errors(int aven_num,int street_num,int markets,int citizens){
  if (aven_num < 1)
    fprintf(stderr, "Minimum of avenues is 1.");
  else if (street_num < 1)
    fprintf(stderr, "Minimum of streets is 1.");
  else return;

  exit(1);
}

void parseCommandLine(){
  int aven_num = 0, street_num = 0;
  int markets = 0, citizens = 0;

  if (scanf("%d %d", &aven_num, &street_num) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the first line of input

  if (scanf("%d %d", &markets, &citizens) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the second line of input

  errors(aven_num, street_num, markets, citizens);

  _g = new Graph(aven_num, street_num);

  int coordX = 0, coordY = 0;
  for(int i = 0; i < markets; i++){        //reads the location of supermarkets
		if(scanf("%d %d", &coordX, &coordY) != 2);
    _g->newMarket(coordX,coordY);
	}

	for(int i = 0; i < citizens; i++){       //reads the location of citizens
		if(scanf("%d %d",&coordX, &coordY) != 2);
    _g->newCitizen(coordX,coordY);
  }

  /* for (int i = 0; i <= aven_num*street_num; i++){
    for (auto x: _g->getVertex(i)->getArch())
      printf("%d-%d\n",_g->getVertex(i)->getId(), x->getDestinyVertex()->getId());
  } */

}

void initializePreFlow(){
  /*Default values of height and excess equals 0*/
  /*Default values of flux and capacity equals 0*/
  Vertex* s= _g->getSource();
  s->setHeight(_g->getSize());

  
  for (auto u:s->getArch()){
    int capacity= u->getCapacity();
    //printf("%dd%ddd\n", u->getOriginVertex()->getId(), u->getDestinyVertex()->getId());
    u->addFlux(capacity);
    u->getDestinyVertex()->setExcess(capacity);
    s->setExcess(-capacity);
  }

  for (auto u:s->getBackArch())
    u->addFlux(-1* u->getCapacity());

//printf("%d\n", _g->getSource()->getExcess());

}

int checkFlow(list<Vertex*> ver) {
    while (!ver.empty()){
      //printf("%d\n", ver.front()->getExcess());
      if (ver.front()->getExcess() > 0){
        return ver.front()->getId();
      }
      ver.pop_front();
    }
    return -1;
}

void relabel(Vertex *u){
  int minHeight = u->getLevel();
  for(ResArch *edge: u->getArch()){
    if(edge->getCapacity() > 0 && edge->getDestinyVertex()->getLevel() < minHeight && !edge->getDestinyVertex()->isOcupied())
      minHeight = edge->getDestinyVertex()->getLevel();
  }

  for(ResArch *edge: u->getBackArch()){
    if(edge->getCapacity() > 0 && edge->getDestinyVertex()->getLevel() < minHeight && edge->getDestinyVertex()->isOcupied())
      minHeight = edge->getDestinyVertex()->getLevel();
  }

  u->setHeight(minHeight + 1);
  u->updateLowerVertex();
}


void Push(ResArch *edge){
  Vertex *u = edge->getOriginVertex();
  Vertex *v = edge->getDestinyVertex();
  int d = 0;
  d = min(u->getExcess(), edge->getCapacity());
  edge->addFlux(d);
  u->setExcess(-d);
  v->setExcess(d);
}


void discharge(Vertex *u){
  while(u->getExcess() > 0){
    if(u->getLowerH() == NULL){
      relabel(u);
    }
    else{
      ResArch *edge = u->getLowerH();
      
      if(edge->getCapacity() > 0 && !edge->getDestinyVertex()->isOcupied()){
        Push(edge);
        edge->getDestinyVertex()->changeOcupied();
        for(ResArch *aux: u->getBackArch()){
          if(aux->getOriginVertex() == edge->getDestinyVertex()) aux->resetFlux();
        }
      }
      
      else if(edge->getCapacity() > 0  && edge->getDestinyVertex()->isOcupied() /* && u->inBackEdges(edge) */){   //ESTÁ PRESO POR CAUSA DA ÚLTIMA CONDIÇÃO DO ELSE IF
        Push(edge);
        edge->getOriginVertex()->changeOcupied();
        for(ResArch *aux: u->getArch()){
          if(aux->getDestinyVertex() == edge->getOriginVertex()) aux->resetFlux();
        }
      }
    }
  }
}


void relabelToFront(){
  list<Vertex *> stack;
  initializePreFlow();

  for (int i = 1; i <= _g->getSize()-2; i++){
    Vertex *u=_g->getVertex(i);
    stack.push_back(u);
  }
  int id = checkFlow(stack);
  while (id != -1){
    int h;
    Vertex* first;

    first = _g->getVertex(id);
    h = first->getLevel();

    discharge(first);

    if(h != first->getLevel()){
      stack.remove(first);
      stack.push_front(first);
    }
  id = checkFlow(stack);
  }
}

int main()
{
  parseCommandLine();
  relabelToFront();
  printf("%d\n", _g->getVertex(_g->getSize()-1)->getExcess());
  return 0;
}