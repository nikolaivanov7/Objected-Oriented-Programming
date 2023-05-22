#include <iostream>
#include <cstring>
using namespace std;
class NoCourseException
{
    private:
    int indeks;
    public:
        NoCourseException(int indeks = 0)
        {
            this->indeks = indeks;
        }
        void showMessage()
        {
            cout << "Demonstratorot so indeks " << indeks << " ne drzi laboratoriski vezbi" << endl;
        }
};
class Kurs
{
    char ime [100];
    int krediti;
public:
   Kurs(const char * ime = "" , int krediti = 0)
   {
       strcpy(this->ime,ime);
       this->krediti = krediti;
   }
   bool operator==(const char *ime) const{
        return strcmp(this->ime,ime)==0;
    }
   void pecati()
   {
       cout << ime << " " << krediti << "ECTS";
   }
};
class Student
{
protected:
    int indeks;
    int * ocenki;
    int brOcenki;
public:
    Student(int indeks = 0,int * ocenki = new int[0] , int brOcenki = 0)
    {
        this->indeks = indeks;
        this->ocenki = new int [brOcenki];
        for(int i = 0; i < brOcenki; i++)
        {
            this->ocenki[i] = ocenki[i];
        }
        this->brOcenki = brOcenki;
    }
    Student(const Student & s)
    {
        this->indeks = s.indeks;
        this->ocenki = new int [s.brOcenki];
        for(int i = 0; i < s.brOcenki; i++)
        {
            this->ocenki[i] = s.ocenki[i];
        }
        this->brOcenki = s.brOcenki;
    }
    Student & operator = (const Student & s)
    {
        if(this != &s)
        {
        delete [] ocenki;
        this->indeks = s.indeks;
        this->ocenki = new int [s.brOcenki];
        for(int i = 0; i < s.brOcenki; i++)
        {
            this->ocenki[i] = s.ocenki[i];
        }
        this->brOcenki = s.brOcenki;
        }
        return * this;
    }
    ~Student()
    {
        delete [] ocenki;
    }
    virtual int getBodovi()
    {
        int passingGrades = 0;
        for(int i = 0; i < brOcenki; i++)
        {
            if(ocenki[i] > 5)
            {
                passingGrades++;
            }
        }
        double avg = (1.0 * passingGrades) / brOcenki;
        int bodovi = avg * 100;
        return bodovi;
    }
    virtual void pecati()
    {
        cout << indeks;
    }
};
class Predavach
{
    protected:
    char * predavach;
    Kurs * kursevi;
    int brKursevi;
public:
    Predavach(char * predavach = new char [0] , Kurs * kursevi = new Kurs [0] , int brKursevi = 0)
    {
        this->predavach = new char [strlen(predavach)+1];
        strcpy(this->predavach,predavach);
        this->kursevi = new Kurs [brKursevi];
        for(int i = 0; i < brKursevi; i++)
        {
            this->kursevi[i] = kursevi[i];
        }
        this->brKursevi = brKursevi;
    }
    Predavach(const Predavach & p)
    {
        this->predavach = new char [strlen(p.predavach)+1];
        strcpy(this->predavach,p.predavach);
        this->kursevi = new Kurs [p.brKursevi];
        for(int i = 0; i < p.brKursevi; i++)
        {
            this->kursevi[i] = p.kursevi[i];
        }
        this->brKursevi = p.brKursevi;
    }
    Predavach & operator = (const Predavach & p)
    {
        if(this != &p)
        {
        delete [] predavach;
        delete [] kursevi;
        this->predavach = new char [strlen(p.predavach)+1];
        strcpy(this->predavach,p.predavach);
        this->kursevi = new Kurs [p.brKursevi];
        for(int i = 0; i < p.brKursevi; i++)
        {
            this->kursevi[i] = p.kursevi[i];
        }
        this->brKursevi = p.brKursevi;
        }
        return * this;
    }
    int getBrojKursevi()
    {
        return brKursevi;
    }
    ~Predavach()
    {
        delete [] predavach;
        delete [] kursevi;
    }
    void pecati()
    {
        cout<<predavach<<" (";
        for(int i = 0; i < brKursevi; i++)
        {
            kursevi[i].pecati();
            if(i < brKursevi - 1)
            {
                cout<<", ";
            }
            else
            {
                cout<<")";
            }
        }
    }
    Kurs operator[](int i){
        if (i<brKursevi&&i>=0)
            return kursevi[i];
        else
            return Kurs();
    }
};
class Demonstrator : public Student, public Predavach
{
private:
    int brCasovi;
public:
    Demonstrator(int indeks = 0,int * ocenki = new int[0] , int brOcenki = 0 , char * predavach = new char [0] , Kurs * kursevi = new Kurs [0] , int brKursevi = 0 ,int brCasovi = 0) : Student(indeks,ocenki,brOcenki) , Predavach(predavach,kursevi,brKursevi)
    {
        this->brCasovi = brCasovi;
    }
    int getBodovi()
    {
        int bodovi = Student :: getBodovi();
        try
        {
            if(brKursevi == 0)
            {
                bodovi = 0;
                throw NoCourseException();
            }
            bodovi += 20 * brCasovi / brKursevi;
        }
        catch(NoCourseException &)
        {
            NoCourseException e(indeks);
            e.showMessage();
        }
        return bodovi;
    }
    void pecati()
    {
        Student :: pecati();
        cout <<": ";
        Predavach::pecati();
    }
};
Student & vratiNajdobroRangiran(Student ** studenti, int n)
{
    int maxInd = 0 ,najdobar = 0;
    for(int i = 0; i < n; i++)
    {
        if(studenti[i]->getBodovi() > najdobar)
        {
            najdobar = studenti[i]->getBodovi();
            maxInd = i;
        }
    }
    return * studenti[maxInd];
}
void pecatiDemonstratoriKurs (char* kurs, Student** studenti, int n)
{
    for(int i = 0; i < n; i++)
    {
        Demonstrator * d = dynamic_cast<Demonstrator *>(studenti[i]);
        if(d)
        {
            for(int j = 0 ; j < d->getBrojKursevi(); j++)
            {
                if((*d)[j] == kurs)
                {
                    d->pecati();
                    cout<<endl;
                    break;
                }
            }
        }
    }
}
int main(){

Kurs kursevi[10];
int indeks,brojKursevi, ocenki[20],ocenka,brojOcenki,tip,brojCasovi,krediti;
char ime[20],imeIPrezime[50];

cin>>tip;

if (tip==1) //test class Demonstrator
{
    cout<<"-----TEST Demonstrator-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
cout<<"Objekt od klasata Demonstrator e kreiran";

} else if (tip==2) //funkcija pecati vo Student
{
    cout<<"-----TEST pecati-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }

Student s(indeks,ocenki,brojOcenki);
s.pecati();

} else if (tip==3) //funkcija getVkupnaOcenka vo Student
{
    cout<<"-----TEST getVkupnaOcenka-----"<<endl;
    cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
Student s(indeks,ocenki,brojOcenki);
cout<<"Broj na bodovi: "<<s.getBodovi()<<endl;

} else if (tip==4) //funkcija getVkupnaOcenka vo Demonstrator
{
  cout<<"-----TEST getVkupnaOcenka-----"<<endl;
  cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
cout<<"Broj na bodovi: "<<d.getBodovi()<<endl;

} else if (tip==5) //funkcija pecati vo Demonstrator
{
 cout<<"-----TEST pecati -----"<<endl;
 cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
d.pecati();

} else if (tip==6) //site klasi
{
    cout<<"-----TEST Student i Demonstrator-----"<<endl;
 cin>>indeks>>brojOcenki;
    for (int i=0;i<brojOcenki;i++){
         cin>>ocenka;
         ocenki[i]=ocenka;
    }
    cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
    }
    cin>>brojCasovi;

Student *s=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
s->pecati();
cout<<"\nBroj na bodovi: "<<s->getBodovi()<<endl;
delete s;


} else if (tip==7) //funkcija vratiNajdobroRangiran
{
    cout<<"-----TEST vratiNajdobroRangiran-----"<<endl;
int k, opt;
cin>>k;
Student **studenti=new Student*[k];
for (int j=0;j<k;j++){
   cin>>opt; //1 Student 2 Demonstrator
   cin>>indeks>>brojOcenki;
   for (int i=0;i<brojOcenki;i++)
      {
         cin>>ocenka;
         ocenki[i]=ocenka;
      }
   if (opt==1){
   		studenti[j]=new Student(indeks,ocenki,brojOcenki);
   }else{
       cin>>imeIPrezime>>brojKursevi;
   		for (int i=0;i<brojKursevi;i++){
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
        }
   		cin>>brojCasovi;
   		studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
   }
}
Student& najdobar=vratiNajdobroRangiran(studenti,k);
cout<<"Maksimalniot broj na bodovi e:"<<najdobar.getBodovi();
cout<<"\nNajdobro rangiran:";
najdobar.pecati();

for (int j=0;j<k;j++) delete studenti[j];
 delete [] studenti;
} else if (tip==8) //funkcija pecatiDemonstratoriKurs
{
cout<<"-----TEST pecatiDemonstratoriKurs-----"<<endl;
int k, opt;
cin>>k;
Student **studenti=new Student*[k];
for (int j=0;j<k;j++){
   cin>>opt; //1 Student 2 Demonstrator
   cin>>indeks>>brojOcenki;
   for (int i=0;i<brojOcenki;i++)
      {
         cin>>ocenka;
         ocenki[i]=ocenka;
      }
   if (opt==1){
   		studenti[j]=new Student(indeks,ocenki,brojOcenki);
   }else{
   cin>>imeIPrezime>>brojKursevi;
    for (int i=0;i<brojKursevi;i++)
      {
         cin>>ime>>krediti;
         kursevi[i]=Kurs(ime,krediti);
      }
      cin>>brojCasovi;
   	  studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
   }
}
char kurs[20];
cin>>kurs;
cout<<"Demonstratori na "<<kurs<<" se:"<<endl;
pecatiDemonstratoriKurs (kurs,studenti,k);
for (int j=0;j<k;j++) delete studenti[j];
delete [] studenti;

}


return 0;
}
