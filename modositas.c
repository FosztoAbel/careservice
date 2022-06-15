#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "modositas.h"
#include "debugmalloc.h"

///a feltoltes nevu fuggveny feltolti a strukturat a filebol levo adatokkal.

Auto *dinamikus()
{
    char c;
    FILE *fp;
    fp = fopen("autoszerviz.txt", "r");
    if (fp == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return NULL;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')meret++;
    fclose(fp);
    meret++;
    Auto *tomb = (Auto*)malloc(sizeof(Auto) * meret);

    return tomb;
}

void feltoltes(Auto *tomb)
{
    char aux[200];

    FILE *fp;
    fp = fopen("autoszerviz.txt", "r");
    if (fp == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }

    while(fgets(aux, 200, fp) != NULL)
    {
        char * token = strtok(aux, "|");
        int darab = 1;
        while( token != NULL )
        {
            switch(darab)
            {
                case 1 :
                {
                    strcpy(tomb[db].marka, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 2 :
                {
                    strcpy(tomb[db].tulaj, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 3 :
                {
                    strcpy(tomb[db].rendszam, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 4 :
                {
                    strcpy(tomb[db].telefonszam, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 5 :
                {
                    strcpy(tomb[db].evjarat, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 6 :
                {
                    strcpy(tomb[db].vizsga, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 7 :
                {
                    strcpy(tomb[db].ar, token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 8 :
                {
                    strcpy(tomb[db].szerviz, token);
                    int n = strlen(tomb[db].szerviz);
                    tomb[db].szerviz[n-1] = '\0';
                    token = strtok(NULL, "|");
                    break;
                }
                default:
                    break;
            }
            darab++;
        }
        db++;
    }
    fclose(fp);
}

///a hozzaad fuggveny hozzaad egy uj autot tulajdonossal es midnen informacioval egyutt a filehoz

void hozzaad()
{
    char aux[200];
    scanf("%*[\n]%[^\n]%*c", aux);

    FILE *fp;
    fp = fopen("autoszerviz.txt", "a");
    if (fp == NULL)
    {
        perror("Fájl megnyitása sikertelen");
        return;
    }
    fprintf(fp, "%s \n", aux);
    fclose(fp);
}

///a torol fuggveny kitorli a filebol azt a sort ahol megtalalja a flehasznalo altal beirt auto markat

void torol(Auto *tomb)
{
    bool c = false;
    char aux[200];
    char torles[20];
    printf("Melyik autot szeretne torolni ? \n");
    printf("Kerem irja be az auto markajat: ");
    scanf("%*[\n]%[^\n]%*c", torles);

    for(int i = 0; i < db; i++)
        if(strcmp(torles, tomb[i].marka) == 0) c = true;
    if(c == true)
    {
        FILE *file1;
        file1 = fopen("autoszerviz.txt", "r");
        if (file1 == NULL)
        {
            perror("Fájl megnyitása sikertelen");
            return;
        }

        FILE *file2;
        file2 = fopen("seged.txt", "w");
        if (file2 == NULL)
        {
            perror("Fájl megnyitása sikertelen");
            return;
        }
        int darab = 0;
        while(fgets(aux, 200, file1) != NULL)
        {
            if(strcmp(torles,tomb[darab].marka) == 0)darab++;
            else
            {
                fprintf(file2, "%s", aux);
                darab++;
            }
        }
        fclose(file1);
        fclose(file2);

        file1 = fopen("autoszerviz.txt", "w");
        if (file1 == NULL)
        {
            perror("Fájl megnyitása sikertelen");
            return;
        }
        file2 = fopen("seged.txt", "r");
        if (file2 == NULL)
        {
            perror("Fájl megnyitása sikertelen");
            return;
        }
        while(fgets(aux, 200, file2) != NULL)
        {
            fprintf(file1, "%s", aux);
        }
        fclose(file1);
        fclose(file2);
        printf("Sikeres torles!");
    }
    else printf("Nincs ilyen auto.");
}
