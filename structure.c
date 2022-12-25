/*

SPIEGAZIONE DEL PROGRAMMA

____________________________________________________________________________________________
    INTRODUZIONE:

Questo codice è stato scritto per risolvere gli scomodi turni di interrogazioni che vengono
estratti casualmente, rendendo meno casuale questa estrazione, selezionando gli interrogati
in base alle altre interrogazioni nei giorni a venire, in modo da avere una distanza media
tra interrogazioni più alta possibile.

Il programma sfrutta due file esterni come database di interrogazioni salvate in passato
e dell'elenco degli alunni di una certa classe

_____________________________________________________________________________________________
    SPIEGAZIONE:

_____________________________________________________________________________________________
    FILE ESTERNI:

- calendario.txt : file contenente due parole chiave (start e end) per facilitarne la
                   lettura, e un numero indefinito di giorni (in formatto "anno") seguito
                   da una lista di numeri corrispondenti agli alunni interrogati quel giorno;

- registro.txt : file contenente un numero (il numero di studenti) seguito dalla lista dei
                 nomi e cognomi degli alunni in ordine alfabetico.

_____________________________________________________________________________________________
    LISTA E SPIEGAZIONE PROCEDURE E FUNZIONI:

- find : funzione che permette di restituire l'indice di un carattere all'interno di una
         stringa ricevuta come argomento
ARGOMENTI : char str[30] --> stringa nella quale cercare in carattere
            char c --> carattere da cercare nella stringa
RETURN : intero rappresentante la prima comparsa di c in str, -1 se non è presente;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- convert : funzione che converte la data da mese\giorno a indice di un array che considera
            tutti i giorni in ordine come un array (da settembre a giugno);
ARGOMENTI : int g --> giorno
            int m --> mese
RETURN : intero rappresentante la data inviata come argomento in formato indice
         del giorno nell'array anno;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- stampaAlunni :  stampa tutti gli alunni salvati nel file registro.txt con relativo numero
                  dell'elenco;
ARGOMENTI : int na --> intero rappresentante il numero totale di alunni
            char al[na][30] --> array di stringhe contenente nome e cognome
                               degli alunni in ordine alfabetico;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- numeroAlunno : funzione che stampa nome e cognome di un certo alunno in base al numero di
                 elenco fornito come argomento;
ARGOMENTI : int na --> \\r53
            char al[na][30] --> \\r54
            int num --> numero dell'ordine alfabetico a cui corrisponde lo studente desiderato
RETURN : restituisce una stringa contenente nome e cognome dello studente di numero num;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- distanza : funzione che riceve come argomento un giorno, uno studente, e l'anno delle
             interrogazioni e restituisce la distanza tra il giorno inserito e il giorno
             più vicino in cui lo studente passato come argomento verrà interrogato;
ARGOMENTI : int num --> numero dell'alunno interessato
            int g --> giorno dell'interrogazione
            char y[303][30] --> \\r68
RETURN : restituisce la distanza dal giorno inserito e l'interrogazione più vicina dell'alunno
         inserito, se non ci sono in un arco di 10 giorni restituisce -1;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- carica : apre il file calendario e salva nell'array y gli interrogati segnati nel file nel
           giorno in cui sono effettivamente interrogati
ARGOMENTI : char y[303][30] --> array con una stringa per ogni giorno dell'anno scolastico,
                                stringa contenente i numeri degli interrogati di tale giorno;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- stampaCalendario : stampa tutti i giorni dell'anno scolastico divisi in mesi, scrivendo
                     anche i realitivi interrogati
ARGOMENTI : char y[303][30] --> \\r68;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- menu : procedura che esegue il menu principale del programma, dal quale sarà possibile
         interagire con le altre funzioni
ARGOMENTI : char y[303][30] --> \\r68
            int na --> r53
            char al[na][30] --> \\r54;

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
- caricai : prima procedura a venire eseguita, permette di inizializzare il calendario e gli
            alunni tramite i due file esterni
ARGOMENTI : char y[303][30] --> \\r68;

_____________________________________________________________________________________________

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// procedure e funzioni

int find(char str[30], char c)
{
    int i;
    for (i = 0; i < 30; i++)
        if (str[i] == c)
            return i;
    return -1;
}

int convert(int g, int m)
{
    switch (m)
    {
    case 9:
    {
        return g - 1;
        break;
    }
    case 10:
    {
        return g + 29;
        break;
    }
    case 11:
    {
        return g + 60;
        break;
    }
    case 12:
    {
        return g + 90;
        break;
    }
    case 1:
    {
        return g + 121;
        break;
    }
    case 2:
    {
        return g + 152;
        break;
    }
    case 3:
    {
        return g + 181;
        break;
    }
    case 4:
    {
        return g + 211;
        break;
    }
    case 5:
    {
        return g + 241;
        break;
    }
    case 6:
    {
        return g + 272;
        break;
    }
    default:
        return -1;
    }
}

void stampaAlunni(int na, char al[na][30])
{
    printf("\n");
    int i;
    for (i = 0; i < na; i++)
        printf("%d %s", i + 1, al[i]);
    printf("\n\n");
}

char *numeroAlunno(int na, char al[na][30], int num) { return al[num - 1]; }

int distanza(int num, int g, char y[303][30])
{
    int i;
    char *tok = strtok(y[g], ",");
        while (tok != NULL)
        {
            if(atoi(tok)==num)return 0;
            tok = strtok(NULL, ",");
        }
    for (i = 1; i < 10; i++)
    {
        if((g+i)<303){
        char *tok1 = strtok(y[g+i], ",");
        while (tok1 != NULL)
        {
            if(atoi(tok1)==num)return i;
            tok1 = strtok(NULL, ",");
        }}
        if((g-i)>0){
        char *tok2 = strtok(y[g-i], ",");
        while (tok2 != NULL)
        {
            if(atoi(tok2)==num)return i;
            tok2 = strtok(NULL, ",");
        }}
    }return -1;
}

void carica(char y[303][30])
{
    FILE *fp;
    fp = fopen("fileSalvataggio/calendario.txt", "r");
    /*
    la struttura del file di testo con il salvataggio sarà:
    stringa per inizio
    start
    N1 M1
    N2 M2
    end

    con N = numero del giorno rappresentato da 1 a 303
    con M = stringa con tutti gli studenti interrogati quel giorno divisi da una virgola
    */
    int i, j, index;

    char frase[30];
    char stud[30];
    char *token;
    fgets(frase, 30, fp);
    while (!feof(fp))
    {
        fgets(frase, 30, fp);
        if (frase[0] == 'e')
        {
            fclose(fp);
            return;
        }
        index = find(frase, ' ');
        for (j = 0; j < index; j++)
            stud[j] = frase[j];
        i = atoi(stud);
        j = index + 1;
        while (frase[j] != '\n')
        {
            y[i][j - (index + 1)] = frase[j];
            j++;
        }
        y[i][j - (index + 1)] = '\0';
    }
}

void stampaCalendario(char y[303][30])
{
    printf("\n");
    int i, j, k, tot;
    tot = 0;
    for (j = 0; j < 10; j++)
    {
        switch (j)
        {
        case 0:
        {
            printf("settembre\n");
            break;
        }
        case 1:
        {
            printf("ottobre\n");
            break;
        }
        case 2:
        {
            printf("novembre\n");
            break;
        }
        case 3:
        {
            printf("dicembre\n");
            break;
        }
        case 4:
        {
            printf("gennaio\n");
            break;
        }
        case 5:
        {
            printf("febbraio\n");
            break;
        }
        case 6:
        {
            printf("marzo\n");
            break;
        }
        case 7:
        {
            printf("aprile\n");
            break;
        }
        case 8:
        {
            printf("maggio\n");
            break;
        }
        case 9:
        {
            printf("giugno\n");
            break;
        }
        }
        if (j == 5)
            k = 28;
        else
        {
            if (j == 0 || j == 2 || j == 7 || j == 9)
                k = 30;
            else
                k = 31;
        }
        for (i = 1; i < (k + 1); i++)
            printf("%d: %s\n", i, y[i + tot - 1]);
        printf("\n");
        tot += k;
    }
}

int datacheck(int g, int m)
{
return 0;
}

void turni(char y[303][30]) //da descrivere ----------------
{
    int check=0;
    int n,i;
    do{
        printf("inserisci un numero ti turni:\n");
        scanf("%d",&n);
        if(n>2 && n<11)check++;
        else printf("valore non valido\n");
    }while(check!=1);
    
    for(i=0;i<n;i++)
    {
        check=0;
        do{
            printf("inserisci una data\n");
        }while(check!=0);
    }

}

void menu(char y[303][30], int na, char al[na][30])
{
    int scelta;
    int i;
    printf("\033[2J\033[1;1H");
    do
    {
        printf("1 - carica\n");            // carica da un file i turni attualmente esistenti con data e relativi interrogati
        printf("2 - stampa calendario\n"); // stampa a video il calendario
        printf("3 - stampa alunni\n");
        printf("4 - aggiungi turni\n"); // aggiunge all'array e al file di salvataggio i vari turni
        printf("5 - fine\n");
        scanf("%d", &scelta);
        printf("\033[2J\033[1;1H");
        switch (scelta)
        {
        case 1:
        {
            carica(y);
            printf("CARICAMENTO SVOLTO CORRETTAMENTE\n\n");
            break;
        }
        case 2:
        {
            stampaCalendario(y);
            break;
        }
        case 3:
        {
            stampaAlunni(na, al);
            break;
        }
        case 4:
        {
            turni(y);
            break;
        }
        case 5:
            break;
        default:
        {
            printf("valore inserito errato\n");
            break;
        }
        }
    } while (scelta != 5);
}

void caricai(char y[303][30])
{
    int i;
    for (i = 0; i < 303; i++)
        y[i][0] = '\0';
    FILE *fp;

    fp = fopen("fileSalvataggio/registro.txt", "r");
    int na; // numero alunni
    fscanf(fp, "%d\n", &na);
    char al[na][30]; // alunni
    for (i = 0; i < na; i++)
        fgets(al[i], 30, fp);
    menu(y, na, al);
}

int main()
{
    // dichiarzione variabili
    char y[303][30]; // array di stringhe che contiene nulla se non ci sono interrogati altrimenti il numero degli interrogati
    
    // serie di procedure

    do{
        printf("e\' un anno bisestile?:\n");
        scanf("%s\n",b);
    }while(b[0]!='S');

    caricai(y);
}