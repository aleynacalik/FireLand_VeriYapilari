#ifndef MODUL5_TREE_H
#define MODUL5_TREE_H

#include <string>
#include "modul1_kayit.h"

using namespace std;

struct AgacDugumu {
    Kayit* kayit;
    AgacDugumu* sol;
    AgacDugumu* sag;
};
 

AgacDugumu* yeniDugumOlustur(Kayit* k);
void agacTemizle(AgacDugumu* kok);
void girisBoslukluYazdir(int seviye);

 
//kayitlari yil/ay bazli filtrele
AgacDugumu* tariheGoreAgacOlustur(Kayit* bas);
void tariheGoreAgacListele(AgacDugumu* kok);
void yilaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil, int& sayac);
void ayaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil, const string& ay, int& sayac);
void tariheGoreFiltrele(AgacDugumu* kok);
 
//yuksek oncelikli kayitlar ustte
AgacDugumu* onceligeGoreAgacOlustur(Kayit* bas);
void onceligeGoreAgacListele(AgacDugumu* kok, int seviye);
void onceligeGoreAgacYazdir(AgacDugumu* kok);
 
//Puan BST'si kurarak filtreleme
AgacDugumu* puanaGoreEkle(AgacDugumu* kok, Kayit* k);
AgacDugumu* puanAgaciOlustur(Kayit* bas);
void puanAraligiGezinti(AgacDugumu* kok, float minPuan, float maxPuan, int& bulunan);
void puanAraligiFiltrele(Kayit* bas, float minPuan, float maxPuan);
 
//agac yuksekligi ile performans bilgisi
int agacYuksekligi(AgacDugumu* kok);
void agacPerformansBilgisi(AgacDugumu* kok);
 
//manuel veri girişli tarih bazli trend analizi
void tarihBazliTrendAnalizi(Kayit* bas, int yil);
 
#endif
