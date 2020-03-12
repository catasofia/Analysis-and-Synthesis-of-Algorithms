#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <stack>
#define NIL -1 
using namespace std;

/* Classes */
class Vertex {
  private:
    int _Id;
    int _grade;
    list<Vertex *> _connections;
  public:
    Vertex() {}
    Vertex(int id, int grade) {
      _Id = id;
      _grade = grade;
    }
    ~Vertex() {}

    int getGrade() { return _grade; }

    int getId() { return _Id; }

    void setGrade(int newGrade) { _grade = newGrade; }

    void setId(int id) { _Id = id; }

    void addConnections(Vertex *v) { _connections.push_back(v); }

    list<Vertex *> getAdjacents() { return _connections; }

    bool hasConnection(int id) {
      for (Vertex *v : _connections)
        if (v->getId() == id)
          return true;
      return false;
    }
};

class Graph {
  private:
    int _numVertexes;
    Vertex *_vertexes;
    bool *_visited;

  public:
    Graph() {}
    Graph(int vertexes) {
      _vertexes = new Vertex[vertexes];
      _numVertexes = vertexes;
      _visited = new bool[vertexes];
    }

    ~Graph() { delete _vertexes; }

    int getGrade(int num) { return _vertexes[num].getGrade(); }

    void newVert(int id);

    Vertex *getVertex(int id) { return &_vertexes[id]; }

    int getNumVectors() { return _numVertexes; }

    void addConnection(int id, int idConnection) {
      _vertexes[id].addConnections(&_vertexes[idConnection]);
    }

    void getSCC();

    void tarjan(int id);
};

void Graph::newVert(int id){
  int grade = 0;
  if (scanf("%d", &grade) != 1)
    printf("ERRO!\n");
  _vertexes[id].setId(id);
  _vertexes[id].setGrade(grade);
}

void SCCUtil(int u, int disc[], int low[], stack<int> *st, 
					bool stackMember[]) 
{ 
	// A static variable is used for simplicity, we can avoid use 
	// of static variable by passing a pointer. 
	static int time = 0; 

	// Initialize discovery time and low value 
	disc[u] = low[u] = ++time; 
	st->push(u); 
	stackMember[u] = true; 

	// Go through all vertices adjacent to this 
	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) 
	{ 
		int v = *i; // v is current adjacent of 'u' 

		// If v is not visited yet, then recur for it 
		if (disc[v] == -1) 
		{ 
			SCCUtil(v, disc, low, st, stackMember); 

			// Check if the subtree rooted with 'v' has a 
			// connection to one of the ancestors of 'u' 
			// Case 1 (per above discussion on Disc and Low value) 
			low[u] = min(low[u], low[v]); 
		} 

		// Update low value of 'u' only of 'v' is still in stack 
		// (i.e. it's a back edge, not cross edge). 
		// Case 2 (per above discussion on Disc and Low value) 
		else if (stackMember[v] == true) 
			low[u] = min(low[u], disc[v]); 
	} 

	// head node found, pop the stack and print an SCC 
	int w = 0; // To store stack extracted vertices 
	if (low[u] == disc[u]) 
	{ 
		while (st->top() != u) 
		{ 
			w = (int) st->top(); 
			cout << w << " "; 
			stackMember[w] = false; 
			st->pop(); 
		} 
		w = (int) st->top(); 
		cout << w << "\n"; 
		stackMember[w] = false; 
		st->pop(); 
	}
}

void Graph::tarjan(int id){
  int *disc = new int[_numVertexes]; 
	int *low = new int[_numVertexes]; 
	bool *stackMember = new bool[_numVertexes]; 
	stack<int> *st = new stack<int>(); 

	// Initialize disc and low, and stackMember arrays 
	for (int i = 0; i < _numVertexes; i++) 
	{ 
		disc[i] = NIL; 
		low[i] = NIL; 
		stackMember[i] = false; 
	} 

	// Call the recursive helper function to find strongly 
	// connected components in DFS tree with vertex 'i' 
	for (int i = 0; i < _numVertexes; i++) 
		if (disc[i] == NIL) 
			SCCUtil(i, disc, low, st, stackMember); 
}

void Graph::getSCC(){
  /*for (int id = 0; id < getNumVectors(); id++)
    _visited[id] = false;*/

  for (int id = 0; id < getNumVectors(); id++)
    if (!_visited[id])
      tarjan(id);
}



/* Global Variable */

Graph *_g;
int _time = 0;

/* Functions */

void parseCommandLine() {
  int id = 0, idConnection = 0;
  int num_vert = 0, num_edges = 0;

  if (scanf("%d,%d", &num_vert, &num_edges) != 2)
    fprintf(stderr, "Scanf error\n"); //1 linha do input

  if (num_vert < 2)
  {
    fprintf(stderr, "Minimum of students are 2.");
    exit(1);
  }
  else if (num_edges < 1)
  {
    fprintf(stderr, "Minimum connections are 1.");
    exit(1);
  }
  //Inicialize graph
  _g = new Graph(num_vert); 

  for (int i = 1; i <= num_vert; i++) //Set Vertices with grade
    _g->newVert(i - 1);

  for (int i = 1; i <= num_edges; i++) {  //Set relations between
    if (scanf("%d %d", &id, &idConnection) != 2)
      fprintf(stderr, "Error");
    _g->addConnection(id - 1, idConnection - 1);
  }
}

void output() {
  for (int i = 0; i < _g->getNumVectors(); ++i)
    printf("%d\n", _g->getGrade(i));
}

int main() {
  parseCommandLine();

  _g->getSCC();
  
  output();
  return 0;
}