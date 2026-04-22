# EduFlow - Dijital Eğitim Platformu

ISE 106 Veri Yapıları Projesi - Kurumsal Operasyon ve Karar Destek Sistemi

## Proje Yapısı

```
eduflow/
├── bin/                    # Çalıştırılabilir dosya (.exe)
├── lib/                    # Object dosyaları (.o)
├── include/                # Header dosyaları (.h)
│   ├── modul1_kayit.h
│   └── modul2_gunluk.h
├── src/                    # Kaynak dosyaları (.cpp)
│   ├── modul1_kayit.cpp
│   └── modul2_gunluk.cpp
├── rapor/
│   └── ekran_goruntuleri/
├── main.cpp
├── Makefile
└── README.md
```

## Derleme ve Çalıştırma

```bash
make              # Derle
./bin/program     # Çalıştır (Linux/Mac)
bin\program.exe   # Çalıştır (Windows)
make clean        # Temizle
```

## Modüller

### Modül 1 - Ana Kayıt Yönetimi
**Veri Yapısı:** Tek Yönlü Bağlı Liste

**10 İşlevsellik:**
1. Kayıt ekle
2. ID'ye göre sil
3. Başlığa göre güncelle
4. Zaman damgası ile listele
5. ID'ye göre ara
6. Toplam kayıt sayısı
7. Boyuta göre küçükten büyüğe sırala
8. En eski 10 kayıt
9. Kritik not ekle
10. Kritik kayıtları listele

### Modül 2 - Operasyon Günlüğü
**Veri Yapısı:** Çift Yönlü Dairesel Bağlı Liste

**5 İşlevsellik:**
1. Günlük kaydı ekle
2. Belirli kayıt ID'ye ait tüm işlemleri listele
3. Belirli tarih aralığındaki işlemler
4. Günlük raporu oluştur
5. İşlem türüne göre listeleme

## Modüller Arası Bağlantı

- Modül 1'de yapılan her değişiklik (ekle/sil/güncelle) otomatik olarak Modül 2'ye loglanır.
