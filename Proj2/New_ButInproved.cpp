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
class ResArch;



/*  Global Variables  */
Graph* _g;
int numNodes=0;

class ResArch{
private:
  int flux = 0;
  Vertex *originVertex;
  Vertex *destinyVertex;
  int _capacity;
  bool changed;

public:
  ResArch(Vertex *origin, Vertex *destiny, int cap){
    originVertex = origin;
    destinyVertex = destiny;
    _capacity = cap;
    changed = false;
  }
  
  Vertex *getOriginVertex() { return originVertex; }
  Vertex *getDestinyVertex() { return destinyVertex; }
  void addFlux(){ flux = 1; }
  void resetFlux() { flux = 0; }
  int getFlux() { return flux; }
  void setCapacity(int c) {_capacity = c;}
  int getCapacity(){ return _capacity; }
  /*void setBack(){
    if(!changed){
      getDestinyVertex()->addArch(getOriginVertex(), 1)
      getOriginVertex()->getArchs().remove(this);
      changed = true;
    }
    else{
      getOriginVertex()->getArchs().remove(this);
    }
  }*/
};


class Vertex{
private:
  list<ResArch *> archs;
  bool _visited;
  Vertex* _parent;
  ResArch *_parentEdge;

public:
  Vertex(){
    _parent = NULL;
  }

  void setParentEdge(ResArch *edge){ _parentEdge = edge; }
  
  ResArch* getParentEdge(){ return _parentEdge;}

  Vertex* getParent(){ return _parent; }
  
  void setParent(Vertex *v){
    _parent = v;
  }
  
  void addArch(Vertex *destiny, int cap) {
    archs.push_back(new ResArch(this, destiny,cap));
  }
  
  list<ResArch *> getArchs() { return archs; }

  void setVisited(){ _visited = true; }

  bool isVisited() {return _visited;}

  void setFalse() { _visited=false; }

};


class Node{
private:
  int _id;
  Vertex* Vin;
  Vertex* Vout;
  ResArch* edgeBetween;
public:
  Node(){
    _id = numNodes++ ;
    Vin = new Vertex();
    Vout = new Vertex();
    Vin->addArch(Vout, 1);
    Vout->setParent(Vin);
    edgeBetween = new ResArch(Vin, Vout, 1);
    Vout->setParentEdge(edgeBetween);
  }
  
  int getId() { return _id; }

  void setId(int id) { _id = id; }
  
  Vertex* getIn(){ return Vin; }
  
  Vertex* getOut(){ return Vout; }
  
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

  void setParentEdge(ResArch *edge){
    Vin->setParentEdge(edge);
  }

  void setNodeFalse(){
    Vin->setFalse();
    Vout->setFalse();
  }

  /* void printCone(){
    printf("%d", _id);
  } */
};


class Graph{
private:
  int _avenues, _streets, _numberNodes;
  Vertex* Source;
  Vertex* Destiny;
  Node *_nodes;

public:
  Graph(int avenues, int streets){
    _avenues = avenues;
    _streets = streets;
    _numberNodes = avenues * streets;
    
    Source = new Vertex();
    Destiny = new Vertex();
    
    _nodes = new Node[_numberNodes];
    addConnections();
  }

  ~Graph() { delete _nodes; }
  
  Node *getNode(int id) { return &_nodes[id]; }

  Node *getNode(int x, int y) { return getNode((x-1) + (y-1) * _avenues); }

  Vertex *getSource(){ return Source;}

  Vertex *getDestiny(){ return Destiny;}

  int getSize(){ return _numberNodes; }

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
  for (int i = 0; i < _numberNodes; i++){
    //printf("%d\n", _nodes[i].getId());
    //_nodes[i].setId(i+1);
    if (i - _avenues > -1){
      //puts("primeiro");
      _nodes[i].addEdges(getNode(i - _avenues));
    }
    if (i%_avenues != 0){
      //puts("segundo");
      _nodes[i].addEdges(getNode(i - 1));
    }
    if ((i+1)%(_avenues)  != 0){
      //puts("terceiro");
      _nodes[i].addEdges(getNode(i + 1));
    }
    if (i + _avenues < _numberNodes){
      //puts("quarto"); 
      _nodes[i].addEdges(getNode(i + _avenues));
    }
  }
}

list<ResArch *> BFS(){
  list<Vertex *> queue; //fila de vértices a percorrer;
  list<ResArch *> path;  //lista com o caminho mais curto;
  
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
    for(ResArch *edge : aux->getArchs()){
      if(!edge->getDestinyVertex()->isVisited() && edge->getCapacity() == 1 && edge->getFlux() == 0 ){
        //printf("%d\n", _g->getNode()->getId());
        //printf("aqui");
        queue.push_back(edge->getDestinyVertex());
        edge->getDestinyVertex()->setVisited();
        edge->getDestinyVertex()->setParent(aux);
        edge->getDestinyVertex()->setParentEdge(edge);
        //if(!queue.empty()) printf("hello");
         
      } 
      if(edge->getDestinyVertex() == t) {
        //printf("estupido");
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
    Vertex *aux = t/* , *auxi */;
    while(aux->getParent() != _g->getSource()){
      path.push_front(aux->getParentEdge());
      aux = aux->getParent();
      /* auxi = aux->getParent();
      aux->setFalse();
      aux->setParent(NULL);
      aux->setParentEdge(NULL);
      aux=auxi; */
    }
    return path;
  }   
}
  /* if(t->getParent() != NULL)  printf("estupidez pegada");
  if(queue.empty()) printf("não pode"); */
/*   return path;
} */


int EdmondsKarp(){
  int max_flow = 0;
  list<ResArch *>path;
  
  while(true){
    path = BFS();
    
    if(!path.empty()){
      //puts("caminho\n");
      max_flow += 1;
      for(ResArch *edge : path){
        edge->addFlux(); /*A->B*/ /*B->A*/

        Vertex *orig = edge->getOriginVertex();
        Vertex *dest = edge->getDestinyVertex();

        //edge->setBack();
        for (ResArch *aux : dest->getArchs()){
          if(aux->getDestinyVertex() == orig) aux->setCapacity(1);
        }
      }
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
  //puts("after cone");

  int coordX = 0, coordY = 0;
  for(int i = 0; i < markets; i++){        //reads the location of supermarkets
		if(scanf("%d %d", &coordX, &coordY) != 2);
    _g->newMarket(coordX,coordY);
	}

	for(int i = 0; i < citizens; i++){       //reads the location of citizens
		if(scanf("%d %d",&coordX, &coordY) != 2);
    _g->newCitizen(coordX,coordY);
  }

  /* for(int i = 1; i <= _g->getSize(); i++){
    _g->getNode(i)->printCone();
  }*/
} 


int main(){
  parseCommandLine();
  printf("%d\n", EdmondsKarp());
  return 0;
}
