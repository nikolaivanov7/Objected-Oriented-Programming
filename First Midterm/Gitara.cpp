#include <iostream>
#include <cstring>
using namespace std;
class Gitara
{
    char seriskiBr [25];
    float nabavnaCena;
    int godina;
    char tip [40];
    void copy(const Gitara & p)
    {
        strcpy(this->seriskiBr,p.seriskiBr);
        this->nabavnaCena = p.nabavnaCena;
        this->godina = p.godina;
        strcpy(this->tip,p.tip);
    }
public:
    Gitara()
    {
        strcpy(seriskiBr,"");
        nabavnaCena = 0.0;
        godina = 0;
        strcpy(tip,"");
    }
    Gitara(char * tip , char * seriskiBr , int godina , float nabavnaCena)
    {
        strcpy(this->seriskiBr,seriskiBr);
        this->nabavnaCena = nabavnaCena;
        this->godina = godina;
        strcpy(this->tip,tip);
    }
    Gitara(const Gitara & g)
    {
        copy(g);
    }
    Gitara & operator = (const Gitara & g)
    {
        if(this != &g)
        {
            copy(g);
        }
        return * this;
    }
    ~Gitara()
    {

    }
    bool daliIsti(Gitara & g)
    {
        return strcmp(this->seriskiBr,g.seriskiBr)==0;
    }
    void pecati()
    {
        cout<<seriskiBr<<" "<<tip<<" "<<nabavnaCena<<endl;
    }
    float getNabavna()
    {
        return nabavnaCena;
    }
    int getGodina()
    {
        return godina;
    }
    char * getTip()
    {
        return tip;
    }
    char * getSeriski()
    {
        return seriskiBr;
    }
};
class Magacin
{
    char ime[30];
    char lokacija[60];
    int godinaNaOtvaranje;
    Gitara * gitari;
    int brGitari;
void copy(const Magacin & m)
{
    strcpy(this->ime,m.ime);
        strcpy(this->lokacija,m.lokacija);
        this->gitari = new Gitara [m.brGitari];
        this->brGitari = m.brGitari;
        this->godinaNaOtvaranje = m.godinaNaOtvaranje;
        for(int i = 0; i < m.brGitari;i++)
        {
            this->gitari[i] = m.gitari[i];
        }
}
public:
    Magacin(char * ime = "" , char * lokacija = "" , int godinaNaOtvaranje = 0)
    {
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->godinaNaOtvaranje = godinaNaOtvaranje;
        gitari = NULL;
        brGitari = 0;
    }
    Magacin(const Magacin & m)
    {
        copy(m);
    }
    Magacin & operator = (const Magacin & m)
    {
        if(this != &m)
        {
            delete [] gitari;
            copy(m);
        }
        return * this;
    }
    ~Magacin()
    {
        delete [] gitari;
    }
    double vrednost()
    {
        double value = 0;
        for(int i = 0; i < brGitari;i++)
        {
            value += gitari[i].getNabavna();
        }
        return value;
    }
    void dodadi(Gitara & d)
    {
        Gitara * tmp = new Gitara[brGitari+1];
        for(int i = 0 ; i < brGitari;i++)
        {
            tmp[i] = gitari[i];
        }
        tmp[brGitari++] = d;
        delete [] gitari;
        gitari = tmp;
    }
    void prodadi(Gitara p)
    {
        int newBr = 0;
        for(int i = 0; i < brGitari; i++)
        {
            if(gitari[i].daliIsti(p)==false)
            {
                newBr++;
            }
        }
        Gitara * tmp = new Gitara [newBr];
        int j = 0;
        for(int i = 0; i < brGitari; i++)
        {
            if(gitari[i].daliIsti(p)==false)
            {
            tmp[j] = gitari[i];
            j++;
            }
        }
        delete [] gitari;
        gitari = tmp;
        brGitari = newBr;
    }
    void pecati(bool daliNovi)
    {
        cout<<ime<<" "<<lokacija<<endl;
        for(int i = 0; i < brGitari; i++)
        {
            if(daliNovi==true && gitari[i].getGodina()>godinaNaOtvaranje)
            {
                gitari[i].pecati();
            }
            else if(daliNovi == false)
            {
                gitari[i].pecati();
            }
        }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}
