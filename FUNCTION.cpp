#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <stack>


#define WHITE -1 
#define GREY 0
#define BLACK 1;


using namespace std;

void setClosed{
    color = black;
}

/* for(int i: listSccs){
    if(_g->getVertex(i)->getColor != BLACK)
        compare(i);
} */

void compare(list<int> sccList){
    if(sccList.size() == 1 && !_g->getVertex(sccList.begin())->hasConnections()){
        _g->getVertex(sccList.begin())->setClosed();   //colocar a preto
        return;
    }

    else if(sccList.size() == 1 && _g->getVertex(sccList.begin())->hasConnections()){        
        list<int>::iterator it;
        for(it = _g->getVertex(sccList.begin())->getConnections().begin(); it != _g->getVertex(sccList.begin())->getConnections().end(); i++)
            max(_g->getVertex(sccList.begin()), _g->getVertex(it));
        _g->getVertex(sccList.begin())->setClosed();
        return;
    }

    else{
        int max = _g->getVertex(sccList.begin())->getGrade();
        for(int i: sccList){
            if(_g->getVertex(i)->getGrade() > max) max = _g->getVertex(i)->getGrade();
            
            for(Vertex* v: _g->getVertex(i)->getConnections())
                if(v->getGrade() > max) max = v->getGrade();
        }

        for(int i: sccList){
            if(_g->getVertex(i)->getGrade() < max) _g->getVertex(i)->setGrade(max);
        }

    }

}
