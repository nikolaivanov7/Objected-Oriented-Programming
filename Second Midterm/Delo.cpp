#include <iostream>
#include <cstring>
using namespace std;
class Delo
{
    char ime [50];
    int godina;
    char zemja [50];
public:
    Delo(char * ime = "" , int godina = 0 , char * zemja = "")
    {
        strcpy(this->ime,ime);
        this->godina = godina;
        strcpy(this->zemja,zemja);
    }
    bool operator == (Delo & d)
    {
        if(strcmp(this->ime,d.ime) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int getGodina()
    {
        return godina;
    }
    char * getZemja()
    {
        return zemja;
    }
    char * getIme()
    {
        return ime;
    }
};
class Pretstava
{
protected:
    Delo d;
    int brProdadeniKarti;
    char data [15];
public:
    Pretstava()
    {
        this->brProdadeniKarti = 0;
        strcpy(this->data,"");
    }
    Pretstava(Delo d , int brProdadeniKarti , char * data)
    {
        this->d = d;
        this->brProdadeniKarti = brProdadeniKarti;
        strcpy(this->data,data);
    }
    Delo getDelo()
    {
        return d;
    }
    int getBrProdadeniKarti()
        {
            return brProdadeniKarti;
        }
    virtual int cena()
    {
        int n = 0 , m = 0;
        if(d.getGodina() >= 1900 && d.getGodina() <= 2099)
        {
            m = 50;
        }
        else if(d.getGodina() >= 1800 && d.getGodina() <= 1899)
        {
            m = 75;
        }
        else
        {
            m = 100;
        }
        if(strcmp(d.getZemja(),"Italija") == 0)
        {
            n = 100;
        }
        else if(strcmp(d.getZemja(),"Rusija") == 0)
        {
            n = 150;
        }
        else
        {
            n = 80;
        }
        return n + m;
    }
};
class Balet : public Pretstava
{
private:
    static int price;
public:
    Balet(Delo d , int brProdadeniKarti , char * data) : Pretstava(d,brProdadeniKarti,data){
    }
    int cena()
    {
        int c = Pretstava ::cena();
        return c + price;
    }
    static void setCenaBalet (int newCena)
    {
        price = newCena;
    }
};
int Balet ::price = 150;
class Opera : public Pretstava
{
public:
    Opera(Delo d , int brProdadeniKarti , char * data) : Pretstava(d,brProdadeniKarti,data){
    }
};
int prihod(Pretstava ** p , int n)
{
    int vkupno = 0;
    for(int i = 0; i < n; i++)
    {
        vkupno += p[i]->cena() * p[i]->getBrProdadeniKarti();
    }
    return vkupno;
}
int brojPretstaviNaDelo(Pretstava ** p , int n , Delo  &d)
{
    int counter = 0;
    for(int i = 0; i < n; i++)
    {
        if(p[i]->getDelo() == d)
        {
            counter++;
        }
    }
    return counter;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
