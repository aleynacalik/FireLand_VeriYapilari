/*
 * main.cpp
 * EduFlow - Dijital Eğitim Platformu
 * Kurumsal Operasyon ve Karar Destek Sistemi
 *
 * ISE 106 - Veri Yapıları Projesi
 * Modül 1: Ana Kayıt Yönetimi (Tek Yönlü Bağlı Liste)
 * Modül 2: Operasyon Günlüğü (Çift Yönlü Dairesel Bağlı Liste)
 * Modül 3: Stack Modülü
 * Modül 4: Talep Yönetim Modülü (Queue)
 * Modül 5: Tarih Bazlı Filtreleme ve Analiz (Binary Search Tree)
 * Modül 6: Hash Analiz Motoru (Hash Tablosu)
 */

#include <iostream>
#include <string>
#include "include/modul1_kayit.h"
#include "include/modul2_gunluk.h"
#include "include/modul3_stack.h"
#include "include/modul4_queue.h"
#include "include/modul5_tree.h"
#include "include/modul6_hash.h"
#include "include/modul7_sikistirma.h"
#include "include/modul8_performans.h"
#include <ctime>


using namespace std;

// Belirli aralikta tamsayi girisi (gecerli olana kadar sorar)
int intSec(const string& prompt, int minVal, int maxVal) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= minVal && x <= maxVal) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[HATA] Gecersiz giris. " << minVal << "-" << maxVal
             << " arasinda bir sayi girmelisiniz." << endl;
    }
}

// Belirli aralikta ondalikli sayi girisi (gecerli olana kadar sorar)
float floatSec(const string& prompt, float minVal, float maxVal) {
    float x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= minVal && x <= maxVal) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[HATA] Gecersiz giris. " << minVal << " - " << maxVal
             << " arasinda bir sayi girmelisiniz." << endl;
    }
}

// Pozitif ID girisi (1 ile 999999 arasi)
int idSec(const string& prompt) {
    return intSec(prompt, 1, 999999);
}

// Puan girişi (0-5 araliginda gecerli sayi olana kadar sorar)
float puanSec() {
    float p;
    while (true) {
        cout << "Ortalama Puan (0-5): ";
        if (cin >> p && p >= 0.0 && p <= 5.0) return p;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[HATA] Gecersiz giris. 0-5 arasinda bir sayi girmelisiniz." << endl;
    }
}

// Kategori için numerik seçim (yanlış girisleri tekrar sorar)
string kategoriSec() {
    int secim;
    while (true) {
        cout << "Kategori (1=Yazilim, 2=Tasarim, 3=Isletme, 4=Dil, 5=Muzik): ";
        if (cin >> secim) {
            switch (secim) {
                case 1: return "Yazilim";
                case 2: return "Tasarim";
                case 3: return "Isletme";
                case 4: return "Dil";
                case 5: return "Muzik";
            }
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[HATA] Gecersiz giris. 1-5 arasinda bir sayi girmelisiniz." << endl;
    }
}

// Ana menüyü göster
void anaMenuGoster() {
    cout << "\n===============================================" << endl;
    cout << "        EDUFLOW - DIJITAL EGITIM PLATFORMU" << endl;
    cout << "===============================================" << endl;
    cout << "1. Modul 1 Islevsellikleri (Kayit Yonetimi)" << endl;
    cout << "2. Modul 2 Islevsellikleri (Operasyon Gunlugu)" << endl;
    cout << "3. Modul 3 Islevsellikleri (Stack)" << endl;
    cout << "4. Modul 4 Islevsellikleri (Queue)" << endl;
    cout << "5. Modul 5 Tree Islevsellikleri" << endl;
    cout << "6. Modul 6 Hash Islevsellikleri" << endl;
    cout << "7. Modul 7 Veri Sikistirma" << endl;
    cout << "8. Modul 8 Performans ve Dizi Analizi" << endl;
    cout << "===============================================" << endl;
    cout << "0. Cikis" << endl;
    cout << "===============================================" << endl;
    cout << "Seciminiz: ";
}

int main() {
    // Liste başlangıçları
    Kayit* kayitBas = NULL;
    LogKaydi* logBas = NULL;
    StackIslem* stackUst = NULL;
    Talep* talepBas = NULL;
    int sonIslenenLogID = 0;

    // Ağaç yapıları
    AgacDugumu* tarihAgaci = NULL;
    AgacDugumu* oncelikAgaci = NULL;

    // Hash Tablosu
    HashTablosu* hashTablosu = NULL;
    PerformansDurumu performansDurumu;
    performansDurumuBaslat(&performansDurumu);

    // Değişkenler
    int secim;
    string baslik, kategori, eskiBaslik, yeniBaslik, yeniKategori, not_, tarih1, tarih2;
    float boyut, puan, yeniBoyut, minPuan, maxPuan;
    int id, oncelikInt, islemInt, altSecim, yil, sayac;
    int hedefID;
    string hamVeri;
    SikistirmaSonucu huffmanSonuc, lzwSonuc, sfSonuc;
    Oncelik oncelik;

    do {
        anaMenuGoster();
        secim = intSec("", 0, 8);
        cin.ignore();

        switch(secim) {
            // ========== MODUL 1: KAYIT YONETIMI ==========
            case 1:
                do {
                    cout << "\n===== MODUL 1 ISLEVSELLIKLERI (KAYIT YONETIMI) =====" << endl;
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
                    cout << "11. Demo Veriler Ekle" << endl;
                    cout << "12. Tum Kayitlari Detayli Goster" << endl;
                    cout << "13. Kaydi Arsivle" << endl;
                    cout << "14. Arsivden Cikar" << endl;
                    cout << "15. Arsivdeki Kayitlari Listele" << endl;
                    cout << "16. Kaydi Revize Asamasina Al" << endl;
                    cout << "17. Revizeyi Tamamla" << endl;
                    cout << "0.  Ana menuye don" << endl;
                    altSecim = intSec("Seciminiz: ", 0, 17);
                    cin.ignore();

                    switch (altSecim) {
                        case 1: // Kayıt Ekle
                        {
                            clock_t t0 = clock();
                            cout << "\n--- KAYIT EKLE ---" << endl;
                            cout << "Baslik: "; getline(cin, baslik);
                            kategori = kategoriSec();
                            boyut = floatSec("Boyut (KB): ", 0.0, 1e9);
                            oncelikInt = intSec("Oncelik (0=Dusuk, 1=Orta, 2=Yuksek): ", 0, 2);
                            puan = puanSec();
                            int durumSecim = intSec("Durum (1=Aktif olarak kaydet, 2=Revize asamasinda baslat): ", 1, 2);
                            oncelik = (Oncelik)oncelikInt;
                            kayitBas = kayitEkle(kayitBas, &logBas, baslik, kategori, boyut, oncelik, puan);
                            if (durumSecim == 2) {
                                Kayit* sonKayit = kayitBas;
                                while (sonKayit != NULL && sonKayit->next != NULL) sonKayit = sonKayit->next;
                                if (sonKayit != NULL) {
                                    kayitBas = kaydiIslemeAl(kayitBas, &logBas, sonKayit->id);
                                }
                            }
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul1-KayitEkle", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 2: // ID'ye Göre Sil
                        {
                            clock_t t0 = clock();
                            cout << "\n--- KAYIT SIL ---" << endl;
                            id = idSec("Silinecek ID: ");
                            kayitBas = kayitSil(kayitBas, &logBas, id);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul1-KayitSil", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 3: // Başlığa Göre Güncelle
                        {
                            clock_t t0 = clock();
                            cout << "\n--- KAYIT GUNCELLE ---" << endl;
                            cout << "Eski Baslik: "; getline(cin, eskiBaslik);
                            cout << "Yeni Baslik: "; getline(cin, yeniBaslik);
                            cout << "Yeni "; yeniKategori = kategoriSec();
                            yeniBoyut = floatSec("Yeni Boyut (KB): ", 0.0, 1e9);
                            kayitBas = kayitGuncelle(kayitBas, &logBas, eskiBaslik, yeniBaslik, yeniKategori, yeniBoyut);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul1-KayitGuncelle", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 4: // Zamanlı Listele
                            zamanliListele(kayitBas);
                            break;
                        case 5: // ID'ye Göre Ara
                        {
                            clock_t t0 = clock();
                            cout << "\n--- KAYIT ARA ---" << endl;
                            id = idSec("Aranacak ID: ");
                            kayitYazdir(kayitAra(kayitBas, id));
                            erisimKaydet(&performansDurumu, id);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul1-KayitAra", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
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
                            id = idSec("Kayit ID: ");
                            cin.ignore();
                            cout << "Kritik Not: "; getline(cin, not_);
                            kayitBas = kritikNotEkle(kayitBas, &logBas, id, not_);
                            break;
                        case 10: // Kritik Kayıtları Listele
                            kritikKayitlariListele(kayitBas);
                            break;
                        case 11: // Demo Veriler
                            kayitBas = demoVerilerEkle(kayitBas, &logBas);
                            break;
                        case 12: // Tüm Kayıtları Detaylı Göster
                            tumKayitlariListele(kayitBas);
                            break;
                        case 13: // Kaydı Arşivle
                            cout << "\n--- KAYIT ARSIVLE ---" << endl;
                            id = idSec("Arsivlenecek ID: ");
                            cin.ignore();
                            kayitBas = kayitArsivle(kayitBas, &logBas, id);
                            break;
                        case 14: // Arşivden Çıkar
                            cout << "\n--- ARSIVDEN CIKAR ---" << endl;
                            id = idSec("Cikarilacak ID: ");
                            cin.ignore();
                            kayitBas = arsivdenCikar(kayitBas, &logBas, id);
                            break;
                        case 15: // Arşivdeki Kayıtları Listele
                            arsivdekiKayitlariListele(kayitBas);
                            break;
                        case 16: // Revize Asamasina Al
                            cout << "\n--- REVIZE ASAMASINA AL ---" << endl;
                            id = idSec("Kayit ID: ");
                            cin.ignore();
                            kayitBas = kaydiIslemeAl(kayitBas, &logBas, id);
                            break;
                        case 17: // Revizeyi Tamamla
                            cout << "\n--- REVIZEYI TAMAMLA ---" << endl;
                            id = idSec("Kayit ID: ");
                            cin.ignore();
                            kayitBas = islemiTamamla(kayitBas, &logBas, id);
                            break;
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 2: OPERASYON GUNLUGU ==========
            case 2:
                do {
                    cout << "\n===== MODUL 2 ISLEVSELLIKLERI (OPERASYON GUNLUGU) =====" << endl;
                    cout << "1. Kayit ID Islemlerini Listele" << endl;
                    cout << "2. Tarih Araliginda Islemler" << endl;
                    cout << "3. Gunluk Raporu Olustur" << endl;
                    cout << "4. Islem Turune Gore Listele" << endl;
                    cout << "5. Tum Loglari Goster" << endl;
                    cout << "0. Ana menuye don" << endl;
                    altSecim = intSec("Seciminiz: ", 0, 5);
                    cin.ignore();

                    switch (altSecim) {
                        case 1: // Kayıt ID İşlemlerini Listele
                        {
                            clock_t t0 = clock();
                            cout << "\n--- KAYIT ISLEMLERI ---" << endl;
                            id = idSec("Kayit ID: ");
                            cin.ignore();
                            kayitIdIslemleriniListele(logBas, id);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul2-KayitIslemleri", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 2: // Tarih Aralığında İşlemler
                        {
                            clock_t t0 = clock();
                            cout << "\n--- TARIH ARALIGINDA ISLEMLER ---" << endl;
                            cout << "Baslangic Tarihi (GG/AA/YYYY): "; getline(cin, tarih1);
                            cout << "Bitis Tarihi (GG/AA/YYYY): "; getline(cin, tarih2);
                            tarihAraligiIslemler(logBas, tarih1, tarih2);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul2-TarihAraligi", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 3: // Günlük Raporu
                        {
                            clock_t t0 = clock();
                            gunlukRaporuOlustur(logBas, kayitBas);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul2-GunlukRapor", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 4: // İşlem Türüne Göre Listele
                        {
                            clock_t t0 = clock();
                            cout << "\n--- ISLEM TURUNE GORE LISTELE ---" << endl;
                            islemInt = intSec("Islem Turu (0=EKLE, 1=SIL, 2=GUNCELLE, 3=DEQUEUE): ", 0, 3);
                            islemTuruneGoreListele(logBas, (IslemTuru)islemInt);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul2-IslemTuru", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 5: // Tüm Logları Göster
                        {
                            clock_t t0 = clock();
                            tumLoglariListele(logBas);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul2-TumLoglar", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 3: STACK ==========
            case 3:
                do {
                    cout << "\n===== MODUL 3 ISLEVSELLIKLERI (STACK) =====" << endl;
                    cout << "1. Islem push (loglardan stack guncelle)" << endl;
                    cout << "2. Undo (pop)" << endl;
                    cout << "3. Stack derinligi" << endl;
                    cout << "4. Son 10 islemi goster" << endl;
                    cout << "5. En sik islem turu analizi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim;
                    cin.ignore();

                    switch (altSecim) {
                        case 1:
                        {
                            clock_t t0 = clock();
                            loglardanStackGuncelle(&stackUst, logBas, &sonIslenenLogID);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul3-StackGuncelle", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 2:
                        {
                            clock_t t0 = clock();
                            undoPop(&stackUst, &kayitBas, &logBas);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul3-UndoPop", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 3:
                        {
                            clock_t t0 = clock();
                            cout << "[STACK] Derinlik: " << stackDerinligi(stackUst) << endl;
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul3-Derinlik", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 4:
                        {
                            clock_t t0 = clock();
                            son10IslemiGoster(stackUst);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul3-Son10", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 5:
                        {
                            clock_t t0 = clock();
                            enSikIslemTuruAnalizi(stackUst);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul3-EnSikAnaliz", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 4: QUEUE ==========
            case 4:
                do {
                    cout << "\n===== MODUL 4 ISLEVSELLIKLERI (QUEUE) =====" << endl;
                    cout << "1. Yeni talep ekle" << endl;
                    cout << "2. Oncelikli talep olustur" << endl;
                    cout << "3. Kuyrugu listele" << endl;
                    cout << "4. Ilk talebi isleme al (dequeue -> Modul 1)" << endl;
                    cout << "5. Ortalama bekleme suresi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim;
                    cin.ignore();

                    switch (altSecim) {
                        case 1:
                        {
                            clock_t t0 = clock();
                            cout << "Baslik: "; getline(cin, baslik);
                            kategori = kategoriSec();
                            boyut = floatSec("Boyut (KB): ", 0.0, 1e9);
                            oncelikInt = intSec("Oncelik (0=Dusuk, 1=Orta, 2=Yuksek): ", 0, 2);
                            puan = puanSec();
                            yeniTalepEkle(&talepBas, kategori, boyut, (Oncelik)oncelikInt, baslik, puan);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul4-YeniTalep", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 2:
                        {
                            clock_t t0 = clock();
                            cout << "Baslik: "; getline(cin, baslik);
                            kategori = kategoriSec();
                            boyut = floatSec("Boyut (KB): ", 0.0, 1e9);
                            puan = puanSec();
                            oncelikliTalepOlustur(&talepBas, kategori, boyut, baslik, puan);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul4-OncelikliTalep", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 3:
                        {
                            clock_t t0 = clock();
                            kuyruguListele(talepBas);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul4-KuyrukListele", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 4:
                        {
                            clock_t t0 = clock();
                            ilkTalebiIslemeAl(&talepBas, &kayitBas, &logBas, &stackUst);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul4-IlkTalepIslemeAl", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 5:
                        {
                            clock_t t0 = clock();
                            ortalamaBeklemeSuresiDakika(talepBas);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul4-OrtalamaBekleme", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 5: TREE ==========
            case 5:
                do {
                    cout << "\n===== MODUL 5 TREE Islevsellikleri =====" << endl;
                    cout << "1. Tarihe gore agac olustur ve listele" << endl;
                    cout << "2. Oncelik gore agac olustur ve listele" << endl;
                    cout << "3. Puan araligi filtreleme" << endl;
                    cout << "4. Agac yuksekligi ve performans bilgisi" << endl;
                    cout << "5. Tarih bazli trend analizi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    altSecim = intSec("Seciminiz: ", 0, 5);
                    cin.ignore();

                    switch (altSecim) {
                        case 1:
                        {
                            clock_t t0 = clock();
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            if (tarihAgaci != NULL) { agacTemizle(tarihAgaci); tarihAgaci = NULL; }
                            tarihAgaci = tariheGoreAgacOlustur(kayitBas);
                            {
                                int altAlt;
                                cout << "\n--- TARIH AGACI SECENEKLERI ---" << endl;
                                cout << "1. Tum kayitlari eskiden yeniye listele" << endl;
                                cout << "2. Yil/ay bazli filtrele" << endl;
                                cout << "Seciminiz: ";
                                cin >> altAlt; cin.ignore();
                                if (altAlt == 1) {
                                    cout << "\n========== TARIH AGACI (Eskiden Yeniye) ==========" << endl;
                                    cout << "  [Tarih]       ID   Baslik  (Kategori)  [Oncelik]" << endl;
                                    cout << "--------------------------------------------------" << endl;
                                    tariheGoreAgacListele(tarihAgaci);
                                    cout << "==================================================" << endl;
                                } else if (altAlt == 2) {
                                    tariheGoreFiltrele(tarihAgaci);
                                }
                            }
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul5-TarihAgaci", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 2:
                        {
                            clock_t t0 = clock();
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            if (oncelikAgaci != NULL) { agacTemizle(oncelikAgaci); oncelikAgaci = NULL; }
                            oncelikAgaci = onceligeGoreAgacOlustur(kayitBas);
                            onceligeGoreAgacYazdir(oncelikAgaci);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul5-OncelikAgaci", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 3:
                        {
                            clock_t t0 = clock();
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            cout << "\n--- PUAN BST FILTRELEME ---" << endl;
                            cout << "Minimum Puan (0.0 - 5.0): "; cin >> minPuan;
                            cout << "Maksimum Puan (0.0 - 5.0): "; cin >> maxPuan;
                            cin.ignore();
                            puanAraligiFiltrele(kayitBas, minPuan, maxPuan);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul5-PuanFiltre", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 4:
                        {
                            clock_t t0 = clock();
                            if (tarihAgaci == NULL && kayitBas != NULL) {
                                tarihAgaci = tariheGoreAgacOlustur(kayitBas);
                                cout << "[BILGI] Performans icin tarih agaci otomatik olusturuldu." << endl;
                            }
                            agacPerformansBilgisi(tarihAgaci);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul5-AgacPerformans", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 5:
                        {
                            clock_t t0 = clock();
                            cout << "\n--- TARIH BAZLI TREND ANALIZI ---" << endl;
                            cout << "Esik Yil (ornek: 2020, 2023): "; cin >> yil;
                            cin.ignore();
                            tarihBazliTrendAnalizi(kayitBas, yil);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul5-TrendAnalizi", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 6: HASH ANALIZ MOTORU ==========
            case 6:
                do {
                    cout << "\n===== MODUL 6 HASH ANALIZ MOTORU =====" << endl;
                    cout << "1. Hash tablosu olustur" << endl;
                    cout << "2. ID'ye gore ortalama puani bul" << endl;
                    cout << "3. Kategoriye gore kayit sayisini bul" << endl;
                    cout << "4. Tum kategorileri analiz et" << endl;
                    cout << "5. Oncelik bazli yogunluk analizi" << endl;
                    cout << "6. Hash tablo performans bilgisi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    altSecim = intSec("Seciminiz: ", 0, 6);
                    cin.ignore();

                    switch (altSecim) {
                        case 1:
                        {
                            clock_t t0 = clock();
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            if (hashTablosu != NULL) { hashTablosuTemizle(hashTablosu); hashTablosu = NULL; }
                            hashTablosu = hashTablosuOlustur(kayitBas);
                            cout << "[BILGI] Hash tablosu olusturuldu (boyut: " << HASH_BOYUTU << ")" << endl;
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-HashOlustur", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 2:
                        {
                            clock_t t0 = clock();
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            id = intSec("\nKayit ID girin: ", 1, 999999);
                            cin.ignore();
                            idyeGoreOrtalamaPuanBul(hashTablosu, id);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-IdOrtalamaPuan", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 3:
                        {
                            clock_t t0 = clock();
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            {
                                cout << "\n--- KATEGORI SECIN ---" << endl;
                                cout << "1. Yazilim" << endl;
                                cout << "2. Tasarim" << endl;
                                cout << "3. Isletme" << endl;
                                cout << "4. Dil" << endl;
                                cout << "5. Muzik" << endl;
                                int katSecim = intSec("Seciminiz (1-5): ", 1, 5);
                                string katList[] = {"Yazilim", "Tasarim", "Isletme", "Dil", "Muzik"};
                                kategori = katList[katSecim - 1];
                                sayac = kategoriyeSayiBul(hashTablosu, kategori);
                                cout << "[BILGI] '" << kategori << "' kategorisinde " << sayac << " kayit var." << endl;
                            }
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-KategoriSayisi", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 4:
                        {
                            clock_t t0 = clock();
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            tumKategorileriAnaliz(hashTablosu);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-TumKategoriAnaliz", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 5:
                        {
                            clock_t t0 = clock();
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            onceligeGoreYogunlukAnalizi(hashTablosu);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-OncelikYogunluk", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 6:
                        {
                            clock_t t0 = clock();
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            hashPerformansBilgisi(hashTablosu);
                            clock_t t1 = clock();
                            olcumEkle(&performansDurumu, "Modul6-HashPerformans", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                            break;
                        }

                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 7: VERI SIKISTIRMA ==========
            case 7:
                do {
                    cout << "\n===== MODUL 7 VERI SIKISTIRMA =====" << endl;
                    cout << "1. Frekans analizi (Modul 1 verisi)" << endl;
                    cout << "2. Huffman sikistirma analizi" << endl;
                    cout << "3. LZW sikistirma analizi" << endl;
                    cout << "4. Shannon-Fano sikistirma analizi" << endl;
                    cout << "5. Uc algoritmayi karsilastir" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim; cin.ignore();

                    hamVeri = kayitlardanHamVeriUret(kayitBas);
                    if (hamVeri.empty() && altSecim != 0) {
                        cout << "[BILGI] Modul 1 kayit listesi bos. Once kayit ekleyin." << endl;
                        continue;
                    }

                    switch (altSecim) {
                        case 1: {
                            KarakterFrekansi frekanslar[256];
                            int adet = frekansAnalizi(hamVeri, frekanslar, 256);
                            frekansTablosuYazdir(frekanslar, adet);
                            break;
                        }
                        case 2:
                            huffmanSonuc = huffmanSikistir(hamVeri);
                            sikistirmaSonucuYazdir(huffmanSonuc);
                            //secilenYontemOranKarsilastirmaYazdir(huffmanSonuc);
                            olcumEkle(&performansDurumu, "Modul7-Huffman", huffmanSonuc.sureMs);
                            break;
                        case 3:
                            lzwSonuc = lzwSikistir(hamVeri);
                            sikistirmaSonucuYazdir(lzwSonuc);
                            //secilenYontemOranKarsilastirmaYazdir(lzwSonuc);
                            olcumEkle(&performansDurumu, "Modul7-LZW", lzwSonuc.sureMs);
                            break;
                        case 4:
                            sfSonuc = shannonFanoSikistir(hamVeri);
                            sikistirmaSonucuYazdir(sfSonuc);
                            //secilenYontemOranKarsilastirmaYazdir(sfSonuc);
                            olcumEkle(&performansDurumu, "Modul7-ShannonFano", sfSonuc.sureMs);
                            break;
                        case 5:
                            huffmanSonuc = huffmanSikistir(hamVeri);
                            lzwSonuc = lzwSikistir(hamVeri);
                            sfSonuc = shannonFanoSikistir(hamVeri);
                            sikistirmaKarsilastirmaYazdir(huffmanSonuc, lzwSonuc, sfSonuc);
                            olcumEkle(&performansDurumu, "Modul7-Huffman", huffmanSonuc.sureMs);
                            olcumEkle(&performansDurumu, "Modul7-LZW", lzwSonuc.sureMs);
                            olcumEkle(&performansDurumu, "Modul7-ShannonFano", sfSonuc.sureMs);
                            break;
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 8: PERFORMANS ==========
            case 8:
                do {
                    cout << "\n===== MODUL 8 PERFORMANS & DIZI ANALIZI =====" << endl;
                    cout << "1. Son 10 erisilen kaydi goster" << endl;
                    cout << "2. Linear Search vs Binary Search" << endl;
                    cout << "3. Tum olcumleri listele (ms)" << endl;
                    cout << "4. Ortalama sureleri hesapla" << endl;
                    cout << "5. En hizli veri yapisi/algoritma onerisi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim; cin.ignore();

                    switch (altSecim) {
                        case 1:
                            son10ErisimYazdir(&performansDurumu);
                            break;
                        case 2:
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            cout << "Aranacak ID: ";
                            cin >> hedefID; cin.ignore();
                            linearBinaryKarsilastir(kayitBas, hedefID, &performansDurumu);
                            erisimKaydet(&performansDurumu, hedefID);
                            break;
                        case 3:
                            tumOlcumleriYazdir(&performansDurumu);
                            break;
                        case 4:
                            ortalamaSureleriYazdir(&performansDurumu);
                            break;
                        case 5:
                            enHizliYapiOner(&performansDurumu);
                            break;
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
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
    stackTemizle(stackUst);
    kuyrukTemizle(talepBas);
    if (tarihAgaci   != NULL) agacTemizle(tarihAgaci);
    if (oncelikAgaci != NULL) agacTemizle(oncelikAgaci);
    if (hashTablosu  != NULL) hashTablosuTemizle(hashTablosu);
    performansDurumuTemizle(&performansDurumu);

    cout << "Bay bay!" << endl;
    return 0;
}
