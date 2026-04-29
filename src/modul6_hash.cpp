#include "../include/modul6_hash.h"
#include <iomanip>

using namespace std;

// ==================== YARDIMCI FONKSIYONLAR ====================

// Hash Fonksiyonu: ID → 0-9 arasında index
int hashFonksiyonu(int id) {
    return id % HASH_BOYUTU;
}

// Hash Tablosu Bellek Temizleme
void hashTablosuTemizle(HashTablosu* ht) {
    if (ht == NULL) return;
    
    for (int i = 0; i < ht->boyut; i++) {
        HashDugumu* iter = ht->table[i];
        while (iter != NULL) {
            HashDugumu* silinecek = iter;
            iter = iter->next;
            delete silinecek;
        }
    }
    delete[] ht->table;
    delete ht;
}

// ==================== 1. HASH TABLOSU OLUŞTURMA ====================

// Hash tablosu oluştur ve başlangıç değerlerini ayarla
HashTablosu* hashTablosuOlustur(Kayit* bas) {
    HashTablosu* ht = new HashTablosu();
    ht->table = new HashDugumu*[HASH_BOYUTU];
    ht->boyut = HASH_BOYUTU;
    ht->doluHucreSayisi = 0;
    ht->capismaSayisi = 0;
    
    // Tüm bucket'ları NULL ile başlat
    for (int i = 0; i < HASH_BOYUTU; i++) {
        ht->table[i] = NULL;
    }
    
    // Modül 1 listesindeki tüm kayıtları hash tabloya ekle
    Kayit* iter = bas;
    while (iter != NULL) {
        hashTableDugumEkle(ht, iter);
        iter = iter->next;
    }
    
    return ht;
}

// Hash tablosuna yeni kayıt ekle (zincir yöntemi)
void hashTableDugumEkle(HashTablosu* ht, Kayit* k) {
    int index = hashFonksiyonu(k->id);
    
    HashDugumu* yeni = new HashDugumu();
    yeni->kayit = k;
    yeni->next = NULL;
    
    // Boş hücre
    if (ht->table[index] == NULL) {
        ht->table[index] = yeni;
        ht->doluHucreSayisi++;
    } else {
        // Çarpışma - zincirin sonuna ekle
        ht->capismaSayisi++;
        HashDugumu* iter = ht->table[index];
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = yeni;
    }
}

// ==================== 2. ID BAZLI ARAMA ====================

// Hash tablosunda ID'ye göre kayıt ara (O(1) ortalama)
Kayit* idyeGoreHashAra(HashTablosu* ht, int id) {
    if (ht == NULL) return NULL;
    
    int index = hashFonksiyonu(id);
    HashDugumu* iter = ht->table[index];
    
    while (iter != NULL) {
        if (iter->kayit->id == id) {
            return iter->kayit;
        }
        iter = iter->next;
    }
    return NULL;
}

// ID'ye göre ortalama puanı bul ve yazdır
void idyeGoreOrtalamaPuanBul(HashTablosu* ht, int id) {
    Kayit* kayit = idyeGoreHashAra(ht, id);
    
    if (kayit == NULL) {
        cout << "[HATA] ID " << id << " ile kayit bulunamadi." << endl;
        return;
    }
    
    cout << "\n========== ID " << id << " ORTALAMA PUAN ==========" << endl;
    cout << "Baslik      : " << kayit->baslik << endl;
    cout << "Kategori    : " << kayit->kategori << endl;
    cout << "Ortalama Puan: " << fixed << setprecision(2) << kayit->ortalamaPuan << " / 5.0" << endl;
    cout << "Oncelik     : " << oncelikToString(kayit->oncelik) << endl;
    cout << "=============================================" << endl;
}

// ==================== 3. KATEGORİ BAZLI GRUPLAMA ====================

// Belirli kategoriye ait kayıt sayısını bul
int kategoriyeSayiBul(HashTablosu* ht, const string& kategori) {
    if (ht == NULL) return 0;
    
    int sayac = 0;
    for (int i = 0; i < ht->boyut; i++) {
        HashDugumu* iter = ht->table[i];
        while (iter != NULL) {
            if (iter->kayit->kategori == kategori) {
                sayac++;
            }
            iter = iter->next;
        }
    }
    return sayac;
}

// Belirli kategoriye ait kayıtları listele
void kategoriyeGoreKayitlariListele(HashTablosu* ht, const string& kategori) {
    if (ht == NULL) {
        cout << "[BILGI] Hash tablosu bos." << endl;
        return;
    }
    
    int sayac = 0;
    cout << "\n========== KATEGORI: " << kategori << " ==========" << endl;
    cout << "ID   | Baslik              | Puan  | Oncelik" << endl;
    cout << "--------------------------------------------------" << endl;
    
    for (int i = 0; i < ht->boyut; i++) {
        HashDugumu* iter = ht->table[i];
        while (iter != NULL) {
            if (iter->kayit->kategori == kategori) {
                cout << left << setw(4) << iter->kayit->id << " | "
                     << setw(19) << iter->kayit->baslik << " | "
                     << fixed << setprecision(1) << setw(4) << iter->kayit->ortalamaPuan << " | "
                     << oncelikToString(iter->kayit->oncelik) << endl;
                sayac++;
            }
            iter = iter->next;
        }
    }
    cout << "================================================" << endl;
    cout << "Toplam: " << sayac << " kayit" << endl;
}

// Tüm kategorileri analiz et ve özet göster
void tumKategorileriAnaliz(HashTablosu* ht) {
    if (ht == NULL) {
        cout << "[BILGI] Hash tablosu bos." << endl;
        return;
    }
    
    // Kategorileri topla (Yazılım, Tasarım, İşletme, Dil, Müzik)
    string kategoriler[] = {"Yazilim", "Tasarim", "Isletme", "Dil", "Muzik"};
    
    cout << "\n========== TUM KATEGORILER ANALIZI ==========" << endl;
    cout << "Kategori      | Kayit Sayisi" << endl;
    cout << "-------------------------------------" << endl;
    
    int toplam = 0;
    for (int i = 0; i < 5; i++) {
        int sayi = kategoriyeSayiBul(ht, kategoriler[i]);
        cout << left << setw(14) << kategoriler[i] << "| " << sayi << endl;
        toplam += sayi;
    }
    cout << "-------------------------------------" << endl;
    cout << "TOPLAM        | " << toplam << endl;
    cout << "===========================================" << endl;
}

// ==================== 4. ÖNCELİK BAZLI YOĞUNLUK ANALİZİ ====================

// Belirli önceliğe ait kayıt sayısını bul
int onceligeGoreSayiBul(HashTablosu* ht, Oncelik onc) {
    if (ht == NULL) return 0;
    
    int sayac = 0;
    for (int i = 0; i < ht->boyut; i++) {
        HashDugumu* iter = ht->table[i];
        while (iter != NULL) {
            if (iter->kayit->oncelik == onc) {
                sayac++;
            }
            iter = iter->next;
        }
    }
    return sayac;
}

// Tüm öncelik seviyelerine göre yoğunluk analizi
void onceligeGoreYogunlukAnalizi(HashTablosu* ht) {
    if (ht == NULL) {
        cout << "[BILGI] Hash tablosu bos." << endl;
        return;
    }
    
    cout << "\n========== ONCELIK YOGUNLUK ANALIZI ==========" << endl;
    cout << "Oncelik  | Kayit Sayisi | Yuzde" << endl;
    cout << "--------------------------------------" << endl;
    
    int dusuk = onceligeGoreSayiBul(ht, DUSUK);
    int orta = onceligeGoreSayiBul(ht, ORTA);
    int yuksek = onceligeGoreSayiBul(ht, YUKSEK);
    int toplam = dusuk + orta + yuksek;
    
    if (toplam == 0) {
        cout << "[BILGI] Kayit bulunamadi." << endl;
        return;
    }
    
    cout << "Dusuk    | " << setw(12) << dusuk << " | "
         << fixed << setprecision(1) << (dusuk * 100.0 / toplam) << "%" << endl;
    cout << "Orta     | " << setw(12) << orta << " | "
         << fixed << setprecision(1) << (orta * 100.0 / toplam) << "%" << endl;
    cout << "Yuksek   | " << setw(12) << yuksek << " | "
         << fixed << setprecision(1) << (yuksek * 100.0 / toplam) << "%" << endl;
    cout << "--------------------------------------" << endl;
    cout << "TOPLAM   | " << setw(12) << toplam << endl;
    cout << "===========================================" << endl;
}

// ==================== 5. HASH PERFORMANS METRİKLERİ ====================

// Load Factor hesapla: dolu hücre / toplam hücre
float loadFactor(HashTablosu* ht) {
    if (ht == NULL) return 0.0;
    return (float)ht->doluHucreSayisi / ht->boyut;
}

// Hash tablo performans bilgisini yazdır
void hashPerformansBilgisi(HashTablosu* ht) {
    if (ht == NULL) {
        cout << "[BILGI] Hash tablosu bos." << endl;
        return;
    }
    
    float lf = loadFactor(ht);
    int toplamKayit = 0;
    for (int i = 0; i < ht->boyut; i++) {
        HashDugumu* iter = ht->table[i];
        while (iter != NULL) {
            toplamKayit++;
            iter = iter->next;
        }
    }
    
    cout << "\n========== HASH TABLO PERFORMANS ==========" << endl;
    cout << "Tablo Boyutu       : " << ht->boyut << endl;
    cout << "Toplam Kayit       : " << toplamKayit << endl;
    cout << "Dolu Hucre Sayisi  : " << ht->doluHucreSayisi << endl;
    cout << "Collision    : " << ht->capismaSayisi << endl;
    cout << "Load Factor        : " << fixed << setprecision(2) << (lf * 100) << "%" << endl;
    cout << "-------------------------------------------" << endl;
    
    if (lf < 0.6) {
        cout << "Performans Durumu  : COK IYI (O(1) arama) ✓" << endl;
    } else if (lf < 0.8) {
        cout << "Performans Durumu  : IYI (ortalama O(1))" << endl;
    } else {
        cout << "Performans Durumu  : UYARI" << endl;
    }
    cout << "===========================================" << endl;
}
