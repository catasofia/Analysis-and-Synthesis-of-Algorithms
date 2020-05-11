#include<iostream> 
#include <list> 

using namespace std;



//na class vertice inicializar visited = false;
//inicializar predecessor a null;

list<ResArch *> BFS(){
  list<Vertex *> queue; //fila de vértices a percorrer;
  list<ResArch *> path;  //lista com o caminho mais curto;

  Vertex *s = _g->getVertex(SOURCE_ID);
  Vertex *t = _g->getVertex(DESTINY_ID);
  
  s->setVisited();
  queue.push_back(s); 

  list<Vertex *>::iterator i;
  

  //enquanto o t não for descoberto e a lista não estiver vazia, vai percorrer 
  //os vertices. Quando encontrar o t ou a lista acabar, para.
  while(t->getParent() == NULL && !queue.empty()){ 
    Vertex *aux = queue.front();
    queue.pop_front();
    
    for(ResArch *edge : aux->getArchs()){
      if(!edge->getDestinyVertex()->isVisited() && edge->getCapacity() > 0){
        queue.push_back(edge->getDestinyVertex());
        edge->getDestinyVertex()->setVisited();
        edge->getDestinyVertex()->setParent(aux);
        edge->getDestinyVertex()->setParentEdges(edge);
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
    }    
    for(ResArch *edge : path){
      edge->addFlux(1);
    }
    else{
      break;
    }
  }
  return max_flow();
}

