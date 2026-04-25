#ifndef MODUL4_QUEUE_H
#define MODUL4_QUEUE_H

#include <string>
#include "modul1_kayit.h"
#include "modul2_gunluk.h"
#include "modul3_stack.h"

using namespace std;

struct Talep {
    int talepID;
    string kategori;
    float boyut;
    Oncelik oncelik;
    string talepZamani;
    string baslik;
    float puan;
    Talep* next;
};

string talepZamaniUret();
void yeniTalepEkle(Talep** bas, string kategori, float boyut, Oncelik oncelik, string baslik, float puan);
void oncelikliTalepOlustur(Talep** bas, string kategori, float boyut, string baslik, float puan);
void kuyruguListele(Talep* bas);
void ilkTalebiIslemeAl(Talep** bas, Kayit** kayitBas, LogKaydi** logBas, StackIslem** stackUst);
float ortalamaBeklemeSuresiDakika(Talep* bas);
void kuyrukTemizle(Talep* bas);

#endif
