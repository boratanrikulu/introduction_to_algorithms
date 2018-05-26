#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int i,k,j_sayi,civi,iht,hazne[10],t;
	srand(time(NULL));
	for(i=0; i<10; i++){ /* haznelerin icini sifirlar */
			hazne[i]=0;
		}
	printf("Jeton sayisi: "); scanf("%d", &j_sayi);
	for(i=0; i<j_sayi; i++){
		printf("%2d. jetonu atmak icin bir tusa basiniz -> ", i+1);
		civi=9;
		for(k=0; k<8; k++){
			iht=rand()%2; /* 1 ise saga, 0 ise sola gider */
			if(iht){
				civi++;
			}
			else{
				civi--;
			}
		}
		iht=rand()%2;
		int b=(civi+1)/2; /* a ve b denklemleri, civi sayisini hazne sayisina cevirir */
		int a=(b)+1;
		if(iht){
			printf("%d. hazneye dustu\n", a);
			hazne[a-1]++;
		}
		else{
			printf("%d. hazneye dustu\n", b);
			hazne[b-1]++;
		}
	}
	printf("\n");
	for(i=0; i<10; i++){
		printf("%2d. haznedeki jeton sayisi: %d\n", i+1, hazne[i]);
	}

	printf("\n");
	printf("Jetonlarin histogram seklinde dagilimlari:\n");

	int max=hazne[0];
	for(i=0; i<10; i++){ /* ayni haznede en fazla kac tane jeton oldugunu bulur */
		while(hazne[i]>max){
			max=hazne[i];
		}
	}
	for(i=max; i>0; i--){
		printf("%3d|", i);
			for(k=0; k<10; k++){
				if(hazne[k]==i){
					printf("  o|");
					hazne[k]--; /* konulan jetonu hazne sayacindan eksiltir */
				}
				else{
					printf("   |");
				}
			}
			printf("\n");
	}
	for(i=0; i<11; i++){
		printf("---+");
	}
	printf("\n");
	printf("   |");
	for(i=0; i<10; i++){
		printf("%3d|", i+1);
	}

	printf("\n\n");
	printf("17253509 - Bedrettin Bora Tanrikulu\n");
	printf("Bilgisayar Muhendisligi, 1. Sinif\n");
}
