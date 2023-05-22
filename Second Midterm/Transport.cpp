#include <iostream>
#include <cstring>
using namespace std;
class Transport
{
protected:
    char destination[100];
    int osnovnaCena;
    int rastojanie;
public:
     Transport(char * destination = "" , int osnovnaCena = 0 , int rastojanie = 0)
     {
         strcpy(this->destination,destination);
         this->osnovnaCena = osnovnaCena;
         this->rastojanie = rastojanie;
     }
     virtual int cenaTransport()
     {
         return osnovnaCena;
     }
     bool operator < (Transport & t)
     {
         if(this->rastojanie < t.rastojanie)
         {
             return true;
         }
         else
         {
             return false;
         }
     }
     int getCena()
     {
         return osnovnaCena;
     }
     char * getDestinacija()
     {
         return destination;
     }
     int getRastojanie()
     {
         return rastojanie;
     }
};
class AvtomobilTransport : public Transport
{
private:
    bool shofer;
public:
    AvtomobilTransport(char * destination = "" , int osnovnaCena = 0 , int rastojanie = 0 , bool shofer = false) : Transport(destination,osnovnaCena,rastojanie)
    {
        this->shofer = shofer;
    }
    int cenaTransport()
    {
        if(shofer == true)
        {
            return osnovnaCena + osnovnaCena * 0.2;
        }
        else
        {
            return osnovnaCena;
        }
    }
};
class KombeTransport : public Transport
{
private:
    int brLugje;
public:
    KombeTransport(char * destination = "" , int osnovnaCena = 0 , int rastojanie = 0 , int brLugje = 0) : Transport(destination,osnovnaCena,rastojanie)
    {
        this->brLugje = brLugje;
    }
    int cenaTransport()
    {
        return osnovnaCena - (brLugje * 200);
    }
};
void pecatiPoloshiPonudi (Transport ** niza, int n , Transport & t)
{
    for(int i = 0; i < n; i++)
    {
        if(niza[i]->getCena() > t.getCena())
        {
            cout<<niza[i]->getDestinacija()<<" "<<niza[i]->getRastojanie()<<" "<<niza[i]->cenaTransport()<<endl;
        }
    }
}
int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}

