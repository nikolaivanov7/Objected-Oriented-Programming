#include <iostream>
#include <cstring>
using namespace std;
class SMS
{
protected:
    double cena;
    char broj[15];
public:
    SMS(char * broj = "",double cena = 0.0)
    {
        this->cena = cena;
        strcpy(this->broj,broj);
    }
    SMS(const SMS & s)
    {
        this->cena = s.cena;
        strcpy(this->broj,s.broj);
    }
    virtual double SMS_cena()
    {
        return cena;
    }
    friend ostream & operator <<(ostream & out, SMS & print)
    {
        out<<"Tel: "<< print.broj <<" - cena: "<< print.SMS_cena() <<"den."<< endl;
    return out;
    }
};
class RegularSMS : public SMS
{
private:
    bool roaming;
    char tekst [1000];
    static int rprocent;
public:
    RegularSMS(char * broj = "",double cena = 0.0,char * tekst = "" ,bool roaming = false) : SMS(broj,cena)
    {
        this->roaming = roaming;
        strcpy(this->tekst,tekst);
    }
    RegularSMS(const RegularSMS & s) : SMS(s)
    {
        strcpy(this->tekst,s.tekst);
        this->roaming = s.roaming;
    }
    static void set_rProcent(int p)
    {
        rprocent = p;
    }
    int calc()
    {
        int counter = 0;
        for(int copy = strlen(tekst); copy > 0; copy = copy - 160)
        {
            counter++;
        }
        return counter;
    }
    double SMS_cena()
    {
        double temp = SMS::SMS_cena();
        if(this->roaming)
        {
            temp = temp + temp * rprocent / 100;
        }
        else
        {
            temp = temp + temp * 0.18;
        }
        return temp * calc();
    }
};
int RegularSMS::rprocent = 300;
class SpecialSMS : public SMS
{
private:
    bool humanity;
    static int sprocent;
public:
    SpecialSMS(char * broj = "",double cena = 0.0,bool humanity = false) : SMS(broj,cena)
    {
        this->humanity = humanity;
    }
    SpecialSMS(const SpecialSMS & s) : SMS(s)
    {
        this->humanity = s.humanity;
    }
    double SMS_cena()
    {
        if(humanity)
        {
            return SMS::SMS_cena();
        }
        else
        {
            return SMS::SMS_cena() + SMS::SMS_cena() * sprocent/100;
        }
    }
    static void set_sProcent(int p)
    {
        sprocent = p;
    }
};
int SpecialSMS::sprocent = 150;
void vkupno_SMS(SMS ** poraka , int n)
{
    int r = 0 , s = 0;
    double reg = 0.0 , spec = 0.0;
    for(int i = 0; i < n; i++)
    {
        RegularSMS * p1 = dynamic_cast<RegularSMS *>(poraka[i]);
        if(p1)
        {
            r++;
            reg = reg + poraka[i]->SMS_cena();
        }
        SpecialSMS * p2 = dynamic_cast<SpecialSMS *>(poraka[i]);
        if(p2)
        {
            s++;
            spec = spec + poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << r << " regularni SMS poraki i nivnata cena e: " << reg << endl;
    cout << "Vkupno ima " << s << " specijalni SMS poraki i nivnata cena e: " << spec << endl;
}
int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}
