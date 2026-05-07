#ifndef MODUL6_HASH_H
#define MODUL6_HASH_H

#include <string>
#include <iostream>
#include "modul1_kayit.h"

using namespace std;
#define HASH_BOYUTU 10
struct HashDugumu {
    Kayit* kayit;   
    HashDugumu* next;
};

struct HashTablosu {
    HashDugumu** table;
    int boyut;     
    int doluHucreSayisi; 
    int capismaSayisi; 
};


int hashFonksiyonu(int id);
void hashTablosuTemizle(HashTablosu* ht);

//hash tablo oluştur
HashTablosu* hashTablosuOlustur(Kayit* bas);
void hashTableDugumEkle(HashTablosu* ht, Kayit* k);

// id bazlı Ortalama Puan Bulma,hızlıca bulmakta yardımcı
Kayit* idyeGoreHashAra(HashTablosu* ht, int id);
void idyeGoreOrtalamaPuanBul(HashTablosu* ht, int id);

//kategorik bazlı Kayıt Sayısını verir ve list eder,hızlıca bulunur
int kategoriyeSayiBul(HashTablosu* ht, const string& kategori);
void kategoriyeGoreKayitlariListele(HashTablosu* ht, const string& kategori);
void tumKategorileriAnaliz(HashTablosu* ht);

// Her öncelik seviyesi (düşük/orta/yüksek) için kaç kayıt olduğunu bulmak
int onceligeGoreSayiBul(HashTablosu* ht, Oncelik onc);
void onceligeGoreYogunlukAnalizi(HashTablosu* ht);

// Collision sayısı ve Load factor
void hashPerformansBilgisi(HashTablosu* ht);
float loadFactor(HashTablosu* ht);

#endif
