#ifndef MODUL7_SIKISTIRMA_H
#define MODUL7_SIKISTIRMA_H

#include <string>
#include "modul1_kayit.h"

using namespace std;

struct KarakterFrekansi {
    char karakter;
    int frekans;
};

struct SikistirmaSonucu {
    string algoritmaAdi;
    double orijinalKB;
    double sikistirilmisKB;
    double tasarrufYuzdesi;
    double oran;
    double sureMs;
};

string kayitlardanHamVeriUret(Kayit* bas);
int frekansAnalizi(const string& veri, KarakterFrekansi frekanslar[], int maxBoyut);
void frekansTablosuYazdir(KarakterFrekansi frekanslar[], int adet);

SikistirmaSonucu huffmanSikistir(const string& veri);
SikistirmaSonucu lzwSikistir(const string& veri);
SikistirmaSonucu shannonFanoSikistir(const string& veri);

void sikistirmaSonucuYazdir(const SikistirmaSonucu& sonuc);
void sikistirmaKarsilastirmaYazdir(const SikistirmaSonucu& a, const SikistirmaSonucu& b, const SikistirmaSonucu& c);
void secilenYontemOranKarsilastirmaYazdir(const SikistirmaSonucu& sonuc);
int buyukKayitlariArsivle(Kayit* bas, LogKaydi** logBas, float esikKB, int yontemSecimi);

#endif
