
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>






//class com arcos da rede residual que tem o vértice seguinte e o vértice anterior
class ResidualArch{
  private:
    int capacity;
    int archFlux;
    Vertex *sourceVertex;
    Vertex *destinyVertex;
    
  public:
    ResidualArch(int cap, Vertex *sV, Vertex *dV){
      capacity = cap;
      flux = 0;
      sourceVertex = sV;
      destinyVertex = dV;
    }

    int getCapacity() {return capacity;}

    int getFlux() {return archFlux;}

    Vertex* getDestinyVertex(return destinyVertex;)

    void addFlux(int flux){
      archFlux += flux;
      capacity -= flux;
    }
};

list<Vertex *> stack;

void init_pre_flow(Graph g){
  for(Vertex v : g){
    v.setHeight(0);
    v.setExcess(0);
  }

  maxHeight = g->getNumberVertexes();
  Vertex *s = g->getSource();
  s.setHeight(maxHeight);


  for(ResidualArch *arch : s.neighbours){
    int capacity = arch.getCapacity();
    
    if (capacity > 0){
      s->setExcess(-capacity);

    //tem de acontecer algo ao arco de sentido contrário;
      arch->addFlux(capacity);
      arch->getDestinyVertex()->setExcess(capacity);
      stack.push(arch->getDestinyVertex());
    }
  }
}

void Discharge(Vertex *u){
  while(u->getExcess() > 0){
    if(listaDeArcosComVDeAlturaMenor.empty()) relabel(u);

    else{
      ResidualArch *arch = u->listaDeArcosComVDeAlturaMenor.front();
      listaDeArcosComVDeAlturaMenor.pop(); //retira o primerio arco utilizado;
    
      if(arch->getCapacity() > 0 && u->getHeight() = arch->getDestinyVertex()->getHeight() + 1){
        pushTel(u, arch);  //criar esta função
      }
    }
  }

}

void pushRel(Vertex *u, ResidualArch *arch){
  int d = 0;
  d = min(u->getExcess, arch->getCapactity());
  arch->addFlux(d);
  //no arco de sentido contrário, tirar o d;
  
  arch->getDestinyVertex()->increaseExcess(d);
  arch->getSourceVertex()->increaseExcess(-d);
}

