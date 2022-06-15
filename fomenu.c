#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "modositas.h"
#include "debugmalloc.h"

///az idoszamitas nevu fuggvennyel szamolja a program ki azt hogy mely autok vizsgaja jar le 30 napon belul


int JuliNap(int ev, int ho, int nap)          ///a Julian datum megadja a Kr.e 4713-tol a datumunkig eltelt napok szamat.
{
    int jdn=(1461*(ev+4800+(ho-14)/12))/4+(367*(ho-2-12*((ho-14)/12)))/12-(3*((ev+4900+(ho-14)/12)/100))/4+nap-32075 ;
    return jdn;
}

void idoszamitas(Auto *tomb)
{
    int ev_most, ho_most, nap_most, ev_lejar, ho_lejar, nap_lejar;
    bool c = false;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    ho_most = t->tm_mon+1;
    nap_most = t->tm_mday;
    ev_most = t->tm_year+1900;

    for(int i = 0; i < db; i++)
    {
        char * token = strtok(tomb[i].vizsga, ".");
        int darab = 1;
        while( token != NULL )
        {
            if(darab == 1)ev_lejar = atoi(token);
            if(darab == 2)ho_lejar = atoi(token);
            if(darab == 3)nap_lejar = atoi(token);

            darab++;
            token = strtok(NULL, ".");
        }
        if(((JuliNap(ev_lejar, ho_lejar, nap_lejar) - JuliNap(ev_most, ho_most, nap_most)) + 1) <= 30)
        {
            printf("Auto:%s\nTulaj:%s\nDatum:%d.%d.%d\n\n", tomb[i].marka, tomb[i].tulaj, ev_lejar, ho_lejar, nap_lejar);
            c = true;
        }
    }   ///JuliNap fuggveny 2x meghivva es a visszateresi erteket egymasbol kivonva + 1 megkapjuk hogy hany nap van a ket datum kozott.
    if(c == false)printf("Nincs olyan auto aminek 30 napon belul lejar a vizsgaja.");
}


///a fomenu fuggveny tartalmazza azokat a menuket illetve alpontokat amelyek szuksegesek ahoz hogy a program tudjon visszalepest csinalni

void menu(Auto *tomb)
{

    ///Fomenu
    printf("Mit szeretne csinalni? Kerem nyomja meg a szamot az utasitas mellett.\n");
    printf("------------------------------------------\n");
    printf("1.UGYFELEK\n");
    printf("2.AUTOK\n");
    printf("3.SZERVIZTORTENET\n");
    printf("4.LISTAZAS(HAMAROSAN LEJAR A VIZSGA)\n");
    printf("5.HOZZAADAS\n");
    printf("6.TORLES\n");
    printf("7.KERESES\n");
    printf("8.KILEPES\n");
    printf("------------------------------------------\n");
    printf("A valasz : ");
    scanf("%d", &valasz);

    switch (valasz)
    {
        case  1 :
        {
            ///Ugyfelek kilistazasa.
            system("cls");
            printf("1.UGYFELEK\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    for(int i = 0; i < db; i ++)
                        printf("Tulaj:%s\nTelefonszam:%s\n\n",tomb[i].tulaj,tomb[i].telefonszam);
                    break;
                }
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }
        }
            break;


        case 2 :
        {
            ///Autok kilistazasa.
            system("cls");
            printf("1.AUTOK\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    for(int i = 0; i < db; i ++)
                        printf("Auto:%s\nRendszam:%s\nEvjarat:%s\n\n", tomb[i].marka, tomb[i].rendszam, tomb[i].evjarat);
                    break;
                }
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }
        }
            break;

        case 3 :
        {
            ///Szerviztortenet kilistazasa.
            system("cls");
            printf("1.SZERVIZTORTENET\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    for(int i = 0; i < db; i++)
                        printf("Auto:%s\nSzerviz:%s\nAr:%s\nVizsga Lejar:%s\n\n", tomb[i].marka, tomb[i].szerviz, tomb[i].ar, tomb[i].vizsga);
                    break;
                }
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }
        }
            break;

        case 4 :
        {
            ///Hamarosan lejaro vizsga kilistazasa.
            system("cls");
            printf("1.30 NAPON BELUL LEJARO VIZSGA\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    ///Autok kilistazasa amelyeknek 30 napon belul lejar a vizsgajuk.
                    idoszamitas(tomb);
                }
                    break;
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }

        }
            break;

        case 5 :
        {
            ///Auto hozzaadasa.
            system("cls");
            printf("1.AUTO HOZZAADASA\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    printf("A forma ahogy meg kell adni az adatokat a kovetkezo:\n");
                    printf("marka|tulajdonos|rendszam|telefonszam|evjarat|vizsga(ev.ho.nap)|ar|javitas\n");
                    hozzaad();
                    printf("Sikeres hozzaadas.");
                }
                    break;
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }
        }
            break;

        case 6 :
        {
            ///Auto torlese.
            system("cls");
            printf("1.AUTO TORLESE\n");
            printf("2.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch (valasz)
            {
                case 1 :
                {
                    for(int i = 0; i < db; i++)
                        printf("%s \n", tomb[i].marka);
                    torol(tomb);
                }
                    break;
                case 2:
                    menu(tomb);
                    break;
                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }

        }
            break;

        case 7 :
        {
            ///Auto keresese.
            system("cls");
            printf("1.KERESES AUTO SZERINT\n");
            printf("2.KERESES TULAJ SZERINT\n");
            printf("3.KERESES RENDSZAM SZERINT\n");
            printf("4.VISSZA\n");
            printf("Valassz az alabbi menuk kozul:");
            scanf("%d", &valasz);
            system("cls");
            switch(valasz)
            {
                case 1:
                {
                    ///Kereses auto szerint.
                    printf("Kerem irja be az auto markajat:");
                    char seged[20];
                    bool c = false;
                    scanf("%*[\n]%[^\n]%*c",seged);
                    for(int i = 0; i < db; i++)
                    {
                        if(strcmp(seged,tomb[i].marka) == 0)
                        {
                            printf("Auto:%s\nRendszam:%s\nEvjarat:%s\nTulaj:%s\nTelefonszam:%s\nSzerviz:%s\nAr:%s\nVizsga Lejar:%s\n\n", tomb[i].marka, tomb[i].rendszam, tomb[i].evjarat, tomb[i].tulaj, tomb[i].telefonszam, tomb[i].szerviz, tomb[i].ar, tomb[i].vizsga);
                            c = true;
                            break;
                        }
                    }
                    if(c == false) printf("Nincs ilyen auto.");
                }
                    break;

                case 2:
                {
                    ///Kereses ugyfel szerint.
                    printf("Kerem irja be az ugyfel nevet:");
                    char seged[20];
                    bool c = false;
                    scanf("%*[\n]%[^\n]%*c",seged);
                    for(int i = 0; i < db; i++)
                    {
                        if(strcmp(seged,tomb[i].tulaj) == 0)
                        {
                            printf("Auto:%s\nRendszam:%s\nEvjarat:%s\nTulaj:%s\nTelefonszam:%s\nSzerviz:%s\nAr:%s\nVizsga Lejar:%s\n\n", tomb[i].marka, tomb[i].rendszam, tomb[i].evjarat, tomb[i].tulaj, tomb[i].telefonszam, tomb[i].szerviz, tomb[i].ar, tomb[i].vizsga);
                            c = true;
                            break;
                        }
                    }
                    if(c == false) printf("Nincs ilyen ugyfel.");
                }
                    break;

                case 3 :
                {
                    ///Kereses rendszam szerint.
                    printf("Kerem irja be az auto rendszamat:");
                    char seged[20];
                    bool c = false;
                    scanf("%*[\n]%[^\n]%*c",seged);
                    for(int i = 0; i < db; i++)
                    {
                        if(strcmp(seged,tomb[i].rendszam) == 0)
                        {
                            printf("Auto:%s\nRendszam:%s\nEvjarat:%s\nTulaj:%s\nTelefonszam:%s\nSzerviz:%s\nAr:%s\nVizsga Lejar:%s\n\n", tomb[i].marka, tomb[i].rendszam, tomb[i].evjarat, tomb[i].tulaj, tomb[i].telefonszam, tomb[i].szerviz, tomb[i].ar, tomb[i].vizsga);
                            c = true;
                            break;
                        }
                    }
                    if(c == false) printf("Nincs ilyen rendszam.");
                }
                    break;

                case 4 :
                    menu(tomb);
                    break;

                default:
                    printf("Ervenytelen valasz!\n");
                    break;
            }
        }
            break;

        case 8 :
        {
            ///Kilepes.
            system("cls");
            printf("Sikeres kilepes.");
        }
            break;

        default:
            printf("Ervenytelen valasz!\n");
            break;
    }
}

