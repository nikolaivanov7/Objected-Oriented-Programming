#include<stdio.h>
#include<ctype.h>
#include<string.h>
struct Pacient
{
    char nameLastname[100];
    int insurance;
    int visits;
};
typedef struct Pacient Pacient;
struct MaticenLekar
{
    char name[100];
    int numOfPacients;
    Pacient array[200];
    float price;
};
typedef struct MaticenLekar MaticenLekar;
int countVisits(MaticenLekar m)
{
    int i, visits = 0;
    for(i = 0; i<m.numOfPacients; i++)
    {
        visits += m.array[i].visits;
    }
    return visits;
}
float countIncome(MaticenLekar m)
{
    int i, unInsured = 0;
    float income = 0.0;
    for(i = 0; i<m.numOfPacients; i++)
    {

        if(m.array[i].insurance == 0)
        {
            unInsured += m.array[i].visits;
        }
    }
    income = unInsured*m.price;
    return income;
}

int cmpDoctors(MaticenLekar m1, MaticenLekar m2)
{
    if(countIncome(m1) > countIncome(m2))
    {
        return 1;
    }
    else if(countIncome(m1) < countIncome(m2))
    {
        return -1;
    }
    else
    {
        if(countVisits(m1) > countVisits(m2))
        {
            return 1;
        }
        else if(countVisits(m1) < countVisits(m2))
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}
void najuspesen_doktor(MaticenLekar *m, int n)
{
    int i;
    MaticenLekar best = m[0];
    for(i = 1; i<n; i++)
    {
        if(cmpDoctors(m[i], best) > 0)
        {
            best = m[i];
        }
    }
    printf("%s ", best.name);
    printf("%.2f", countIncome(best));
    printf(" %d", countVisits(best));
}
int main()
{
    MaticenLekar m[100];
    int i, j, n;
    scanf("%d", &n);
    for(i = 0; i<n; i++)
    {
        scanf("%s", &m[i].name);
        scanf("%d", &m[i].numOfPacients);
        scanf("%f", &m[i].price);
        for(j = 0; j<m[i].numOfPacients; j++)
        {
            scanf("%s", &m[i].array[j].nameLastname);
            scanf("%d", &m[i].array[j].insurance);
            scanf("%d", &m[i].array[j].visits);
        }
    }
    najuspesen_doktor(m, n);
}
