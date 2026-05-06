

#include "../include/modul2_gunluk.h"
#include "../include/modul1_kayit.h"


int sonLogID = 0;

// ==================== YARDIMCI FONKSİYONLAR ====================

string islemToString(IslemTuru t) {
    switch(t) {
        case EKLE:     return "EKLE";
        case SIL:      return "SIL";
        case GUNCELLE: return "GUNCELLE";
        case DEQUEUE:  return "DEQUEUE";
        default:       return "BILINMIYOR";
    }
}


string logZamani() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", localtime(&now));
    return string(buf);
}


void logYazdir(LogKaydi* log) {
    if (log == NULL) return;
    
    cout << "----------------------------------------" << endl;
    cout << "Log ID: " << log->logID << endl;
    cout << "Islem: " << islemToString(log->islemTuru) << endl;
    cout << "Kayit ID: " << log->kayitID << endl;
    cout << "Zaman: " << log->tarihSaat << endl;
    if (!log->oncekiDeger.empty())
        cout << "Onceki Deger: " << log->oncekiDeger << endl;
    if (!log->yeniDeger.empty())
        cout << "Yeni Deger: " << log->yeniDeger << endl;
    cout << "----------------------------------------" << endl;
}

bool tarihGecerliMi(string tarih) {

    if (tarih.length() != 10) {
        return false;
    }

    // Ayraç "/" veya "." olabilir; ikisi de tutarli olmali
    char ayrac = tarih[2];
    if ((ayrac != '/' && ayrac != '.') || tarih[5] != ayrac) {
        return false;
    }


    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // ayrac karakterleri
        if (tarih[i] < '0' || tarih[i] > '9') {
            return false;
        }
    }
    

    int gun = (tarih[0] - '0') * 10 + (tarih[1] - '0');
    int ay = (tarih[3] - '0') * 10 + (tarih[4] - '0');
    int yil = (tarih[6] - '0') * 1000 + (tarih[7] - '0') * 100 + 
              (tarih[8] - '0') * 10 + (tarih[9] - '0');
    
    
    if (gun < 1 || gun > 31) {
        return false;
    }
    
    
    if (ay < 1 || ay > 12) {
        return false;
    }
    

    
    return true;
}


// "GG/AA/YYYY" -> "YYYYAAGG" (string olarak doğru karşılaştırılır)
string tarihiKarsilastirmaFormatina(string tarih) {
    return tarih.substr(6, 4) + tarih.substr(3, 2) + tarih.substr(0, 2);
}

bool tarihSiralamaGecerliMi(string tarih1, string tarih2) {
    return tarihiKarsilastirmaFormatina(tarih1) <= tarihiKarsilastirmaFormatina(tarih2);
}

// ==================== 5 İŞLEVSELLİK ====================


LogKaydi* gunlukKaydiEkle(LogKaydi* bas, IslemTuru tur, int kayitID, 
                          string onceki, string yeni) {
    

    LogKaydi* yeniLog = new LogKaydi();
    sonLogID++;
    yeniLog->logID = sonLogID;
    yeniLog->islemTuru = tur;
    yeniLog->kayitID = kayitID;
    yeniLog->tarihSaat = logZamani();
    yeniLog->oncekiDeger = onceki;
    yeniLog->yeniDeger = yeni;
    

    if (bas == NULL) {
        yeniLog->next = yeniLog;
        yeniLog->prev = yeniLog;
        cout << "[LOG] Kayit eklendi. Log ID: " << sonLogID << endl;
        return yeniLog;
    }
    

    LogKaydi* son = bas->prev;
    
    son->next = yeniLog;
    yeniLog->prev = son;
    yeniLog->next = bas;
    bas->prev = yeniLog;
    
    cout << "[LOG] Kayit eklendi. Log ID: " << sonLogID << endl;
    return bas;
}


void kayitIdIslemleriniListele(LogKaydi* bas, int kayitID) {
    if (bas == NULL) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }
    
    cout << "\n========== KAYIT ID " << kayitID << " ISLEMLERI ==========" << endl;
    
    LogKaydi* iter = bas;
    int bulunan = 0;
    
   
    do {
        if (iter->kayitID == kayitID) {
            cout << "[" << iter->tarihSaat << "] " 
                 << islemToString(iter->islemTuru);
            if (!iter->oncekiDeger.empty()) 
                cout << " | Onceki: " << iter->oncekiDeger;
            if (!iter->yeniDeger.empty()) 
                cout << " | Yeni: " << iter->yeniDeger;
            cout << endl;
            bulunan++;
        }
        iter = iter->next;
    } while (iter != bas);
    
    if (bulunan == 0) {
        cout << "Bu kayit icin islem bulunamadi." << endl;
    }
    cout << "=================================================" << endl;
}


void tarihAraligiIslemler(LogKaydi* bas, string baslangic, string bitis) {
    
     // Tarih format kontrolü
    if (!tarihGecerliMi(baslangic)) {
        cout << "[HATA] Baslangic tarihi gecersiz! Format: GG/AA/YYYY" << endl;
        cout << "       Ornek: 01/04/2026" << endl;
        return;
    }
    
    if (!tarihGecerliMi(bitis)) {
        cout << "[HATA] Bitis tarihi gecersiz! Format: GG/AA/YYYY" << endl;
        cout << "       Ornek: 30/04/2026" << endl;
        return;
    }
    
    // Başlangıç <= Bitiş kontrolü
    if (!tarihSiralamaGecerliMi(baslangic, bitis)) {
        cout << "[HATA] Baslangic tarihi, bitis tarihinden sonra olamaz!" << endl;
        return;
    }
    
    
    if (bas == NULL) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }
    
    cout << "\n========== " << baslangic << " - " << bitis << " ARASI ==========" << endl;

    string baslangicKarsi = tarihiKarsilastirmaFormatina(baslangic);
    string bitisKarsi = tarihiKarsilastirmaFormatina(bitis);

    LogKaydi* iter = bas;
    int bulunan = 0;

    do {
        string logTarih = tarihiKarsilastirmaFormatina(iter->tarihSaat.substr(0, 10));
        if (logTarih >= baslangicKarsi && logTarih <= bitisKarsi) {
            cout << "[" << iter->tarihSaat << "] "
                 << islemToString(iter->islemTuru)
                 << " - Kayit ID: " << iter->kayitID << endl;
            bulunan++;
        }
        iter = iter->next;
    } while (iter != bas);
    
    if (bulunan == 0) {
        cout << "Bu aralikta islem bulunamadi." << endl;
    }
    cout << "======================================================" << endl;
}


void gunlukRaporuOlustur(LogKaydi* bas, Kayit* kayitBas) {
    if (bas == NULL) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }

    // 1. İşlem türü ve sıklık
    int toplam = 0;
    int ekleSayisi = 0, silSayisi = 0, guncelleSayisi = 0, dequeueSayisi = 0;

    LogKaydi* iter = bas;
    do {
        toplam++;
        switch(iter->islemTuru) {
            case EKLE:     ekleSayisi++; break;
            case SIL:      silSayisi++; break;
            case GUNCELLE: guncelleSayisi++; break;
            case DEQUEUE:  dequeueSayisi++; break;
        }
        iter = iter->next;
    } while (iter != bas);

    cout << "\n============== GUNLUK RAPORU ==============" << endl;
    cout << "Toplam Islem Sayisi: " << toplam << endl;
    cout << "---------------------------------------------" << endl;
    cout << "EKLE:     " << ekleSayisi << " adet ("
         << (toplam > 0 ? (ekleSayisi * 100 / toplam) : 0) << "%)" << endl;
    cout << "SIL:      " << silSayisi << " adet ("
         << (toplam > 0 ? (silSayisi * 100 / toplam) : 0) << "%)" << endl;
    cout << "GUNCELLE: " << guncelleSayisi << " adet ("
         << (toplam > 0 ? (guncelleSayisi * 100 / toplam) : 0) << "%)" << endl;
    cout << "DEQUEUE:  " << dequeueSayisi << " adet ("
         << (toplam > 0 ? (dequeueSayisi * 100 / toplam) : 0) << "%)" << endl;

    // 2. Kritik kayıt analizi
    cout << "\n--- KRITIK KAYIT ANALIZI ---" << endl;

    if (kayitBas == NULL) {
        cout << "Modul 1 kayit listesi bos, kritik kayit yok." << endl;
        cout << "=============================================" << endl;
        return;
    }

    int kritikSayisi = 0;
    int kritikUzerindeToplamIslem = 0;

    Kayit* k = kayitBas;
    while (k != NULL) {
        if (!k->kritikNot.empty()) kritikSayisi++;
        k = k->next;
    }

    cout << "Kritik notu olan kayit sayisi: " << kritikSayisi << endl;

    if (kritikSayisi == 0) {
        cout << "Kritik kayit bulunmadigi icin detayli analiz yok." << endl;
        cout << "=============================================" << endl;
        return;
    }

    cout << "---------------------------------------------" << endl;

    k = kayitBas;
    while (k != NULL) {
        if (!k->kritikNot.empty()) {
            int kEkle = 0, kSil = 0, kGuncelle = 0, kDequeue = 0;
            LogKaydi* lit = bas;
            do {
                if (lit->kayitID == k->id) {
                    switch (lit->islemTuru) {
                        case EKLE:     kEkle++; break;
                        case SIL:      kSil++; break;
                        case GUNCELLE: kGuncelle++; break;
                        case DEQUEUE:  kDequeue++; break;
                    }
                }
                lit = lit->next;
            } while (lit != bas);

            int kToplam = kEkle + kSil + kGuncelle + kDequeue;
            kritikUzerindeToplamIslem += kToplam;

            cout << "Kayit ID " << k->id << " (" << k->baslik << "): "
                 << kToplam << " islem"
                 << " [E:" << kEkle << " S:" << kSil
                 << " G:" << kGuncelle << " D:" << kDequeue << "]" << endl;
        }
        k = k->next;
    }

    cout << "---------------------------------------------" << endl;
    cout << "Kritik kayitlar uzerinde toplam islem: " << kritikUzerindeToplamIslem << endl;
    cout << "Tum loglara orani: %"
         << (toplam > 0 ? (kritikUzerindeToplamIslem * 100 / toplam) : 0) << endl;
    cout << "=============================================" << endl;
}


void islemTuruneGoreListele(LogKaydi* bas, IslemTuru tur) {
    if (bas == NULL) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }
    
    cout << "\n========== " << islemToString(tur) << " ISLEMLERI ==========" << endl;
    
    LogKaydi* iter = bas;
    int bulunan = 0;
    
    do {
        if (iter->islemTuru == tur) {
            cout << "Log ID: " << iter->logID 
                 << " | [" << iter->tarihSaat << "] "
                 << "| Kayit ID: " << iter->kayitID << endl;
            bulunan++;
        }
        iter = iter->next;
    } while (iter != bas);
    
    if (bulunan == 0) {
        cout << "Bu turde islem bulunamadi." << endl;
    }
    cout << "================================================" << endl;
}

// ==================== EKSTRA FONKSİYONLAR ====================


void tumLoglariListele(LogKaydi* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Gunluk bos." << endl;
        return;
    }
    
    cout << "\n========== TUM LOG KAYITLARI ==========" << endl;
    
    LogKaydi* iter = bas;
    do {
        logYazdir(iter);
        iter = iter->next;
    } while (iter != bas);
}

int toplamLogSayisi(LogKaydi* bas) {
    if (bas == NULL) return 0;
    
    int sayac = 0;
    LogKaydi* iter = bas;
    do {
        sayac++;
        iter = iter->next;
    } while (iter != bas);
    
    return sayac;
}


void listeTemizleLog(LogKaydi* bas) {
    if (bas == NULL) return;
    
 
    LogKaydi* son = bas->prev;
    son->next = NULL;
    
    LogKaydi* iter = bas;
    while (iter != NULL) {
        LogKaydi* silinecek = iter;
        iter = iter->next;
        delete silinecek;
    }
}
