#ifndef MODUL3_STACK_H
#define MODUL3_STACK_H

#include <string>
#include "modul1_kayit.h"
#include "modul2_gunluk.h"

using namespace std;

struct StackIslem {
    IslemTuru tur;
    int kayitID;
    string oncekiDeger;
    string yeniDeger;
    string zaman;
    StackIslem* next;
};

void stackeIslemPush(StackIslem** ust, IslemTuru tur, int kayitID, string oncekiDeger, string yeniDeger, string zaman);
void loglardanStackGuncelle(StackIslem** ust, LogKaydi* logBas, int* sonIslenenLogID);
void undoPop(StackIslem** ust, Kayit** kayitBas, LogKaydi** logBas);
int stackDerinligi(StackIslem* ust);
void son10IslemiGoster(StackIslem* ust);
void enSikIslemTuruAnalizi(StackIslem* ust);
void stackTemizle(StackIslem* ust);

#endif
