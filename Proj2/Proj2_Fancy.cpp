#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>

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
  Vertex *originVertex;
  Vertex *destinyVertex;

public:
  ResArch(Vertex *origin, Vertex *destiny){
    originVertex = origin;
    destinyVertex = destiny;
  }
  Vertex *getOriginVertex() { return originVertex; }
  Vertex *getDestinyVertex() { return destinyVertex; }
};

class Vertex{
private:
  int _id;
  Type _type;
  list<ResArch *> archs;

public:
  Vertex(){
    _id = NIL;
    _type = none;
  }

  int getId() { return _id; }

  Type getType() { return _type; }

  void setId(int id) { _id = id; }

  void setType(Type ntype) {
    if (_type==none)
      _type = ntype;
    else
      _type = both;
  }

  void addArch(Vertex* destiny) {
    ResArch* narch = new ResArch(this, destiny);
    archs.push_back(narch);
  }

  list<ResArch *> getArch() { return archs; }
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
    addConnections();
    setOrigin_Destiny();
  }

  ~Graph() { delete _vertexes; }

  Vertex *getVertex(int id) { return &_vertexes[id]; }

  Vertex *getVertex(int x, int y) { return getVertex(y + (x - 1) * _avenues); }

  void addConnections();

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
    aux->addArch(s);
  }
};

void Graph::addConnections(){
  for (int i = 1; i <= _numberVertexes; i++){
    _vertexes[i].setId(i+1);
    if (i - _avenues >= 0)
      _vertexes[i].addArch(&_vertexes[i - _avenues]);
    if ((i)% _avenues != 0 && (i)% _streets != 0)
      _vertexes[i].addArch(&_vertexes[i - 1]);

    if ((i+1)%_streets != 0 && (i+1)%_avenues != 0)
      _vertexes[i].addArch(&_vertexes[i + 1]);

    if (i + _avenues <= _numberVertexes - 1)
      _vertexes[i].addArch(&_vertexes[i + _avenues]);
  }
}

void errors(int aven_num,int street_num,int markets,int citizens){
  if (aven_num < 1)
    fprintf(stderr, "Minimum of avenues is 1.");
  else if (street_num < 1)
    fprintf(stderr, "Minimum of streets is 1.");
  else if (markets < 1)
    fprintf(stderr, "Minimum of markets is 1.");
  else if (citizens < 1)
    fprintf(stderr, "Minimum of citizens is 1.");
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
		scanf("%d %d", &coordX, &coordY);
    _g->newMarket(coordX,coordY);
	}

	for(int i = 0; i < citizens; i++){       //reads the location of citizens
		scanf("%d %d",&coordX, &coordY);
    _g->newCitizen(coordX,coordY);
  }
}

int main()
{
  parseCommandLine();
  return 0;
}
