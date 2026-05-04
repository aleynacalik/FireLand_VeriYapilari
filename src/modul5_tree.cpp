#include "../include/modul5_tree.h"
#include <iostream>
#include <string>

using namespace std;
// ==================== YARDIMCI FONKSIYONLAR ====================
 
AgacDugumu* yeniDugumOlustur(Kayit* k) {
    AgacDugumu* yeni = new AgacDugumu();
    yeni->kayit = k;
    yeni->sol   = NULL;
    yeni->sag   = NULL;
    return yeni;
}
 
// Agaci bellek temizleme kayitlari silmez, sadece agac dugumlerini)
void agacTemizle(AgacDugumu* kok) {
    if (kok == NULL) return;
    agacTemizle(kok->sol);
    agacTemizle(kok->sag);
    delete kok;
}
 
// Agac gorsellestirmesi icin girinti
void girisBoslukluYazdir(int seviye) {
    for (int i = 0; i < seviye; i++) cout << "    ";
}
 
// Tarih stringinden YYYYMMDDHHMMSS formatinda karsilastirma anahtari uret
// Ornek: "27/04/2026 14:30:45" -> "20260427143045"
string tarihAnahtarUret(const string& tarih) {
    // Tarih formati: "DD/MM/YYYY HH:MM:SS"
    if (tarih.length() < 19) return "00000000000000";
    string yil    = tarih.substr(6, 4);    // YYYY
    string ay     = tarih.substr(3, 2);    // MM
    string gun    = tarih.substr(0, 2);    // DD
    string saat   = tarih.substr(11, 2);   // HH
    string dakika = tarih.substr(14, 2);   // MM
    string saniye = tarih.substr(17, 2);   // SS
    return yil + ay + gun + saat + dakika + saniye;
}
 
// ==================== 1. ISLEVSELLIK ====================
// Tarihe gore BST olustur ve yil/ay bazli filtrele
//
// BST kurma kurali (hoca slaytindan):
//   - Eklenecek dugumun anahtari kokten KUCUKSE  -> SOL alt agaca dal
//   - Eklenecek dugumun anahtari kokten BUYUKSE  -> SAG alt agaca dal
//   - Boş bir yere gelindiğinde yeni dugumu oraya bagla
//
// Tarih anahtari: "DD/MM/YYYY HH:MM:SS" -> "YYYYMMDDHHMMSS" stringine donusturulur
// Boylece string karsilastirmasi kronolojik siraya esit olur.
// Ornek: "26/04/2026 14:30:45" -> "20260426143045"
//        "01/01/2024 10:15:30" -> "20240101101530"  <- daha kucuk -> SOLA gider (daha eski)
 
AgacDugumu* tariheGoreEkle(AgacDugumu* kok, Kayit* k) {
    // Temel durum: bos dugume ulastik, yeni dugumu buraya bagla
    if (kok == NULL) return yeniDugumOlustur(k);
 
    // Karsilastirilacak tarih anahtarlarini uret (YYYYMMDDHHMMSS formati)
    string yeniAnahtar = tarihAnahtarUret(k->tarih);
    string kokAnahtar  = tarihAnahtarUret(kok->kayit->tarih);
 
    // Hoca slaytindaki dugum ekleme algoritmasi:
    // "kucuk olan deger sola, buyuk olan deger saga eklenir"
    if (yeniAnahtar <= kokAnahtar)
        kok->sol = tariheGoreEkle(kok->sol, k);  // Daha eski -> sol alt agaca
    else
        kok->sag = tariheGoreEkle(kok->sag, k);  // Daha yeni -> sag alt agaca
 
    return kok; // Guncellenmis kok adresini geri dondur (rekürsif yapi)
}
 
// Modul 1'deki tum kayitlari BST'ye ekleyerek tarih agacini olusturur
AgacDugumu* tariheGoreAgacOlustur(Kayit* bas) {
    AgacDugumu* kok = NULL; // Bos agac ile basla
    Kayit* iter = bas;
    while (iter != NULL) {
        // Her kayit icin rekürsif ekleme: kucuk sola, buyuk saga
        kok = tariheGoreEkle(kok, iter);
        iter = iter->next;
    }
    return kok;
}
 
// INORDER (Ortada-kok) gezinti: Sol -> Kok -> Sag
// Hoca slaytina gore InOrder gezinti siralanmis listeyi verir.
// Bu agacta InOrder = eskiden yeniye kronolojik sira demektir.
void tariheGoreAgacListele(AgacDugumu* kok) {
    if (kok == NULL) return;                      // Bos dugum: geri don
    tariheGoreAgacListele(kok->sol);              // Once sol alt agaci gez (daha eski)
    // Kok dugumundeki bilgiyi yazdir
    cout << "  [" << kok->kayit->tarih.substr(0,10) << "]"
         << "  ID:" << kok->kayit->id
         << "  " << kok->kayit->baslik
         << "  (" << kok->kayit->kategori << ")"
         << "  [" << oncelikToString(kok->kayit->oncelik) << "]" << endl;
    tariheGoreAgacListele(kok->sag);              // Sonra sag alt agaci gez (daha yeni)
}
 
// YIL BAZLI FILTRELEME:
// Inorder gezinti yaparak sadece istenen yila ait kayitlari ekrana yazar.
// Tum dugumler ziyaret edilir (O(N) karmasiklik - hoca slaytindaki dolas ma alg.)
void yilaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil) {
    if (kok == NULL) return;
    yilaGoreFiltreleYazdir(kok->sol, yil);        // Sol alt agaci gez
    // Tarih formati: "GG/AA/YYYY SS:DD:SS" -> yil kismi index 6, uzunluk 4
    string kayitYili = kok->kayit->tarih.substr(6, 4);
    if (kayitYili == yil) {                        // Yil eslesmesi varsa yazdir
        cout << "  [" << kok->kayit->tarih.substr(0,10) << "]"
             << "  ID:" << kok->kayit->id
             << "  " << kok->kayit->baslik
             << "  (" << kok->kayit->kategori << ")"
             << "  Puan:" << kok->kayit->ortalamaPuan << "/5.0" << endl;
    }
    yilaGoreFiltreleYazdir(kok->sag, yil);        // Sag alt agaci gez
}
 
// AY BAZLI FILTRELEME:
// Inorder gezinti ile hem yil hem ay eslesmesi aranan kayitlari yazdirir.
// Tarih formati: "GG/AA/YYYY" -> ay index 3, yil index 6
void ayaGoreFiltreleYazdir(AgacDugumu* kok, const string& yil, const string& ay) {
    if (kok == NULL) return;
    ayaGoreFiltreleYazdir(kok->sol, yil, ay);
    string kayitAy  = kok->kayit->tarih.substr(3, 2); // AA
    string kayitYil = kok->kayit->tarih.substr(6, 4); // YYYY
    if (kayitYil == yil && kayitAy == ay) {
        cout << "  [" << kok->kayit->tarih.substr(0,10) << "]"
             << "  ID:" << kok->kayit->id
             << "  " << kok->kayit->baslik
             << "  (" << kok->kayit->kategori << ")"
             << "  Puan:" << kok->kayit->ortalamaPuan << "/5.0" << endl;
    }
    ayaGoreFiltreleYazdir(kok->sag, yil, ay);
}
 
// Kullaniciya secim sunarak yil veya ay bazli filtreleme menusunu calistir
void tariheGoreFiltrele(AgacDugumu* kok) {
    if (kok == NULL) {
        cout << "[BILGI] Agac bos. Once 'Tarihe gore agac olustur' secenegini calistirin." << endl;
        return;
    }
 
    cout << "\n--- TARIH BAZLI FILTRELEME ---" << endl;
    cout << "1. Yil bazli filtrele  (ornek: 2025)" << endl;
    cout << "2. Ay bazli filtrele   (ornek: Nisan 2025)" << endl;
    cout << "Seciminiz: ";
 
    int secim;
    cin >> secim;
    cin.ignore();
 
    if (secim == 1) {
        cout << "Yil girin (YYYY): ";
        string yil;
        cin >> yil; cin.ignore();
 
        cout << "\n========== " << yil << " YILINA AIT KAYITLAR ==========" << endl;
        int sayac = 0;
 
        // Kaç kayıt bulunduğunu saymak için geçici bir lambda yerine tekrar gezinti
        // (C++98 uyumlu olsun diye sayaci parametre olarak geçmiyoruz, 
        //  önce yazdir sonra ayri say)
        yilaGoreFiltreleYazdir(kok, yil);
 
        // Toplam sayısı için tekrar gez
        // (basit bir yardimci fonksiyon daha temiz olur)
        cout << "=================================================" << endl;
 
    } else if (secim == 2) {
        cout << "Yil girin  (YYYY): ";
        string yil; cin >> yil; cin.ignore();
        cout << "Ay girin   (01-12): ";
        string ay; cin >> ay; cin.ignore();
 
        // Tek haneli ay girilirse basa 0 ekle
        if (ay.length() == 1) ay = "0" + ay;
 
        // Ay adini bul
        string ayAdi[] = {"", "Ocak","Subat","Mart","Nisan","Mayis","Haziran",
                           "Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};
        int ayInt = 0;
        for (int i = 0; i < 2; i++) {
            if (ay[i] >= '0' && ay[i] <= '9')
                ayInt = ayInt * 10 + (ay[i] - '0');
        }
        string ayAdiStr = (ayInt >= 1 && ayInt <= 12) ? ayAdi[ayInt] : "?";
 
        cout << "\n========== " << ayAdiStr << " " << yil << " KAYITLARI ==========" << endl;
        ayaGoreFiltreleYazdir(kok, yil, ay);
        cout << "=================================================" << endl;
 
    } else {
        cout << "[HATA] Gecersiz secim." << endl;
    }
}
 
// ==================== 2. ISLEVSELLIK ====================
// Oncelik gore BST olustur (sol=dusuk, sag=yuksek)
// Ayni oncelikte puana gore ayirt edilir
 
AgacDugumu* onceligeGoreEkle(AgacDugumu* kok, Kayit* k) {
    if (kok == NULL) return yeniDugumOlustur(k);
 
    int yeniSkor = (int)k->oncelik * 100 + (int)(k->ortalamaPuan * 10);
    int kokSkor  = (int)kok->kayit->oncelik * 100 + (int)(kok->kayit->ortalamaPuan * 10);
 
    if (yeniSkor <= kokSkor)
        kok->sol = onceligeGoreEkle(kok->sol, k);
    else
        kok->sag = onceligeGoreEkle(kok->sag, k);
 
    return kok;
}
 
AgacDugumu* onceligeGoreAgacOlustur(Kayit* bas) {
    AgacDugumu* kok = NULL;
    Kayit* iter = bas;
    while (iter != NULL) {
        kok = onceligeGoreEkle(kok, iter);
        iter = iter->next;
    }
    return kok;
}
 
// Ters inorder (buyukten kucuge = yuksek oncelikliler once)
void onceligeGoreAgacListele(AgacDugumu* kok, int seviye) {
    if (kok == NULL) return;
    onceligeGoreAgacListele(kok->sag, seviye + 1);
 
    girisBoslukluYazdir(seviye);
    string oncelikStr = oncelikToString(kok->kayit->oncelik);
    cout << "[" << oncelikStr << "] "
         << kok->kayit->baslik
         << "  (Puan: " << kok->kayit->ortalamaPuan << "/5.0)"
         << "  ID:" << kok->kayit->id << endl;
 
    onceligeGoreAgacListele(kok->sol, seviye + 1);
}
 
void onceligeGoreAgacYazdir(AgacDugumu* kok) {
    cout << "\n========== ONCELIK AGACI (Yuksek -> Dusuk) ==========" << endl;
    cout << "(Girintili gosterim: ust satirlar daha yuksek oncelikli)" << endl;
    cout << "------------------------------------------------------" << endl;
    onceligeGoreAgacListele(kok, 0);
    cout << "======================================================" << endl;
}
 
// ==================== 3. ISLEVSELLIK ====================
// Puan araligi filtreleme - Puan BST'si kurarak filtreleme
//
// BST kurma kurali:
//   Dusuk puan -> sola,  Yuksek puan -> saga
// Boylece InOrder gezinti puanlari kucukten buyuge verir.
//
// Filtreleme avantaji:
//   minPuan'dan kucuk olan tum sol alt agaci atlayabiliriz.
//   Bu sayede her kaydi kontrol etmek zorunda kalmayiz.
 
// Puan BST'sine dugum ekle (kucuk sola, buyuk saga)
AgacDugumu* puanaGoreEkle(AgacDugumu* kok, Kayit* k) {
    if (kok == NULL) return yeniDugumOlustur(k);
    // Hocanin slaytindaki ekleme algoritmasi:
    // kucuk olan deger sola, buyuk olan deger saga
    if (k->ortalamaPuan <= kok->kayit->ortalamaPuan)
        kok->sol = puanaGoreEkle(kok->sol, k);
    else
        kok->sag = puanaGoreEkle(kok->sag, k);
    return kok;
}
 
// Puan BST'si olustur - Modul 1 listesinden tum kayitlari ekle
AgacDugumu* puanAgaciOlustur(Kayit* bas) {
    AgacDugumu* kok = NULL;
    Kayit* iter = bas;
    while (iter != NULL) {
        kok = puanaGoreEkle(kok, iter);
        iter = iter->next;
    }
    return kok;
}
 
// InOrder gezinti ile puan araligindaki kayitlari yazdir
// BST avantaji: minPuan'dan kucuk sol alt agaci atliyoruz
void puanAraligiGezinti(AgacDugumu* kok, float minPuan, float maxPuan, int& bulunan) {
    if (kok == NULL) return;
 
    // Sol alt agaci yalnizca minPuan ihtimali varsa gez
    // (BST'de sol taraf her zaman daha kucuk puana sahip)
    if (kok->kayit->ortalamaPuan > minPuan)
        puanAraligiGezinti(kok->sol, minPuan, maxPuan, bulunan);
 
    // Kok dugumu aralikta mi kontrol et
    if (kok->kayit->ortalamaPuan >= minPuan && kok->kayit->ortalamaPuan <= maxPuan) {
        cout << "  ID:" << kok->kayit->id
             << "  Baslik: " << kok->kayit->baslik
             << "  Puan: " << kok->kayit->ortalamaPuan << "/5.0"
             << "  [" << oncelikToString(kok->kayit->oncelik) << "]" << endl;
        bulunan++;
    }
 
    // Sag alt agaci yalnizca maxPuan ihtimali varsa gez
    if (kok->kayit->ortalamaPuan < maxPuan)
        puanAraligiGezinti(kok->sag, minPuan, maxPuan, bulunan);
}
 
// Ana filtreleme fonksiyonu - BST kurar ve aralik filtrelemesi yapar
void puanAraligiFiltrele(Kayit* bas, float minPuan, float maxPuan) {
    if (bas == NULL) {
        cout << "[BILGI] Kayit listesi bos." << endl;
        return;
    }
    if (minPuan > maxPuan) {
        cout << "[HATA] Minimum puan, maksimum puandan buyuk olamaz!" << endl;
        return;
    }
    if (minPuan < 0.0f || maxPuan > 5.0f) {
        cout << "[HATA] Puan araligi 0.0 - 5.0 arasinda olmalidir!" << endl;
        return;
    }
 
    // Once puan BST'sini olustur
    AgacDugumu* puanKok = puanAgaciOlustur(bas);
 
    cout << "\n========== PUAN BST - ARALIK FILTRELEME ==========" << endl;
    cout << "Aralik: " << minPuan << " - " << maxPuan << endl;
    cout << "---------------------------------------------------" << endl;
 
    int bulunan = 0;
    puanAraligiGezinti(puanKok, minPuan, maxPuan, bulunan);
 
    if (bulunan == 0)
        cout << "  Bu puan araliginda kayit bulunamadi." << endl;
    else
        cout << "---------------------------------------------------" << endl
             << "  Toplam " << bulunan << " kayit bulundu." << endl;
 
    cout << "===================================================" << endl;
 
    // Gecici agaci temizle (Modul 1 kayitlarini silmez, sadece agac dugumlerini)
    agacTemizle(puanKok);
}
 
// ==================== 4. ISLEVSELLIK ====================
// Agac yuksekligi ve performans bilgisi
 
int agacYuksekligi(AgacDugumu* kok) {
    if (kok == NULL) return 0;
    int solYukseklik = agacYuksekligi(kok->sol);
    int sagYukseklik = agacYuksekligi(kok->sag);
    return 1 + (solYukseklik > sagYukseklik ? solYukseklik : sagYukseklik);
}
 
int dugumSayisi(AgacDugumu* kok) {
    if (kok == NULL) return 0;
    return 1 + dugumSayisi(kok->sol) + dugumSayisi(kok->sag);
}
 
int yaprakSayisi(AgacDugumu* kok) {
    if (kok == NULL) return 0;
    if (kok->sol == NULL && kok->sag == NULL) return 1;
    return yaprakSayisi(kok->sol) + yaprakSayisi(kok->sag);
}
 
void agacPerformansBilgisi(AgacDugumu* kok) {
    if (kok == NULL) {
        cout << "[BILGI] Agac bos. Once agac olusturun." << endl;
        return;
    }
 
    int yukseklik = agacYuksekligi(kok);
    int toplam    = dugumSayisi(kok);
    int yaprak    = yaprakSayisi(kok);
    int dahili    = toplam - yaprak;
 
    // Ideal BST yuksekligi: log2(n) + 1
    // log2 hesabi donguylle
    int idealYukseklik = 1;
    int temp = toplam;
    while (temp > 1) { temp /= 2; idealYukseklik++; }
 
    cout << "\n========== AGAC PERFORMANS BILGISI ==========" << endl;
    cout << "Toplam Dugum Sayisi  : " << toplam << endl;
    cout << "Agac Yuksekligi      : " << yukseklik << endl;
    cout << "Yaprak Dugum Sayisi  : " << yaprak << endl;
    cout << "Dahili Dugum Sayisi  : " << dahili << endl;
    cout << "Ideal BST Yuksekligi : " << idealYukseklik << " (log2(" << toplam << ")+1)" << endl;
    cout << "----------------------------------------------" << endl;
 
    if (yukseklik <= idealYukseklik + 1) {
        cout << "Performans Durumu    : DENGELI - Arama O(log n)" << endl;
    } else if (yukseklik <= idealYukseklik * 2) {
        cout << "Performans Durumu    : ORTA - Arama yaklasik O(log n)" << endl;
    } else {
        cout << "Performans Durumu    : DENGESIZ - Arama O(n)'e yaklasabilir" << endl;
        cout << "Oneri: Kayitlar sirali eklendiginde agac dengesizlesir." << endl;
    }
    cout << "==============================================" << endl;
}
 
// ==================== 5. ISLEVSELLIK ====================
// Belirlenen yil oncesi / sonrasi trend analizi
// EduFlow icin varsayilan yil: 2020 (COVID donemini baz alir)
 
void tarihBazliTrendAnalizi(Kayit* bas, int yil) {
    if (bas == NULL) {
        cout << "[BILGI] Kayit listesi bos." << endl;
        return;
    }
 
    int oncesiSayisi = 0, sonrasiSayisi = 0;
    float oncesiToplam = 0.0f, sonrasiToplam = 0.0f;
    int oncesiYuksek = 0, sonrasiYuksek = 0;
 
    Kayit* iter = bas;
    while (iter != NULL) {
        // Tarihin yilini cikart: "GG/AA/YYYY ..." formatindan
        int kayitYili = 0;
        if (iter->tarih.length() >= 10) {
            kayitYili = (iter->tarih[6]  - '0') * 1000 +
                        (iter->tarih[7]  - '0') * 100  +
                        (iter->tarih[8]  - '0') * 10   +
                        (iter->tarih[9]  - '0');
        }
 
        if (kayitYili < yil) {
            oncesiSayisi++;
            oncesiToplam += iter->ortalamaPuan;
            if (iter->oncelik == YUKSEK) oncesiYuksek++;
        } else {
            sonrasiSayisi++;
            sonrasiToplam += iter->ortalamaPuan;
            if (iter->oncelik == YUKSEK) sonrasiYuksek++;
        }
        iter = iter->next;
    }
 
    float oncesiOrt  = (oncesiSayisi  > 0) ? oncesiToplam  / oncesiSayisi  : 0.0f;
    float sonrasiOrt = (sonrasiSayisi > 0) ? sonrasiToplam / sonrasiSayisi : 0.0f;
 
    cout << "\n========== TARIH BAZLI TREND ANALIZI ==========" << endl;
    cout << "Esik Yil: " << yil << endl;
    cout << "------------------------------------------------" << endl;
    cout << yil << " ONCESI:" << endl;
    cout << "  Kayit Sayisi        : " << oncesiSayisi << endl;
    cout << "  Ort. Puan           : " << oncesiOrt << "/5.0" << endl;
    cout << "  Yuksek Oncelikli    : " << oncesiYuksek << endl;
    cout << "------------------------------------------------" << endl;
    cout << yil << " VE SONRASI:" << endl;
    cout << "  Kayit Sayisi        : " << sonrasiSayisi << endl;
    cout << "  Ort. Puan           : " << sonrasiOrt << "/5.0" << endl;
    cout << "  Yuksek Oncelikli    : " << sonrasiYuksek << endl;
    cout << "------------------------------------------------" << endl;
 
    // Trend yorumu
    if (oncesiSayisi == 0 && sonrasiSayisi == 0) {
        cout << "Yorum: Analiz icin yeterli kayit yok." << endl;
    } else if (sonrasiSayisi > oncesiSayisi) {
        cout << "Trend : Icerik uretimi " << yil << " sonrasinda ARTMIS." << endl;
    } else if (sonrasiSayisi < oncesiSayisi) {
        cout << "Trend : Icerik uretimi " << yil << " sonrasinda AZALMIS." << endl;
    } else {
        cout << "Trend : Icerik uretimi esik yil oncesi ve sonrasi DENGELI." << endl;
    }
 
    if (oncesiSayisi > 0 && sonrasiSayisi > 0) {
        if (sonrasiOrt > oncesiOrt)
            cout << "Kalite: " << yil << " sonrasi iceriklerin puani DAHA YUKSEK." << endl;
        else if (sonrasiOrt < oncesiOrt)
            cout << "Kalite: " << yil << " oncesi iceriklerin puani DAHA YUKSEK." << endl;
        else
            cout << "Kalite: Puan ortalamalari esit." << endl;
    }
 
    cout << "================================================" << endl;
}