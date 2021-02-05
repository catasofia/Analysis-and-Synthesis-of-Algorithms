#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>

#define SUPERMARKET 1
#define CITIZEN 0
#define EMPTY_CROSSROAD -1
#define LIVING_IN_A_MARKET 2


using namespace std;


//Class Vertex tem de ter uma lista de arcos residuais com 
//os arcos para a frente e outra lista de arcos residuais com os arcos de sentido inverso
// lista ordenada com os arcos que levam a um vizinho com altura <
class Vertex{
	private:
		int type;
		int height;
		int excess;
		bool ocupied;
		list<Vertex *> _connections;

	public:
		int getType() {return type;}

		void setExcess(int e){excess = e;}
		void increaseExcess(int e){excess += e;}

		void setType(int newType) { 
			if (type == SUPERMARKET){
				type = LIVING_IN_A_MARKET; 
				ocupied = !ocupied;
			}
		}

		bool isOcupied() { return ocupied; }

		
};

class Graph{
	private:
    int _numVertexes;
    Vertex **_vertexes;
    
  public:
    Graph(int streets, int avenues) {
      _vertexes = new Vertex*[avenues];

	  for(int i = 0; i < avenues; i++)
	  	_vertexes[i] = new Vertex[streets];

      _numVertexes = streets*avenues;
    }

    ~Graph() { delete _vertexes; }

    void newVert(int id, int type);
	
	Vertex *getVertex(int x, int y) { return &_vertexes[x][y]; }


};


void Graph::newVert(int i, int j){
	_vertexes[i][j].setType(EMPTY_CROSSROAD);
}


Graph *_g;

void parseCommandLine(){
	int aven_num = 0, street_num = 0;
	int markets = 0, citizens = 0;

	if (scanf("%d %d", &aven_num, &street_num) != 2)
		fprintf(stderr, "Scanf error\n"); //reads the first line of input

	if (scanf("%d %d", &markets, &citizens) != 2)
		fprintf(stderr, "Scanf error\n"); //reads the second line of input

	if (aven_num < 1){
		fprintf(stderr, "Minimum of avenues is 1.");
		exit(1);
	}

	if (street_num < 1){
		fprintf(stderr, "Minimum of streets is 1.");
		exit(1);
	}

	if (markets < 1){
		fprintf(stderr, "Minimum of markets is 1.");
		exit(1);
	}

	if (citizens < 1){
		fprintf(stderr, "Minimum of citizens is 1.");
		exit(1);
	}


	_g = new Graph(street_num, aven_num);


	for(int i = 0; i < aven_num; i++)
		for(int j = 0; j < street_num; j++)
			_g->newVert(i, j);


	int coordX = 0, coordY = 0;
	for(int i = 0; i < markets; i++){        //reads the location of supermarkets
		scanf("%d %d", &coordX, &coordY);
		_g->getVertex(coordX, coordY)->setType(SUPERMARKET);
	}
	
	for(int i = 0; i < citizens; i++){       //reads the location of citizens
		scanf("%d %d",&coordX, &coordY);
		_g->getVertex(coordX, coordY)->setType(CITIZEN);
	}
}


int main(){
	parseCommandLine();

	return 0;
}