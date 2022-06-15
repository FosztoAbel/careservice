#ifndef MODOSITAS_H_INCLUDED
#define MODOSITAS_H_INCLUDED

int meret, db, valasz; ///azert dekralaltam globalisan hogy a foprogram lassa a valtozast amit a "feltoltes" nevu mellekprogram vegez, mivel a db v�ltoz� miut�n elv�gezt�k a felt�lt�st nem fog v�ltozni mivel azt csak a struktura bejarasara hasznalom.

typedef struct Auto
{
    char marka[20];
    char tulaj[20];
    char rendszam[10];
    char telefonszam[11];
    char evjarat[5];
    char szerviz[100];
    char vizsga[20];
    char ar[10];
} Auto;

Auto *dinamikus();
void feltoltes(Auto *tomb);
void hozzaad();
void torol(Auto *tomb);

#endif // MODOSITAS_H_INCLUDED
