// ONEMLI NOT: Bu program bir GNU/LINUX dagitimi uzerinde yazilmistir. "gcc-5.4.0" ile test edilmistir.
// Derleme icin "gcc" kullaniniz.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// fonksiyon tanimlamalari
void mevcutKisiSayisi(FILE *ff); // DATA.dat dosyasinda hali hazirda bulunan kisi sayisini bulur
/* 1. KISI EKLE */
void kisiEkle(FILE *ff);
void bilgiAl(FILE *ff);
void bilgiYaz(FILE *ff);
/* 2. GORUNTULE */
void kisileriGoster(FILE *ff);
void kisileriEkranaBas();
/* 3. GUNCELLE */
void bilgiGuncelle(FILE *ff);
/* 4. SIL */
void kisiSil(FILE *ff);
/* 5. ARAMA */
void kisiAra(FILE *ff); 
/* MENU */
int menu(); 
void clear(); // ekrani temizler
char islemTekrarSor(); // islem tekrari icin sorgu yapar
void charTemizle(); // char giris sonucunda programin bozulmasini engeller

// GLOBAL tanimlamalar
struct adres{
	char mahalle[100];
	char sokak[100];
	char apt_ismi[100];
	char kapi_no[100];
	char ilce[100];
	char il[100];
};

struct dogum_gunu{
	char gun[100];
	char ay[100];
	char yil[100];
};

struct bilgiler{
	int no;
	char ad[100];
	char soyad[100];
	char cep_tel[100];
	char ev_tel[100];
	char is_tel[100];
	char eposta[100];
	struct dogum_gunu dogum_gunu;
	struct adres adres;
};
struct bilgiler kisi;

int	main(){
	FILE *ff;
	int opt;
	char c;
	ff = fopen("DATA.dat", "r+b");
	if(!ff){ // DATA.dat dosyasina erisilemezse olusturulur
			ff = fopen("DATA.dat", "wb"); 
			if(!ff){ // olusturulamaz ise surucu hatasi verir
				printf("Surucu bulunamadi..\n");
				return 1;
			}
			else{
				fclose(ff); // WRITE modunda acilan dosya tekrar normale donerek READ+ modunda acilir
				ff = fopen("DATA.dat", "r+b");
			}
	}
	mevcutKisiSayisi(ff);
	clear(); // program ilk calistirildiginda terminali temizler ve programi temiz bir arayuzde gosterir
	do{
		opt = menu();
		switch (opt){
			case 1: // KISI EKLE
				do{
					clear();
					kisiEkle(ff);
					c = islemTekrarSor();
					charTemizle();
				} while(c == 'E');
				clear(); break;
			case 2: // GORUNTULE
				if(kisi.no>0){
					clear();
					kisileriGoster(ff);
					printf("\t\t(->) Ana menuye donmek icin tiklayiniz.."); getche();
					clear(); break;
				}
				else{
					clear();
					printf("(->) UYARI: Rehbere kayitli kisi yok.. Oncelikle Rehbere kisi ekleyiniz..\n");
					break;
				}
			case 3: // GUNCELLE
				if(kisi.no>0){
					do{
						clear();
						bilgiGuncelle(ff);
						c = islemTekrarSor();
						charTemizle();
					} while(c == 'E');
					clear(); break;
				}
				else{
					clear();
					printf("(->) UYARI: Rehbere kayitli kisi yok.. Oncelikle Rehbere kisi ekleyiniz..\n");
					break;
				}
			case 4: // SIL
				if(kisi.no>0){
					do{
						clear();
						kisiSil(ff);
						c = islemTekrarSor();
						charTemizle();
					} while(c == 'E');
					clear(); break;
				}
				else{
					clear();
					printf("(->) UYARI: Rehbere kayitli kisi yok.. Oncelikle Rehbere kisi ekleyiniz..\n");
					break;
				}
			case 5: // ARAMA YAP
				if(kisi.no>0){
					do{
						clear();
						kisiAra(ff);
						c = islemTekrarSor();
						charTemizle();
					} while(c == 'E');
					clear(); break;
				}
				else{
					clear();
					printf("(->) UYARI: Rehbere kayitli kisi yok.. Oncelikle Rehbere kisi ekleyiniz..\n");
					break;
				}
			case 9:
				exit(0);
			default:
				clear();
				printf("(->) UYARI: Menu seceneklerine uygun girdi yapmadiniz..\n");
				break;
		}
	} while(1);
	fclose(ff);
	return 0;
}

// DATA.dat dosyasinda kac kisi ekli oldugunu bulur
void mevcutKisiSayisi(FILE *ff){
	kisi.no = 0;
	fseek(ff, 0, SEEK_END);
	kisi.no = ftell(ff);
	kisi.no = kisi.no / sizeof(kisi); // dosya boyutunu, sizeof(kisi)'e bu sayede dosyada mevcut olarak kac kisi oldugu bulunur
}

/* 1. KISI EKLE */
// eklenecek kisi hakkinda bilgi alinir ve DATA.dat dosyasina yazilir
void kisiEkle(FILE *ff){
	bilgiAl(ff);
	bilgiYaz(ff);
}

void bilgiAl(FILE *ff){
	// Buradaki yapinin bu sekilde kurulmasinin sebebi, 'gets' fonksinyonunun sorunlar cikarmasi ve 'bosluk' karakterninin de alinabilmesi icin
	// 'fgets' fonksiyonunun kullanilmasidir. 'fgets' fonksiyonu ile alinan verinin en son karakteri '\n' olarak kabul edildigi icin
	// kisileriGoster(); fonksiyonunun yapisini bozmaktaydi, bu sebepten dolayi alinan tum verilerin en son karakteri '\0' yapilarak, '\n' yok edilmistir
	printf("\n\n\t\t Kisinin bilgilerini giriniz..");
	printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t| Adi           : "); fgets(kisi.ad, sizeof(kisi.ad), stdin); kisi.ad[strlen(kisi.ad)-1] = '\0';
	printf("\t\t| Soyadi        : "); fgets(kisi.soyad, sizeof(kisi.soyad), stdin); kisi.soyad[strlen(kisi.soyad)-1] = '\0';
	printf("\t\t| Cep Telefonu  : "); fgets(kisi.cep_tel, sizeof(kisi.cep_tel), stdin); kisi.cep_tel[strlen(kisi.cep_tel)-1] = '\0';
	printf("\t\t| Ev Telefonu   : "); fgets(kisi.ev_tel, sizeof(kisi.ev_tel), stdin); kisi.ev_tel[strlen(kisi.ev_tel)-1] = '\0';
	printf("\t\t| Is Telefonu   : "); fgets(kisi.is_tel, sizeof(kisi.is_tel), stdin); kisi.is_tel[strlen(kisi.is_tel)-1] = '\0';
	printf("\t\t| Mail Adresi   : "); fgets(kisi.eposta, sizeof(kisi.eposta), stdin); kisi.eposta[strlen(kisi.eposta)-1] = '\0';
	
	printf("\t\t| Dogum Gunu"); 
		printf("\n\t\t|\t (Gun)  : "); fgets(kisi.dogum_gunu.gun, sizeof(kisi.dogum_gunu.gun), stdin); kisi.dogum_gunu.gun[strlen(kisi.dogum_gunu.gun)-1] = '\0';
		printf("\t\t|\t (Ay)   : "); fgets(kisi.dogum_gunu.ay, sizeof(kisi.dogum_gunu.ay), stdin); kisi.dogum_gunu.ay[strlen(kisi.dogum_gunu.ay)-1] = '\0';
		printf("\t\t|\t (Yil)  : "); fgets(kisi.dogum_gunu.yil, sizeof(kisi.dogum_gunu.yil), stdin); kisi.dogum_gunu.yil[strlen(kisi.dogum_gunu.yil)-1] = '\0';
	
	printf("\t\t| Ev Adresi ");
		printf("\n\t\t|\t Mahalle: "); fgets(kisi.adres.mahalle, sizeof(kisi.adres.mahalle), stdin); kisi.adres.mahalle[strlen(kisi.adres.mahalle)-1] = '\0';
		printf("\t\t|\t Sokak  : "); fgets(kisi.adres.sokak, sizeof(kisi.adres.sokak), stdin); kisi.adres.sokak[strlen(kisi.adres.sokak)-1] = '\0';
		printf("\t\t|\t Apt Adi: "); fgets(kisi.adres.apt_ismi, sizeof(kisi.adres.apt_ismi), stdin); kisi.adres.apt_ismi[strlen(kisi.adres.apt_ismi)-1] = '\0';
		printf("\t\t|\t Kapi No: "); fgets(kisi.adres.kapi_no, sizeof(kisi.adres.kapi_no), stdin); kisi.adres.kapi_no[strlen(kisi.adres.kapi_no)-1] = '\0';
		printf("\t\t|\t Ilce   : "); fgets(kisi.adres.ilce, sizeof(kisi.adres.ilce), stdin); kisi.adres.ilce[strlen(kisi.adres.ilce)-1] = '\0';
		printf("\t\t|\t Il     : "); fgets(kisi.adres.il, sizeof(kisi.adres.il), stdin); kisi.adres.il[strlen(kisi.adres.il)-1] = '\0';
	printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	kisi.no++;
}

void bilgiYaz(FILE *ff){
	fseek(ff, ((kisi.no-1)*sizeof(kisi)), SEEK_SET);
	fwrite(&kisi, sizeof(kisi), 1, ff);
}

/* 2. GORUNTULE */
// DATA.dat dosyasinda bulunan tum veriler kutu icerisinde ekrana basilir
void kisileriGoster(FILE *ff){
	int k; int temp;
	printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	temp = kisi.no;
	if(kisi.no>0){
		printf("\n\t\t|Rehbere kayitli kisiler:");
		for(int i=0; i<temp; i++){
			fseek(ff, i*sizeof(kisi), SEEK_SET);
			fread(&kisi, sizeof(kisi), 1, ff);
			kisileriEkranaBas();
		}
	}
	else
		printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
	kisi.no = temp;
	printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

void kisileriEkranaBas(){
	printf("\n\t\t|-----------------\n");
			printf("\t\t|   %3d. KISI\n", kisi.no);
			printf("\t\t|-----------------\n");
			printf("\t\t|  Adi           : %s\n", kisi.ad);
			printf("\t\t|  Soyadi        : %s\n", kisi.soyad);
			printf("\t\t|  Cep Telefonu  : %s\n", kisi.cep_tel);
			printf("\t\t|  Ev Telefonu   : %s\n", kisi.ev_tel);
			printf("\t\t|  Is Telefonu   : %s\n", kisi.is_tel);
			printf("\t\t|  Mail Adresi   : %s\n", kisi.eposta);
			printf("\t\t|  Dogum Gunu    : %s-%s-%s\n", kisi.dogum_gunu.gun, kisi.dogum_gunu.ay, kisi.dogum_gunu.yil); 
			printf("\t\t|  Ev Adresi     : %s,%s,\n\t\t|\t\t   %s,%s,%s/%s", kisi.adres.mahalle, kisi.adres.sokak, kisi.adres.apt_ismi, kisi.adres.kapi_no, kisi.adres.ilce, kisi.adres.il);
}

/* 3. GUNCELLE */
// "kisi.no" yani kalinan en son numara bir "temp" degerine alinir, daha sonrasinda guncellenecek numaraya gore "bilgiAl"
//  ya da diger islemler uygulanir ardindan "kisi.no" eski haline getirilerek guncellenir
void bilgiGuncelle(FILE *ff){
	kisileriGoster(ff);
	int k, temp, sec, sec2;
	printf("\t\t(++) Guncellemek istediginiz kisinin numarisi: "); scanf("%d", &k);
	k--;
	fseek(ff, k * sizeof(kisi), SEEK_SET);
	temp = kisi.no;
	kisi.no = k;
	charTemizle();
	if(0<=k && k<temp){
		clear();
		printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n\t\t| Hangi bilgiyi guncellemek istersiniz ?\n");
		printf("\t\t|  1) Adi ve Soyadi\n");
		printf("\t\t|  2) Telefon Numarasi\n");
		printf("\t\t|  3) Mail Adresi\n");
		printf("\t\t|  4) Dogum Gunu\n");
		printf("\t\t|  5) Ev Adresi\n");
		printf("\t\t|  6) HEPSI");
		printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\t\t\t\t\tSecenek: ");scanf("%d", &sec);
		charTemizle();
		switch (sec){
			case 1:
				clear();
				printf("\n\n\t\t Kisiye ait yeni adi ve soyadini giriniz..");
				fread(&kisi, sizeof(kisi), 1, ff);
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Adi           : "); fgets(kisi.ad, sizeof(kisi.ad), stdin); kisi.ad[strlen(kisi.ad)-1] = '\0';
				printf("\t\t| Soyadi        : "); fgets(kisi.soyad, sizeof(kisi.soyad), stdin); kisi.soyad[strlen(kisi.soyad)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				bilgiYaz(ff);
				printf("\t\t(!!) Kisi guncellendi!\n");
				kisi.no = temp;
				break;
			case 2:
				clear();
				fread(&kisi, sizeof(kisi), 1, ff);
				printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\t\t| Hangi bilgiyi guncellemek istersiniz ?\n");
				printf("\t\t|  1) Cep Telefonu\n");
				printf("\t\t|  2) Ev Telefonu\n");
				printf("\t\t|  3) Is Telefonu\n");
				printf("\t\t|  4) HEPSI\n");
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t\t\t\tSecenek: ");scanf("%d", &sec2);
				charTemizle();
				switch (sec2){
					case 1:
						clear();
						printf("\n\n\t\t Kisiye ait yeni cep telefonu numarasini giriniz..\n");
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						printf("\t\t| Cep Telefonu  : "); fgets(kisi.cep_tel, sizeof(kisi.cep_tel), stdin); kisi.cep_tel[strlen(kisi.cep_tel)-1] = '\0';
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
						bilgiYaz(ff);
						printf("\t\t(!!) Kisi guncellendi!\n");
						break;
					case 2:
						clear();
						printf("\n\n\t\t Kisiye ait yeni ev telefonu numarasini giriniz..\n");
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						printf("\t\t| Ev Telefonu   : "); fgets(kisi.ev_tel, sizeof(kisi.ev_tel), stdin); kisi.ev_tel[strlen(kisi.ev_tel)-1] = '\0';
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
						bilgiYaz(ff);
						printf("\t\t(!!) Kisi guncellendi!\n");
						break;
					case 3:
						clear();
						printf("\n\n\t\t Kisiye ait yeni is telefonu numarasini giriniz..\n");
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						printf("\t\t| Is Telefonu   : "); fgets(kisi.is_tel, sizeof(kisi.is_tel), stdin); kisi.is_tel[strlen(kisi.is_tel)-1] = '\0';
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
						bilgiYaz(ff);
						printf("\t\t(!!) Kisi guncellendi!\n");
						break;
					case 4:
						clear();
						printf("\n\n\t\t Kisiye ait yeni telefon numaralarini giriniz..\n");
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						printf("\t\t| Cep Telefonu  : "); fgets(kisi.cep_tel, sizeof(kisi.cep_tel), stdin); kisi.cep_tel[strlen(kisi.cep_tel)-1] = '\0';
						printf("\t\t| Ev Telefonu   : "); fgets(kisi.ev_tel, sizeof(kisi.ev_tel), stdin); kisi.ev_tel[strlen(kisi.ev_tel)-1] = '\0';
						printf("\t\t| Is Telefonu   : "); fgets(kisi.is_tel, sizeof(kisi.is_tel), stdin); kisi.is_tel[strlen(kisi.is_tel)-1] = '\0';
						printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
						bilgiYaz(ff);
						printf("\t\t(!!) Kisi guncellendi!\n");
						break;
					default:
						printf("\t\t(->) UYARI: Menu seceneklerine uygun girdi yapmadiniz..\n");
						break;
				}
				kisi.no = temp;
				break;
			case 3:
				clear();
				printf("\n\n\t\t Kisiye ait yeni mail adresini giriniz..");
				fread(&kisi, sizeof(kisi), 1, ff);
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Mail Adresi   : "); fgets(kisi.eposta, sizeof(kisi.eposta), stdin); kisi.eposta[strlen(kisi.eposta)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				bilgiYaz(ff);
				printf("\t\t(!!) Kisi guncellendi!\n");
				kisi.no = temp;
				break;
			case 4:
				clear();
				printf("\n\n\t\t Kisiye ait yeni dogum gunu tarihini giriniz..");
				fread(&kisi, sizeof(kisi), 1, ff);
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Dogum Gunu"); 
					printf("\n\t\t|\t (Gun)  : "); fgets(kisi.dogum_gunu.gun, sizeof(kisi.dogum_gunu.gun), stdin); kisi.dogum_gunu.gun[strlen(kisi.dogum_gunu.gun)-1] = '\0';
					printf("\t\t|\t (Ay)   : "); fgets(kisi.dogum_gunu.ay, sizeof(kisi.dogum_gunu.ay), stdin); kisi.dogum_gunu.ay[strlen(kisi.dogum_gunu.ay)-1] = '\0';
					printf("\t\t|\t (Yil)  : "); fgets(kisi.dogum_gunu.yil, sizeof(kisi.dogum_gunu.yil), stdin); kisi.dogum_gunu.yil[strlen(kisi.dogum_gunu.yil)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				bilgiYaz(ff);
				printf("\t\t(!!) Kisi guncellendi!\n");
				kisi.no = temp;
				break;
			case 5:
				clear();
				printf("\n\n\t\t Kisiye ait yeni ev adresini giriniz..");
				fread(&kisi, sizeof(kisi), 1, ff);
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Ev Adresi ");
					printf("\n\t\t|\t Mahalle: "); fgets(kisi.adres.mahalle, sizeof(kisi.adres.mahalle), stdin); kisi.adres.mahalle[strlen(kisi.adres.mahalle)-1] = '\0';
					printf("\t\t|\t Sokak  : "); fgets(kisi.adres.sokak, sizeof(kisi.adres.sokak), stdin); kisi.adres.sokak[strlen(kisi.adres.sokak)-1] = '\0';
					printf("\t\t|\t Apt Adi: "); fgets(kisi.adres.apt_ismi, sizeof(kisi.adres.apt_ismi), stdin); kisi.adres.apt_ismi[strlen(kisi.adres.apt_ismi)-1] = '\0';
					printf("\t\t|\t Kapi No: "); fgets(kisi.adres.kapi_no, sizeof(kisi.adres.kapi_no), stdin); kisi.adres.kapi_no[strlen(kisi.adres.kapi_no)-1] = '\0';
					printf("\t\t|\t Ilce   : "); fgets(kisi.adres.ilce, sizeof(kisi.adres.ilce), stdin); kisi.adres.ilce[strlen(kisi.adres.ilce)-1] = '\0';
					printf("\t\t|\t Il     : "); fgets(kisi.adres.il, sizeof(kisi.adres.il), stdin); kisi.adres.il[strlen(kisi.adres.il)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				bilgiYaz(ff);
				printf("\t\t(!!) Kisi guncellendi!\n");
				kisi.no = temp;
				break;
			case 6:
				clear();
				bilgiAl(ff);
				bilgiYaz(ff);
				kisi.no = temp;
				break;
			default:
				printf("\t\t(->) UYARI: Menu seceneklerine uygun girdi yapmadiniz..\n");
				break;
		}
		kisi.no = temp;
	}
	else{
		printf("\t\t(!!) Bu numaraya ait bir kisi bulunamadi\n");
		kisi.no = temp;
	}
}

/* 4. SIL */
// silinecek degerden sonraki tum bilgiler bir adim sola kayar, ardindan programin sonun kalan sizeof(kisi) kadar alan
// kopyalama teknigi ile silinir, bu sekilde veri silinmis olur
void kisiSil(FILE *ff){
	kisileriGoster(ff);
	int k, temp;
	char c;
	FILE *ff_copy;
	printf("\t\t(++) Silmek istediginiz kisinin numarisi: "); scanf("%d", &k);
	charTemizle();
	k--;
	temp = kisi.no;
	kisi.no = k;
	if(0<=k && k<temp){
		printf("\t\t(->) Kisi silinecek, Bu islemin geri donusu yoktur, Devam etmek istiyor musun (E/e)? "); c = getchar();
		if(c == '\n') { c = getchar(); } // fazladan bir "\n" algilayip secenege cevap verilmeden kapanmasini engeller
		if(toupper(c) == 'E'){
			for(int i=k; i<temp; i++){ // silinecek kisiden sonraki herkes bir adim yukari kayar, bu sayede kisi silinmis olur
				fseek(ff, (i+1)*sizeof(kisi), SEEK_SET); fread(&kisi, sizeof(kisi), 1, ff);
				fseek(ff, i*sizeof(kisi), SEEK_SET); kisi.no=i+1; fwrite(&kisi, sizeof(kisi), 1, ff);
			}
			printf("\t\t(!!) Kisi silindi!\n");
			kisi.no = temp;
			kisi.no--;
			temp = kisi.no;
			ff_copy = fopen("DATA_copy.dat", "wb");
			for(int i=0; i<temp; i++){ // kisi silindikten sonra dosya sonunda kalan sizeof(kisi) kadarlik alani, kopyala-yapistir teknigi ile siler
				fseek(ff, i*sizeof(kisi), SEEK_SET); fread(&kisi, sizeof(kisi), 1, ff);
				fseek(ff_copy, i*sizeof(kisi), SEEK_SET); fwrite(&kisi, sizeof(kisi), 1, ff_copy);
			}
			fclose(ff);
			remove("DATA.dat");
			rename("DATA_copy.dat", "DATA.dat");
			fclose(ff_copy);
			fopen("DATA.dat", "r+b");
		}
		else
			printf("\t\t(!!) Kisi silme islemi iptal edildi!\n");
		kisi.no = temp;
	}
	else{
		printf("\t\t(!!) Bu numaraya ait bir kisi bulunamadi\n");
		kisi.no = temp;
	}
}

/* 5. ARAMA */
void kisiAra(FILE *ff){
	int sec, sec2;
	int temp, control;
	control = 0;
	temp = kisi.no;
	printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t| Hangi bilgiye gore arama yapmak istersiniz ?\n");
	printf("\t\t|  1) Adi\n");
	printf("\t\t|  2) Soyadi\n");
	printf("\t\t|  3) Telefon Numarasi\n");
	printf("\t\t|  4) Mail Adresi\n");
	printf("\t\t|  5) Dogum Gunu\n");
	printf("\t\t|  6) Yasadigi Il");
	printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t\t\tSecenek: "); scanf("%d", &sec);
	charTemizle();
	switch (sec){
		case 1: // AD
			clear();
			char tempad[100];
			printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t| Adi           : "); fgets(tempad, sizeof(tempad), stdin); tempad[strlen(tempad)-1] = '\0';
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			clear();
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t|Arama sonucu:");
			for(int i=0; i<temp; i++){
				fseek(ff, i*sizeof(kisi), SEEK_SET);
				fread(&kisi, sizeof(kisi), 1, ff);
				if(!strcmp(tempad, kisi.ad)){
					kisileriEkranaBas();
					control++;
				}
			}
			if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
				printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			kisi.no = temp;
			break;
		case 2: // SOYAD
			clear();
			char tempsoyad[100];
			printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t| Soyadi        : "); fgets(tempsoyad, sizeof(tempsoyad), stdin); tempsoyad[strlen(tempsoyad)-1] = '\0';
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			clear();
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t|Arama sonucu:");
			for(int i=0; i<temp; i++){
				fseek(ff, i*sizeof(kisi), SEEK_SET);
				fread(&kisi, sizeof(kisi), 1, ff);
				if(!strcmp(tempsoyad, kisi.soyad)){
					kisileriEkranaBas();
					control++;
				}
			}
			if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
				printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			kisi.no = temp;
			break;
		case 3: // TELEFON NUMARASI
			clear();
			char tempcep_tel[100],tempev_tel[100],tempis_tel[100];
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t| Hangi telefon bilgisini guncelleyeceksiniz ?\n");
			printf("\t\t|  1) Cep Telefonu\n");
			printf("\t\t|  2) Ev Telefonu\n");
			printf("\t\t|  3) Is Telefonu\n");
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t\t\t\tSecenek: ");scanf("%d", &sec2);
			charTemizle();
			switch (sec2){
			case 1:
				clear();
				printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Cep Telefonu  : "); fgets(tempcep_tel, sizeof(tempcep_tel), stdin); tempcep_tel[strlen(tempcep_tel)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				clear();
				printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\t\t|Arama sonucu:");
				for(int i=0; i<temp; i++){
					fseek(ff, i*sizeof(kisi), SEEK_SET);
					fread(&kisi, sizeof(kisi), 1, ff);
					if(!strcmp(tempcep_tel, kisi.cep_tel)){
						kisileriEkranaBas();
						control++;
					}
				}
				if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
					printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				kisi.no = temp;
				break;
			case 2:
				clear();
				printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Ev Telefonu   : "); fgets(tempev_tel, sizeof(tempev_tel), stdin); tempev_tel[strlen(tempev_tel)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				clear();
				printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\t\t|Arama sonucu:");
				for(int i=0; i<temp; i++){
					fseek(ff, i*sizeof(kisi), SEEK_SET);
					fread(&kisi, sizeof(kisi), 1, ff);
					if(!strcmp(tempev_tel, kisi.ev_tel)){
						kisileriEkranaBas();
						control++;
					}
				}
				if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
					printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				kisi.no = temp;
				break;
			case 3:
				clear();
				printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("\t\t| Is Telefonu   : "); fgets(tempis_tel, sizeof(tempis_tel), stdin); tempis_tel[strlen(tempis_tel)-1] = '\0';
				printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				clear();
				printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\t\t|Arama sonucu:");
				for(int i=0; i<temp; i++){
					fseek(ff, i*sizeof(kisi), SEEK_SET);
					fread(&kisi, sizeof(kisi), 1, ff);
					if(!strcmp(tempis_tel, kisi.is_tel)){
						kisileriEkranaBas();
						control++;
					}
				}
				if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
					printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
				printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
				kisi.no = temp;
				break;
			default:
				printf("\t\t(->) UYARI: Menu seceneklerine uygun girdi yapmadiniz..\n");
				break;
		}
		kisi.no = temp;
		break;
		case 4: // MAIL ADRESI
			clear();
			char tempeposta[100];
			printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t| Mail Adresi   : "); fgets(tempeposta, sizeof(tempeposta), stdin); tempeposta[strlen(tempeposta)-1] = '\0';
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			clear();
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t|Arama sonucu:");
			for(int i=0; i<temp; i++){
				fseek(ff, i*sizeof(kisi), SEEK_SET);
				fread(&kisi, sizeof(kisi), 1, ff);
				if(!strcmp(tempeposta, kisi.eposta)){
					kisileriEkranaBas();
					control++;
				}
			}
			if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
				printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			kisi.no = temp;
			break;
		case 5: // DOGUM GUNU
			clear();
			char tempdogum_gunugun[100],tempdogum_gunuay[100],tempdogum_gunuyil[100];
			printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\t\t| Dogum Gunu"); 
			printf("\n\t\t|\t (Gun)  : "); fgets(tempdogum_gunugun, sizeof(tempdogum_gunugun), stdin); tempdogum_gunugun[strlen(tempdogum_gunugun)-1] = '\0';
			printf("\t\t|\t (Ay)   : "); fgets(tempdogum_gunuay, sizeof(tempdogum_gunuay), stdin); tempdogum_gunuay[strlen(tempdogum_gunuay)-1] = '\0';
			printf("\t\t|\t (Yil)  : "); fgets(tempdogum_gunuyil, sizeof(tempdogum_gunuyil), stdin); tempdogum_gunuyil[strlen(tempdogum_gunuyil)-1] = '\0';
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			clear();
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t|Arama sonucu:");
			for(int i=0; i<temp; i++){
				fseek(ff, i*sizeof(kisi), SEEK_SET);
				fread(&kisi, sizeof(kisi), 1, ff);
				if(!strcmp(tempdogum_gunugun, kisi.dogum_gunu.gun)&&!strcmp(tempdogum_gunuay, kisi.dogum_gunu.ay)&&!strcmp(tempdogum_gunuyil, kisi.dogum_gunu.yil)){
					kisileriEkranaBas();
					control++;
				}
			}
			if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
				printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			kisi.no = temp;
			break;
		case 6: // YASADIGI IL
			clear();
			char tempadresil[100];
			printf("\n\n\t\t Arama yapilacak bilgileri giriniz..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("\t\t| Yasadigi Il   : "); fgets(tempadresil, sizeof(tempadresil), stdin); tempadresil[strlen(tempadresil)-1] = '\0';
			printf("\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			clear();
			printf("\n\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			printf("\n\t\t|Arama sonucu:");
			for(int i=0; i<temp; i++){
				fseek(ff, i*sizeof(kisi), SEEK_SET);
				fread(&kisi, sizeof(kisi), 1, ff);
				if(!strcmp(tempadresil, kisi.adres.il)){
					kisileriEkranaBas();
					control++;
				}
			}
			if(!control) // control "0" ise, yani aramada herhangi biri bulunamadiysa
				printf("\n\t\t|  (!!) Rehbere kayitli kisi bulunamadi..");
			printf("\n\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
			kisi.no = temp;
			break;
		default:
			kisi.no = temp;
			printf("\t\t(->) UYARI: Menu seceneklerine uygun girdi yapmadiniz..\n");
			break;
	}
}

/* MENU */
// programda uygulanacak secenegi alir ve main()'e yollar
int menu(){
	int opt;
	printf( "\n");	
	printf( "\t\t  ___\n");
	printf( "\t\t /   \\\n");
	printf( "\t\t |   |\n");
	printf( "\t\t |   |\n");
	printf( "\t\t/~~~~~~~~~~~~~~~~~~~~\\\n");
	printf( "\t\t|     SECENEKLER     |\t\t\t\t\t   Cikmak Icin(9)\n");
	printf( "\t\t|~~~~~~~~~~~~~~~~~~~~|\t#####    #######  #     #  ######   #######  #####\n");
	printf( "\t\t| 1- Kisi Ekle       |\t#    #   #        #     #  #     #  #        #    #\n");
	printf( "\t\t| 2- Goruntule       |\t#####    #####    #######  ######   ######   #####\n");
	printf( "\t\t| 3- Guncelle        |\t#    #   #        #     #  #     #  #        #    #\n");
	printf( "\t\t| 4- Sil             |\t#     #  #######  #     #  ######   #######  #     #\n");
	printf( "\t\t| 5- Arama yap       |\t\t\t\t    Kayitli Kisi Sayisi: \"%d\"\n", kisi.no);
   printf( "\t\t\\~~~~~~~~~~~~~~~~~~~~/\n");
	printf( "\t\t/         _          \\\n");
	printf( "\t\t| (Y)  | [_]  | (N)  |\n"); 
	printf( "\t\t| (1)  | (2)  | (3)  |\n");
	printf( "\t\t| (4)  | (5)  | (6)  |\n");
	printf( "\t\t| (7)  | (8)  | (9)  |\n");
	printf( "\t\t| (*)  | (0)  | (#)  |\n");
   printf( "\t\t\\~~~~~~~~~~~~~~~~~~~~/\t Secenek: "); scanf("%d",&opt);
   	charTemizle();
	return opt;
}

void clear(){
	system("clear||cls");
	system("clear||cls"); // "clear", linux sistemler icin ; "cls", windows sistemler icin
	// sekmeler arasi farki biraz daha acmak icin komutu iki defa yurutulur
}

char islemTekrarSor(){
	printf("\t\t(->) Islemi tekrarlamak ister misin (E/e)? "); char c; 
	c = getchar();
	if(c == '\n') { c = getchar(); } // fazladan bir "\n" algilayip secenege cevap verilmeden kapanmasini engeller
	return toupper(c);
	clear();
}

void charTemizle(){
	char ch;
	while(ch != '\n'){ (ch = getchar()); } // char girmesi sonucunda programin bozulmasini engeller
}