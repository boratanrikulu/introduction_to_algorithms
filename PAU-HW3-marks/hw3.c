#include <stdio.h>
#include <math.h>

void giris(int no[], int note[], int N);
float ortalama(int note[], int N);
void goruntule(int no[], int note[], int N);
float bagil_ortalama(int note[], int N);
void sirala(int no[], int note[], int N, char nasil);
void otele(int note[], int N, float ort, float bagil_ort);
float standart(int note[], int N, float ort);
void harf_notlari(int Note[], int N);
int yukseklik(int harf_notlari[]);
void dikey_histogram(int cp_harf_notlari[], int yukseklik, char harfler[]);
void yatay_histogram(int harf_notlari[], int yukseklik, char harfler[]);

int main(){
	int N;
	int OgrNo[BUFSIZ], BNotu[BUFSIZ];
	printf("Ogrenci sayisini giriniz: "); scanf("%d", &N);
	giris(OgrNo, BNotu, N);
	printf("\n");
	goruntule(OgrNo, BNotu, N);
	printf("\n");
	float ort = ortalama(BNotu, N);
	printf("# Not ortalamasi: %5.2f\n", ort);

	float bagil_ort = bagil_ortalama(BNotu, N); 
	printf("# Bagil not ortalamasi: %5.2f\n", bagil_ort); // 20 ve ustundeki notlarin ortalamasi
	otele(BNotu, N, ort, bagil_ort); // ortalama 50'den kucukse oteler ve otelenmis ortalamayi bastirir

	printf("\n");
	printf("# Basari notlarina gore kucukten buyuge sirali olarak #\n"); //siralama yapilir
	sirala(OgrNo, BNotu, N, 'x'); goruntule(OgrNo, BNotu, N);printf("\n");

	printf("# Ogrenci numaralarina gore kucukten buyuge sirali olarak #\n"); //siralama yapilir
	sirala(OgrNo, BNotu, N, 'y'); goruntule(OgrNo, BNotu, N);printf("\n");

	printf("# Standart sapma: \"%5.2f\"", standart(BNotu, N, ortalama(BNotu, N))); printf("\n\n");
	harf_notlari(BNotu, N); //histrogram cizilir

	return 0;
}

void giris(int no[], int note[], int N){
	int i;
	for (i=0; i<N; i++){
	printf("Ogrenci no gir: "); scanf("%d", &no[i]);
	printf("%d numarali ogrencinin basari notunu gir : ", no[i]); scanf("%d", &note[i]);
	}
}

void goruntule(int no[], int note[], int N){
	printf("Ogrenci#\tNotu\n");
	for (int i=0; i<N; i++){
		printf("%8d\t%d\n", no[i], note[i]);
	}
}

float ortalama(int note[], int N){
	float t;
	int i;
	t = 0;
	for (i=0; i<N; i++){
		t = t + note[i];
	}
	float ort = t / N;
	return ort;
}

void sirala(int no[], int note[], int N, char nasil){
	for (int i=0; i<N-1; i++){
		for (int j=0; j<N-1-i; j++){
			if (nasil == 'x'){ // Ogrenci notlarina gore siralar
				if (note[j+1]<note[j]){
					int gec = note[j];
					note[j] = note[j+1];
					note[j+1] = gec;

					gec = no[j];
					no[j] = no[j+1];
					no[j+1] = gec;
				}
			}
			if (nasil == 'y'){ // Ogrenci numarasina gore siralar
				if (no[j+1]<no[j]){
					int gec = no[j];
					no[j] = no[j+1];
					no[j+1] = gec;

					gec = note[j];
					note[j] = note[j+1];
					note[j+1] = gec;
				}
			}
		}
	}
}

float bagil_ortalama(int note[], int N){
	float t=0;
	int kisi=0;
	for (int i=0; i<N; i++){
		if (20<=note[i]){
			t += note[i];
			kisi++; // 20 ve ustundeki kisi sayisi bulur
		}
	}
	float bagil_ort = t / kisi;
	return bagil_ort;
}

void otele(int note[], int N, float ort, float bagil_ort){
	if(bagil_ort < 50){
		float istenen = 50.00;
		for (int i=0; i<N; i++){
			if(30<=note[i]){
				if (100-note[i] <= round(istenen - bagil_ort)) // 100'den daha fazla bir degere otelenmemesi icin, bu sekilde bir yapi kullandim
					note[i] = 100; 
				else
					note[i] += round(istenen - bagil_ort); // *.5' den büyükleri yuvarlamak icin "round" kullandim
			}
		}
		ort = ortalama(note, N); //otelenmis notlarin tekrar ortalamasi alinir
		printf("# Otelenmis not ortalamasi: %5.2f\n", ort);
	}
}

float standart(int Note[], int N, float ort){
	float x=0;
	for(int i=0; i<N; i++){
		x += pow(ort-Note[i],2)/N;
	}
	return sqrt(x);
}

void harf_notlari(int Note[], int N){
	int harf_notlari[10];
	for(int i=0; i<10; i++){
		harf_notlari[i] = 0; //harf_notlari sayaclarini sifirlar
	}
	for(int i=0; i<N; i++){
		if(90<=Note[i] && Note[i] <= 100)
			harf_notlari[0]++;  //A1
		else if(80<=Note[i] && Note[i] < 90)
			harf_notlari[1]++;	//A2
		else if(75<=Note[i] && Note[i] < 80)
			harf_notlari[2]++;	//B1
		else if(70<=Note[i] && Note[i] < 75)
			harf_notlari[3]++;	//B2
		else if(65<=Note[i] && Note[i] < 70)
			harf_notlari[4]++;	//C1
		else if(60<=Note[i] && Note[i] < 65)
			harf_notlari[5]++;	//C2
		else if(55<=Note[i] && Note[i] < 60)
			harf_notlari[6]++;	//D1
		else if(50<=Note[i] && Note[i] < 55)
			harf_notlari[7]++;	//D2
		else if(40<=Note[i] && Note[i] < 50)
			harf_notlari[8]++;	//E
		else if(0<=Note[i] && Note[i] < 40)
			harf_notlari[9]++;	//F
	}
	int cp_harf_notlari[N]; // kurdugum histogram algoritmasi eksiltmek uzerine oldugu icin, ayni anda hem dikey hem de yatay histogrami
	for(int i=0; i<10; i++){  // tek dizi uzerinden bastiramadim. bunu duzeltmek icin dizinin iki kopyasini alip yatay ve dikey histrogramlarina
		cp_harf_notlari[i] = harf_notlari[i]; // birbinirin aynisi iki kopya yollayarak cozdum.
	}
	char harfler[21] = "A1A2B1B2C1C2D1D2E F ";
	yatay_histogram(cp_harf_notlari, yukseklik(harf_notlari), harfler);
	dikey_histogram(harf_notlari, yukseklik(harf_notlari), harfler);
}

int yukseklik(int harf_notlari[]){
	int yukseklik=harf_notlari[0];
	for(int i=0; i<10; i++){ // ayni harf notundan en fazla kac tane oldugunu bulur
		while(harf_notlari[i]>yukseklik){
			yukseklik=harf_notlari[i];
		}
	}
	return yukseklik;
}

void yatay_histogram(int harf_notlari[], int yukseklik, char harfler[]){
	printf("# Başarı notları dağılım aralıkları (yatay histogram) #\n\n");
	for (int i=0; i<20; i+=2){
		printf("%c", harfler[i]); printf("%c|", harfler[i+1]);
		for(int j=0; j<harf_notlari[i/2]; harf_notlari[i/2]--){
			if(harf_notlari[i/2]>0){
				printf(" * "); // konulan harf notunu, harf_notu sayacindan eksiltir
			}
			else
				printf("\n");
		} printf("\n");
	}
	printf("--+");
	for(int i=0; i<yukseklik; i++){
		printf("---");
	}
	printf("\n");
	printf("  |");
	for(int i=0; i<yukseklik; i++){
		printf(" %d ", i+1);
	}
	printf("\n\n");
}

void dikey_histogram(int harf_notlari[], int yukseklik, char harfler[]){
	printf("# Başarı notları dağılım aralıkları (dikey histogram) #\n\n");
	for(int i=yukseklik; i>0; i--){
		printf("%2d| ", i);
			for(int j=0; j<10; j++){
				if(harf_notlari[j]==i){
					printf("** ");
					harf_notlari[j]--; // konulan harf notunu, harf_notu sayacindan eksiltir
				}
				else{
					printf("   ");
				}
			}
			printf("|\n");
	}

	printf("--+");
	for(int i=0; i<10; i++){
		printf("---");
	} printf("-+\n    ");

	for(int i=0; i<=18; i+=2){
		printf("%c", harfler[i]); printf("%c ", harfler[i+1]);
	}printf("\n");
}