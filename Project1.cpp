/*Project 1*/

/*
 - Criar Grafo - Vertices dados na primeira linha
 - Cada Vertice com o seu id e dps a nota esperada
 - Cada um terá tambem a sua lista de antecessores (?)
 
 - No input
 - A medida que se da a nota esperada, cria-se os vertices
 - A medida que se da as conexões, coloca-se o antecessor
    e atualiza-se a nota esperada para nota maxima entre ambos

 - Complexidade? o(n)??
 - Variaveis globais? -> Classe Grafo?
 - Memoria e Tempo limitados

-------------------------------------------------------------------------
 -Ter classe Vertice que tem uma lista dos vertices que lhe são adjacentes
 -Aplicar Algoritmo de Tarjan e em vez de comparar o LOW e colocar o menor,
   comparar o valor do vértice (nota do teste) e colocar o maior;
 -Complexidade -> O(V + E)
 -Ter um atributo com o id do parent;

 ->Função "push_back" adiciona no fim da lista  --- penso que O(1) "amortized";


*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

//GLOBAL VARIABLES
int *vertices; //a.k.a alunos inscritos
int *edges;    //a.k.a as conexões, n utilizado agr

void parse()
{
  int num_vert = 0, num_edges = 0;
  scanf("%d, %d", &num_vert, &num_edges); //1 linha do input

  if (num_vert < 2)
  {
    printf("Minimum of students are 2.");
    exit(1);
  }
  else if (num_edges < 1)
  {
    printf("Minimum connections are 1.");
    exit(1);
  }

  vertices = new int[num_vert];
  for (int i = 0; i < num_vert; i++)
  {
    scanf("%d", &vertices[i]);
    //printf("%d",vertices[i]);
  }
}

int main()
{
  parse();
  return 0;
}