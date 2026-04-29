/*
 * MODÜL 6 - HASH ANALIZ MOTORU
 * Veri Yapısı: Hash Tablosu (Chaining)
 * 
 * Amaç: ID, kategori ve öncelik bazlı hızlı analiz ve sorgulama.
 * Hash Boyutu: 10 (Load Factor ~50%)
 */

#ifndef MODUL6_HASH_H
#define MODUL6_HASH_H

#include <string>
#include <iostream>
#include "modul1_kayit.h"

using namespace std;

// ==================== HASH TABLOSU YAPILARI ====================

#define HASH_BOYUTU 10

// Zincir düğümü (Chaining için)
struct HashDugumu {
    Kayit* kayit;           // Modül 1'den pointer
    HashDugumu* next;       // Çarpışmada sonraki
};

// Hash Tablosu Ana Yapısı
struct HashTablosu {
    HashDugumu** table;     // 10 bucket dizi
    int boyut;              // 10
    int doluHucreSayisi;    // Dolu hücre sayısı (performans metriği)
    int capismaSayisi;      // Çarpışma sayısı
};

// ==================== FONKSIYON BİLDİRİMLERİ ====================

// Yardımcı Fonksiyonlar
int hashFonksiyonu(int id);
void hashTablosuTemizle(HashTablosu* ht);

// 1. HASH TABLOSU OLUŞTURMA
HashTablosu* hashTablosuOlustur(Kayit* bas);
void hashTableDugumEkle(HashTablosu* ht, Kayit* k);

// 2. ID BAZLI ARAMA - Ortalama Puan Bulma
// Bir kayıt ID'si verildiğinde o kayda verilen puanları hızlıca bulmak
Kayit* idyeGoreHashAra(HashTablosu* ht, int id);
void idyeGoreOrtalamaPuanBul(HashTablosu* ht, int id);

// 3. KATEGORİ BAZLI GRUPLAMA - Kayıt Sayısı
// Belirli bir kategoriye ait kaç kayıt olduğunu hızlıca bulmak
int kategoriyeSayiBul(HashTablosu* ht, const string& kategori);
void kategoriyeGoreKayitlariListele(HashTablosu* ht, const string& kategori);
void tumKategorileriAnaliz(HashTablosu* ht);

// 4. ÖNCELİK BAZLI YOĞUNLUK ANALİZİ
// Her öncelik seviyesi (düşük/orta/yüksek) için kaç kayıt olduğunu analiz etmek
int onceligeGoreSayiBul(HashTablosu* ht, Oncelik onc);
void onceligeGoreYogunlukAnalizi(HashTablosu* ht);

// 5. HASH PERFORMANS METRİKLERİ
// Collision sayısı ve Load factor
void hashPerformansBilgisi(HashTablosu* ht);
float loadFactor(HashTablosu* ht);

#endif
