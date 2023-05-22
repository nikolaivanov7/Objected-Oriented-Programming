#include <stdio.h>
#include <string.h>
#include <ctype.h>
struct Vozenje
{
    char imeVozenje [100];
    int minuti;
    float cena;
    int studentskiPopust;
};
typedef struct Vozenje Vozenje;
struct ZabavenPark
{
    char imeZabavenPark [100];
    char lokacija[100];
    Vozenje vozenja[100];
    int brVozenja;
};
typedef struct ZabavenPark ZabavenPark;
void print(ZabavenPark z[] , int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("%s %s\n",z[i].imeZabavenPark,z[i].lokacija);
        for(j=0;j<z[i].brVozenja;j++)
        {
            printf("%s %d %.2f\n",z[i].vozenja[j].imeVozenje,z[i].vozenja[j].minuti,z[i].vozenja[j].cena);
        }
    }
}
void najdobar_park(ZabavenPark z[] , int n)
{
    int i , j , max = 0 , maxid = 0 , maxvozenja = 0 , najpopusti , vozenja;
    for(i = 0; i < n; i++)
    {
        najpopusti = 0;
        vozenja = 0;
        for(j = 0; j < z[i].brVozenja;j++)
        {
            if(z[i].vozenja[j].studentskiPopust == 1)
            {
                najpopusti++;
            }
            vozenja += z[i].vozenja[j].minuti;
        }
        if(najpopusti > max)
        {
            max = najpopusti;
            maxid = i;
            maxvozenja = vozenja;
        }
        else if (najpopusti == max && vozenja > maxvozenja)
        {
            maxid = i;
            maxvozenja = vozenja;
        }
    }
    printf("Najdobar park: %s %s",z[maxid].imeZabavenPark,z[maxid].lokacija);
}
int main()
{
    int i, j, n, broj;
	ZabavenPark ff[100];
	scanf("%d", &n);
    for (i = 0; i < n; i++){
		scanf("%s", ff[i].imeZabavenPark);
		scanf("%s", ff[i].lokacija);
        scanf("%d", &ff[i].brVozenja);
		for (j = 0; j < ff[i].brVozenja; j++){
			scanf("%s", ff[i].vozenja[j].imeVozenje);
			scanf("%d", &ff[i].vozenja[j].minuti);
			scanf("%f", &ff[i].vozenja[j].cena);
            scanf("%d", &ff[i].vozenja[j].studentskiPopust);
		}
}
    print(ff,n);
    najdobar_park(ff,n);
    return 0;
}
