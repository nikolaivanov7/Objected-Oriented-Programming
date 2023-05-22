#include <stdio.h>
#include <string.h>
struct Tanc
{
    char ime [15];
    char zemja [15];
};
typedef struct Tanc Tanc;
struct Tancer
{
    char ime [20];
    char prezime [20];
    Tanc tanci[5];
};
typedef struct Tancer Tancer;
void tancuvanje(Tancer * t , int n , char * zemja)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(strcmp(t[i].tanci[j].zemja,zemja)==0)
            {
               printf("%s %s, %s\n",t[i].ime , t[i].prezime , t[i].tanci[j].ime);
               break;
            }
        }
    }
}
int main ()
{
    int i, j, n;
    char zemja[15];
	Tancer tanceri[5];
    scanf("%d",&n);
    for(i = 0; i < n; i++){
        scanf("%s",&tanceri[i].ime);
        scanf("%s",&tanceri[i].prezime);
        for(j = 0; j < 3; j++){
        	scanf("%s",&tanceri[i].tanci[j].ime);
            scanf("%s",&tanceri[i].tanci[j].zemja);
        }
    }
    scanf("%s",&zemja);
    tancuvanje(tanceri, n, zemja);
}
