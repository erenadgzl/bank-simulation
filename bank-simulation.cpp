#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

#define MAX 20

struct gise{
	int islemsuresi=0;
	int toplamhizmetsuresi=0;
	int musterisayisi=0;
	int gisedekimusterino;
};
typedef struct gise giseler;

struct kuyruk{
	int beklemesuresi;
	int musterino;
	struct kuyruk *next;
};
typedef struct kuyruk q;

q* push(q *kuyruk);
q* pop(q *kuyruk);
int islemsuresi();

	int top=-1;
	giseler gise[3];
	int musterino=1;
int main(){
	int N;
	int sayac=0;
	double ortalama;


	q *kuyruk=NULL;
	srand(time(NULL));
	int islemdk,dakika=0,musterigetir=0,enbuyukbeklemesuresi=0,sirasayisi=0,enbuyuksirasayisi=0,enuzunbekleyen,toplambeklemesuresi=0;
	q *link;
	int h=0,m=0;

	N=60; //Çalýþma süresi dakika
	do{
			if(dakika==N)
				printf("@BANKA KAPANDI@\n");

			if(dakika>=60){ //h deðiþkeninde kaç saat geçtiði hesaplanýyor.
				h=dakika/60;
				if(h>12)
					h=h%12;
			}

		if(musterigetir==dakika && dakika<N){ //Rastgele müþteri alýmý
			musterigetir=dakika+rand()%6+1; //Bir next müþterinin geleceði dakikanýn hesabý
			printf("(Saat %.2d:%.2d)//%d.Musteri geldi.",h,dakika%60,musterino);
			kuyruk=push(kuyruk); //kuyruk oluþturuluyor.
			islemdk=islemsuresi();//iþlem süresi belirleniyor.
			}

			for(int i=0;i<3;i++){
			if(gise[i].islemsuresi==0 && kuyruk!=NULL) // boþ giþeler kontrol edilip müþteriler giþelere gönderiliyor.
			{	printf("(Saat %.2d:%.2d)//%d.gise %d.musteriyi aldi.\n",h,dakika%60,i+1,kuyruk->musterino);

				if(enbuyukbeklemesuresi<kuyruk->beklemesuresi)//en büyük bekleme süresinin güncellenmesi
					{
					enbuyukbeklemesuresi=kuyruk->beklemesuresi;
					enuzunbekleyen=kuyruk->musterino;
					}
				toplambeklemesuresi+=kuyruk->beklemesuresi;	// ortalama bekleme süresinin hesaplanmasý için toplam süreyi hesaplýyoruz.
				gise[i].gisedekimusterino=kuyruk->musterino;
				gise[i].toplamhizmetsuresi+=islemdk; //giþedeki toplam hizmet süresi
				gise[i].musterisayisi++; // giþeye gelen toplam müþteri sayýsý hesaplanmasý
				gise[i].islemsuresi=islemdk;// giþeye gelen müþterinin kaç dakikalýk iþlemi olduðunu atýyoruz
				kuyruk=pop(kuyruk);
				break;
			}
			}



			for(int p=0;p<3;p++) //islemi biten musteriler giseden gönderiliyor ve gisedeki islem suresi hesaplanýyor
			{
				if(gise[p].islemsuresi>0)
					{
					gise[p].islemsuresi--; //giþelerdeki iþlemsürelerini her dakika düþürüyoruz
					if(gise[p].islemsuresi==0) // iþlem bitmiþ ise
						{
							printf("(Saat %.2d:%.2d)//%d. musterinin  %d. gisede isi bitti.\n",h,(dakika+1)%60,gise[p].gisedekimusterino,p+1);
						}
					}

			}
			sayac=0;
			for(int p=0;p<3;p++){   //Giþelerde iþlemlerini bitmemiþ olanlarýn kontrolü sayaç ile yapýlýyor
				sayac+=gise[p].islemsuresi; //sayacýn deðeri 0 ise bütün giþelerde iþlemlerimiz bitti.
			}

			sirasayisi=0;
			link=kuyruk;
			while(link!=NULL){ //BEKLEYENLERÝN BEKLEME SÜRELERÝ HER DÖNGÜDE 1 DAKÝKA ARTIYOR VE KUYRUK SAYISI HESAPLANIYOR
				link->beklemesuresi++;
				link=link->next;
				sirasayisi++;
			}
			if(sirasayisi>enbuyuksirasayisi){//EN UZUN KUYRUK SAYISI GÜNCELLENÝYOR
				enbuyuksirasayisi=sirasayisi;
			}
			dakika++;
	}while(dakika<N || kuyruk!=NULL || sayac!=0); //Süre dolunca kuyruk boþ ise ve giþelerde müþteri yok ise döngü sona erer.


	printf("\n%d. musteri kuyrukta en uzun bekledi. %d.dk\n",enuzunbekleyen,enbuyukbeklemesuresi);
	printf("En uzun kuyruk: %d\n",enbuyuksirasayisi);
	ortalama=(double)((double)toplambeklemesuresi/(double)(musterino-1));
	printf("Ortalama bekleme suresi :%.2lf\n\n",ortalama);

	for(int i=0;i<3;i++){
		printf("%d.Gisenin musteri sayisi:%d.",i+1,gise[i].musterisayisi);
		printf("//Ortalama hizmet suresi:%.1lf.dk\n",((double)gise[i].toplamhizmetsuresi/(double)gise[i].musterisayisi));
	}


 	return 0;
}


q* pop(q *kuyruk){
	if(top==-1)
	printf("\nKuyruk zaten bos.\n");
	else{
	kuyruk=kuyruk->next;
	top--;
	}
	return kuyruk;
}


q* push(q *kuyruk){
	if(top<MAX){
	if(kuyruk==NULL){
			kuyruk=(q *)malloc(1*sizeof(q));
			kuyruk->musterino=musterino;
			kuyruk->beklemesuresi=0;
			musterino++;
			kuyruk->next=NULL;
			top++;
		}else{
				q *temp=kuyruk;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=(q *)malloc(1*sizeof(q));
			temp=temp->next;
			temp->next=NULL;
			temp->beklemesuresi=0;
			temp->musterino=musterino;
			musterino++;
			top++;
			}
			return kuyruk;
	}else{
		printf("\nKuyruk doldu müsteri alinamiyor.\n");
	}

}

int islemsuresi(){
	int islem;
	switch(rand()%4+1){ //Random iþlem seçiliyor.
			case 1: islem=rand()%8+3; printf("(%ddk)Eft yapilacak.\n",islem); break;
			case 2: islem=rand()%11+10;printf("(%ddk)Kredi cekme yapilacak.\n",islem); break;
			case 3: islem=rand()%11+2;printf("(%ddk)Fatura odeme yapilacak.\n",islem); break;
			case 4: islem=rand()%7+1;printf("(%ddk)Para cekme yapilacak.\n",islem); break;
		}
	return islem;
}
