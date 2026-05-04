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
    cout << "18. Modul 3 Islevsellikleri" << endl;
    cout << "19. Modul 4 Islevsellikleri" << endl;
    cout << "20. Modul 5 Tree Islevsellikleri" << endl;
    cout << "21. Modul 6 Hash Islevsellikleri" << endl;
    cout << "22. Modul 7 Veri Sikistirma" << endl;
    cout << "23. Modul 8 Performans ve Dizi Analizi" << endl;
    cout << "===============================================" << endl;
    cout << "0.  Cikis" << endl;
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
            {
                clock_t t0 = clock();
                cout << "\n--- KAYIT EKLE ---" << endl;
                cout << "Baslik: "; getline(cin, baslik);
                cout << "Kategori (Yazilim/Tasarim/Isletme/Dil/Muzik): "; getline(cin, kategori);
                cout << "Boyut (KB): "; cin >> boyut;
                cout << "Oncelik (0=Dusuk, 1=Orta, 2=Yuksek): "; cin >> oncelikInt;
                cout << "Ortalama Puan (0-5): "; cin >> puan;
                oncelik = (Oncelik)oncelikInt;
                kayitBas = kayitEkle(kayitBas, &logBas, baslik, kategori, boyut, oncelik, puan);
                clock_t t1 = clock();
                olcumEkle(&performansDurumu, "Modul1-KayitEkle", 1000.0 * (t1 - t0) / CLOCKS_PER_SEC);
                break;
            }
                
            case 2: // ID'ye Göre Sil
            {
                clock_t t0 = clock();
                cout << "\n--- KAYIT SIL ---" << endl;
                cout << "Silinecek ID: "; cin >> id;
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
                cout << "Yeni Kategori: "; getline(cin, yeniKategori);
                cout << "Yeni Boyut (KB): "; cin >> yeniBoyut;
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
                cout << "Aranacak ID: "; cin >> id;
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

            case 18: // Modul 3 Islevsellikleri
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
                            loglardanStackGuncelle(&stackUst, logBas, &sonIslenenLogID);
                            break;
                        case 2:
                            undoPop(&stackUst, &kayitBas, &logBas);
                            break;
                        case 3:
                            cout << "[STACK] Derinlik: " << stackDerinligi(stackUst) << endl;
                            break;
                        case 4:
                            son10IslemiGoster(stackUst);
                            break;
                        case 5:
                            enSikIslemTuruAnalizi(stackUst);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            case 19: // Modul 4 Islevsellikleri
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
                            cout << "Baslik: "; getline(cin, baslik);
                            cout << "Kategori: "; getline(cin, kategori);
                            cout << "Boyut (KB): "; cin >> boyut;
                            cout << "Oncelik (0=Dusuk, 1=Orta, 2=Yuksek): "; cin >> oncelikInt;
                            cout << "Ortalama Puan (0-5): "; cin >> puan;
                            cin.ignore();
                            yeniTalepEkle(&talepBas, kategori, boyut, (Oncelik)oncelikInt, baslik, puan);
                            break;
                        case 2:
                            cout << "Baslik: "; getline(cin, baslik);
                            cout << "Kategori: "; getline(cin, kategori);
                            cout << "Boyut (KB): "; cin >> boyut;
                            cout << "Ortalama Puan (0-5): "; cin >> puan;
                            cin.ignore();
                            oncelikliTalepOlustur(&talepBas, kategori, boyut, baslik, puan);
                            break;
                        case 3:
                            kuyruguListele(talepBas);
                            break;
                        case 4:
                            ilkTalebiIslemeAl(&talepBas, &kayitBas, &logBas, &stackUst);
                            break;
                        case 5:
                            ortalamaBeklemeSuresiDakika(talepBas);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 5: TREE ==========
            case 20:
                do {
                    cout << "\n===== MODUL 5 TREE Islevsellikleri =====" << endl;
                    cout << "1. Tarihe gore agac olustur ve listele" << endl;
                    cout << "2. Oncelik gore agac olustur ve listele" << endl;
                    cout << "3. Puan araligi filtreleme" << endl;
                    cout << "4. Agac yuksekligi ve performans bilgisi" << endl;
                    cout << "5. Tarih bazli trend analizi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim; cin.ignore();
 
                    switch (altSecim) {
                        case 1:
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
                            break;
 
                        case 2:
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            if (oncelikAgaci != NULL) { agacTemizle(oncelikAgaci); oncelikAgaci = NULL; }
                            oncelikAgaci = onceligeGoreAgacOlustur(kayitBas);
                            onceligeGoreAgacYazdir(oncelikAgaci);
                            break;
 
                        case 3:
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            cout << "\n--- PUAN BST FILTRELEME ---" << endl;
                            cout << "Minimum Puan (0.0 - 5.0): "; cin >> minPuan;
                            cout << "Maksimum Puan (0.0 - 5.0): "; cin >> maxPuan;
                            cin.ignore();
                            puanAraligiFiltrele(kayitBas, minPuan, maxPuan);
                            break;
 
                        case 4:
                            if (tarihAgaci == NULL && kayitBas != NULL) {
                                tarihAgaci = tariheGoreAgacOlustur(kayitBas);
                                cout << "[BILGI] Performans icin tarih agaci otomatik olusturuldu." << endl;
                            }
                            agacPerformansBilgisi(tarihAgaci);
                            break;
 
                        case 5:
                            cout << "\n--- TARIH BAZLI TREND ANALIZI ---" << endl;
                            cout << "Esik Yil (ornek: 2020, 2023): "; cin >> yil;
                            cin.ignore();
                            tarihBazliTrendAnalizi(kayitBas, yil);
                            break;
 
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;
            
            // ========== MODUL 6: HASH ANALIZ MOTORU ==========
            case 21:
                do {
                    cout << "\n===== MODUL 6 HASH ANALIZ MOTORU =====" << endl;
                    cout << "1. Hash tablosu olustur" << endl;
                    cout << "2. ID'ye gore ortalama puani bul" << endl;
                    cout << "3. Kategoriye gore kayit sayisini bul" << endl;
                    cout << "4. Tum kategorileri analiz et" << endl;
                    cout << "5. Oncelik bazli yogunluk analizi" << endl;
                    cout << "6. Hash tablo performans bilgisi" << endl;
                    cout << "0. Ana menuye don" << endl;
                    cout << "Seciminiz: ";
                    cin >> altSecim; cin.ignore();
                    
                    switch (altSecim) {
                        case 1:
                            if (kayitBas == NULL) {
                                cout << "[BILGI] Kayit listesi bos. Once kayit ekleyin." << endl;
                                break;
                            }
                            if (hashTablosu != NULL) { hashTablosuTemizle(hashTablosu); hashTablosu = NULL; }
                            hashTablosu = hashTablosuOlustur(kayitBas);
                            cout << "[BILGI] Hash tablosu olusturuldu (boyut: " << HASH_BOYUTU << ")" << endl;
                            break;
                        
                        case 2:
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            cout << "\nKayit ID girin: "; cin >> id;
                            cin.ignore();
                            idyeGoreOrtalamaPuanBul(hashTablosu, id);
                            break;
                        
                        case 3:
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            cout << "\nKategori (Yazilim/Tasarim/Isletme/Dil/Muzik): ";
                            getline(cin, kategori);
                            sayac = kategoriyeSayiBul(hashTablosu, kategori);
                            cout << "[BILGI] '" << kategori << "' kategorisinde " << sayac << " kayit var." << endl;
                            break;
                        
                        case 4:
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            tumKategorileriAnaliz(hashTablosu);
                            break;
                        
                        case 5:
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            onceligeGoreYogunlukAnalizi(hashTablosu);
                            break;
                        
                        case 6:
                            if (hashTablosu == NULL) {
                                cout << "[BILGI] Hash tablosu bos. Once 'Hash tablosu olustur' secenegini calistirin." << endl;
                                break;
                            }
                            hashPerformansBilgisi(hashTablosu);
                            break;
                        
                        case 0: break;
                        default: cout << "[HATA] Gecersiz secim!" << endl;
                    }
                } while (altSecim != 0);
                break;

            // ========== MODUL 7: VERI SIKISTIRMA ==========
            case 22:
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
                            olcumEkle(&performansDurumu, "Modul7-Huffman", huffmanSonuc.sureMs);
                            break;
                        case 3:
                            lzwSonuc = lzwSikistir(hamVeri);
                            sikistirmaSonucuYazdir(lzwSonuc);
                            olcumEkle(&performansDurumu, "Modul7-LZW", lzwSonuc.sureMs);
                            break;
                        case 4:
                            sfSonuc = shannonFanoSikistir(hamVeri);
                            sikistirmaSonucuYazdir(sfSonuc);
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
            case 23:
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
