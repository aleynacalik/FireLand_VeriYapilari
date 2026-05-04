#ifndef MODUL8_PERFORMANS_H
#define MODUL8_PERFORMANS_H

#include <string>
#include "modul1_kayit.h"

using namespace std;

struct PerformansOlcumu {
    string etiket;
    double sureMs;
    PerformansOlcumu* next;
};

struct PerformansDurumu {
    int son10Erisim[10];
    int erisimSayisi;
    PerformansOlcumu* olcumBas;
};

void performansDurumuBaslat(PerformansDurumu* durum);
void performansDurumuTemizle(PerformansDurumu* durum);

void erisimKaydet(PerformansDurumu* durum, int kayitID);
void son10ErisimYazdir(const PerformansDurumu* durum);

void olcumEkle(PerformansDurumu* durum, const string& etiket, double sureMs);
void tumOlcumleriYazdir(const PerformansDurumu* durum);
void ortalamaSureleriYazdir(const PerformansDurumu* durum);
void enHizliYapiOner(const PerformansDurumu* durum);

void linearBinaryKarsilastir(Kayit* bas, int hedefID, PerformansDurumu* durum);

#endif
