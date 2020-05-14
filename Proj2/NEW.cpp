#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <queue>

using namespace std;
#define NIL -1

/*  Pre-load Class's*/
class Vertex;
class Node;
class Graph;
class ResEdge;

Graph *_g;
int numNodes = 0;

class ResEdge{
  private:
    int _capacity;
    int _flow;
    Vertex *_origin;
    Vertex *_destiny;

  public:
    ResEdge(Vertex *origin, Vertex *destiny, int capacity){
      _origin = origin;
      _destiny = destiny;
      _capacity = capacity;
      _flow = 0;
    }
    Vertex *getOriginVertex() { return _origin; }
    Vertex *getDestinyVertex() { return _destiny; }
    int getFlow() { return _flow; }
    int getCapacity() { return _capacity; }
    void addFlow() { _flow=1; }
    void setCapacity() { _capacity = 1; }
};

class Vertex{
  private:
    int _id;
    bool _visited;
    Vertex *_parent;
    ResEdge *_parentEdge;
    list<ResEdge *> _edges;
    
  public:
    Vertex(int id){
      _visited = false;
      _parent = NULL;
      _parentEdge = NULL;
      _id = id;
      
    }
    void addEdge(Vertex* destiny, int cap){
      _edges.push_back(new ResEdge(this, destiny, cap));
    }
    void addEdge(ResEdge* destiny){
      _edges.push_back(destiny);
    }
    int getId() { return _id; }
    bool isVisited(){ return _visited; }
    Vertex* getParent(){ return _parent; }
    ResEdge* getParentEdge(){ return _parentEdge; }
    list<ResEdge *> getEdges() { return _edges; }
    void setVisited(bool change) { _visited = change; }
    void setParent(Vertex *pred) { _parent = pred; }
    void setParentEdge(ResEdge *edge) { _parentEdge = edge; }
};

class Node{
  private:
    int _id;
    Vertex  *Vin, *Vout;
    ResEdge *edgeBetween_front;
    ResEdge *edgeBetween_back;

  public:
    Node(){
      _id = numNodes++;
      Vin = new Vertex(_id);
      Vout = new Vertex(_id);
      edgeBetween_front = new ResEdge(Vin, Vout, 1);
      Vin->addEdge(edgeBetween_front);
      edgeBetween_back = new ResEdge(Vout, Vin, 0);
      Vout->addEdge(edgeBetween_back);
    }
    int getId() { return _id; }
    void setId(int id) {_id=id;}
    Vertex *getVin() { return Vin; }
    Vertex *getVout() { return Vout; }
    ResEdge *getEdgeBetween_front() { return edgeBetween_front; }
    ResEdge *getEdgeBetween_back() { return edgeBetween_back; }
    void addEdge(Node *Destiny){
      Vout->addEdge(Destiny->getVin(), 1);
      Destiny->getVin()->addEdge(Vout, 0);
    }
    void reset(){
      Vin->setVisited(false);
      Vin->setParent(NULL);
      Vin->setParentEdge(NULL);
      Vout->setVisited(false);
      Vout->setParent(NULL);
      Vout->setParentEdge(NULL);
    }
    
};

class Graph{
  private:
    Node* _nodes;
    int _avenues,_streets;
    Vertex *Source, *Sink;
  public:
    Graph(int avenues, int streets){
      _avenues = avenues;
      _streets = streets;
      Source = new Vertex(-1);
      Sink = new Vertex(_avenues * _streets);
      _nodes = new Node[_avenues * _streets];
      addConnections();
    }
    Vertex* getSource() { return Source; }
    Vertex* getSink() { return Sink; }
    Node* getListNodes() { return _nodes; }
    Node* getNode(int id) { return &_nodes[id]; }
    Node* getNode(int x, int y) { return getNode(x-1 + (y-1)*_avenues); }
    int getSize() { return _avenues*_streets; }
    void addConnections(){
      for(int i = 0; i < getSize(); i++){
        if((i+1) % _avenues != 0)  //Right
          getNode(i)->addEdge(getNode(i + 1));
        if(i % _avenues != 0)   //Left
          getNode(i)->addEdge(getNode(i - 1));
        if(i + _avenues < getSize()) //Down
          getNode(i)->addEdge(getNode(i + _avenues));
        if(i - _avenues >= 0)  //Up
          getNode(i)->addEdge(getNode(i - _avenues));
      }
    }

    void newMarket(int x, int y){
      Vertex *vout = getNode(x , y)->getVout();
      vout->addEdge(Sink, 1);
    }
    void newCitizen(int x, int y){
      Vertex *vin = getNode(x,y)->getVin();
      Source->addEdge(vin, 1); /*Marado com 3 para o mesmo?*/
    }
};

list<Vertex *> BFS(){
  list<ResEdge *> path;
  list<Vertex *> nextVertexs;
  queue<Vertex *> vertexQueue;
  Vertex *source = _g->getSource();
  Vertex *sink = _g->getSink();

  for(int i = 0; i < _g->getSize(); i++){
    _g->getNode(i)->reset();
  }
  
  sink->setVisited(false);
  sink->setParent(NULL);
  sink->setParentEdge(NULL);
  source->setVisited(true);
  vertexQueue.push(source);

  while(!vertexQueue.empty() && sink->getParent() == NULL){
    Vertex *front = vertexQueue.front();
    vertexQueue.pop();
    for(ResEdge *edge : front->getEdges()){
      if(!edge->getDestinyVertex()->isVisited() && edge->getCapacity() == 1 && edge->getFlow() == 0){
        vertexQueue.push(edge->getDestinyVertex());
        edge->getDestinyVertex()->setVisited(true);
        edge->getDestinyVertex()->setParent(front);
        edge->getDestinyVertex()->setParentEdge(edge);
      }
    }
  }
  if(!sink->isVisited()){
    return nextVertexs;
  }

  nextVertexs.push_back(sink->getParent());
  while(!vertexQueue.empty()){
    Vertex *nextV = vertexQueue.front();
    vertexQueue.pop();
    for(ResEdge *aux : nextV->getEdges())
      if (aux->getDestinyVertex() == sink)
        nextVertexs.push_back(nextV);
  }
  return nextVertexs;
}

int Edmonds(){
  bool adding = true;
  int max_flow = 0;
  list <ResEdge *> path;
  list <Vertex *> parents;
  list <Vertex *> usedVertexes;
  Vertex *sink = _g->getSink();
  Vertex *temp = sink;
  
  parents = BFS();
  while(!parents.empty()){
    while(!parents.empty()){
      Vertex *parent = parents.front();
      parents.pop_front();
      sink->setParent(parent);
      for(ResEdge *aux : parent->getEdges())
        if(aux->getDestinyVertex() == sink) sink->setParentEdge(aux);
    
      while(temp->getParent() != NULL){
        path.push_front(temp->getParentEdge()); 
        temp = temp->getParent();
      }
      puts("deif");
      if(usedVertexes.empty()){
        adding = true;
      }
      else{
        //puts("Onde bou?");
        Vertex *aux = sink;
        while(aux->getParent() != NULL){
          for(Vertex *v : usedVertexes)
            if (aux == v) {
              adding = false;
              path.clear();
              //puts("limpou3");
              break;
            }
          aux = aux->getParent();
        }
      }
      if(adding){
        max_flow++;
        for(ResEdge *edge : path){
          edge->addFlow(); 
          Vertex *orig = edge->getOriginVertex();
          if(orig != _g->getSource())
            usedVertexes.push_front(orig);
          Vertex *dest = edge->getDestinyVertex();
          for(ResEdge *backEdge : dest->getEdges()){
            if (backEdge->getDestinyVertex() == orig)
              backEdge->setCapacity();
          }
        }
        path.clear();
      }
      adding = true;
    }
    parents = BFS();
  }
  return max_flow;
}


void parseCommandLine(){
  int aven_num = 0, street_num = 0;
  int markets = 0, citizens = 0;

  if (scanf("%d %d", &aven_num, &street_num) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the first line of input

  if (scanf("%d %d", &markets, &citizens) != 2)
    fprintf(stderr, "Scanf error\n"); //reads the second line of input
    
  _g = new Graph(aven_num, street_num);

/*for(int i=0; i<_g->getSize();i++)
    for (auto x: _g->getNode(i)->getVout()->getEdges())
      printf("%d->%d\n", _g->getNode(i)->getId(), x->getDestinyVertex()->getId());*/

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
  printf("%d\n", Edmonds());
}