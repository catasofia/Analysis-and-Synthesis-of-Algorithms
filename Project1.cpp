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