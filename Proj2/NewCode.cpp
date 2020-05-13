#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <queue>

using namespace std;
#define NIL -1


/*  Pre-load Class's*/
class Vertex;
class Node;
class Graph;
class ResEdge;



/*  Global Variables  */
Graph* _g;
//Vertex* nextVertex = NULL;
list<Vertex *> nextVertexes;
int numNodes=0;

class ResEdge{
private:
  int _flux = 0;
  int _capacity;
  Vertex *_originVertex;
  Vertex *_destinyVertex;

public:
  ResEdge(Vertex *origin, Vertex *destiny, int cap){
    _capacity = cap;
    _originVertex = origin;
    _destinyVertex = destiny;
  }
  
  void addFlux(){ _flux = 1; }
  int getFlux() { return _flux; }
  int getCapacity(){ return _capacity; }
  void setCapacity(int c) { _capacity = c; }
  Vertex *getOriginVertex() { return _originVertex; }
  Vertex *getDestinyVertex() { return _destinyVertex; }
};


class Vertex{
private:
  bool _visited;
  Vertex* _parent; //For BFS
  ResEdge *_parentEdge; //For BFS
  list<ResEdge *> _archs;


public:
  Vertex(){
    _parent = NULL;
    _visited = false;
  }

  void setParent(Vertex *v){ _parent = v; }
  void setParentEdge(ResEdge *edge){ _parentEdge = edge; }
  void setFalse() { _visited=false; }
  void setVisited(){ _visited = true; }
  Vertex* getParent(){ return _parent; }
  ResEdge* getParentEdge(){ return _parentEdge;}
  list<ResEdge *> getArchs() { return _archs; }
  bool isVisited() { return _visited; }
  void addArch(Vertex *destiny, int cap) {
    _archs.push_back(new ResEdge(this, destiny,cap));
  }
};


class Node{
private:
  int _id;
  Vertex* Vin;
  Vertex* Vout;
  ResEdge* edgeBetween;
public:
  Node(){
    _id = numNodes++ ;
    Vin = new Vertex();
    Vout = new Vertex();
    Vin->addArch(Vout, 1);
    Vout->setParent(Vin);
    Vout->setParentEdge(edgeBetween);
    edgeBetween = new ResEdge(Vin, Vout, 1);
  }
  

  
  int getId() { return _id; }
  Vertex* getIn(){ return Vin; }
  Vertex* getOut(){ return Vout; }
  void setId(int id) { _id = id; }
  void addEdges(Node* DestinyNode) {
    Vout->addArch(DestinyNode->getIn(),1);
    DestinyNode->getIn()->addArch(Vout,0);
  }
  void addtoDestiny(Vertex* Destiny) {
    Vout->addArch(Destiny,1);
  }
  void setParent(Vertex *u){
    Vin->setParent(u);
  }
  void setParentEdge(ResEdge *edge){
    Vin->setParentEdge(edge);
  }
  void setNodeFalse(){
    Vin->setFalse();
    Vout->setFalse();
  }
};


class Graph{
private:
  int _avenues, _streets;
  Vertex* Source;
  Vertex* Destiny;
  Node *_nodes;

public:
  Graph(int avenues, int streets){
    _avenues = avenues;
    _streets = streets;
    int _numberNodes = avenues * streets;
    
    Source = new Vertex();
    Destiny = new Vertex();
    
    _nodes = new Node[_numberNodes];
    addConnections();
  }

  ~Graph() { delete _nodes; }
  
  Vertex *getSource(){ return Source;}
  Vertex *getDestiny(){ return Destiny;}
  Node *getNode(int id) { return &_nodes[id]; }
  Node *getNode(int x, int y) { return getNode((x-1) + (y-1) * _avenues); }
  int getSize(){ return _avenues * _streets; }
  void addConnections();
  void newMarket(int x, int y){
    Vertex* t = getDestiny();
    Node* aux = getNode(x,y);
    aux->addtoDestiny(t);
  }
  void newCitizen(int x, int y){
    Vertex* s = getSource();
    Node* aux = getNode(x,y);
    s->addArch(aux->getIn(),1);
  }
};

void Graph::addConnections(){
  for (int i = 0; i < getSize(); i++){
    if (i - _avenues > -1)
      _nodes[i].addEdges(getNode(i - _avenues));
    if (i%_avenues != 0)
      _nodes[i].addEdges(getNode(i - 1));
    if ((i+1)%(_avenues)  != 0)
      _nodes[i].addEdges(getNode(i + 1));
    if (i + _avenues < getSize())
      _nodes[i].addEdges(getNode(i + _avenues));
  }
}

list<ResEdge *> BFS(){
  list<Vertex *> queue; //fila de vértices a percorrer;
  list<ResEdge *> path;  //lista com o caminho mais curto;
  
  for(int i = 0; i < _g->getSize(); i++){
     _g->getNode(i)->setNodeFalse(); 
     _g->getNode(i)->setParent(NULL);
     _g->getNode(i)->setParentEdge(NULL); 
  }

  Vertex *s = _g->getSource();   
  Vertex *t = _g->getDestiny();

  t->setFalse();
  t->setParent(NULL);
  t->setParentEdge(NULL);
  
  s->setVisited();
  queue.push_back(s); 

  //enquanto o t não for descoberto e a lista não estiver vazia, vai percorrer 
  //os vertices. Quando encontrar o t ou a lista acabar, para.
  while(t->getParent() == NULL && !queue.empty()){ 
    Vertex *aux = queue.front();
    queue.pop_front();
    for(ResEdge *edge : aux->getArchs()){
      if(!edge->getDestinyVertex()->isVisited() && edge->getCapacity() == 1 && edge->getFlux() == 0 ){
        queue.push_back(edge->getDestinyVertex());
        edge->getDestinyVertex()->setVisited();
        edge->getDestinyVertex()->setParent(aux);
        edge->getDestinyVertex()->setParentEdge(edge);         
      } 
      if(edge->getDestinyVertex() == t){
        while(!queue.empty()){
          Vertex *temp = queue.front();
          queue.pop_front();
          for(ResEdge *edge1 : temp->getArchs()){
            if (edge1->getDestinyVertex() == t){
              nextVertexes.push_back(temp);
          }
        }}

        /* for (ResEdge *edge: queue.front()->getArchs())
          if (edge->getDestinyVertex() == t)
            nextVertex = queue.front(); */
        break;
      }
    }
  }

  if(!t->isVisited()) {
    return path;  
  }

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


int EdmondsKarp(){
  bool canAdd = true;
  int max_flow = 0;
  list<ResEdge *>path;
  
  while(true){
    path = BFS();
    
    if(!path.empty()){
      max_flow += 1;
      for(ResEdge *edge : path){
        edge->addFlux();
        Vertex *orig = edge->getOriginVertex();
        Vertex *dest = edge->getDestinyVertex();
        for (ResEdge *aux : dest->getArchs())
          if(aux->getDestinyVertex() == orig) aux->setCapacity(1);
      }

      while(!nextVertexes.empty()){
        Vertex *nextV = nextVertexes.front();
        nextVertexes.pop_front();
        Vertex *aux = _g->getDestiny();
        aux->setParent(nextV);
        for(ResEdge * edgeAux : nextV->getArchs()){
          if (edgeAux->getDestinyVertex() == aux) aux->setParentEdge(edgeAux);
        }
        
        while(aux->getParent() != NULL){
          if (aux->getParentEdge()->getFlux() == 1){
            canAdd = false;
            break;
          }
          aux = aux->getParent();
        }

        if(canAdd){
          aux = _g->getDestiny();
          while(aux->getParent() != NULL){
            //printf("entrei\n");
            ResEdge *edge = aux->getParentEdge();
            edge->addFlux();
            Vertex *orig = edge->getOriginVertex();
            Vertex *dest = edge->getDestinyVertex();
            for (ResEdge *auxE : dest->getArchs())
              if(auxE->getDestinyVertex() == orig) 
                auxE->setCapacity(1);
            aux = aux->getParent();
          }
        max_flow += 1;
        }
        canAdd = true;
    }
      /* if (nextVertex!=NULL){
        Vertex *aux = _g->getDestiny();
        while(aux->getParent() != NULL){
            ResEdge *edge = aux->getParentEdge();
            edge->addFlux();
            Vertex *orig = edge->getOriginVertex();
            Vertex *dest = edge->getDestinyVertex();
            for (ResEdge *aux : dest->getArchs())
              if(aux->getDestinyVertex() == orig) 
                aux->setCapacity(1);
            aux = aux->getParent();
        }
        nextVertex = NULL;
      } */
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