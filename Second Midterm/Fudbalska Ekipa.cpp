#include <iostream>
#include <cstring>
using namespace std;
class FudbalskaEkipa
{
protected:
    char trener [100];
    int golovi [10];
public:
    FudbalskaEkipa(char * trener , int * golovi)
    {
        strcpy(this->trener,trener);
        for(int i = 0; i < 10; i++)
        {
            this->golovi[i] = golovi[i];
        }
    }
    FudbalskaEkipa & operator += (int nov)
    {
        int novi[10];
        for(int i=0; i<9; i++)
            novi[i]=golovi[i+1];
        novi[9]=nov;
        for(int i=0; i<10; i++)
            golovi[i]=novi[i];
        return *this;
    }
    virtual char * getIme() = 0;
    virtual int uspeh() = 0;
    friend ostream & operator << (ostream & out , FudbalskaEkipa & f)
    {
        out<<f.getIme()<<endl;
        out<<f.trener<<endl;
        out<<f.uspeh()<<endl;
        return out;
    }
    bool operator > (FudbalskaEkipa & f)
    {
        return uspeh() > f.uspeh();
    }
};
class Klub : public FudbalskaEkipa
{
private:
    char ime [100];
    int brTituli;
public:
    Klub(char * trener , int * golovi,char * ime , int brTituli) : FudbalskaEkipa(trener,golovi)
    {
        strcpy(this->ime,ime);
        this->brTituli = brTituli;
    }
    friend ostream & operator << (ostream & out , Klub & k)
    {
        out<<k.ime<<endl;
        out<<k.trener<<endl;
        out<<k.uspeh()<<endl;
        return out;
    }
    char * getIme()
    {
        return ime;
    }
    int uspeh()
    {
        int suma = 0;
        for(int i = 0; i < 10; i++)
        {
            suma += golovi[i];
        }
        return (suma * 3) + (brTituli * 1000);
    }
};
class Reprezentacija : public FudbalskaEkipa
{
    char drzhava [100];
    int brNastapi;
public:
    Reprezentacija(char * trener , int * golovi,char * drzhava,int brNastapi) : FudbalskaEkipa(trener,golovi)
    {
        strcpy(this->drzhava,drzhava);
        this->brNastapi = brNastapi;
    }
    friend ostream & operator << (ostream & out , Reprezentacija & r)
    {
        out<<r.drzhava<<endl;
        out<<r.trener<<endl;
        out<<r.uspeh()<<endl;
        return out;
    }
    int uspeh()
    {
        int suma = 0;
        for(int i = 0; i < 10; i++)
        {
            suma += golovi[i];
        }
        return (suma * 3) + (brNastapi * 50);
    }
    char * getIme()
    {
        return drzhava;
    }
};
void najdobarTrener (FudbalskaEkipa ** niza , int n)
{
    int indeks = 0;
    int max = 0;
    for(int i = 0; i < n; i++)
    {
        if(niza[i]->uspeh() > max)
        {
            max = niza[i]->uspeh();
            indeks = i;
        }
    }
    cout<<*niza[indeks];
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
