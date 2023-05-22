#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5
struct RabotnaNedela
{
    int casovi[DENOVI];
    int nedela;
};
typedef struct RabotnaNedela RabotnaNedela;
struct Rabotnik
{
    char ime [50];
    RabotnaNedela nedeli [NEDELI];
};
typedef struct Rabotnik Rabotnik;
int maxNedela (Rabotnik * r)
{
    int i , j , tmp , vkupno = 0 , max = 0 ;
    for(i = 0; i < 5; i++)
    {
        max += r -> nedeli[0].casovi[i];
        tmp = 1;
    }
    for(i = 1; i < 4; i++)
    {
        vkupno = 0;
        for(j = 0; j < 5; j++)
        {
            vkupno += r->nedeli[i].casovi[j];
        }
        if(vkupno > max)
        {
            max = vkupno;
            tmp = i + 1;
        }
    }
    return tmp;
}
void table(Rabotnik * r , int n)
{
  int i , j ,k, vkupno , vkupno2;
  printf("Rab\t1\t2\t3\t4\tVkupno\n");
  for(int i = 0; i< n; i++)
  {
      vkupno2 = 0;
      printf("%s\t",r[i].ime);
      for(j = 0; j < 4; j++)
      {
          vkupno = 0;
          for(k = 0; k < 5;k++)
          {
              vkupno += r[i].nedeli[j].casovi[k];
          }
          vkupno2 += vkupno;
          printf("%d\t",vkupno);
      }
      printf("%d\n",vkupno2);
  }
}
int main() {
    int n;
    scanf("%d", &n);
    Rabotnik rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}

