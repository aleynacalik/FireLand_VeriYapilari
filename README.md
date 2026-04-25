# EduFlow - Dijital Eğitim Platformu

ISE 106 Veri Yapıları Projesi - Kurumsal Operasyon ve Karar Destek Sistemi

## Proje Yapısı

```
eduflow/
├── bin/                    # Çalıştırılabilir dosya (.exe)
├── lib/                    # Object dosyaları (.o)
├── include/                # Header dosyaları (.h)
│   ├── modul1_kayit.h
│   ├── modul2_gunluk.h
│   ├── modul3_stack.h
│   └── modul4_queue.h
├── src/                    # Kaynak dosyaları (.cpp)
│   ├── modul1_kayit.cpp
│   ├── modul2_gunluk.cpp
│   ├── modul3_stack.cpp
│   └── modul4_queue.cpp
├── rapor/
│   └── ekran_goruntuleri/
├── main.cpp
├── Makefile
└── README.md
```

## Derleme ve Çalıştırma

```bash
mingw32-make              # Derle
mingw32-make run          # Çalıştır (Windows)
mingw32-make clean        # Temizle
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

### Modül 3 - Stack Modülü
**Veri Yapısı:** Stack (LIFO)

**5 İşlevsellik:**
1. İşlem push (Modül 2 loglarından stack güncelleme)
2. Undo (pop) ile geri alma
3. Stack derinliği gösterme
4. Son 10 işlemi listeleme
5. En sık işlem türü analizi

### Modül 4 - Talep Yönetim Modülü
**Veri Yapısı:** Queue (öncelik sıralı bağlı liste yaklaşımı)

**5 İşlevsellik:**
1. Yeni talep ekle
2. Öncelikli talep oluştur
3. Kuyruğu listele
4. İlk talebi işleme al (dequeue) ve Modül 1'e kayıt ekle
5. Ortalama bekleme süresi hesapla

## Ana Menüde İşlevsellikler

- `1-17`: Modül 1, Modül 2 ve mevcut ekstra işlemler
- `18`: **Modul 3 Islevsellikleri** (Stack alt menüsü)
- `19`: **Modul 4 Islevsellikleri** (Queue alt menüsü)

## Modüller Arası Bağlantı

- Modül 1'de yapılan her değişiklik (ekle/sil/güncelle) otomatik olarak Modül 2'ye loglanır.
- Modül 3, Modül 2 log kayıtlarını stack'e alarak undo ve analiz sağlar.
- Modül 4'te işlenen talepler Modül 1'e kayıt olarak eklenir.
- Modül 4 dequeue işlemi Modül 2'ye loglanır ve Modül 3 stack'ine push edilir.
