#include "../include/modul1_kayit.h"
#include "../include/modul2_gunluk.h"
#include <sstream>
#include <iomanip>


int sonKayitID = 0;

static string boyutuYazdir(float b) {
    ostringstream oss;
    oss << fixed << setprecision(1) << b;
    return oss.str();
}

// "GG/AA/YYYY HH:MM:SS" -> "YYYYAAGGHHMMSS" (string olarak dogru karsilastirilir)
static string tarihiSiralanabilirYap(const string& tarih) {
    if (tarih.length() < 19) return tarih;
    return tarih.substr(6, 4) + tarih.substr(3, 2) + tarih.substr(0, 2)
         + tarih.substr(11, 2) + tarih.substr(14, 2) + tarih.substr(17, 2);
}

// ==================== YARDIMCI FONKSİYONLAR ====================


string simdikiZaman() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", localtime(&now));
    return string(buf);
}


string oncelikToString(Oncelik o) {
    switch(o) {
        case DUSUK:  return "Dusuk";
        case ORTA:   return "Orta";
        case YUKSEK: return "Yuksek";
        default:     return "Bilinmiyor";
    }
}


string durumToString(Durum d) {
    switch(d) {
        case AKTIF:   return "Aktif";
        case ISLEMDE: return "Islemde (Revize)";
        case ARSIV:   return "Arsiv";
        default:      return "Bilinmiyor";
    }
}


void kayitYazdir(Kayit* k) {
    if (k == NULL) {
        cout << "Kayit bulunamadi!" << endl;
        return;
    }
    cout << "----------------------------------------" << endl;
    cout << "ID: " << k->id << endl;
    cout << "Baslik: " << k->baslik << endl;
    cout << "Kategori: " << k->kategori << endl;
    cout << "Boyut: " << k->boyut << " KB" << endl;
    cout << "Tarih: " << k->tarih << endl;
    cout << "Oncelik: " << oncelikToString(k->oncelik) << endl;
    cout << "Durum: " << durumToString(k->durum) << endl;
    cout << "Ortalama Puan: " << k->ortalamaPuan << "/5.0" << endl;
    if (!k->kritikNot.empty()) {
        cout << "Kritik Not: " << k->kritikNot << endl;
    }
    cout << "----------------------------------------" << endl;
}

// ==================== 10 İŞLEVSELLİK ====================


Kayit* kayitEkle(Kayit* bas, LogKaydi** logBas, string baslik, string kategori, 
                 float boyut, Oncelik oncelik, float puan) {
    
    
    Kayit* yeniKayit = new Kayit();
    sonKayitID++;
    yeniKayit->id = sonKayitID;
    yeniKayit->baslik = baslik;
    yeniKayit->kategori = kategori;
    yeniKayit->boyut = boyut;
    yeniKayit->tarih = simdikiZaman();
    yeniKayit->oncelik = oncelik;
    yeniKayit->durum = AKTIF;
    yeniKayit->ortalamaPuan = puan;
    yeniKayit->kritikNot = "";
    yeniKayit->next = NULL;
    
 
    *logBas = gunlukKaydiEkle(*logBas, EKLE, yeniKayit->id, "", yeniKayit->baslik);
    
  
    if (bas == NULL) {
        cout << "[BASARILI] Kayit eklendi. ID: " << sonKayitID << endl;
        return yeniKayit;
    }
    
   
    Kayit* iter = bas;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = yeniKayit;
    
    cout << "[BASARILI] Kayit eklendi. ID: " << sonKayitID << endl;
    return bas;
}


Kayit* kayitSil(Kayit* bas, LogKaydi** logBas, int id) {
    if (bas == NULL) {
        cout << "[HATA] Liste bos!" << endl;
        return NULL;
    }
    
    
    if (bas->id == id) {
        Kayit* temp = bas->next;
        
        
        string srl = to_string(bas->id) + "|" + bas->baslik + "|" + bas->kategori + "|"
           + to_string(bas->boyut) + "|" + bas->tarih + "|"
           + to_string((int)bas->oncelik) + "|" + to_string((int)bas->durum) + "|"
           + to_string(bas->ortalamaPuan) + "|" + bas->kritikNot;
        
           *logBas = gunlukKaydiEkle(*logBas, SIL, id, srl, "");
        
        cout << "[BASARILI] Silindi: " << bas->baslik << endl;
        delete bas;
        return temp;
    }
    

    Kayit* iter = bas;
    while (iter->next != NULL) {
        if (iter->next->id == id) {
            Kayit* silinecek = iter->next;
            iter->next = silinecek->next;
            
            string srl = to_string(silinecek->id) + "|" + silinecek->baslik + "|" + silinecek->kategori + "|"
           + to_string(silinecek->boyut) + "|" + silinecek->tarih + "|"
           + to_string((int)silinecek->oncelik) + "|" + to_string((int)silinecek->durum) + "|"
           + to_string(silinecek->ortalamaPuan) + "|" + silinecek->kritikNot;
        
           *logBas = gunlukKaydiEkle(*logBas, SIL, id, srl, "");
            
            cout << "[BASARILI] Silindi: " << silinecek->baslik << endl;
            delete silinecek;
            return bas;
        }
        iter = iter->next;
    }
    
    cout << "[HATA] ID " << id << " bulunamadi!" << endl;
    return bas;
}


Kayit* kayitGuncelle(Kayit* bas, LogKaydi** logBas, string eskiBaslik,
                     string yeniBaslik, string yeniKategori, float yeniBoyut) {
    Kayit* iter = bas;
    while (iter != NULL) {
        if (iter->baslik == eskiBaslik) {

            string onceki = "baslik=" + iter->baslik
                          + ", kategori=" + iter->kategori
                          + ", boyut=" + boyutuYazdir(iter->boyut);
            string yeni = "baslik=" + yeniBaslik
                        + ", kategori=" + yeniKategori
                        + ", boyut=" + boyutuYazdir(yeniBoyut);

            *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, iter->id, onceki, yeni);

            iter->baslik = yeniBaslik;
            iter->kategori = yeniKategori;
            iter->boyut = yeniBoyut;
            cout << "[BASARILI] Guncellendi. ID: " << iter->id << endl;
            return bas;
        }
        iter = iter->next;
    }
    cout << "[HATA] '" << eskiBaslik << "' bulunamadi!" << endl;
    return bas;
}


void zamanliListele(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }
    
    cout << "\n========== KAYIT LISTESI (ZAMANLI) ==========" << endl;
    Kayit* iter = bas;
    int sira = 1;
    while (iter != NULL) {
        cout << sira << ". [" << iter->tarih << "] " 
             << iter->baslik << " (ID:" << iter->id << ")" << endl;
        iter = iter->next;
        sira++;
    }
    cout << "==============================================" << endl;
}


Kayit* kayitAra(Kayit* bas, int id) {
    Kayit* iter = bas;
    while (iter != NULL) {
        if (iter->id == id) return iter;
        iter = iter->next;
    }
    return NULL;
}


int toplamKayitSayisi(Kayit* bas) {
    int sayac = 0;
    Kayit* iter = bas;
    while (iter != NULL) {
        sayac++;
        iter = iter->next;
    }
    return sayac;
}


void boyutaSirala(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }
    
    int n = toplamKayitSayisi(bas);
    Kayit** dizi = new Kayit*[n];
    
 
    Kayit* iter = bas;
    for (int i = 0; i < n; i++) {
        dizi[i] = iter;
        iter = iter->next;
    }
    

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (dizi[j]->boyut > dizi[j+1]->boyut) {
                Kayit* temp = dizi[j];
                dizi[j] = dizi[j+1];
                dizi[j+1] = temp;
            }
        }
    }
    
   
    cout << "\n========== BOYUTA GORE SIRALI ==========" << endl;
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << dizi[i]->baslik << " - " << dizi[i]->boyut << " KB" << endl;
    }
    cout << "==========================================" << endl;
    
    delete[] dizi;
}


void enEski10Kayit(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }

    int n = toplamKayitSayisi(bas);
    Kayit** dizi = new Kayit*[n];

    Kayit* iter = bas;
    for (int i = 0; i < n; i++) {
        dizi[i] = iter;
        iter = iter->next;
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tarihiSiralanabilirYap(dizi[j]->tarih) > tarihiSiralanabilirYap(dizi[j+1]->tarih)) {
                Kayit* temp = dizi[j];
                dizi[j] = dizi[j+1];
                dizi[j+1] = temp;
            }
        }
    }

    int gosterilecek = (n < 10) ? n : 10;
    cout << "\n========== EN ESKI " << gosterilecek << " KAYIT ==========" << endl;
    for (int i = 0; i < gosterilecek; i++) {
        cout << i + 1 << ". " << dizi[i]->baslik << " [" << dizi[i]->tarih << "]" << endl;
    }
    cout << "========================================" << endl;

    delete[] dizi;
}


Kayit* kritikNotEkle(Kayit* bas, LogKaydi** logBas, int id, string not_) {
    Kayit* kayit = kayitAra(bas, id);
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " bulunamadi!" << endl;
        return bas;
    }

    string oncekiNot = kayit->kritikNot.empty() ? "(yok)" : kayit->kritikNot;
    *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, id, oncekiNot, not_);

    kayit->kritikNot = not_;
    cout << "[BASARILI] Kritik not eklendi: " << kayit->baslik << endl;
    return bas;
}


void kritikKayitlariListele(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }
    
    cout << "\n========== KRITIK KAYITLAR ==========" << endl;
    Kayit* iter = bas;
    int bulunan = 0;
    while (iter != NULL) {
        if (!iter->kritikNot.empty()) {
            cout << "ID:" << iter->id << " - " << iter->baslik << endl;
            cout << "   NOT: " << iter->kritikNot << endl;
            bulunan++;
        }
        iter = iter->next;
    }
    if (bulunan == 0) cout << "Kritik notu olan kayit yok." << endl;
    cout << "=======================================" << endl;
}

// ==================== ARŞIV İŞLEMLERİ ====================

Kayit* kayitArsivle(Kayit* bas, LogKaydi** logBas, int id) {
    Kayit* kayit = kayitAra(bas, id);
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " bulunamadi!" << endl;
        return bas;
    }
    if (kayit->durum == ARSIV) {
        cout << "[BILGI] Bu kayit zaten arsivde: " << kayit->baslik << endl;
        return bas;
    }

    string oncekiDurum = durumToString(kayit->durum);
    kayit->durum = ARSIV;
    *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, id, oncekiDurum, "Arsiv");

    cout << "[BASARILI] Arsivlendi: " << kayit->baslik << endl;
    return bas;
}

Kayit* arsivdenCikar(Kayit* bas, LogKaydi** logBas, int id) {
    Kayit* kayit = kayitAra(bas, id);
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " bulunamadi!" << endl;
        return bas;
    }
    if (kayit->durum != ARSIV) {
        cout << "[BILGI] Bu kayit arsivde degil: " << kayit->baslik << endl;
        return bas;
    }

    kayit->durum = AKTIF;
    *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, id, "Arsiv", "Aktif");

    cout << "[BASARILI] Arsivden cikarildi: " << kayit->baslik << endl;
    return bas;
}

Kayit* kaydiIslemeAl(Kayit* bas, LogKaydi** logBas, int id) {
    Kayit* kayit = kayitAra(bas, id);
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " bulunamadi!" << endl;
        return bas;
    }
    if (kayit->durum == ARSIV) {
        cout << "[BILGI] Arsivdeki kayit revize asamasina alinamaz: " << kayit->baslik << endl;
        return bas;
    }
    if (kayit->durum == ISLEMDE) {
        cout << "[BILGI] Bu kayit zaten revize asamasinda: " << kayit->baslik << endl;
        return bas;
    }

    string oncekiDurum = durumToString(kayit->durum);
    kayit->durum = ISLEMDE;
    *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, id, oncekiDurum, "Islemde (Revize)");

    cout << "[BASARILI] Revize asamasina alindi: " << kayit->baslik << endl;
    return bas;
}

Kayit* islemiTamamla(Kayit* bas, LogKaydi** logBas, int id) {
    Kayit* kayit = kayitAra(bas, id);
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " bulunamadi!" << endl;
        return bas;
    }
    if (kayit->durum != ISLEMDE) {
        cout << "[BILGI] Bu kayit revize asamasinda degil: " << kayit->baslik << endl;
        return bas;
    }

    kayit->durum = AKTIF;
    *logBas = gunlukKaydiEkle(*logBas, GUNCELLE, id, "Islemde (Revize)", "Aktif");

    cout << "[BASARILI] Revize tamamlandi, kayit aktif: " << kayit->baslik << endl;
    return bas;
}

void arsivdekiKayitlariListele(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }

    cout << "\n========== ARSIVDEKI KAYITLAR ==========" << endl;
    Kayit* iter = bas;
    int bulunan = 0;
    while (iter != NULL) {
        if (iter->durum == ARSIV) {
            cout << "ID:" << iter->id << " - " << iter->baslik
                 << " [" << iter->tarih << "]" << endl;
            bulunan++;
        }
        iter = iter->next;
    }
    if (bulunan == 0) cout << "Arsivde kayit yok." << endl;
    cout << "==========================================" << endl;
}

// ==================== EKSTRA FONKSİYONLAR ====================

void tumKayitlariListele(Kayit* bas) {
    if (bas == NULL) {
        cout << "[BILGI] Liste bos." << endl;
        return;
    }
    Kayit* iter = bas;
    while (iter != NULL) {
        kayitYazdir(iter);
        iter = iter->next;
    }
}


Kayit* demoVerilerEkle(Kayit* bas, LogKaydi** logBas) {
    string tarihler[5] = {
        "10/03/2024 09:00:00",  // Python Programlama
        "22/06/2018 14:30:00",  // Web Tasarim Temelleri
        "05/11/1999 10:15:00",  // Girisimcilik 101 (2000 oncesi )
        "18/09/2022 11:45:00",  // Ingilizce Konusma
        "01/02/2026 08:00:00"   // Gitar Dersleri
    };

    int eskiSayi = toplamKayitSayisi(bas);

    bas = kayitEkle(bas, logBas, "Python Programlama", "Yazilim", 1500.0, YUKSEK, 4.8);
    bas = kayitEkle(bas, logBas, "Web Tasarim Temelleri", "Tasarim", 800.0, ORTA, 4.2);
    bas = kayitEkle(bas, logBas, "Girisimcilik 101", "Isletme", 500.0, DUSUK, 3.9);
    bas = kayitEkle(bas, logBas, "Ingilizce Konusma", "Dil", 1200.0, YUKSEK, 4.5);
    bas = kayitEkle(bas, logBas, "Gitar Dersleri", "Muzik", 600.0, ORTA, 4.0);

    
    Kayit* iter = bas;
    int sira = 0;
    while (iter != NULL) {
        if (sira >= eskiSayi && sira < eskiSayi + 5) {
            iter->tarih = tarihler[sira - eskiSayi];

            // Demo simulasyonu ilgili ekle log kaydinin tarihini de kayitla esitle
            if (*logBas != NULL) {
                LogKaydi* lit = *logBas;
                do {
                    if (lit->kayitID == iter->id && lit->islemTuru == EKLE) {
                        lit->tarihSaat = iter->tarih;
                        break;
                    }
                    lit = lit->next;
                } while (lit != *logBas);
            }
        }
        iter = iter->next;
        sira++;
    }

    cout << "\n[BILGI] 5 adet demo kayit eklendi (gecmis tarihlerle simulasyon)." << endl;
    return bas;
}


void listeTemizle(Kayit* bas) {
    while (bas != NULL) {
        Kayit* silinecek = bas;
        bas = bas->next;
        delete silinecek;
    }
}
