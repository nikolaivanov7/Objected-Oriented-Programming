#include<iostream>
#include<string.h>
using namespace std;
class OutOfBoundException{};
class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(){}
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
    bool getDopolnitelenPin()
    {
        return povekjePin;
    }
    virtual int tezinaProbivanje()
    {
        int br=0;
        int p = pin;
        while(p>0)
        {
            br++;
            p/=10;
        }
        return br;
    }
    friend ostream& operator<<(ostream &out,Karticka &k)
    {
        out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return out;
    }
    char* getSmetka()
    {
        return smetka;
    }
    virtual ~Karticka(){}

};
class SpecijalnaKarticka : public Karticka
{
private:
   int *dopolnitelni;
   int brDopolnitelni;
   const static int P;

public:
    SpecijalnaKarticka()
    {
        brDopolnitelni =0;
        dopolnitelni = new int [brDopolnitelni];
    }
    SpecijalnaKarticka(char* smetka,int pin) : Karticka(smetka,pin)
    {
        brDopolnitelni =0;
        dopolnitelni = new int [brDopolnitelni];
    }
    /*SpecijalnaKarticka& operator = (SpecijalnaKarticka &sc)
    {
        if(this!=&sc)
        {
            brDopolnitelni =sc.brDopolnitelni;
            dopolnitelni = new int [sc.brDopolnitelni];
            for(int i=0;i<sc.brDopolnitelni;i++)
            {
                dopolnitelni[i] = sc.dopolnitelni[i];
            }
            this->pin=sc.pin;
            this->povekjePin=sc.povekjePin;
        }
        return *this;
    }*/
    SpecijalnaKarticka& operator+=(int nov)
    {
        if(brDopolnitelni==P)
            throw OutOfBoundException();
        int *temp;
        temp = new int[brDopolnitelni+1];
        for(int i=0;i<brDopolnitelni;i++)
        {
            temp[i] = dopolnitelni[i];
        }
        temp[brDopolnitelni] = nov;
        brDopolnitelni++;
        delete []dopolnitelni;
        dopolnitelni = temp;
        return *this;
    }
    int tezinaProbivanje()
    {
        int t = Karticka::tezinaProbivanje();
        return t +brDopolnitelni;
    }
    ~SpecijalnaKarticka()

    {
        //delete []dopolnitelni;
    }
};
const int SpecijalnaKarticka::P = 4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    static void setLIMIT(int l)
    {
        LIMIT = l;
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }

    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->tezinaProbivanje()<=LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(smetka,karticki[i]->getSmetka())==0)
            {
                SpecijalnaKarticka *s = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(s!=0)
                {
                    *s+=novPin;
                }
            }
        }
    }
};
int Banka::LIMIT = 7;
int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

   komercijalna.dodadiDopolnitelenPin(smetka,pin);

}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
