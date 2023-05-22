#include <iostream>
#include <cstring>
using namespace std;
class Vozac
{
protected:
    char ime [100];
    int vozrast;
    int brTrki;
    bool veteran;
public:
    Vozac(const char * ime = "" , int vozrast = 0 , int brTrki = 0 , bool veteran = false)
    {
        strcpy(this->ime,ime);
        this->vozrast = vozrast;
        this->brTrki = brTrki;
        this->veteran = veteran;
    }
    friend ostream & operator << (ostream & out , Vozac & v)
    {
        out << v.ime << endl;
        out << v.vozrast << endl;
        out << v.brTrki << endl;
        if(v.veteran == true)
        {
            out << "VETERAN" << endl;
        }
        return out;
    }
    virtual double zarabotuvacka() = 0;
    virtual double danok() = 0;
    bool operator == (Vozac & v)
    {
        if(zarabotuvacka() == v.zarabotuvacka())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class Avtomobilist : public Vozac
{
private:
    double cena;
public:
    Avtomobilist(const char * ime = "" , int vozrast = 0 , int brTrki = 0 , bool veteran = false , double cena = 0.0) : Vozac(ime,vozrast,brTrki,veteran)
    {
        this->cena = cena;
    }
    double zarabotuvacka()
    {
        return cena / 5;
    }
    double danok()
    {
        if(brTrki > 10)
        {
            return zarabotuvacka() * 0.15;
        }
        else
        {
            return zarabotuvacka() * 0.1;
        }
    }
    bool operator == (Avtomobilist & v)
    {
        if(zarabotuvacka() == v.zarabotuvacka())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class Motociklist : public Vozac
{
private:
    int mokjnost;
public:
    Motociklist(const char * ime = "" , int vozrast = 0 , int brTrki = 0 , bool veteran = false , int mokjnost = 0) : Vozac(ime,vozrast,brTrki,veteran)
    {
        this->mokjnost = mokjnost;
    }
    double zarabotuvacka()
    {
        return mokjnost * 20;
    }
    double danok()
    {
        if(veteran == true)
        {
            return zarabotuvacka() * 0.25;
        }
        else
        {
            return zarabotuvacka() * 0.2;
        }
    }
    bool operator == (Motociklist & v)
    {
        if(zarabotuvacka() == v.zarabotuvacka())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
int soIstaZarabotuvachka (Vozac ** vozaci , int n , Vozac * pok)
{
    int counter = 0;
    for(int i = 0; i < n; i++)
    {
        if(*pok == *vozaci[i])
        {
            counter++;
        }
    }
    return counter;
}
int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
