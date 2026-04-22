/*
 * main.cpp
 * EduFlow - Dijital Eğitim Platformu
 * Kurumsal Operasyon ve Karar Destek Sistemi
 * 
 * ISE 106 - Veri Yapıları Projesi
 * Modül 1: Ana Kayıt Yönetimi (Tek Yönlü Bağlı Liste)
 * Modül 2: Operasyon Günlüğü (Çift Yönlü Dairesel Bağlı Liste)
 */

#include <iostream>
#include <string>
#include "include/modul1_kayit.h"
#include "include/modul2_gunluk.h"

using namespace std;

// Ana menüyü göster
void anaMenuGoster() {
    cout << "\n===============================================" << endl;
    cout << "        EDUFLOW - DIJITAL EGITIM PLATFORMU" << endl;
    cout << "===============================================" << endl;
    cout << "1.  Kayit Ekle" << endl;
    cout << "2.  ID'ye Gore Sil" << endl;
    cout << "3.  Basliga Gore Guncelle" << endl;
    cout << "4.  Zaman Damgasi ile Listele" << endl;
    cout << "5.  ID'ye Gore Ara" << endl;
    cout << "6.  Toplam Kayit Sayisi" << endl;
    cout << "7.  Boyuta Gore Sirala" << endl;
    cout << "8.  En Eski 10 Kayit" << endl;
    cout << "9.  Kritik Not Ekle" << endl;
    cout << "10. Kritik Kayitlari Listele" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "11. Kayit ID Islemlerini Listele" << endl;
    cout << "12. Tarih Araliginda Islemler" << endl;
    cout << "13. Gunluk Raporu Olustur" << endl;
    cout << "14. Islem Turune Gore Listele" << endl;
    cout << "15. Tum Loglari Goster" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "16. Demo Veriler Ekle" << endl;
    cout << "17. Tum Kayitlari Detayli Goster" << endl;
    cout << "0.  Cikis" << endl;
    cout << "===============================================" << endl;
    cout << "Seciminiz: ";
}

int main() {
    // Liste başlangıçları
    Kayit* kayitBas = NULL;
    LogKaydi* logBas = NULL;
    
    // Değişkenler
    int secim;
    string baslik, kategori, eskiBaslik, yeniBaslik, yeniKategori, not_, tarih1, tarih2;
    float boyut, puan, yeniBoyut;
    int id, oncelikInt, islemInt;
    Oncelik oncelik;
    
    // Hoşgeldin mesajı
    cout << "================================================" << endl;
    cout << "   EDUFLOW - Dijital Egitim Platformu" << endl;
    cout << "   Veri Yapilari Projesi (ISE 106)" << endl;
    cout << "   Modul 1: Ana Kayit Yonetimi" << endl;
    cout << "   Modul 2: Operasyon Gunlugu" << endl;
    cout << "================================================" << endl;
    
    do {
        anaMenuGoster();
        cin >> secim;
        cin.ignore();
        
        switch(secim) {
            // ========== MODÜL 1 İŞLEMLERİ ==========
            
            case 1: // Kayıt Ekle
                cout << "\n--- KAYIT EKLE ---" << endl;
                cout << "Baslik: "; getline(cin, baslik);
                cout << "Kategori (Yazilim/Tasarim/Isletme/Dil/Muzik): "; getline(cin, kategori);
                cout << "Boyut (KB): "; cin >> boyut;
                cout << "Oncelik (0=Dusuk, 1=Orta, 2=Yuksek): "; cin >> oncelikInt;
                cout << "Ortalama Puan (0-5): "; cin >> puan;
                oncelik = (Oncelik)oncelikInt;
                kayitBas = kayitEkle(kayitBas, &logBas, baslik, kategori, boyut, oncelik, puan);
                break;
                
            case 2: // ID'ye Göre Sil
                cout << "\n--- KAYIT SIL ---" << endl;
                cout << "Silinecek ID: "; cin >> id;
                kayitBas = kayitSil(kayitBas, &logBas, id);
                break;
                
            case 3: // Başlığa Göre Güncelle
                cout << "\n--- KAYIT GUNCELLE ---" << endl;
                cout << "Eski Baslik: "; getline(cin, eskiBaslik);
                cout << "Yeni Baslik: "; getline(cin, yeniBaslik);
                cout << "Yeni Kategori: "; getline(cin, yeniKategori);
                cout << "Yeni Boyut (KB): "; cin >> yeniBoyut;
                kayitBas = kayitGuncelle(kayitBas, &logBas, eskiBaslik, yeniBaslik, yeniKategori, yeniBoyut);
                break;
                
            case 4: // Zamanlı Listele
                zamanliListele(kayitBas);
                break;
                
            case 5: // ID'ye Göre Ara
                cout << "\n--- KAYIT ARA ---" << endl;
                cout << "Aranacak ID: "; cin >> id;
                kayitYazdir(kayitAra(kayitBas, id));
                break;
                
            case 6: // Toplam Kayıt Sayısı
                cout << "\nToplam Kayit Sayisi: " << toplamKayitSayisi(kayitBas) << endl;
                break;
                
            case 7: // Boyuta Göre Sırala
                boyutaSirala(kayitBas);
                break;
                
            case 8: // En Eski 10 Kayıt
                enEski10Kayit(kayitBas);
                break;
                
            case 9: // Kritik Not Ekle
                cout << "\n--- KRITIK NOT EKLE ---" << endl;
                cout << "Kayit ID: "; cin >> id;
                cin.ignore();
                cout << "Kritik Not: "; getline(cin, not_);
                kayitBas = kritikNotEkle(kayitBas, &logBas, id, not_);
                break;
                
            case 10: // Kritik Kayıtları Listele
                kritikKayitlariListele(kayitBas);
                break;
                
            // ========== MODÜL 2 İŞLEMLERİ ==========
            
            case 11: // Kayıt ID İşlemlerini Listele
                cout << "\n--- KAYIT ISLEMLERI ---" << endl;
                cout << "Kayit ID: "; cin >> id;
                kayitIdIslemleriniListele(logBas, id);
                break;
                
            case 12: // Tarih Aralığında İşlemler
                cout << "\n--- TARIH ARALIGINDA ISLEMLER ---" << endl;
                cout << "Baslangic Tarihi (GG/AA/YYYY): "; getline(cin, tarih1);
                cout << "Bitis Tarihi (GG/AA/YYYY): "; getline(cin, tarih2);
                tarihAraligiIslemler(logBas, tarih1, tarih2);
                break;
                
            case 13: // Günlük Raporu
                gunlukRaporuOlustur(logBas);
                break;
                
            case 14: // İşlem Türüne Göre Listele
                cout << "\n--- ISLEM TURUNE GORE LISTELE ---" << endl;
                cout << "Islem Turu (0=EKLE, 1=SIL, 2=GUNCELLE, 3=DEQUEUE): "; cin >> islemInt;
                islemTuruneGoreListele(logBas, (IslemTuru)islemInt);
                break;
                
            case 15: // Tüm Logları Göster
                tumLoglariListele(logBas);
                break;
                
            // ========== EKSTRA ==========
            
            case 16: // Demo Veriler
                kayitBas = demoVerilerEkle(kayitBas, &logBas);
                break;
                
            case 17: // Tüm Kayıtları Detaylı Göster
                tumKayitlariListele(kayitBas);
                break;
                
            case 0: // Çıkış
                cout << "\nProgram sonlandiriliyor..." << endl;
                break;
                
            default:
                cout << "\n[HATA] Gecersiz secim!" << endl;
        }
        
    } while(secim != 0);
    
    // Bellek temizliği
    listeTemizle(kayitBas);
    listeTemizleLog(logBas);
    
    cout << "Gule gule!" << endl;
    return 0;
}
