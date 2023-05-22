#include <iostream>
#include <cstring>
using namespace std;
class Exception
{
    private:
    char msg[50];
public:
    Exception(char * msg = "") {
        strcpy(this->msg, msg);
    }
    void showMessage() {
        cout<<msg;
    }
};
class Trud
{
    protected:
    char vid;
    int godina;
public:
    Trud(char  vid = 'A', int godina = 0)
    {
        this->vid,vid;
        this->godina = godina;
    }
    char getVid()
    {
        return vid;
    }
    int getGodina() {
        return godina;
    }
    friend istream &operator>>(istream &i, Trud &t){
    i>>t.vid>>t.godina;
        return i;
    }
};
class Student
{
protected:
    char ime [30];
    int indeks;
    int godNaUpis;
    int * lista;
    int brPolozeni;
public:
    Student(char * ime = "" , int indeks = 0 , int godNaUpis = 0 , int * lista = new int [0] , int brPolozeni = 0)
    {
        strcpy(this->ime,ime);
        this->indeks = indeks;
        this->godNaUpis = godNaUpis;
        this->lista = new int [brPolozeni];
        for(int i = 0; i < brPolozeni; i++)
        {
            this->lista[i] = lista[i];
        }
        this->brPolozeni = brPolozeni;
    }
    Student(const Student & s)
    {
        strcpy(this->ime,s.ime);
        this->indeks = s.indeks;
        this->godNaUpis = s.godNaUpis;
        this->lista = new int [s.brPolozeni];
        for(int i = 0; i < s.brPolozeni; i++)
        {
            this->lista[i] = s.lista[i];
        }
        this->brPolozeni = s.brPolozeni;
    }
    Student & operator = (const Student & s)
    {
        if(this != &s)
        {
        delete [] lista;
        strcpy(this->ime,s.ime);
        this->indeks = s.indeks;
        this->godNaUpis = s.godNaUpis;
        this->lista = new int [s.brPolozeni];
        for(int i = 0; i < s.brPolozeni; i++)
        {
            this->lista[i] = s.lista[i];
        }
        this->brPolozeni = s.brPolozeni;
        }
        return * this;
    }
    virtual double rang()
    {
        double sum = 0.0;
        for(int i = 0; i < brPolozeni; i++)
        {
            sum += lista[i];
        }
        double avg = sum / brPolozeni;
        return avg;
    }
    friend ostream & operator << (ostream & out , Student & s)
    {
        out << s.indeks << " "  << s.ime << " " << s.godNaUpis << " " << s.rang() << endl;
    }
    ~Student()
    {
        delete [] lista;
    }
};
class PhDStudent : public Student
{
private:
    Trud * trudovi;
    int brTrudovi;
public:
    PhDStudent()
    {
        this->brTrudovi = 0;
        this->trudovi = new Trud [0];
    }
    PhDStudent(char * ime , int indeks, int godNaUpis, int * lista, int brPolozeni , Trud *trudovi , int brTrudovi) : Student(ime,indeks,godNaUpis,lista,brPolozeni)
    {
        this->brTrudovi = brTrudovi;
        this->trudovi = new Trud [brTrudovi];
        for(int i = 0; i < brTrudovi; i++)
        {
            this->trudovi[i] = trudovi[i];
        }
    }
    PhDStudent(const PhDStudent & p) : Student(p)
    {
        this->brTrudovi = p.brTrudovi;
        this->trudovi = new Trud [p.brTrudovi];
        for(int i = 0; i < p.brTrudovi; i++)
        {
            this->trudovi[i] = p.trudovi[i];
        }
    }
    PhDStudent & operator = (const PhDStudent & p)
    {
        if(this != &p)
        {
        delete [] trudovi;
        Student :: operator = (p);
        this->brTrudovi = p.brTrudovi;
        this->trudovi = new Trud [p.brTrudovi];
        for(int i = 0; i < p.brTrudovi; i++)
        {
            this->trudovi[i] = p.trudovi[i];
        }
        }
        return * this;
    }
    double rang()
    {
        double bodovi = 0.0;
        for(int i = 0; i < brTrudovi; i++)
        {
            if(trudovi[i].getVid() == 'c')
            {
                bodovi++;
            }
            else if(trudovi[i].getVid() == 'j')
            {
                bodovi = bodovi + 3;
            }
        }
        return Student::rang() + bodovi;
    }
    PhDStudent & operator += (Trud & t)
    {
        if(t.getGodina() > godNaUpis)
        {
           throw Exception("Ne moze da se vnese dadeniot trud\n");
        }
        Trud * tmp = new Trud [brTrudovi + 1];
        for(int i = 0; i < brTrudovi; i++)
        {
            tmp[i] = trudovi[i];
        }
        tmp[brTrudovi++] = t;
        delete [] trudovi;
        trudovi = tmp;
        return * this;
    }
     ~PhDStudent() {
        delete [] trudovi;
    }
};
int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
