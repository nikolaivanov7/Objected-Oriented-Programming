#include <stdio.h>
#include <string.h>
struct Voz
{
    char relacija [50];
    int kilometri;
    int brPatnici;
};
typedef struct Voz Voz;
struct ZeleznickaStanica
{
    char grad [20];
    Voz vozovi[30];
    int brVozovi;
};
typedef struct ZeleznickaStanica ZeleznickaStanica;
void najkratkaRelacija(ZeleznickaStanica * zs , int n , char * grad)
{
    int najkratka = 2147483647 , ind_i = 0 , ind_j = 0;
    for(int i = 0 ; i< n; i++)
    {
        if(strcmp(zs[i].grad,grad)==0)
        {
            for(int j = 0; j < zs[i].brVozovi;j++)
            {
                if(zs[i].vozovi[j].kilometri <= najkratka)
                {
                    ind_i = i;
                    ind_j = j;
                    najkratka = zs[i].vozovi[j].kilometri;
                }
            }
        }
    }
    printf("Najkratka relacija: %s (%d km)",zs[ind_i].vozovi[ind_j].relacija,zs[ind_i].vozovi[ind_j].kilometri);
}
int main ()
{
    int n;
    scanf("%d",&n);
    ZeleznickaStanica zStanica[100];
    for(int i = 0; i < n; i++)
    {
        scanf("%s %d",zStanica[i].grad,&zStanica[i].brVozovi);
        for(int j = 0; j < zStanica[i].brVozovi;j++)
        {
            scanf("%s %d %d",zStanica[i].vozovi[j].relacija,&zStanica[i].vozovi[j].kilometri,&zStanica[i].vozovi[j].brPatnici);
        }
    }
    char grad[25];
    scanf("%s",grad);
    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
