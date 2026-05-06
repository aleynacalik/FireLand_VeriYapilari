/*
 * MODÜL 1 - ANA KAYIT YÖNETİMİ
 * Veri Yapısı: Tek Yönlü Bağlı Liste
 * 
 * Amaç: Sistem verilerinin merkezi deposu. Tüm temel bilgiler burada saklanır.
 */

#ifndef MODUL1_KAYIT_H
#define MODUL1_KAYIT_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Öncelik seviyeleri
enum Oncelik { DUSUK = 0, ORTA = 1, YUKSEK = 2 };

// Kayıt durumları
enum Durum { AKTIF = 0, ISLEMDE = 1, ARSIV = 2 };

struct LogKaydi;


struct Kayit {
    int id;
    string baslik;
    string kategori;
    float boyut;
    string tarih;
    Oncelik oncelik;
    Durum durum;
    float ortalamaPuan;
    string kritikNot;
    Kayit* next;
};


string simdikiZaman();
string oncelikToString(Oncelik o);
string durumToString(Durum d);
void kayitYazdir(Kayit* k);


Kayit* kayitEkle(Kayit* bas, LogKaydi** logBas, string baslik, string kategori, float boyut, Oncelik oncelik, float puan);
Kayit* kayitSil(Kayit* bas, LogKaydi** logBas, int id);
Kayit* kayitGuncelle(Kayit* bas, LogKaydi** logBas, string eskiBaslik, string yeniBaslik, string yeniKategori, float yeniBoyut);
void zamanliListele(Kayit* bas);
Kayit* kayitAra(Kayit* bas, int id);
int toplamKayitSayisi(Kayit* bas);
void boyutaSirala(Kayit* bas);
void enEski10Kayit(Kayit* bas);
Kayit* kritikNotEkle(Kayit* bas, LogKaydi** logBas, int id, string not_);
void kritikKayitlariListele(Kayit* bas);

// Arşiv işlemleri
Kayit* kayitArsivle(Kayit* bas, LogKaydi** logBas, int id);
Kayit* arsivdenCikar(Kayit* bas, LogKaydi** logBas, int id);
void arsivdekiKayitlariListele(Kayit* bas);

// İşleme alma / tamamlama (revize akışı)
Kayit* kaydiIslemeAl(Kayit* bas, LogKaydi** logBas, int id);
Kayit* islemiTamamla(Kayit* bas, LogKaydi** logBas, int id);

// Ekstra
void tumKayitlariListele(Kayit* bas);
Kayit* demoVerilerEkle(Kayit* bas, LogKaydi** logBas);
void listeTemizle(Kayit* bas);

#endif
