#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



int parseCommandLine(){
	int aven_num = 0, street_num = 0;
	int markets = 0, citizens = 0;

	if (scanf("%d %d", &aven_num, &street_num) != 2)
		fprintf(stderr, "Scanf error\n"); //reads the first line of input
	if (aven_num==0)
		return 0;
	int matriz[aven_num][street_num];
	int matriz2[aven_num][street_num];

	int x=0,y=0;
	

	for(int i=0; i<=street_num;i++){
		for(int ii=0; ii<=aven_num;ii++){
			if (i!=0){
				if (ii==0) 
					printf("%d     ",i);
				else{
					printf("(%d,%d)",i,ii);
				if (ii+1<=aven_num) printf("--");
				}
			}
			else {
				printf("    ");
				if (ii!=0)
					printf("%d  ",ii);
			}
			
		}
		if (i+1<=street_num && i>0){
			puts("");
			printf("        ");
			for(int ii=1; ii<aven_num+1;ii++) printf("|      ");
		}
		puts("");
		if (i==0) puts("");
	}

	//1 SUPERMERCADO E 1 CIDADAO NO MINIMO ?

}


int main(){
	while(1){
		int x = parseCommandLine();
		if (x==0) break;
	}
	return 0;
}