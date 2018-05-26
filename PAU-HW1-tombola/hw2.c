#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void pul_cekis();
void kurallar(int pul[3]);
int f_asal(int top);
int f_max(int pul[3]);
int f_min(int pul[3]);
int f_ort(int pul[3]);

int main(){
	char q;
	srand(time(NULL));
	printf("Oyuna baslamak icin herhangi bir tusa basiniz..."); getch(); printf("\n");

	do {
		pul_cekis();	/* Pullar cekiliyor */
		printf("Oyun devam icin [e/E]?");
		q = getche(); printf("\n");
	} while(q == 'e' || q == 'E');
	return 0;
}

void pul_cekis(){
	int pul[3];
	pul[0] = rand()%99+1;	/* Birinci pul cekiliyor */
	printf("Pul 1 = %-3d\n", pul[0]);

	do {
		pul[1] = rand()%99+1;
	} while( pul[1] == pul[0] );	/* İkinci pul cekiliyor (birinci pulla ayni olmayacak sekilde) */
	printf("Pul 2 = %-3d\n", pul[1]);

	do {
	pul[2] = rand()%99+1;
	} while(pul[2] == pul[0] || pul[2] == pul[1]);	/* Ucuncu pul cekiliyor (birinci ve ikinci pulla ayni olmayacak sekilde) */
	printf("Pul 3 = %-3d\n", pul[2]);
	kurallar(pul);	/* Kural ciktilari */
}

void kurallar(int pul[3]){
	int top;
	while(1){
		//	Kural 1
		top=pul[0]+pul[1]+pul[2];
		if(top < 150){
			printf("Tebrikler, kazandiniz. (1. kural)\n");
			break;	/* sadece tek bir durumu basabilmek icin sonsuz dongu ve "break" kullandim */
		}

		//	Kural 2
		if(f_asal(top)==0){
			printf("Tebrikler, kazandiniz. (2. kural)\n");
			break;
		}

		//	Kural3
		if(f_max(pul) - f_min(pul) > f_ort(pul)){
			printf("Tebrikler, kazandiniz. (3. kural)\n");
			break;
		}

		//	Kural disi
		else{
			printf("Maalesef kaybettiniz...!\n");
			break;
		}
	}
}

int f_asal(int top){
	int kontrol = 0;
	for (int i=2; i<top; i++){	/* "top" degeri asal mi diye bakiliyor */
		if (top%i == 0)
			kontrol++; 
	}
	return kontrol;
}

int f_max(int pul[3]){
	int max = pul[0];
	for(int i=0; i<3; i++){
		if(pul[i]>max)
			max=pul[i];
	}
	return max;
}

int f_min(int pul[3]){
	int min = pul[0];
	for(int i=0; i<3; i++){
		if(pul[i]<min)
			min=pul[i];
	}
	return min;
}

int f_ort(int pul[3]){
	int ort;
	for(int i=0; i<3; i++){
		if (pul[i] != f_min(pul) && pul[i] != f_max(pul))
				ort = pul[i];
	}
	return ort;
}