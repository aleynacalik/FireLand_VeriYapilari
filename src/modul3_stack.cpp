#include "../include/modul3_stack.h"

#include <iostream>
#include <sstream>

using namespace std;

void stackeIslemPush(StackIslem** ust, IslemTuru tur, int kayitID, string oncekiDeger, string yeniDeger, string zaman) {
    StackIslem* yeni = new StackIslem();
    yeni->tur = tur;
    yeni->kayitID = kayitID;
    yeni->oncekiDeger = oncekiDeger;
    yeni->yeniDeger = yeniDeger;
    yeni->zaman = zaman;
    yeni->next = *ust;
    *ust = yeni;
    cout << "[STACK] Islem push edildi. Kayit ID: " << kayitID << endl;
}

void loglardanStackGuncelle(StackIslem** ust, LogKaydi* logBas, int* sonIslenenLogID) {
    if (logBas == NULL) {
        cout << "[BILGI] Log listesi bos." << endl;
        return;
    }

    LogKaydi* iter = logBas;
    bool yeniIslemVar = false;

    do {
        if (iter->logID > *sonIslenenLogID &&
            (iter->islemTuru == EKLE || iter->islemTuru == SIL || iter->islemTuru == GUNCELLE)) {
            stackeIslemPush(ust, iter->islemTuru, iter->kayitID, iter->oncekiDeger, iter->yeniDeger, iter->tarihSaat);
            yeniIslemVar = true;
        }
        iter = iter->next;
    } while (iter != logBas);

    if (logBas->prev != NULL) {
        *sonIslenenLogID = logBas->prev->logID;
    }

    if (!yeniIslemVar) {
        cout << "[BILGI] Stack icin yeni islem bulunamadi." << endl;
    } else {
        cout << "[BASARILI] Stack guncellendi." << endl;
    }
}

void undoPop(StackIslem** ust, Kayit** kayitBas, LogKaydi** logBas) {
    if (*ust == NULL) {
        cout << "[HATA] Stack bos, geri alinacak islem yok." << endl;
        return;
    }

    StackIslem* silinecek = *ust;
    *ust = (*ust)->next;

    cout << "\n[UNDO] Geri aliniyor -> Kayit ID: " << silinecek->kayitID << endl;

    if (silinecek->tur == EKLE) {
        *kayitBas = kayitSil(*kayitBas, logBas, silinecek->kayitID);
        cout << "[UNDO] EKLE islemi geri alindi (kayit silindi)." << endl;
    } else if (silinecek->tur == GUNCELLE) {
        Kayit* kayit = kayitAra(*kayitBas, silinecek->kayitID);
        if (kayit == NULL) {
            cout << "[HATA] Guncelleme geri alinamadi, kayit bulunamadi." << endl;
        } else {
            *kayitBas = kayitGuncelle(*kayitBas, logBas, silinecek->yeniDeger, silinecek->oncekiDeger, kayit->kategori, kayit->boyut);
            cout << "[UNDO] GUNCELLE islemi geri alindi." << endl;
        }
    } else if (silinecek->tur == SIL) {
        if (silinecek->oncekiDeger.empty()) {
            cout << "[HATA] SIL islemi icin oncekiDeger bos, geri alinamiyor." << endl;
        } else {
            string veri = silinecek->oncekiDeger;
            stringstream ss(veri);
            string idStr, baslik, kategori, boyutStr, tarih, oncelikStr, durumStr, puanStr, kritikNot;

            getline(ss, idStr, '|');
            getline(ss, baslik, '|');
            getline(ss, kategori, '|');
            getline(ss, boyutStr, '|');
            getline(ss, tarih, '|');
            getline(ss, oncelikStr, '|');
            getline(ss, durumStr, '|');
            getline(ss, puanStr, '|');
            getline(ss, kritikNot, '|');

            if (idStr.empty() || baslik.empty() || kategori.empty() || boyutStr.empty()
                || tarih.empty() || oncelikStr.empty() || durumStr.empty() || puanStr.empty()) {
                cout << "[HATA] SIL islemi undo icin log verisi eksik." << endl;
            } else {
                Kayit* yeni = new Kayit();
                yeni->id = stoi(idStr);
                yeni->baslik = baslik;
                yeni->kategori = kategori;
                yeni->boyut = stof(boyutStr);
                yeni->tarih = tarih;
                yeni->oncelik = static_cast<Oncelik>(stoi(oncelikStr));
                yeni->durum = static_cast<Durum>(stoi(durumStr));
                yeni->ortalamaPuan = stof(puanStr);
                yeni->kritikNot = kritikNot;

                yeni->next = *kayitBas;
                *kayitBas = yeni;

                cout << "[UNDO] SIL islemi geri alindi (kayit geri yuklendi)." << endl;
            }
        }
    } else {
        cout << "[UYARI] Bu islem turu icin undo tanimli degil." << endl;
    }

    delete silinecek;
}

int stackDerinligi(StackIslem* ust) {
    int sayac = 0;
    StackIslem* iter = ust;
    while (iter != NULL) {
        sayac++;
        iter = iter->next;
    }
    return sayac;
}

void son10IslemiGoster(StackIslem* ust) {
    if (ust == NULL) {
        cout << "[BILGI] Stack bos." << endl;
        return;
    }

    cout << "\n========== STACK SON 10 ISLEM ==========" << endl;
    StackIslem* iter = ust;
    int sira = 1;
    while (iter != NULL && sira <= 10) {
        cout << sira << ". [" << iter->zaman << "] "
             << islemToString(iter->tur) << " | Kayit ID: " << iter->kayitID << endl;
        iter = iter->next;
        sira++;
    }
    cout << "========================================" << endl;
}

void enSikIslemTuruAnalizi(StackIslem* ust) {
    if (ust == NULL) {
        cout << "[BILGI] Stack bos." << endl;
        return;
    }

    int ekle = 0, sil = 0, guncelle = 0, dequeue = 0;
    StackIslem* iter = ust;
    while (iter != NULL) {
        if (iter->tur == EKLE) ekle++;
        else if (iter->tur == SIL) sil++;
        else if (iter->tur == GUNCELLE) guncelle++;
        else if (iter->tur == DEQUEUE) dequeue++;
        iter = iter->next;
    }

    int enYuksek = ekle;
    string enSik = "EKLE";
    if (sil > enYuksek) { enYuksek = sil; enSik = "SIL"; }
    if (guncelle > enYuksek) { enYuksek = guncelle; enSik = "GUNCELLE"; }
    if (dequeue > enYuksek) { enYuksek = dequeue; enSik = "DEQUEUE"; }

    cout << "\n========== EN SIK ISLEM ANALIZI ==========" << endl;
    cout << "EKLE: " << ekle << endl;
    cout << "SIL: " << sil << endl;
    cout << "GUNCELLE: " << guncelle << endl;
    cout << "DEQUEUE: " << dequeue << endl;
    cout << "En sik islem: " << enSik << " (" << enYuksek << " adet)" << endl;
    cout << "==========================================" << endl;
}

void stackTemizle(StackIslem* ust) {
    while (ust != NULL) {
        StackIslem* silinecek = ust;
        ust = ust->next;
        delete silinecek;
    }
}
