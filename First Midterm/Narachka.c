#include <stdio.h>
#include <string.h>
struct Proizvod
{
    char kod[20];
    int cena;
    int brDostapniProizvodi;
};
typedef struct Proizvod Proizvod;
struct Narachka
{
    char ime[15];
    Proizvod proizvodi[10];
    char Naracani[10];
    int brProizvodiNaracani;
};
typedef struct Narachka Narachka;
void pecatiFaktura (Narachka n)
{
    printf("Faktura za %s\n", n.ime);
    Proizvod tmp;
    int i , j , vkupno = 0;
    for(i = 0; i < n.brProizvodiNaracani;i++)
    {
        for(j = 0; j < n.brProizvodiNaracani; j++)
        {
            if(strcmp(n.proizvodi[i].kod,n.proizvodi[i].kod)==0)
            {
                tmp = n.proizvodi[i];
                n.proizvodi[i] = n.proizvodi[j];
                n.proizvodi[j] = tmp;
            }
        }
    }
    int flag = 0;
    for(i = 0; i < n.brProizvodiNaracani;i++)
    {
        if(n.Naracani[i] > n.proizvodi[i].brDostapniProizvodi)
        {
            printf("Fakturata ne moze da se izgotvi");
            flag = 1;
            break;
        }
        else
        {
         printf("%s %d %d %d\n",n.proizvodi[i].kod,n.proizvodi[i].cena,n.Naracani[i],n.proizvodi[i].cena * n.Naracani[i]);
         vkupno += n.proizvodi[i].cena * n.Naracani[i];
        }
    }
    if(!flag)
        {
            printf("Vkupnata suma na fakturata e %d",vkupno);
        }

}
int main ()
{
    struct Narachka narachka;
    scanf("%s",&narachka.ime);
    scanf("%d",&narachka.brProizvodiNaracani);
    for(int i = 0; i < narachka.brProizvodiNaracani; i++)
    {
        scanf("%s",&narachka.proizvodi[i].kod);
        scanf("%d",&narachka.proizvodi[i].cena);
        scanf("%d",&narachka.proizvodi[i].brDostapniProizvodi);
        for(int j = 0; j < narachka.brProizvodiNaracani;j++)
    {
        scanf("%d",&narachka.Naracani[j]);
    }
    }
    pecatiFaktura(narachka);
    return 0;
}
