#include <stdio.h>
struct Igrac
{
    char korisnickoIme [15];
    int nivo;
    int osvoeniPoeni;
};
typedef struct Igrac Igrac;
struct KompjuterskaIgra
{
    char imeNaIgra [20];
    Igrac igraci [30];
    int brIgraci;
};
typedef struct KompjuterskaIgra KompjuterskaIgra;
void najdobarIgrac (KompjuterskaIgra * igri , int n)
{
    int indeksNajmnoguIgraci = 0;
    for(int i = 0; i < n; i++)
    {
        if(igri[i].brIgraci > igri[indeksNajmnoguIgraci].brIgraci)
        {
            indeksNajmnoguIgraci = i;
        }
    }
    KompjuterskaIgra najpopularna = igri[indeksNajmnoguIgraci];
    int indeksmax = 0;
    for(int i = 1; i < najpopularna.brIgraci;i++)
    {
        if(najpopularna.igraci[i].osvoeniPoeni>najpopularna.igraci[indeksmax].osvoeniPoeni)
        {
            indeksmax=i;
        }
        else if (najpopularna.igraci[i].osvoeniPoeni==najpopularna.igraci[indeksmax].osvoeniPoeni)
        {
            if (najpopularna.igraci[i].nivo>najpopularna.igraci[indeksmax].nivo)
            {
                indeksmax=i;
            }
        }
    }
    printf("Najdobar igrac e igracot so korisnicko ime %s koj ja igra igrata %s",najpopularna.igraci[indeksmax].korisnickoIme,najpopularna.imeNaIgra);
}
int main()
{
    int n , m;
    char ime[20];
    scanf("%d",&n);
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova[100];
        scanf("%s %d",&nova[i].imeNaIgra,&nova[i].brIgraci);
        Igrac pole[30];
        for (int j = 0; j < nova[i].brIgraci; j++) {
            scanf("%s %d %d",&nova[i].igraci[j].korisnickoIme,&nova[i].igraci[j].nivo,&nova[i].igraci[j].osvoeniPoeni);
        }
        poleigri[i]=nova[i];
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
