#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <queue>

using namespace std;
#define NIL -1

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
  int flux = 0;
  int capacity = 1;
  Vertex *originVertex;
  Vertex *destinyVertex;

public:
  ResArch(Vertex *origin, Vertex *destiny){
    originVertex = origin;
    destinyVertex = destiny;
  }
  
  Vertex *getOriginVertex() { return originVertex; }
  Vertex *getDestinyVertex() { return destinyVertex; }
  void addFlux(){ flux = 1; }
  void resetFlux() { flux = 0; }
  int getFlux() { return flux; }
};


class Vertex{
private:
  int _id;
  Type _type;
  list<ResArch *> archs;
  list<ResArch *> backArchs;
  bool _visited;
  Vertex* _parent;
  ResArch *_parentEdge;

public:
  Vertex(){
    _id = NIL;
    _type = none;
    _parent = NULL;
  }

  int getId() { return _id; }

  Type getType() { return _type; }

  void setId(int id) { _id = id; }

  void setType(Type ntype) {
    if (_type==none)  _type = ntype;
    else  _type = both;
  }

  void setParentEdge(ResArch *edge){ _parentEdge = edge; }
  
  ResArch* getParentEdge(){ return _parentEdge;}

  Vertex* getParent(){ return _parent; }
  
  void setParent(Vertex *v){
    _parent = v;
  }

  void setVisited(){ _visited = true; }

  bool isVisited() {return _visited;}

  void setFalse() { _visited=false; }

  void addArch(Vertex* destiny) {
    archs.push_back(new ResArch(this, destiny));
  }

  list<ResArch *> getArchs() { return archs; }

};

class Graph{
private:
  int _avenues, _streets, _numberVertexes;
  const int SOURCE_ID=0;
  int DESTINY_ID;
  Vertex *_vertexes;

public:
  Graph(int avenues, int streets){
    _avenues = avenues;
    _streets = streets;
    _numberVertexes = avenues * streets;
    DESTINY_ID = _numberVertexes+1;
    _vertexes = new Vertex[_numberVertexes+1];
    addConnections();
  }

  ~Graph() { delete _vertexes; }

  Vertex *getVertex(int id) { return &_vertexes[id]; }

  Vertex *getVertex(int x, int y) { return getVertex(x + (y - 1) * _avenues); }

  Vertex *getSource(){ return getVertex(SOURCE_ID);}

  Vertex *getDestiny(){ return getVertex(DESTINY_ID);}

  int getSize(){ return _numberVertexes; }

  void addConnections();

  void setOrigin_Destiny(){
    getVertex(SOURCE_ID)->setId(SOURCE_ID);
    getVertex(DESTINY_ID)->setId(DESTINY_ID);
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

list<ResArch *> BFS(){
  list<Vertex *> queue; //fila de vértices a percorrer;
  list<ResArch *> path;  //lista com o caminho mais curto;
  
  for(int i = 0; i < _g->getSize() + 2; i++) _g->getVertex(i)->setFalse(); 

  Vertex *s = _g->getSource();   
  Vertex *t = _g->getDestiny();
  
  s->setVisited();
  queue.push_back(s); 

  //enquanto o t não for descoberto e a lista não estiver vazia, vai percorrer 
  //os vertices. Quando encontrar o t ou a lista acabar, para.
  while(t->getParent() == NULL && !queue.empty()){ 
    Vertex *aux = queue.front();
    queue.pop_front();
    
    for(ResArch *edge : aux->getArchs()){
      if(!edge->getDestinyVertex()->isVisited() && edge->getFlux() == 0){
        queue.push_back(edge->getDestinyVertex());
        edge->getDestinyVertex()->setVisited();
        edge->getDestinyVertex()->setParent(aux);
        edge->getDestinyVertex()->setParentEdge(edge);
      }
      if(edge->getDestinyVertex() == t) break;
    }

    if(!t->isVisited()) return path;  

    //a partir do t vai fazer backtrack até até chegar ao s, que não tem pai
    //e vai adicionar os arcos ao caminho
    else{
      Vertex *aux = t;
      while(aux->getParent() != NULL){
        path.push_front(aux->getParentEdge());
        aux = aux->getParent();
      }
      return path;
    }   
  }
  return path;
}


int EdmondsKarp(){
  int max_flow = 0;
  list<ResArch *>path;
  
  while(true){
    path = BFS();
    
    if(!path.empty()){
      max_flow += 1;
      for(ResArch *edge : path)
        edge->addFlux();
    }
    else break;
  }
  return max_flow;
}



void errors(int aven_num,int street_num){
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
  
  errors(aven_num, street_num);

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

}


int main(){
  parseCommandLine();
  printf("%d\n", EdmondsKarp());
  return 0;
}
