#include "../include/modul7_sikistirma.h"

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;
// Modul 7: Kayitlardan uretilen ham veri uzerinde sikistirma analizleri yapar.
namespace {
struct HuffmanDugum {
    char ch;
    int frekans;
    HuffmanDugum* sol;
    HuffmanDugum* sag;
};
// Verilen karakter ve frekans ile yeni bir Huffman dugumu uretir.
HuffmanDugum* huffmanDugumOlustur(char ch, int frekans) {
    HuffmanDugum* dugum = new HuffmanDugum();
    dugum->ch = ch;
    dugum->frekans = frekans;
    dugum->sol = NULL;
    dugum->sag = NULL;
    return dugum;
}
// Huffman agacini post-order dolasip tum dugumleri serbest birakir.
void huffmanTemizle(HuffmanDugum* kok) {
    if (kok == NULL) return;
    huffmanTemizle(kok->sol);
    huffmanTemizle(kok->sag);
    delete kok;
}
// Huffman agacindaki yapraklara ulasip bit kodlarini tabloya yazar.
void huffmanKodOlustur(HuffmanDugum* kok, const string& kod, string kodTablosu[256]) {
    if (kok == NULL) return;
    if (kok->sol == NULL && kok->sag == NULL) {
        unsigned char idx = static_cast<unsigned char>(kok->ch);
        kodTablosu[idx] = kod.empty() ? "0" : kod;
        return;
    }
    huffmanKodOlustur(kok->sol, kod + "0", kodTablosu);
    huffmanKodOlustur(kok->sag, kod + "1", kodTablosu);
}
// Shannon-Fano adiminda frekanslari buyukten kucuge siralar.
void frekansSiralaAzalan(KarakterFrekansi dizi[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dizi[j].frekans < dizi[j + 1].frekans) {
                KarakterFrekansi t = dizi[j];
                dizi[j] = dizi[j + 1];
                dizi[j + 1] = t;
            }
        }
    }
}
// Geçici havuzdan en dusuk frekansli dugumu cekip birlestirmede kullanir.
HuffmanDugum* enKucukDugumuCikar(HuffmanDugum* havuz[], int* adet) {
    if (*adet <= 0) return NULL;
    int minIndex = 0;
    for (int i = 1; i < *adet; i++) {
        if (havuz[i]->frekans < havuz[minIndex]->frekans) minIndex = i;
    }
    HuffmanDugum* secilen = havuz[minIndex];
    for (int i = minIndex; i < *adet - 1; i++) havuz[i] = havuz[i + 1];
    (*adet)--;
    return secilen;
}
// Shannon-Fano icin veri grubunu dengeye yakin iki alt gruba boler.
void shannonFanoRekursif(KarakterFrekansi veriler[], int sol, int sag, string kodTablosu[256]) {
    if (sol >= sag) return;

    int toplam = 0;
    for (int i = sol; i <= sag; i++) toplam += veriler[i].frekans;

    int hedef = toplam / 2;
    int kumeToplam = 0;
    int bolme = sol;

    for (int i = sol; i <= sag; i++) {
        if (kumeToplam + veriler[i].frekans <= hedef) {
            kumeToplam += veriler[i].frekans;
            bolme = i;
        } else {
            break;
        }
    }

    if (bolme == sag) bolme = sag - 1;

    for (int i = sol; i <= bolme; i++) {
        unsigned char idx = static_cast<unsigned char>(veriler[i].karakter);
        kodTablosu[idx] += "0";
    }
    for (int i = bolme + 1; i <= sag; i++) {
        unsigned char idx = static_cast<unsigned char>(veriler[i].karakter);
        kodTablosu[idx] += "1";
    }

    shannonFanoRekursif(veriler, sol, bolme, kodTablosu);
    shannonFanoRekursif(veriler, bolme + 1, sag, kodTablosu);
}
// Ortak sonuc formatini tek yerde olusturarak tekrar eden hesaplari toplar.
SikistirmaSonucu sonucOlustur(const string& ad, int orijinalBit, int sikismisBit, double sureMs) {
    SikistirmaSonucu sonuc;
    sonuc.algoritmaAdi = ad;
    sonuc.orijinalKB = static_cast<double>(orijinalBit) / (8.0 * 1024.0);
    sonuc.sikistirilmisKB = static_cast<double>(sikismisBit) / (8.0 * 1024.0);
    sonuc.tasarrufYuzdesi = (orijinalBit > 0) ? (100.0 * (orijinalBit - sikismisBit) / orijinalBit) : 0.0;
    sonuc.oran = (orijinalBit > 0) ? (static_cast<double>(sikismisBit) / orijinalBit) : 1.0;
    sonuc.sureMs = sureMs;
    return sonuc;
}
}  // namespace

string kayitlardanHamVeriUret(Kayit* bas) {
    string veri;
    Kayit* iter = bas;
    while (iter != NULL) {
        veri += iter->baslik + "|" + iter->kategori + "|" + iter->kritikNot + ";";
        iter = iter->next;
    }
    return veri;
}
// Metindeki karakter frekanslarini hesaplayip buyukten kucuge siralar.
int frekansAnalizi(const string& veri, KarakterFrekansi frekanslar[], int maxBoyut) {
    int sayac[256];
    for (int i = 0; i < 256; i++) sayac[i] = 0;

    for (size_t i = 0; i < veri.size(); i++) {
        unsigned char idx = static_cast<unsigned char>(veri[i]);
        sayac[idx]++;
    }

    int adet = 0;
    for (int i = 0; i < 256 && adet < maxBoyut; i++) {
        if (sayac[i] > 0) {
            frekanslar[adet].karakter = static_cast<char>(i);
            frekanslar[adet].frekans = sayac[i];
            adet++;
        }
    }
    frekansSiralaAzalan(frekanslar, adet);
    return adet;
}

void frekansTablosuYazdir(KarakterFrekansi frekanslar[], int adet) {
    cout << "\n========== FREKANS ANALIZI ==========" << endl;
    cout << "Karakter | Frekans" << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < adet; i++) {
        string gosterim;
        if (frekanslar[i].karakter == ' ') gosterim = "[bosluk]";
        else if (frekanslar[i].karakter == '\n') gosterim = "[satir-sonu]";
        else gosterim = string(1, frekanslar[i].karakter);
        cout << setw(8) << left << gosterim << " | " << frekanslar[i].frekans << endl;
    }
    cout << "=====================================" << endl;
}
// Huffman agaci olusturup tahmini sikistirilmis bit boyutunu hesaplar.
SikistirmaSonucu huffmanSikistir(const string& veri) {
    clock_t t0 = clock();
    if (veri.empty()) {
        return sonucOlustur("Huffman", 0, 0, 0.0);
    }

    KarakterFrekansi frekanslar[256];
    int frekansAdet = frekansAnalizi(veri, frekanslar, 256);
    HuffmanDugum* havuz[512];
    int havuzAdet = 0;
    for (int i = 0; i < frekansAdet; i++) {
        havuz[havuzAdet++] = huffmanDugumOlustur(frekanslar[i].karakter, frekanslar[i].frekans);
    }

    while (havuzAdet > 1) {
        HuffmanDugum* a = enKucukDugumuCikar(havuz, &havuzAdet);
        HuffmanDugum* b = enKucukDugumuCikar(havuz, &havuzAdet);
        HuffmanDugum* parent = huffmanDugumOlustur('\0', a->frekans + b->frekans);
        parent->sol = a;
        parent->sag = b;
        havuz[havuzAdet++] = parent;
    }

    HuffmanDugum* kok = havuz[0];
    string kodTablosu[256];
    huffmanKodOlustur(kok, "", kodTablosu);

    int sikismisBit = 0;
    for (size_t i = 0; i < veri.size(); i++) {
        unsigned char idx = static_cast<unsigned char>(veri[i]);
        sikismisBit += static_cast<int>(kodTablosu[idx].size());
    }

    int orijinalBit = static_cast<int>(veri.size()) * 8;
    huffmanTemizle(kok);
    clock_t t1 = clock();
    double ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
    return sonucOlustur("Huffman", orijinalBit, sikismisBit, ms);
}
// LZW sozluk temelli kodlama ile sikistirma oranini ve sureyi olcer.
SikistirmaSonucu lzwSikistir(const string& veri) {
    clock_t t0 = clock();
    if (veri.empty()) {
        return sonucOlustur("LZW", 0, 0, 0.0);
    }

    const int SOZLUK_LIMIT = 4096;
    string anahtar[SOZLUK_LIMIT];
    int deger[SOZLUK_LIMIT];
    int sozlukAdet = 0;
    for (int i = 0; i < 256; i++) {
        anahtar[sozlukAdet] = string(1, static_cast<char>(i));
        deger[sozlukAdet] = i;
        sozlukAdet++;
    }

    int sonrakiKod = 256;
    string w;
    int ciktiAdet = 0;
    int ciktiKodlari[16384];
    for (size_t i = 0; i < veri.size(); i++) {
        string wc = w + veri[i];
        int wcIndex = -1;
        for (int j = 0; j < sozlukAdet; j++) {
            if (anahtar[j] == wc) {
                wcIndex = j;
                break;
            }
        }
        if (wcIndex != -1) {
            w = wc;
        } else {
            if (!w.empty()) {
                for (int j = 0; j < sozlukAdet; j++) {
                    if (anahtar[j] == w) {
                        ciktiKodlari[ciktiAdet++] = deger[j];
                        break;
                    }
                }
            }
            if (sozlukAdet < SOZLUK_LIMIT) {
                anahtar[sozlukAdet] = wc;
                deger[sozlukAdet] = sonrakiKod++;
                sozlukAdet++;
            }
            w = string(1, veri[i]);
        }
    }
    if (!w.empty()) {
        for (int j = 0; j < sozlukAdet; j++) {
            if (anahtar[j] == w) {
                ciktiKodlari[ciktiAdet++] = deger[j];
                break;
            }
        }
    }

    int orijinalBit = static_cast<int>(veri.size()) * 8;
    int sikismisBit = ciktiAdet * 12;
    clock_t t1 = clock();
    double ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
    return sonucOlustur("LZW", orijinalBit, sikismisBit, ms);
}
// Shannon-Fano bol-parcala yaklasimi ile kodlar ve cikti boyutunu hesaplar.
SikistirmaSonucu shannonFanoSikistir(const string& veri) {
    clock_t t0 = clock();
    if (veri.empty()) {
        return sonucOlustur("Shannon-Fano", 0, 0, 0.0);
    }

    KarakterFrekansi frekanslar[256];
    int adet = frekansAnalizi(veri, frekanslar, 256);
    string kodTablosu[256];

    if (adet == 1) {
        unsigned char idx = static_cast<unsigned char>(frekanslar[0].karakter);
        kodTablosu[idx] = "0";
    } else {
        shannonFanoRekursif(frekanslar, 0, adet - 1, kodTablosu);
    }

    int sikismisBit = 0;
    for (size_t i = 0; i < veri.size(); i++) {
        unsigned char idx = static_cast<unsigned char>(veri[i]);
        sikismisBit += static_cast<int>(kodTablosu[idx].size());
    }

    int orijinalBit = static_cast<int>(veri.size()) * 8;
    clock_t t1 = clock();
    double ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
    return sonucOlustur("Shannon-Fano", orijinalBit, sikismisBit, ms);
}
// Tek algoritma sonucunu okunabilir bir blok halinde ekrana basar.
void sikistirmaSonucuYazdir(const SikistirmaSonucu& sonuc) {
    cout << "\n========== " << sonuc.algoritmaAdi << " SONUCU ==========" << endl;
    cout << "Orijinal Boyut      : " << fixed << setprecision(4) << sonuc.orijinalKB << " KB" << endl;
    cout << "Sikistirilmis Boyut : " << fixed << setprecision(4) << sonuc.sikistirilmisKB << " KB" << endl;
    cout << "Sikistirma Orani    : " << fixed << setprecision(4) << sonuc.oran << endl;
    cout << "Tasarruf            : %" << fixed << setprecision(2) << sonuc.tasarrufYuzdesi << endl;
    cout << "Sure                : " << fixed << setprecision(3) << sonuc.sureMs << " ms" << endl;
    cout << "======================================" << endl;
}
// Uc sikistirma algoritmasini ayni tabloda karsilastirmali sunar.
void sikistirmaKarsilastirmaYazdir(const SikistirmaSonucu& a, const SikistirmaSonucu& b, const SikistirmaSonucu& c) {
    cout << "\n========== SIKISTIRMA KARSILASTIRMASI ==========" << endl;
    cout << left << setw(16) << "Algoritma"
         << setw(14) << "OrijinalKB"
         << setw(16) << "SikismisKB"
         << setw(12) << "Tasarruf%"
         << "Sure(ms)" << endl;
    cout << "------------------------------------------------" << endl;

    const SikistirmaSonucu sonuclar[3] = {a, b, c};
    for (int i = 0; i < 3; i++) {
        cout << left << setw(16) << sonuclar[i].algoritmaAdi
             << setw(14) << fixed << setprecision(4) << sonuclar[i].orijinalKB
             << setw(16) << fixed << setprecision(4) << sonuclar[i].sikistirilmisKB
             << setw(12) << fixed << setprecision(2) << sonuclar[i].tasarrufYuzdesi
             << fixed << setprecision(3) << sonuclar[i].sureMs << endl;
    }
    cout << "================================================" << endl;
}

void secilenYontemOranKarsilastirmaYazdir(const SikistirmaSonucu& sonuc) {
    cout << "\n--- SECILEN YONTEM ORAN KARSILASTIRMASI ---" << endl;
    cout << "Algoritma          : " << sonuc.algoritmaAdi << endl;
    cout << "Orijinal Boyut     : " << fixed << setprecision(4) << sonuc.orijinalKB << " KB" << endl;
    cout << "Sikistirilmis Boyut: " << fixed << setprecision(4) << sonuc.sikistirilmisKB << " KB" << endl;
    cout << "Oran (Sikismis/Orijinal): " << fixed << setprecision(4) << sonuc.oran << endl;
    cout << "Tasarruf           : %" << fixed << setprecision(2) << sonuc.tasarrufYuzdesi << endl;
    cout << "-------------------------------------------" << endl;
}

int buyukKayitlariArsivle(Kayit* bas, LogKaydi** logBas, float esikKB, int yontemSecimi) {
    if (bas == NULL) {
        cout << "[BILGI] Kayit listesi bos. Arsivlenecek kayit yok." << endl;
        return 0;
    }

    int adaySayisi = 0;
    int arsivlenenSayisi = 0;
    Kayit* iter = bas;
    while (iter != NULL) {
        if (iter->boyut >= esikKB && iter->durum != ARSIV) {
            adaySayisi++;
            string ham = iter->baslik + "|" + iter->kategori + "|" + iter->kritikNot + ";";
            SikistirmaSonucu sonuc;
            if (yontemSecimi == 1) sonuc = huffmanSikistir(ham);
            else if (yontemSecimi == 2) sonuc = lzwSikistir(ham);
            else sonuc = shannonFanoSikistir(ham);

            if (sonuc.sikistirilmisKB < sonuc.orijinalKB) {
                kayitArsivle(bas, logBas, iter->id);
                arsivlenenSayisi++;
            }
        }
        iter = iter->next;
    }

    cout << "\n========== MODUL 7 ARSIVLEME OZETI ==========" << endl;
    cout << "Esik Boyut (KB): " << fixed << setprecision(2) << esikKB << endl;
    cout << "Aday Kayit Sayisi: " << adaySayisi << endl;
    cout << "Arsivlenen Kayit Sayisi: " << arsivlenenSayisi << endl;
    cout << "=============================================" << endl;
    return arsivlenenSayisi;
}
