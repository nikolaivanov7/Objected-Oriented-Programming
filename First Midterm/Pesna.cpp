#include <iostream>
#include <cstring>
using namespace std;
enum
{
    pop,
    rap,
    rok
};
class Pesna
{
private:
    char * ime;
    int vremetraenje;
    tip type;
void copy (const Pesna & p)
{
    this -> ime = new char [strlen(p.ime)+1];
    strcpy(this->ime,p.ime);
    this->vremetraenje = p.vremetraenje;
    this->type = p.type;
}
public:
    Pesna()
    {

    }
    Pesna(char * ime,int vremetraenje,tip type =)
    {
        this -> ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this -> vremetraenje = vremetraenje;
        this ->type = type;
    }
    Pesna(const Pesna & p)
    {
        copy(p);
    }
    Pesna & operator = (const Pesna & p)
    {
        if(this != &p)
        {
            delete [] ime;
            copy(p);
        }
        return * this;
    }
    ~Pesna()
    {
        delete [] ime;
    }
    void pecati()
    {
        cout<<"\""<<ime<<"\""<<" - "<<vremetraenje<<"min"<<endl;
    }
    int getVremetraenje()
    {
        return vremetraenje;
    }
    char * getIme()
    {
        return ime;
    }
    tip getTip()
    {
        return type;
    }
};
class CD
{
private:
    Pesna pesni [10];
    int brPesni;
    int maxVreme;
void copy(const CD & cd)
{
    this->maxVreme = cd.maxVreme;
    this->brPesni = cd.brPesni;
    for(int i = 0; i < brPesni;i++)
    {
        this->pesni[i] = cd.pesni[i];
    }
}
public:
    CD(Pesna pesni[10] , int brPesni = 0,int maxVreme = 0)
    {
        this->maxVreme = maxVreme;
        this->brPesni = brPesni;
        for(int i = 0; i < brPesni;i++)
        {
            this->pesni[i] = pesni[i];
        }
    }
    CD(const CD & cd)
    {
        copy(cd);
    }
    CD (int maxVreme)
    {
        this->brPesni = 0;
        this->maxVreme = maxVreme;
    }
    CD operator = (const CD & cd)
    {
        if(this != & cd)
        {
            copy(cd);
        }
        return * this;
    }
    Pesna getPesna(int i)
    {
        return pesni[i];
    }
    int getBrPesni
    {
        return brPesni;
    }
    void dodadiPesna (Pesna p)
    {
        int suma = 0;
        if(brPesni < 10)
        {
            for(int i = 0; i < brPesni; i++)
            {
                suma += pesni[i].getVremetraenje();
            }
            if(suma < maxVremetraenje)
            {
                return;
            }
        }
        Pesna * tmp = new Pesna [brPesni + 1];
        for(int i = 0; i < brPesni; i++)
        {
            tmp[i] = pesni[i];
        }
        tmp[brPesni++] = p;
        delete [] pesni;
        pesni = tmp;
    }
    void pecatiPesniPoTip (tip t)
    {
        for(int i = 0; i < brPesni; i++)
        {
            if(pesni[i].getTip() == t)
            {
                pesni[i].pecati();
            }
        }
    }

};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
