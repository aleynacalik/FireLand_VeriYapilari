# EduFlow - Dijital Egitim Platformu

ISE 106 Veri Yapilari Projesi - Kurumsal Operasyon ve Karar Destek Sistemi

## Proje Yapisi

```
FireLand_VeriYapilari-main/
├── bin/                         # Calistirilabilir dosya (.exe)
├── lib/                         # Object dosyalari (.o)
├── include/                     # Header dosyalari
│   ├── modul1_kayit.h
│   ├── modul2_gunluk.h
│   ├── modul3_stack.h
│   ├── modul4_queue.h
│   ├── modul5_tree.h
│   ├── modul6_hash.h
│   ├── modul7_sikistirma.h
│   └── modul8_performans.h
├── src/                         # Kaynak dosyalari
│   ├── modul1_kayit.cpp
│   ├── modul2_gunluk.cpp
│   ├── modul3_stack.cpp
│   ├── modul4_queue.cpp
│   ├── modul5_tree.cpp
│   ├── modul6_hash.cpp
│   ├── modul7_sikistirma.cpp
│   └── modul8_performans.cpp
├── main.cpp
├── Makefile
└── README.md
```

## Derleme ve Calistirma

```bash
mingw32-make              # Derle
mingw32-make run          # Çalıştır (Windows)
mingw32-make clean        # Temizle
```

## Moduller

### Modul 1 - Ana Kayit Yonetimi
**Veri Yapisi:** Tek yonlu bagli liste

- Kayit ekleme / silme / guncelleme
- ID ile arama
- Boyuta gore siralama
- En eski kayitlari listeleme
- Kritik not yonetimi

### Modul 2 - Operasyon Gunlugu
**Veri Yapisi:** Cift yonlu dairesel bagli liste

- Islem logu olusturma
- Kayit ID bazli gecmis islemleri gosterme
- Tarih araligi raporlama
- Islem turu bazli raporlama

### Modul 3 - Stack Modulu
**Veri Yapisi:** Stack (LIFO)

- Loglardan stack guncelleme
- Undo islemleri
- Son islem analizi
- Islem turu yogunluk analizi

### Modul 4 - Talep Yonetimi
**Veri Yapisi:** Queue (oncelik sirali)

- Talep ekleme
- Oncelikli talep olusturma
- Kuyruk listeleme
- Dequeue -> Modul 1 kayit olusturma

### Modul 5 - Tree Analizi
**Veri Yapisi:** Binary Search Tree

- Tarihe gore agac
- Oncelige gore agac
- Puan araligi filtreleme
- Agac yuksekligi / performans bilgisi
- Trend analizi

### Modul 6 - Hash Analiz Motoru
**Veri Yapisi:** Hash Table (chaining)

- Hash tablo olusturma
- ID bazli hizli arama
- Kategori bazli sayim
- Oncelik yogunluk analizi
- Hash performans metrikleri

### Modul 7 - Veri Sikistirma
**Amac:** Modul 1 verisini arsivleme ve boyut optimizasyonu

- Frekans analizi
- Huffman sikistirma (orijinal/sikismis boyut, oran, tasarruf)
- LZW sikistirma (orijinal/sikismis boyut, oran, tasarruf)
- Shannon-Fano sikistirma (orijinal/sikismis boyut, oran, tasarruf)
- Uc algoritma karsilastirma tablosu


### Modul 8 - Performans ve Dizi Analizi
**Amac:** Tum moduller icin sure/etkinlik analizi ve optimizasyon onerisi

- Son 10 erisilen kayit
- Linear Search vs Binary Search karsilastirma
- Islem bazli ms olcum kaydi
- Modul bazli ortalama sure hesaplama
- En hizli yapi/algoritma onerisi

## Ana Menu Haritasi

- `1-17`: Modul 1 + Modul 2 temel islemler ve ekstra ekranlar
- `18`: Modul 3 (Stack alt menusu)
- `19`: Modul 4 (Queue alt menusu)
- `20`: Modul 5 (Tree alt menusu)
- `21`: Modul 6 (Hash alt menusu)
- `22`: Modul 7 (Veri Sikistirma alt menusu)
- `23`: Modul 8 (Performans ve Dizi Analizi alt menusu)

## Moduller Arasi Baglantilar

- Modul 1 islemleri otomatik olarak Modul 2 gunlugune yazilir.
- Modul 3, Modul 2 loglarini stack'e alir ve undo/analiz yapar.
- Modul 4 talepleri Modul 1'e kayit olarak aktarir; dequeue islem logu Modul 2 ve Modul 3'e yansir.
- Modul 7 ham veriyi Modul 1 kayitlarindan alir.
- Modul 8, Modul 1/7 dahil tum olcumleri toplayip karsilastirma ve optimizasyon onerisi sunar.
