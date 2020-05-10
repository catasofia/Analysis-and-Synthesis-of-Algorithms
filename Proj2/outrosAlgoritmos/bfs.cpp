#include<iostream> 
#include <list> 

using namespace std;

void BFS(){
  bool *visited = new bool[numberV];
  list<Vertex *> queue; //fila de vértices a percorrer;
  list<Vertex *> path;  //lista com o caminho mais curto;
  
  for(int i = 0; i < _g->getSize(); int++) visited[i] = false;

  Vertex *s = _g->getVertex(SOURCE_ID);
  
  visited[SOURCE_ID] = true;
  
  queue.push_back(s); 

  list<int>::iterator i;
  
  while(!queue.empty()){
    s = queue.front();
    queue.pop_front();
    path.push_front();
    parent[s] = null;

    for(i = s->getArchs()->begin(); i != s->getArchs()->end(); i++){
      if(!visited[*i]){
        visited[*i] = true;
        queue.push_back(*i);
        parent[*i] = s;
      }
    }
  }
}


