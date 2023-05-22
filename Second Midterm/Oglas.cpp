#include <iostream>
#include <cstring>
using namespace std;
class NegativnaVrednost
{
private:
    char msg[50];
public:
    NegativnaVrednost(char * msg = "")
    {
        strcpy(this->msg,msg);
    }
    void message()
    {
        cout<<msg;
    }
};
class Oglas
{
    char naslov [50];
    char kategorija [30];
    char opis[100];
    double cena;
public:
    Oglas(const char * naslov = "" ,const char * kategorija = "", const char * opis = "" , double cena = 0.0)
    {
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena = cena;
    }
    bool operator > (Oglas & o)
    {
        if(this->cena > o.cena)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend ostream & operator << (ostream & out , Oglas & o)
    {
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        return out;
    }
    double getCena()
    {
        return cena;
    }
    char * getKategorija()
    {
        return kategorija;
    }
};
class Oglasnik
{
    char ime [20];
    Oglas * oglasi;
    int brOglasi;
public:
    Oglasnik(const char * ime = "" , Oglas * oglasi = new Oglas [0] , int brOglasi = 0)
    {
        strcpy(this->ime,ime);
        this->brOglasi = brOglasi;
        oglasi = new Oglas [brOglasi];
        for(int i = 0; i < brOglasi; i++)
        {
            this->oglasi[i] = oglasi[i];
        }
    }
    Oglasnik(const Oglasnik & o)
    {
        strcpy(this->ime,o.ime);
        this->brOglasi = o.brOglasi;
        oglasi = new Oglas [o.brOglasi];
        for(int i = 0; i < o.brOglasi; i++)
        {
            this->oglasi[i] = o.oglasi[i];
        }
    }
    Oglasnik & operator = (const Oglasnik & o)
    {
        if(this != &o)
        {
        delete [] oglasi;
        strcpy(this->ime,o.ime);
        this->brOglasi = o.brOglasi;
        oglasi = new Oglas [o.brOglasi];
        for(int i = 0; i < o.brOglasi; i++)
        {
            this->oglasi[i] = o.oglasi[i];
        }
        }
        return * this;
    }
    ~Oglasnik()
    {
        delete [] oglasi;
    }
    Oglasnik & operator += (Oglas & og)
    {
        if(og.getCena() < 0)
        {
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran! \n");
        }
        else{
        Oglas * tmp = new Oglas [brOglasi+1];
        for(int i = 0; i < brOglasi; i++)
        {
            tmp[i] = oglasi[i];
        }
        tmp[brOglasi++] = og;
        delete [] oglasi;
        oglasi = tmp;
        }
        return * this;
    }
    friend ostream & operator << (ostream & out , Oglasnik & og)
    {
         cout << og.ime << endl;
         for(int i = 0; i < og.brOglasi; i++)
         {
             out<<og.oglasi[i]<<endl;
         }
         return out;
    }
    void oglasiOdKategorija(const char *k)
    {
        for(int i = 0; i < brOglasi; i++)
        {
            if(strcmp(oglasi[i].getKategorija(),k) == 0)
            {
                cout<<oglasi[i]<<endl;
            }
        }
    }
    void najniskaCena()
    {
        double minPrice = oglasi[0].getCena();
        int ind = 0;
        for(int i = 1; i < brOglasi; i++)
        {
            if(oglasi[i].getCena() < minPrice)
            {
                minPrice = oglasi[i].getCena();
                ind = i;
            }
        }
        cout<<oglasi[ind]<<endl;
    }
};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
			ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
