#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME_LENGTH 100
#define MAX_ATV 100

typedef struct {
    char nume[MAX_NAME_LENGTH];
    int an_fabricatie;
    int disponibilitate;
} ATV;

void afiseaza_meniu();
void submeniu_afisare();
void submeniu_adaugare();
void submeniu_cautare();
void submeniu_imprumut();
void submeniu_returnare();

void adauga_atv_in_fisier();
int incarca_atvuri_din_fisier(ATV atvuri[], int max);
void cauta_atv_in_fisier();
void imprumuta_atv();
void returneaza_atv();

int main() {
    int optiune;

    do {
        afiseaza_meniu();
        printf("Introduceti optiunea dorita: ");
        scanf("%d", &optiune);
        while(getchar() != '\n');

        if (optiune < 0 || optiune > 5) {
            printf("Optiune invalida. Va rugam sa incercati din nou.\n");
            Sleep(2000);
            system("cls");
            continue;
        }

        switch(optiune) {
            case 1: {
                system("cls");
                printf("\n--- Submeniu - Afisare ATV-uri Disponibile ---\n");
                ATV atvuri[MAX_ATV];
                int nr = incarca_atvuri_din_fisier(atvuri, MAX_ATV);
                if (nr == 0) {
                    printf("Nu exista niciun ATV in fisier.\n");
                } else {
                    printf("\nATV-uri disponibile:\n");
                    int i;
                    for ( i = 0; i < nr; i++) {
                        if (atvuri[i].disponibilitate == 1) {
                            printf("Nume: ");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                            printf("%s", atvuri[i].nume);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            printf(", An: ");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                            printf("%d\n", atvuri[i].an_fabricatie);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        }
                    }
                }
                printf("Apasati orice tasta pentru a reveni la Meniul Principal.\n");
                getchar();
                system("cls");
                break;
            }
            case 2:
                system("cls");
                submeniu_adaugare();
                break;
            case 3:
                system("cls");
                submeniu_cautare();
                break;
            case 4:
                system("cls");
                submeniu_imprumut();
                break;
            case 5:
                system("cls");
                submeniu_returnare();
                break;
            case 0:
                printf("Iesire din aplicatie.\n");
                exit(0);
            default:
                break;
        }
    } while(optiune != 0);

    return 0;
}

void afiseaza_meniu() {
    printf("\nMeniu Principal:\n");
    printf("1. Afiseaza ATV-urile disponibile\n");
    printf("2. Adauga un ATV\n");
    printf("3. Cauta un ATV\n");
    printf("4. Imprumuta un ATV\n");
    printf("5. Returneaza un ATV\n");
    printf("0. Iesire\n");
}

void submeniu_adaugare() {
    printf("\n--- Submeniu - Adaugare ATV ---\n");
    adauga_atv_in_fisier();
    printf("Apasati orice tasta pentru a reveni la Meniul Principal.\n");
    getchar();
    system("cls");
}

void submeniu_cautare() {
    printf("\n--- Submeniu - Cauta ATV ---\n");
    cauta_atv_in_fisier();
    printf("Apasati orice tasta pentru a reveni la Meniul Principal.\n");
    getchar();
    system("cls");
}

void submeniu_imprumut() {
    printf("\n--- Submeniu - Imprumuta ATV ---\n");
    imprumuta_atv();
    printf("Apasati orice tasta pentru a reveni la Meniul Principal.\n");
    getchar();
    system("cls");
}

void submeniu_returnare() {
    printf("\n--- Submeniu - Returnare ATV ---\n");
    returneaza_atv();
    printf("Apasati orice tasta pentru a reveni la Meniul Principal.\n");
    getchar();
    system("cls");
}

void adauga_atv_in_fisier() {
    ATV atv;
    FILE *fisier = fopen("ATV.txt", "a");

    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return;
    }

    printf("Introduceti numele ATV-ului(trebuie sa inceapa cu 'atv'): ");
    fgets(atv.nume, MAX_NAME_LENGTH, stdin);
    atv.nume[strcspn(atv.nume, "\n")] = '\0';

    if (strncmp(atv.nume, "atv", 3) != 0) {
        printf("Numele trebuie sa inceapa cu 'atv'. Va rugam sa incercati din nou.\n");
        return;
    }

    printf("Introduceti anul fabricatiei: ");
    scanf("%d", &atv.an_fabricatie);
    while(getchar() != '\n');

    atv.disponibilitate = 1;

    fprintf(fisier, "%s,%d,%d\n", atv.nume, atv.an_fabricatie, atv.disponibilitate);
    fclose(fisier);
    printf("ATV-ul a fost adaugat cu succes.\n");
}

int incarca_atvuri_din_fisier(ATV atvuri[], int max) {
    FILE *fisier = fopen("ATV.txt", "r");
    if (fisier == NULL) {
        return 0;
    }

    int count = 0;
    while (count < max && fscanf(fisier, "%99[^,],%d,%d\n", atvuri[count].nume, &atvuri[count].an_fabricatie, &atvuri[count].disponibilitate) == 3) {
        count++;
    }

    fclose(fisier);
    return count;
}

void cauta_atv_in_fisier() {
    char nume_cautat[MAX_NAME_LENGTH];
    FILE *fisier = fopen("ATV.txt", "r");
    ATV atv;

    if (fisier == NULL) {
        printf("Nu exista niciun ATV in fisier.\n");
        return;
    }

    printf("Introduceti numele ATV-ului de cautat: ");
    fgets(nume_cautat, MAX_NAME_LENGTH, stdin);
    nume_cautat[strcspn(nume_cautat, "\n")] = '\0';

    int gasit = 0;
    while (fscanf(fisier, "%99[^,],%d,%d\n", atv.nume, &atv.an_fabricatie, &atv.disponibilitate) == 3) {
        if (strcmp(atv.nume, nume_cautat) == 0) {
            printf("ATV gasit: Nume: ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            printf("%s", atv.nume);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            printf(", An: ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            printf("%d\n", atv.an_fabricatie);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            gasit = 1;
            break;
        }
    }

    if (!gasit) {
        printf("ATV-ul nu a fost gasit.\n");
    }

    fclose(fisier);
}

void imprumuta_atv() {
    char nume_cautat[MAX_NAME_LENGTH];
    FILE *fisier = fopen("ATV.txt", "r");
    FILE *fisier_temp = fopen("ATV_temp.txt", "w");
    ATV atv;
    int gasit = 0;

    if (fisier == NULL || fisier_temp == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return;
    }

    printf("Introduceti numele ATV-ului de imprumutat: ");
    fgets(nume_cautat, MAX_NAME_LENGTH, stdin);
    nume_cautat[strcspn(nume_cautat, "\n")] = '\0';

    while (fscanf(fisier, "%99[^,],%d,%d\n", atv.nume, &atv.an_fabricatie, &atv.disponibilitate) == 3) {
        if (strcmp(atv.nume, nume_cautat) == 0 && atv.disponibilitate == 1) {
            atv.disponibilitate = 0;
            gasit = 1;
        }
        fprintf(fisier_temp, "%s,%d,%d\n", atv.nume, atv.an_fabricatie, atv.disponibilitate);
    }

    fclose(fisier);
    fclose(fisier_temp);

    remove("ATV.txt");
    rename("ATV_temp.txt", "ATV.txt");

    if (gasit) {
        printf("ATV-ul a fost imprumutat.\n");
    } else {
        printf("ATV-ul nu a fost gasit sau nu este disponibil.\n");
    }
}

void returneaza_atv() {
    char nume_cautat[MAX_NAME_LENGTH];
    FILE *fisier = fopen("ATV.txt", "r");
    FILE *fisier_temp = fopen("ATV_temp.txt", "w");
    ATV atv;
    int gasit = 0;

    if (fisier == NULL || fisier_temp == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return;
    }

    printf("Introduceti numele ATV-ului de returnat: ");
    fgets(nume_cautat, MAX_NAME_LENGTH, stdin);
    nume_cautat[strcspn(nume_cautat, "\n")] = '\0';

    while (fscanf(fisier, "%99[^,],%d,%d\n", atv.nume, &atv.an_fabricatie, &atv.disponibilitate) == 3) {
        if (strcmp(atv.nume, nume_cautat) == 0 && atv.disponibilitate == 0) {
            atv.disponibilitate = 1;
            gasit = 1;
        }
        fprintf(fisier_temp, "%s,%d,%d\n", atv.nume, atv.an_fabricatie, atv.disponibilitate);
    }

    fclose(fisier);
    fclose(fisier_temp);

    remove("ATV.txt");
    rename("ATV_temp.txt", "ATV.txt");

    if (gasit) {
        printf("ATV-ul a fost returnat.\n");
    } else {
        printf("ATV-ul nu a fost gasit sau nu este imprumutat.\n");
    }
}
