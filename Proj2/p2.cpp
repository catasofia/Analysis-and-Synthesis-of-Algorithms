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

	//1 SUPERMERCADO E 1 CIDADAO NO MINIMO ?

}


int main(){
	parseCommandLine();

	return 0;
}