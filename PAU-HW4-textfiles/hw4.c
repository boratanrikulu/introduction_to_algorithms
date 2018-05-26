#include <stdio.h>
#include <string.h>
#include <math.h>
int oku(FILE *dd_r);
int yaz(FILE *dd_w);
void kacKisi(FILE *dd_r);
float BNotu(int Vize, int Final, int Proje);
char *harfNotu(float BNotu, unsigned short ogrDevam);
float standart(float farkToplam, unsigned short ogrSayi);
float sinifOrtalama(float toplam, unsigned short ogrSayi);
void sifirla();
void goster(FILE *dd_w);
void bastirHarf(FILE *dd_w);

// Global tanimlamalar
int harf_notlari[11];
struct ogrTip{
	int No;
	char Ad[20];
	char Soyad[20];
	unsigned Vize;
	unsigned Final;
	unsigned Proje;
	unsigned short Devam;
	unsigned short Sayi;
	float BNotu;
	char Harf[2];
} ogr;

int	main(){
	FILE *dd_r, *dd_w;
	float toplam = 0;
	float ortalama;
	dd_r=fopen("CENG101_IN.txt", "r");
	dd_w=fopen("CENG101_OUT.TXT", "w+");
	if(!dd_r || !dd_w)
		printf("Surucu veya dosya bulunamadi..\n");

	else{
		int c;
		fprintf(dd_w,"OGRENCI#\tAD\tSOYAD\t\tVIZE\tFINAL\tPROJE\tB.NOTU\tHARF\n");
		for(int i=0; i<38; i++) { fprintf(dd_w, "=="); } fprintf(dd_w, "\n"); // basligin cizgisini cizer
		kacKisi(dd_r); // kac kisi oldugunu bulur, ogr.Sayi degerine aktarir
		rewind(dd_r);
		sifirla(); // harf_notlari sayaclarini sifirlar
		while((c = oku(dd_r)) != EOF){ // okuma ve yazma islemleri yapiliyor
			ogr.BNotu = BNotu(ogr.Vize, ogr.Final, ogr.Proje);		/* tum degerleri diziye kopyalayip islem yapmak istemedigimden dolayi, */
			strncpy(ogr.Harf, harfNotu(ogr.BNotu, ogr.Devam), 2);	/* okunan satirla ilgili islemleri yapip dosyaya verileri kullanarak yazdirdim, */
			yaz(dd_w);												/* bu sayede dizi tanimlayip tum verileri RAM uzerinde tutmak zorunda kalmadim. */
			toplam += ogr.BNotu;
		}
		ortalama = sinifOrtalama(toplam,ogr.Sayi);
		rewind(dd_r);
		float farkToplam=0;
		while((c = oku(dd_r)) != EOF){ // standart sapmayi bulmak icin tekrar taraniyor
			ogr.BNotu = BNotu(ogr.Vize, ogr.Final, ogr.Proje);
			farkToplam += pow((ortalama - ogr.BNotu), 2);
		}

		fprintf(dd_w, "Ogrenci Sayisi: %hu\n", (ogr.Sayi));
		fprintf(dd_w, "Basari Notlari Ortalamasi: %5.2f\n", ortalama);
		fprintf(dd_w, "Basari Notlari Standart Sapmasi: %5.2f\n", standart(farkToplam,ogr.Sayi));
		bastirHarf(dd_w); // harf notlari dagilim bilgilerini gosterir
		rewind(dd_w);
		goster(dd_w); // yazilarak islem yapilan dosyayi terminal uzerinde goruntuler

		fclose(dd_r); fclose(dd_w);
	}
	return 0;
}

int oku(FILE *dd_r){
	return fscanf(dd_r, "%d%s%s%u%u%u%hu", &ogr.No, ogr.Ad, ogr.Soyad, &ogr.Vize, &ogr.Final, &ogr.Proje, &ogr.Devam);
}
int yaz(FILE *dd_w){
	return fprintf(dd_w, "%d\t%s\t%s\t\t%3u\t%3u\t%3u\t%3.0f\t%s\n", ogr.No, ogr.Ad, ogr.Soyad, ogr.Vize, ogr.Final, ogr.Proje, ogr.BNotu, ogr.Harf);
}
void kacKisi(FILE *dd_r){
	ogr.Sayi = 1;
	while(!feof(dd_r)){ // kac kisi oldugunu, satir sayisini baz alarak bulur
		char control = fgetc(dd_r);
		if(control == '\n'){
			ogr.Sayi++;
		}
	}
}
float BNotu(int vize, int final, int proje){
	static float BNotu;
	BNotu = vize*0.3 + final*0.4 + proje*0.3;
	return BNotu;
}
void goster(FILE *dd_w){
	int c;
	while((c = getc(dd_w)) != EOF){
		putchar(c);
	}
}
void sifirla(){
	for(int i=0; i<11; i++){
		harf_notlari[i] = 0; // harf_notlari sayaclarini sifirlar
	}
}
char *harfNotu(float BNotu, unsigned short ogrDevam){
	static char harf[2];
	if(ogrDevam==0){
		harf_notlari[10]++; strcpy(harf, "F2"); }
	else if(89.50<=BNotu && BNotu <= 100){
		harf_notlari[0]++; strcpy(harf, "A1"); }
	else if(79.50<=BNotu && BNotu < 89.50){
		harf_notlari[1]++; strcpy(harf, "A2"); }
	else if(74.50<=BNotu && BNotu < 79.50){
		harf_notlari[2]++; strcpy(harf, "B1"); }
	else if(69.50<=BNotu && BNotu < 74.50){
		harf_notlari[3]++; strcpy(harf, "B2"); }
	else if(64.50<=BNotu && BNotu < 69.50){
		harf_notlari[4]++; strcpy(harf, "C1"); }
	else if(59.50<=BNotu && BNotu < 64.50){
		harf_notlari[5]++; strcpy(harf, "C2"); }
	else if(54.50<=BNotu && BNotu < 59.50){
		harf_notlari[6]++; strcpy(harf, "D1"); }
	else if(49.50<=BNotu && BNotu < 54.50){
		harf_notlari[7]++; strcpy(harf, "D2"); }
	else if(39.50<=BNotu && BNotu < 49.50){
		harf_notlari[8]++; strcpy(harf, "E"); }
	else if(0<=BNotu && BNotu < 39.50){
		harf_notlari[9]++; strcpy(harf, "F1"); }
	return harf;
}
void bastirHarf(FILE *dd_w){
	char harfler[23] = "A1A2B1B2C1C2D1D2E F1F2";
	fprintf(dd_w, "Harf Notlari Dagilimlari:\n");
	for(int i=0; i<22; i+=2){
		fprintf(dd_w, "%c", harfler[i]); fprintf(dd_w, "%c:", harfler[i+1]); fprintf(dd_w, "%3d\n", harf_notlari[i/2]);
	}
}
float sinifOrtalama(float toplam, unsigned short ogrSayi){
	float ortalama;
	ortalama = toplam/ogrSayi;
	return ortalama;
}
float standart(float farkToplam, unsigned short ogrSayi){
	float x = sqrt(farkToplam/(ogrSayi-1));
	return x;
}