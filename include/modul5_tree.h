#ifndef MODUL5_TREE_H
#define MODUL5_TREE_H

#include <string>
#include "modul1_kayit.h"

using namespace std;

// ==================== AGAC DUGUMU ====================
 
struct AgacDugumu {
    Kayit* kayit;       // Modul 1'den gelen kayit pointer'i
    AgacDugumu* sol;
    AgacDugumu* sag;
};
 
// ==================== FONKSIYON BILDIRIMLERI ====================
 
// Yardimci
AgacDugumu* yeniDugumOlustur(Kayit* k);
void agacTemizle(AgacDugumu* kok);
void girisBoslukluYazdir(int seviye);
 
// 5 Islevsellik
 
// 1. Tarihe gore agac → kayitlari yil/ay bazli filtrele
AgacDugumu* tariheGoreAgacOlustur(Kayit* bas);
void tariheGoreAgacListele(AgacDugumu* kok);
void yilaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil);
void ayaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil, const string& ay);
void tariheGoreFiltrele(AgacDugumu* kok);
 
// 2. Oncelik gore agac → yuksek oncelikli kayitlar ustte
AgacDugumu* onceligeGoreAgacOlustur(Kayit* bas);
void onceligeGoreAgacListele(AgacDugumu* kok, int seviye);
void onceligeGoreAgacYazdir(AgacDugumu* kok);
 
// 3. Puan araligi filtreleme - Puan BST'si kurarak filtreleme
AgacDugumu* puanaGoreEkle(AgacDugumu* kok, Kayit* k);
AgacDugumu* puanAgaciOlustur(Kayit* bas);
void puanAraligiGezinti(AgacDugumu* kok, float minPuan, float maxPuan, int& bulunan);
void puanAraligiFiltrele(Kayit* bas, float minPuan, float maxPuan);
 
// 4. Tree yuksekligi → derinlik ile performans olcumu
int agacYuksekligi(AgacDugumu* kok);
void agacPerformansBilgisi(AgacDugumu* kok);
 
// 5. 2020 tarihi icin oncesi/sonrasi analiz (EduFlow'a uygun: COVID donemini baz alir)
void tarihBazliTrendAnalizi(Kayit* bas, int yil);
 
#endif
