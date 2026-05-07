#include "../include/modul4_queue.h"

#include <ctime>
#include <iostream>

using namespace std;

int sonTalepID = 0;

int oncelikSkoru(Oncelik o) {
    // Siralama karsilastirmasi icin enum degerlerini tek bir puana cevirir.
    if (o == YUKSEK) return 3;
    if (o == ORTA) return 2;
    return 1;
}

time_t stringiTimeTyeCevir(string tarihSaat) {
    tm zaman = {};
    // Beklenen format: "GG/AA/YYYY SS:DD:SS"
    if (tarihSaat.length() >= 19) {
        zaman.tm_mday = (tarihSaat[0] - '0') * 10 + (tarihSaat[1] - '0');
        zaman.tm_mon = ((tarihSaat[3] - '0') * 10 + (tarihSaat[4] - '0')) - 1;
        zaman.tm_year = ((tarihSaat[6] - '0') * 1000 + (tarihSaat[7] - '0') * 100 +
                         (tarihSaat[8] - '0') * 10 + (tarihSaat[9] - '0')) - 1900;
        zaman.tm_hour = (tarihSaat[11] - '0') * 10 + (tarihSaat[12] - '0');
        zaman.tm_min = (tarihSaat[14] - '0') * 10 + (tarihSaat[15] - '0');
        zaman.tm_sec = (tarihSaat[17] - '0') * 10 + (tarihSaat[18] - '0');
    }
    return mktime(&zaman);
}

string talepZamaniUret() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", localtime(&now));
    return string(buf);
}

void yeniTalepEkle(Talep** bas, string kategori, float boyut, Oncelik oncelik, string baslik, float puan) {
    Talep* yeni = new Talep();
    sonTalepID++;
    yeni->talepID = sonTalepID;
    yeni->kategori = kategori;
    yeni->boyut = boyut;
    yeni->oncelik = oncelik;
    yeni->talepZamani = talepZamaniUret();
    yeni->baslik = baslik;
    yeni->puan = puan;
    yeni->next = NULL;

    // Oncelik daha yuksekse talep listenin basina eklenir.
    if (*bas == NULL || oncelikSkoru((*bas)->oncelik) < oncelikSkoru(oncelik)) {
        yeni->next = *bas;
        *bas = yeni;
    } else {
        // Ayni veya daha dusuk oncelikler arasinda uygun noktaya yerlestirilir.
        Talep* iter = *bas;
        while (iter->next != NULL &&
               oncelikSkoru(iter->next->oncelik) >= oncelikSkoru(oncelik)) {
            iter = iter->next;
        }
        yeni->next = iter->next;
        iter->next = yeni;
    }

    cout << "[QUEUE] Talep eklendi. Talep ID: " << yeni->talepID << endl;
}

void oncelikliTalepOlustur(Talep** bas, string kategori, float boyut, string baslik, float puan) {
    // Kisa yol: kullanicidan oncelik almadan dogrudan YUKSEK oncelikli talep olusturur.
    yeniTalepEkle(bas, kategori, boyut, YUKSEK, baslik, puan);
}

void kuyruguListele(Talep* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Kuyruk bos." << endl;
        return;
    }

    cout << "\n========== TALEP KUYRUGU ==========" << endl;
    Talep* iter = bas;
    int sira = 1;
    while (iter != NULL) {
        cout << sira << ". TalepID: " << iter->talepID
             << " | Baslik: " << iter->baslik
             << " | Kategori: " << iter->kategori
             << " | Boyut: " << iter->boyut << " KB"
             << " | Oncelik: " << oncelikToString(iter->oncelik)
             << " | Zaman: " << iter->talepZamani << endl;
        iter = iter->next;
        sira++;
    }
    cout << "===================================" << endl;
}

void ilkTalebiIslemeAl(Talep** bas, Kayit** kayitBas, LogKaydi** logBas, StackIslem** stackUst) {
    if (*bas == NULL) {
        cout << "[HATA] Kuyruk bos, islenecek talep yok." << endl;
        return;
    }

    // FIFO/priority akisi: kuyrugun basindaki talep secilir.
    Talep* islenecek = *bas;
    *bas = (*bas)->next;

    // Talep, Modul 1'e kalici kayit olarak aktarilir.
    *kayitBas = kayitEkle(*kayitBas, logBas, islenecek->baslik, islenecek->kategori,
                          islenecek->boyut, islenecek->oncelik, islenecek->puan);

    int yeniKayitID = 0;
    if (*kayitBas != NULL) {
        Kayit* iter = *kayitBas;
        while (iter->next != NULL) {
            iter = iter->next;
        }
        yeniKayitID = iter->id;
    }

    // Islem Modul 2 gunlugune ve Modul 3 stack'ine DEQUEUE olarak kaydedilir.
    *logBas = gunlukKaydiEkle(*logBas, DEQUEUE, yeniKayitID, "Talep kuyrugundan", islenecek->baslik);
    stackeIslemPush(stackUst, DEQUEUE, yeniKayitID, "Talep kuyrugundan", islenecek->baslik, logZamani());

    cout << "[BASARILI] Talep isleme alindi ve Modul 1'e kayit eklendi." << endl;
    cout << "          Talep ID: " << islenecek->talepID << " -> Kayit ID: " << yeniKayitID << endl;

    delete islenecek;
}

float ortalamaBeklemeSuresiDakika(Talep* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Kuyruk bos." << endl;
        return 0.0f;
    }

    time_t now = time(0);
    double toplamDakika = 0.0;
    int sayac = 0;

    // Her talep icin (simdi - talepZamani) farki alinip ortalamasi hesaplanir.
    Talep* iter = bas;
    while (iter != NULL) {
        time_t talepZamani = stringiTimeTyeCevir(iter->talepZamani);
        if (talepZamani > 0) {
            double farkSaniye = difftime(now, talepZamani);
            toplamDakika += (farkSaniye / 60.0);
            sayac++;
        }
        iter = iter->next;
    }

    float ortalama = (sayac > 0) ? static_cast<float>(toplamDakika / sayac) : 0.0f;
    cout << "[ANALIZ] Ortalama bekleme suresi: " << ortalama << " dakika" << endl;
    return ortalama;
}

void kuyrukTemizle(Talep* bas) {
    while (bas != NULL) {
        Talep* silinecek = bas;
        bas = bas->next;
        delete silinecek;
    }
}
