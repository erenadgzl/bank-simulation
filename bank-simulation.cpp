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

	N=60; //�al��ma s�resi dakika
	do{
			if(dakika==N)
				printf("@BANKA KAPANDI@\n");

			if(dakika>=60){ //h de�i�keninde ka� saat ge�ti�i hesaplan�yor.
				h=dakika/60;
				if(h>12)
					h=h%12;
			}

		if(musterigetir==dakika && dakika<N){ //Rastgele m��teri al�m�
			musterigetir=dakika+rand()%6+1; //Bir next m��terinin gelece�i dakikan�n hesab�
			printf("(Saat %.2d:%.2d)//%d.Musteri geldi.",h,dakika%60,musterino);
			kuyruk=push(kuyruk); //kuyruk olu�turuluyor.
			islemdk=islemsuresi();//i�lem s�resi belirleniyor.
			}

			for(int i=0;i<3;i++){
			if(gise[i].islemsuresi==0 && kuyruk!=NULL) // bo� gi�eler kontrol edilip m��teriler gi�elere g�nderiliyor.
			{	printf("(Saat %.2d:%.2d)//%d.gise %d.musteriyi aldi.\n",h,dakika%60,i+1,kuyruk->musterino);

				if(enbuyukbeklemesuresi<kuyruk->beklemesuresi)//en b�y�k bekleme s�resinin g�ncellenmesi
					{
					enbuyukbeklemesuresi=kuyruk->beklemesuresi;
					enuzunbekleyen=kuyruk->musterino;
					}
				toplambeklemesuresi+=kuyruk->beklemesuresi;	// ortalama bekleme s�resinin hesaplanmas� i�in toplam s�reyi hesapl�yoruz.
				gise[i].gisedekimusterino=kuyruk->musterino;
				gise[i].toplamhizmetsuresi+=islemdk; //gi�edeki toplam hizmet s�resi
				gise[i].musterisayisi++; // gi�eye gelen toplam m��teri say�s� hesaplanmas�
				gise[i].islemsuresi=islemdk;// gi�eye gelen m��terinin ka� dakikal�k i�lemi oldu�unu at�yoruz
				kuyruk=pop(kuyruk);
				break;
			}
			}



			for(int p=0;p<3;p++) //islemi biten musteriler giseden g�nderiliyor ve gisedeki islem suresi hesaplan�yor
			{
				if(gise[p].islemsuresi>0)
					{
					gise[p].islemsuresi--; //gi�elerdeki i�lems�relerini her dakika d���r�yoruz
					if(gise[p].islemsuresi==0) // i�lem bitmi� ise
						{
							printf("(Saat %.2d:%.2d)//%d. musterinin  %d. gisede isi bitti.\n",h,(dakika+1)%60,gise[p].gisedekimusterino,p+1);
						}
					}

			}
			sayac=0;
			for(int p=0;p<3;p++){   //Gi�elerde i�lemlerini bitmemi� olanlar�n kontrol� saya� ile yap�l�yor
				sayac+=gise[p].islemsuresi; //sayac�n de�eri 0 ise b�t�n gi�elerde i�lemlerimiz bitti.
			}

			sirasayisi=0;
			link=kuyruk;
			while(link!=NULL){ //BEKLEYENLER�N BEKLEME S�RELER� HER D�NG�DE 1 DAK�KA ARTIYOR VE KUYRUK SAYISI HESAPLANIYOR
				link->beklemesuresi++;
				link=link->next;
				sirasayisi++;
			}
			if(sirasayisi>enbuyuksirasayisi){//EN UZUN KUYRUK SAYISI G�NCELLEN�YOR
				enbuyuksirasayisi=sirasayisi;
			}
			dakika++;
	}while(dakika<N || kuyruk!=NULL || sayac!=0); //S�re dolunca kuyruk bo� ise ve gi�elerde m��teri yok ise d�ng� sona erer.


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
		printf("\nKuyruk doldu m�steri alinamiyor.\n");
	}

}

int islemsuresi(){
	int islem;
	switch(rand()%4+1){ //Random i�lem se�iliyor.
			case 1: islem=rand()%8+3; printf("(%ddk)Eft yapilacak.\n",islem); break;
			case 2: islem=rand()%11+10;printf("(%ddk)Kredi cekme yapilacak.\n",islem); break;
			case 3: islem=rand()%11+2;printf("(%ddk)Fatura odeme yapilacak.\n",islem); break;
			case 4: islem=rand()%7+1;printf("(%ddk)Para cekme yapilacak.\n",islem); break;
		}
	return islem;
}
