#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;
class UserExistsException
{
private:
    char msg[100];
public:
    UserExistsException(const char * msg = "")
    {
        strcpy(this->msg, msg);
    }
    void showMessage()
    {
        cout<<msg;
    }
};
enum typeC
{
    standard,
    loyal,
    vip
};
class Customer
{
    char ime [50];
    char email[50];
    typeC tip;
    static int osPopust;
    const static int dopPopust;
    int brKupeniProizvodi;
public:
    Customer(const char * ime = "" , const char * email = "" , typeC tip = typeC(standard) , int brKupeniProizvodi = 0)
    {
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->tip = tip;
        this->brKupeniProizvodi = brKupeniProizvodi;
    }
    char * getEmail()
    {
        return email;
    }
    typeC gettip()
    {
        return tip;
    }
    void setTip (typeC tip)
    {
        this->tip = tip;
    }
    static void setDiscount1 (int newOsnoven)
    {
        osPopust = newOsnoven;
    }
    int getKupeniProizvodi()
    {
        return brKupeniProizvodi;
    }
    int popust()
    {
        if(tip == standard)
        {
            return 0;
        }
        else if(tip == loyal)
        {
            return osPopust;
        }
        else
        {
            return osPopust + dopPopust;
        }
    }
    friend ostream & operator << (ostream & out , Customer & c)
    {
        out << c.ime << endl;
        out << c.email << endl;
        out << c.brKupeniProizvodi << endl;
        if(c.tip == standard)
        {
            out<<"standard ";
        }
        else if(c.tip == loyal)
        {
            out<<"loyal ";
        }
        else
        {
            out<<"vip ";
        }
        out << c.popust() << endl;
        return out;
    }
};
int Customer ::osPopust = 10;
const int Customer::dopPopust = 20;
class FINKI_bookstore
{
    Customer * kupuvaci;
    int brKupuvaci;
public:
    FINKI_bookstore(Customer * kupuvaci = new Customer [0] , int brKupuvaci = 0)
    {
        this->kupuvaci = new Customer [brKupuvaci];
        for(int i = 0; i < brKupuvaci; i++)
        {
            this->kupuvaci[i] = kupuvaci[i];
        }
        this->brKupuvaci = brKupuvaci;
    }
    FINKI_bookstore (const FINKI_bookstore & f)
    {
        this->kupuvaci = new Customer [f.brKupuvaci];
        for(int i = 0; i < f.brKupuvaci; i++)
        {
            this->kupuvaci[i] = f.kupuvaci[i];
        }
        this->brKupuvaci = f.brKupuvaci;
    }
    FINKI_bookstore & operator = (const FINKI_bookstore & f)
    {
        if(this != &f)
        {
        delete [] kupuvaci;
        this->kupuvaci = new Customer [f.brKupuvaci];
        for(int i = 0; i < f.brKupuvaci; i++)
        {
            this->kupuvaci[i] = f.kupuvaci[i];
        }
        this->brKupuvaci = f.brKupuvaci;
        }
        return * this;
    }
    FINKI_bookstore & operator += (Customer & customers)
    {
        int flag = 0;
        for(int i = 0; i < brKupuvaci; i++)
        {
            if(strcmp(kupuvaci[i].getEmail(),customers.getEmail())==0)
            {
                flag = 1;
            }
            if(flag == 1)
            {
                throw UserExistsException("The user already exists in the list!\n");
            }
            if(flag == 0)
            {
                Customer * tmp = new Customer [brKupuvaci+1];
                for(int i = 0; i < brKupuvaci; i++)
                {
                    tmp[i] = kupuvaci[i];
                }
                tmp[brKupuvaci++] = customers;
                delete [] kupuvaci;
                kupuvaci = tmp;
            }
        }
        return * this;
    }
    void update()
    {
        for(int i = 0; i < brKupuvaci; i++)
        {
            if(kupuvaci[i].gettip() == standard && kupuvaci[i].getKupeniProizvodi() > 5)
            {
                kupuvaci[i].setTip(loyal);
            }
            if(kupuvaci[i].gettip() == loyal && kupuvaci[i].getKupeniProizvodi() > 10)
            {
                kupuvaci[i].setTip(vip);
            }
        }
    }
    friend ostream & operator << (ostream & out , FINKI_bookstore & f)
    {
        for(int i = 0; i < f.brKupuvaci; i++)
        {
            out<<f.kupuvaci[i];
        }
        return out;
    }
    void setCustomers(Customer * kupuvaci, int brKupuvaci)
    {
        this->brKupuvaci = brKupuvaci;
        this->kupuvaci = new Customer[brKupuvaci];
        for(int i=0; i<brKupuvaci; i++)
            this->kupuvaci[i] = kupuvaci[i];
    }
};
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;

    fc+=c;

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
