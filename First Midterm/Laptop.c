#include <stdio.h>
#include <string.h>
struct Laptop
{
    char firma [100];
    float golemina;
    int touch;
    int cena;
};
typedef struct Laptop Laptop;
struct ITStore
{
    char prodavnica [100];
    char lokacija [100];
    Laptop laptopi[100];
    int brLaptopi;
};
typedef struct ITStore ITStore;
void print(ITStore it[] , int n)
{
    int i , j;
    for(int i = 0; i < n; i++)
    {
        printf("%s %s\n",it[i].prodavnica , it[i].lokacija);
        for(j = 0 ; j < it[i].brLaptopi; j++)
        {
            printf("%s %.1f %d\n",it[i].laptopi[j].firma,it[i].laptopi[j].golemina,it[i].laptopi[j].cena);
        }
    }
}
void najeftina_ponuda(ITStore it[] , int n)
{

}

int main()
{
    int n;
    scanf("%d",&n);
    ITStore it[100];
    for(int i = 0; i < n; i++)
    {
        scanf("%s",&it[i].prodavnica);
        scanf("%s",&it[i].lokacija);
        scanf("%d",&it[i].brLaptopi);
        for(int j = 0; j < it[i].brLaptopi;j++)
        {
            scanf("%s",&it[i].laptopi[j].firma);
            scanf("%f",&it[i].laptopi[j].golemina);
            scanf("%d",&it[i].laptopi[j].touch);
            scanf("%d",&it[i].laptopi[j].cena);
        }
    }
    print(it,n);
    return 0;
}
