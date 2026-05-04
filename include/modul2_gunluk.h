/*
 * MODÜL 2 - OPERASYON GÜNLÜĞÜ
 * Veri Yapısı: Çift Yönlü Dairesel Bağlı Liste
 * 
 * Amaç: Sistem işlemlerinin detaylı kaydı. Undo/redo işlemleri için referans sağlar.
 */

#ifndef MODUL2_GUNLUK_H
#define MODUL2_GUNLUK_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;


enum IslemTuru { EKLE = 0, SIL = 1, GUNCELLE = 2, DEQUEUE = 3 };


struct LogKaydi {
    int logID;
    IslemTuru islemTuru;
    int kayitID;
    string tarihSaat;
    string oncekiDeger;
    string yeniDeger;
    LogKaydi* prev;
    LogKaydi* next;
};


string islemToString(IslemTuru t);
string logZamani();
void logYazdir(LogKaydi* log);


LogKaydi* gunlukKaydiEkle(LogKaydi* bas, IslemTuru tur, int kayitID, string onceki, string yeni);
void kayitIdIslemleriniListele(LogKaydi* bas, int kayitID);
void tarihAraligiIslemler(LogKaydi* bas, string baslangic, string bitis);
void gunlukRaporuOlustur(LogKaydi* bas);
void islemTuruneGoreListele(LogKaydi* bas, IslemTuru tur);

// Ekstra
void tumLoglariListele(LogKaydi* bas);
int toplamLogSayisi(LogKaydi* bas);
void listeTemizleLog(LogKaydi* bas);

#endif
