#include <iostream>
#include <cstring>
using namespace std;
enum Extension
{
    pdf = 0,
    txt = 1,
    exe = 2
};
class File
{
    char * ime;
    Extension ekst;
    char * sopstvenik;
    int golemina;
    void copy(const File & f)
    {
        this->ime = new char [strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->ekst = f.ekst;
        this->sopstvenik = new char [strlen(f.sopstvenik)+1];
        strcpy(this->sopstvenik,f.sopstvenik);
        this->golemina = f.golemina;
    }
public:
    File()
    {
        this->ime = new char [0];
        strcpy(this->ime,"");
        this -> ekst = (Extension) 0;
        this->sopstvenik = new char [0];
        strcpy(this->sopstvenik,"");
        this->golemina = 0;
    }
    File(char * ime , char * sopstvenik ,int golemina,Extension ekst)
    {
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->ekst = ekst;
        this->sopstvenik = new char [strlen(sopstvenik)+1];
        strcpy(this->sopstvenik,sopstvenik);
        this->golemina = golemina;
    }
    File(const File & f)
    {
        copy(f);
    }
    File & operator = (const File & f)
    {
        if(this != &f)
        {
            delete [] ime;
            delete [] sopstvenik;
            copy(f);
        }
        return * this;
    }
    ~File()
    {
        delete [] ime;
        delete [] sopstvenik;
    }
    void print()
    {
        cout<<"File name: "<<ime;
        if (ekst==pdf){
            cout<<".pdf"<<endl;
        }
        if (ekst==txt){
            cout<<".txt"<<endl;
        }
        if (ekst==exe){
            cout<<".exe"<<endl;
        }
        cout<<"File owner: "<<sopstvenik<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
    bool equals(const File & that)
    {
        if(strcmp(this->ime,that.ime)==0 &&
           this->ekst == that.ekst &&
           strcmp(this->sopstvenik,that.sopstvenik)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool equalsType(const File & that)
    {
        if(strcmp(this->ime,that.ime)==0 &&
           this->ekst == that.ekst)
           {
               return true;
           }
        else
        {
            return false;
        }
    }
};
class Folder
{
    char * direktorium;
    int brDatoteki;
    File * datoteki;
    void copy(const Folder & f)
    {
        this->direktorium = new char [strlen(f.direktorium)+1];
        strcpy(this->direktorium,f.direktorium);
        this->brDatoteki = f.brDatoteki;
        this->datoteki = new File [f.brDatoteki];
        for(int i = 0; i < f.brDatoteki;i++)
        {
            this->datoteki[i] = f.datoteki[i];
        }
    }
public:
    Folder()
    {
        this->direktorium = new char [0];
        strcpy(this->direktorium,"");
        brDatoteki = 0;
        this->datoteki = new File [0];
    }
    Folder(char * direktorium , int brDatoteki , File * datoteki)
    {
        this->direktorium = new char [strlen(direktorium)+1];
        strcpy(this->direktorium,direktorium);
        this->brDatoteki = brDatoteki;
        this->datoteki = new File [this->brDatoteki];
        for(int i = 0; i < this->brDatoteki;i++)
        {
            this->datoteki[i] = datoteki[i];
        }
    }
    Folder(const char * direktorium)
    {
        this->direktorium = new char [strlen(direktorium)+1];
        strcpy(this->direktorium,direktorium);
        this->brDatoteki = 0;
        this->datoteki = new File [0];
    }
    Folder(const Folder & f)
    {
        copy(f);
    }
    Folder & operator = (const Folder & f)
    {
        if(this!= &f)
        {
        delete [] direktorium;
        delete [] datoteki;
        copy(f);
        }
        return * this;
    }
    ~Folder()
    {
        delete [] direktorium;
        delete [] datoteki;
    }
    void print()
    {
        cout<<"Folder name: "<<direktorium<<endl;
        for(int i = 0; i < brDatoteki;i++)
        {
            datoteki[i].print();
        }
    }
    void remove (const File & file)
    {
        File * tmp = new File [brDatoteki - 1];
        int j = 0;
        for(int i = 0; i < brDatoteki; i++)
        {
            if(datoteki[i].equals(file) == false)
            {
            tmp[j++] = datoteki[i];
            }
        }
        brDatoteki--;
        delete [] datoteki;
        datoteki = tmp;
    }
    void add (const File & file)
    {
        File * tmp = new File [brDatoteki+1];
        for(int i = 0; i < brDatoteki; i++)
        {
            tmp[i] = datoteki[i];
        }
        tmp[brDatoteki++] = file;
        delete [] datoteki;
        datoteki = tmp;
    }
};
#include<iostream>
#include<cstring>

using namespace std;

int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}
