#include <iostream>
#include<cstring>
using namespace std;

class BadInputException
{
public:
    char *novo;
    BadInputException(char *popravi)
    {
        int n=strlen(popravi),br=0;
        for(int i=0; i<n; i++)
        {
            if(isalpha(popravi[i]))
                br++;
        }
        this->novo=new char[br+1];
        int j=-1;
        for(int i=0; i<n; i++)
        {
            if(isalpha(popravi[i]))
            {
                j++;
                novo[j]=popravi[i];
            }
        }
    }
};

class StudentKurs
{
protected:
    char ime[30];
    int ocenkaPismeno;
    bool daliUsno;
    static int MAX;
public:
    static const int MINOCENKA=6;
    int getDaliUsno()
    {
        return this->daliUsno;
    }
    char *getIme()
    {
        return this->ime;
    }
    StudentKurs(char ime[30]="",int ocenkaPismeno=0,bool daliUsno=false)
    {
        strcpy(this->ime,ime);
        this->ocenkaPismeno=ocenkaPismeno;
        this->daliUsno=daliUsno;
    }
    static void setMAX(int maxi)
    {
        StudentKurs::MAX=maxi;
    }
    virtual int ocenka()
    {
        return this->ocenkaPismeno;
    }
    friend ostream &operator<<(ostream &output, StudentKurs &u)
    {
        output<<u.ime<<" --- "<<u.ocenka()<<endl;
        return output;
    }

};
class StudentKursUsno : public StudentKurs
{
private:
    char *opisnaOcenka;
public:
    StudentKursUsno(char ime[30]="",int ocenkaPismeno=0,bool daliUsno=false,char *opisnaOcenka=""):StudentKurs(ime,ocenkaPismeno,daliUsno)
    {
        this->opisnaOcenka=new char[strlen(opisnaOcenka)+1];
        strcpy(this->opisnaOcenka,opisnaOcenka);
    }
    virtual int ocenka()
    {
        if(ocenkaPismeno<StudentKurs::MAX)
        {
            if(strcmp(this->opisnaOcenka,"odlicen")==0)
                return this->ocenkaPismeno+2;
            else if(strcmp(this->opisnaOcenka,"dobro")==0)
                return this->ocenkaPismeno+1;
        }
        else if(strcmp(this->opisnaOcenka,"losho")==0)
            return this->ocenkaPismeno-1;
        else return this->ocenkaPismeno;
    }
    friend ostream &operator<<(ostream &output, StudentKursUsno &u)
    {
        output<<u.ime<<" "<<u.ocenka()<<endl;
        return output;
    }
    StudentKursUsno &operator+=(char *opisnaOcenka)
    {
        int n=strlen(opisnaOcenka);
        int flag=0;
        for(int i=0; i<n; i++)
        {
            if(!isalpha(opisnaOcenka[i]))
            {
                flag=1;
                break;
            }
        }
        if(flag) throw BadInputException(opisnaOcenka);
        this->daliUsno=true;
        this->opisnaOcenka=new char[n];
        strcpy(this->opisnaOcenka,opisnaOcenka);

        return *this;
    }
};

class KursFakultet
{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj )
    {
        strcpy(this->naziv,naziv);
        for (int i=0; i<broj; i++)
        {
            //ako studentot ima usno isprashuvanje
            StudentKursUsno *s=dynamic_cast<StudentKursUsno*>(studenti[i]);
            if (s)
            {
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet()
    {
        for (int i=0; i<broj; i++) delete studenti[i];
    }
    void pecatiStudenti()
    {
        cout<<"Kursot "<<this->naziv<<" go polozile:"<<endl;
        for(int i=0; i<this->broj; i++)
        {
            if(studenti[i]->ocenka()>=StudentKurs::MINOCENKA)
                cout<<*studenti[i];
        }
    }
    void postaviOpisnaOcenka(char *ime,char *opisnaOcenka)
    {
        for(int i=0; i<broj; i++)
        {
            if(strcmp(studenti[i]->getIme(),ime)==0)
            {
                StudentKursUsno *s=dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(s) *(s)+=opisnaOcenka;
            }
        }
    }
};
int StudentKurs::MAX=10;
int main()
{

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0; i<n; i++)
    {
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0; i<n; i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0; i<m; i++)
    {
        cin>>ime>>opisna;
        try
        {
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
        catch(BadInputException e)
        {
            cout<<"Greshna opisna ocenka"<<endl;
            programiranje.postaviOpisnaOcenka(ime,e.novo);
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
