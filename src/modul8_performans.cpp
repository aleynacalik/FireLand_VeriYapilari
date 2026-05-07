#include "../include/modul8_performans.h"

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;
// Modul 8: Erisim ve sure metriklerini toplayip performans karsilastirmasi sunar.
namespace {
// Dogrusal arama: sirasiz dizide hedef ID'yi basi sona tarar.
int linearSearchID(int dizi[], int adet, int hedef) {
    for (int i = 0; i < adet; i++) {
        if (dizi[i] == hedef) return static_cast<int>(i);
    }
    return -1;
}
// Ikili arama: sirali dizide ortadan bolerek hedefi arar.
int binarySearchID(int dizi[], int adet, int hedef) {
    int l = 0;
    int r = adet - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (dizi[m] == hedef) return m;
        if (dizi[m] < hedef) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
}  // namespace
// Performans durumunu temiz baslangic degerleriyle hazirlar
void performansDurumuBaslat(PerformansDurumu* durum) {
    durum->erisimSayisi = 0;
    for (int i = 0; i < 10; i++) durum->son10Erisim[i] = -1;
    durum->olcumBas = NULL;
}
// Olcum bagli listesini tamamen serbest birakir.
void performansDurumuTemizle(PerformansDurumu* durum) {
    PerformansOlcumu* iter = durum->olcumBas;
    while (iter != NULL) {
        PerformansOlcumu* sil = iter;
        iter = iter->next;
        delete sil;
    }
    durum->olcumBas = NULL;
}
// Son 10 erisimi halka benzeri kaydirma mantigiyla gunceller
void erisimKaydet(PerformansDurumu* durum, int kayitID) {
    if (durum->erisimSayisi < 10) {
        durum->son10Erisim[durum->erisimSayisi] = kayitID;
        durum->erisimSayisi++;
        return;
    }

    for (int i = 0; i < 9; i++) {
        durum->son10Erisim[i] = durum->son10Erisim[i + 1];
    }
    durum->son10Erisim[9] = kayitID;
}
// Son erisimleri en guncelden eskiye dogru ekrana yazar.
void son10ErisimYazdir(const PerformansDurumu* durum) {
    cout << "\n========== SON 10 ERISILEN KAYIT ==========" << endl;
    if (durum->erisimSayisi == 0) {
        cout << "[BILGI] Henuz erisim kaydi yok." << endl;
        cout << "===========================================" << endl;
        return;
    }

    for (int i = durum->erisimSayisi - 1, sira = 1; i >= 0; i--, sira++) {
        cout << sira << ". Kayit ID: " << durum->son10Erisim[i] << endl;
    }
    cout << "===========================================" << endl;
}
// Yeni bir sure olcumunu bagli listenin basina ekler.
void olcumEkle(PerformansDurumu* durum, const string& etiket, double sureMs) {
    PerformansOlcumu* yeni = new PerformansOlcumu();
    yeni->etiket = etiket;
    yeni->sureMs = sureMs;
    yeni->next = durum->olcumBas;
    durum->olcumBas = yeni;
}
// Kaydedilen tum olcumleri etiket/sure formatinda listeler.
void tumOlcumleriYazdir(const PerformansDurumu* durum) {
    cout << "\n========== ISLEM SURELERI (MS) ==========" << endl;
    if (durum->olcumBas == NULL) {
        cout << "[BILGI] Olcum yok." << endl;
        cout << "=========================================" << endl;
        return;
    }

    const PerformansOlcumu* iter = durum->olcumBas;
    while (iter != NULL) {
        cout << left << setw(28) << iter->etiket
             << fixed << setprecision(3) << iter->sureMs << " ms" << endl;
        iter = iter->next;
    }
    cout << "=========================================" << endl;
}
// Kaydedilen olcumleri etiket bazinda ortalama sureye cevirerek raporlar.
void ortalamaSureleriYazdir(const PerformansDurumu* durum) {
    cout << "\n========== MODUL BAZLI ORTALAMA ==========" << endl;
    if (durum->olcumBas == NULL) {
        cout << "[BILGI] Ortalama hesaplamak icin olcum yok." << endl;
        cout << "==========================================" << endl;
        return;
    }

    const int MAX_GRUP = 128;
    string etiketler[MAX_GRUP];
    double toplamlar[MAX_GRUP];
    int adetler[MAX_GRUP];
    int grupSayisi = 0;

    const PerformansOlcumu* iter = durum->olcumBas;
    while (iter != NULL) {
        bool bulundu = false;
        for (int i = 0; i < grupSayisi; i++) {
            if (etiketler[i] == iter->etiket) {
                toplamlar[i] += iter->sureMs;
                adetler[i]++;
                bulundu = true;
                break;
            }
        }
        if (!bulundu && grupSayisi < MAX_GRUP) {
            etiketler[grupSayisi] = iter->etiket;
            toplamlar[grupSayisi] = iter->sureMs;
            adetler[grupSayisi] = 1;
            grupSayisi++;
        }
        iter = iter->next;
    }

    for (int i = 0; i < grupSayisi; i++) {
        double ort = toplamlar[i] / adetler[i];
        cout << left << setw(28) << etiketler[i]
             << fixed << setprecision(3) << ort
             << " ms (n=" << adetler[i] << ")" << endl;
    }
    cout << "==========================================" << endl;
}
// Ortalama surelere gore en hizli olculen yapi/algoritmayi onerir.
void enHizliYapiOner(const PerformansDurumu* durum) {
    if (durum->olcumBas == NULL) {
        cout << "[BILGI] Oneri icin yeterli olcum yok." << endl;
        return;
    }

    const int MAX_GRUP = 128;
    string etiketler[MAX_GRUP];
    double toplamlar[MAX_GRUP];
    int adetler[MAX_GRUP];
    int grupSayisi = 0;

    const PerformansOlcumu* iter = durum->olcumBas;
    while (iter != NULL) {
        bool bulundu = false;
        for (int i = 0; i < grupSayisi; i++) {
            if (etiketler[i] == iter->etiket) {
                toplamlar[i] += iter->sureMs;
                adetler[i]++;
                bulundu = true;
                break;
            }
        }
        if (!bulundu && grupSayisi < MAX_GRUP) {
            etiketler[grupSayisi] = iter->etiket;
            toplamlar[grupSayisi] = iter->sureMs;
            adetler[grupSayisi] = 1;
            grupSayisi++;
        }
        iter = iter->next;
    }

    string enIyi;
    double minOrt = 1e18;
    for (int i = 0; i < grupSayisi; i++) {
        double ort = toplamlar[i] / adetler[i];
        if (ort < minOrt) {
            minOrt = ort;
            enIyi = etiketler[i];
        }
    }

    cout << "\n========== OPTIMIZASYON ONERISI ==========" << endl;
    cout << "En hizli olculen yapi/algoritma: " << enIyi << endl;
    cout << "Ortalama sure: " << fixed << setprecision(3) << minOrt << " ms" << endl;
    cout << "==========================================" << endl;
}
// Ayni hedef ID icin linear ve binary search surelerini olcer.
void linearBinaryKarsilastir(Kayit* bas, int hedefID, PerformansDurumu* durum) {
    if (bas == NULL) {
        cout << "[BILGI] Kayit listesi bos." << endl;
        return;
    }

    int adet = 0;
    for (Kayit* iter = bas; iter != NULL; iter = iter->next) adet++;

    int* idler = new int[adet];
    int k = 0;
    for (Kayit* iter = bas; iter != NULL; iter = iter->next) idler[k++] = iter->id;

    int* sirali = new int[adet];
    for (int i = 0; i < adet; i++) sirali[i] = idler[i];
    for (int i = 0; i < adet - 1; i++) {
        for (int j = 0; j < adet - i - 1; j++) {
            if (sirali[j] > sirali[j + 1]) {
                int t = sirali[j];
                sirali[j] = sirali[j + 1];
                sirali[j + 1] = t;
            }
        }
    }

    clock_t t0 = clock();
    int li = linearSearchID(idler, adet, hedefID);
    clock_t t1 = clock();
    int bi = binarySearchID(sirali, adet, hedefID);
    clock_t t2 = clock();

    double linearMs = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
    double binaryMs = 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;

    olcumEkle(durum, "Linear Search", linearMs);
    olcumEkle(durum, "Binary Search", binaryMs);

    cout << "\n========== ARAMA KARSILASTIRMASI ==========" << endl;
    cout << "Hedef ID: " << hedefID << endl;
    cout << "Linear Search: " << fixed << setprecision(6) << linearMs
         << " ms | " << (li >= 0 ? "Bulundu" : "Bulunamadi") << endl;
    cout << "Binary Search: " << fixed << setprecision(6) << binaryMs
         << " ms | " << (bi >= 0 ? "Bulundu" : "Bulunamadi") << endl;
    if (linearMs < binaryMs) cout << "Sonuc: Bu olcumde Linear Search daha hizli." << endl;
    else if (binaryMs < linearMs) cout << "Sonuc: Bu olcumde Binary Search daha hizli." << endl;
    else cout << "Sonuc: Iki yontem esit surede." << endl;
    cout << "===========================================" << endl;

    delete[] idler;
    delete[] sirali;
}
