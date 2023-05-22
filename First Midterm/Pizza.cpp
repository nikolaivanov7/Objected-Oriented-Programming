#include <iostream>
#include <cstring>
using namespace std;
class Pica
{
    char ime [15];
    int cena;
    char * sostojki;
    int namaluvanje;
    void copy(const Pica & p)
    {
        strcpy(this->ime,p.ime);
        this->cena = p.cena;
        this-> sostojki = new char [strlen(p.sostojki)+1];
        strcpy(this->sostojki,p.sostojki);
        this->namaluvanje = p.namaluvanje;
    }
public:
    Pica()
    {
        char * ime = "";
        cena = 0;
        this->sostojki = new char [0];
        namaluvanje = 0;
    }
    Pica(char * ime, int cena , char * sostojki, int namaluvanje)
    {
        strcpy(this->ime,ime);
        this->cena = cena;
        this-> sostojki = new char [strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->namaluvanje = namaluvanje;
    }
    Pica(const Pica & p)
    {
        copy(p);
    }
    Pica & operator = (const Pica & p)
    {
        if(this != &p)
        {
            delete [] this->sostojki;
            copy(p);
        }
        return * this;
    }
    ~Pica()
    {
        delete [] sostojki;
    }
    void pecati()
    {
        cout<<ime<<" - "<<sostojki<<", "<<cena<<" "<<cena-cena*namaluvanje/100<<endl;
    }
    bool istiSe(Pica p)
    {
        if(strcmp(this->sostojki,p.sostojki)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    char * getSostojki()
    {
        return sostojki;
    }
    int getNamaluvanje()
    {
        return namaluvanje;
    }
};
class Picerija
{
    char ime [15];
    Pica * pici;
    int brPici;
    void copy(const Picerija & pc)
    {
        strcpy(this->ime,pc.ime);
        this->brPici = pc.brPici;
        pici = new Pica [this->brPici];
        for(int i = 0; i < this->brPici;i++)
        {
            this->pici[i] = pc.pici[i];
        }
    }
public:
    Picerija()
    {
        char * ime = "";
        this->pici = new Pica[0];
        int brPici = 0;
    }
    Picerija(char * ime , Pica * pici , int brPici)
    {
        strcpy(this->ime,ime);
        this->pici = new Pica [this->brPici];
        for(int i = 0; i < this->brPici;i++)
        {
            this->pici[i] = pici[i];
        }
        this->brPici = brPici;
    }
    Picerija(char * ime)
    {
        strcpy(this->ime,ime);
        pici = new Pica [0];
        this->brPici = 0;
    }
    Picerija(const Picerija & pc)
    {
        copy(pc);
    }
    Picerija & operator = (const Picerija & pc)
    {
        if(this != &pc)
        {
            delete [] pici;
            copy(pc);
        }
        return * this;
    }
    ~Picerija()
    {
        delete [] pici;
    }
    void dodadi (Pica P)
    {
        for(int i = 0; i < brPici; i++)
        {
            if(strcmp(P.getSostojki(),pici[i].getSostojki())==0)
            {
                return;
            }
        }
        Pica * tmp = new Pica [brPici+1];
        for(int i = 0; i < brPici; i++)
        {
            tmp[i] = pici[i];
        }
        delete [] this -> pici;
        this->pici = tmp;
        this->pici[this->brPici] = P;
        this->brPici++;
    }
    void piciNaPromocija()
    {
        for(int i = 0; i < brPici; i++)
        {
            if(pici[i].getNamaluvanje() > 0)
            {
                pici[i].pecati();
            }
        }
    }
    void setIme(char * ime)
    {
        strcpy(this->ime,ime);
    }
     char * getIme()
    {
        return this->ime;
    }
};
int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
