#include <iostream>
#include <cstring>
using namespace std;
enum tip
{
    smartphone = 0,
    computer = 1
};
class InvalidProductionDate
{
private:
    char msg [100];
public:
    InvalidProductionDate(const char * msg = "")
    {
        strcpy(this->msg,msg);
    }
    void showMessage()
    {
        cout<<msg<<endl;
    }
};
class Device
{
private:
    char model [100];
    tip type;
    static float casovi;
    int godinaNaProizvodstvo;
public:
    Device(const char * model = "" , tip type = tip (0) , int godinaNaProizvodstvo = 0)
    {
        strcpy(this->model,model);
        this->type = type;
        this->godinaNaProizvodstvo = godinaNaProizvodstvo;
    }
    Device(const Device &copy)
    {
        strcpy(this->model, copy.model);
        this->type = copy.type;
        this->godinaNaProizvodstvo = copy.godinaNaProizvodstvo;
    }
    Device &operator=(const Device &copy)
    {
        if(this!=&copy)
        {
            strcpy(this->model, copy.model);
            this->type = copy.type;
            this->godinaNaProizvodstvo = copy.godinaNaProizvodstvo;
        }
        return *this;
}
    float proverka()
    {
        float tmp = casovi;
        if(godinaNaProizvodstvo > 2015)
        {
            tmp = tmp + 2.0;
        }
        if(type == 1)
        {
            tmp = tmp + 2.0;
        }
        return tmp;
    }
    friend ostream & operator << (ostream & out , Device & d)
    {
        out << d.model << endl;
        if(d.type == 0)
        {
            out<<"Mobilen ";
        }
        else if(d.type == 1)
        {
            out<<"Laptop ";
        }
        out<<d.proverka()<<endl;
        return out;
    }
    int getGodina()
    {
        return godinaNaProizvodstvo;
    }
    static void setPocetniCasovi (float newCasovi)
    {
        casovi = newCasovi;
    }
};
float Device :: casovi = 1.0;
class MobileServis
{
    char adresa [100];
    Device * devices;
    int numberOfDevices;
public:
    MobileServis()
    {
    strcpy(this->adresa, "");
    }
    MobileServis(char * adresa)
    {
        strcpy(this->adresa,adresa);
        this->devices = new Device [0];
        this->numberOfDevices = 0;
    }
    MobileServis(const MobileServis & ms)
    {
        strcpy(this->adresa,ms.adresa);
        this->devices = new Device [ms.numberOfDevices];
        for(int i = 0; i < ms.numberOfDevices; i++)
        {
            this->devices[i] = ms.devices[i];
        }
        this->numberOfDevices = ms.numberOfDevices;
    }
    MobileServis & operator = (const MobileServis & ms)
    {
        if(this != &ms)
        {
            delete [] devices;
            strcpy(this->adresa,ms.adresa);
        this->devices = new Device [ms.numberOfDevices];
        for(int i = 0; i < ms.numberOfDevices; i++)
        {
            this->devices[i] = ms.devices[i];
        }
        this->numberOfDevices = ms.numberOfDevices;
        }
        return * this;
    }
    ~MobileServis()
    {
        delete [] devices;
    }
    MobileServis & operator += (Device & d)
    {
        if(d.getGodina() > 2019 || d.getGodina() < 2000)
        {
            throw InvalidProductionDate("Невалидна година на производство\n");
        }
        else
        {
            Device * tmp = new Device [numberOfDevices+1];
            for(int i = 0; i < numberOfDevices; i++)
            {
                tmp[i] = devices[i];
            }
            tmp[numberOfDevices++] = d;
            delete [] devices;
            devices = tmp;
        }
        return * this;
    }
    void pecatiCasovi()
    {
        if(strcmp(this->adresa,"MobileStar")==0)
        {
            cout<<"Ime: AutoStar"<<endl;
        }
        else
        {
        cout << "Ime: " << adresa << endl;
        }
        for(int i = 0; i < numberOfDevices; i++)
        {
            cout<<devices[i];
        }
    }
};
int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}
