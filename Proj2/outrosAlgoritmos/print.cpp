#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



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
	int matriz[aven_num][street_num];
	int matriz2[aven_num][street_num];

	int x=0,y=0;
	for(int i=0; i<markets;i++){
		scanf("%d %d",&x, &y);
		matriz[x][y] = 1;
	}
	
	for(int i=0; i<citizens;i++){
		scanf("%d %d",&x, &y);
		matriz2[x][y] = 2;
	}

	for(int i=1; i<=street_num;i++){
		for(int ii=1; ii<=aven_num;ii++){
			if (matriz2[ii][i] == 2){
				printf("\033[0;34m");
				printf("P");}
			else if (matriz[ii][i] == 1){
				printf("\033[0;31m");
				printf("S");}
			else {
				printf("\033[0m");
				printf("O");}
			printf("\033[0m");
			if (ii+1<=aven_num) printf("--");
		}
		if (i+1<=street_num){
			puts("");
			for(int ii=1; ii<=aven_num;ii++) printf("|  ");
		}
		puts("");
	}

	//1 SUPERMERCADO E 1 CIDADAO NO MINIMO ?

}


int main(){
	parseCommandLine();

	return 0;
}