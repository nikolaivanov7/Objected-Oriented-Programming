#include <iostream>
#include <cstring>
using namespace std;
class Pizza
{
protected:
    char ime [20];
    char sostojki[100];
    double cena;
public:
    Pizza(char * ime = "" , char * sostojki = "" , double cena = 0.0)
    {
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);
        this->cena = cena;
    }
    virtual double price()
    {
        return cena;
    }
    friend ostream & operator << (ostream & out , Pizza & p)
    {
        out << p.ime << ": " << p.sostojki << ", - " << p.price() << endl;
        return out;
    }
    bool operator < (Pizza & p)
    {
        return this->price() < p.price();
    }
};
enum Size
{
    mala,
    golema,
    familijarna
};
class FlatPizza : public Pizza
{
private:
    Size s;
public:
    FlatPizza(char * ime = "" , char * sostojki = "" , double cena = 0.0,Size s = Size(mala)) : Pizza(ime,sostojki,cena)
    {
        this->s = s;
    }
    double price()
    {
        if(s == mala)
        {
            return cena + cena * 0.1;
        }
        if(s == golema)
        {
            return cena + cena * 0.5;
        }
        if(s == familijarna)
        {
            return cena + cena * 0.3;
        }
    }
    friend ostream & operator << (ostream & out , FlatPizza & fp)
    {
        out << fp.ime << ": "<< fp.sostojki << ", ";
        if(fp.s == mala)
        {
            out<<"small - ";
        }
        else if(fp.s == golema)
        {
            out<<"big - ";
        }
        else
        {
            out<<"family - ";
        }
        out<<fp.price()<<endl;
        return out;
    }
    /*bool operator < (FlatPizza & p)
    {
        return this->price() < p.price();
    }*/
};
class FoldedPizza : public Pizza
{
private:
    bool testo;
public:
    FoldedPizza(char * ime = "" , char * sostojki = "" , double cena = 0.0,bool testo = false) : Pizza(ime,sostojki,cena)
    {
        this->testo = testo;
    }
    void setWhiteFlour(bool _testo)
    {
        testo = _testo;
    }
    double price()
    {
        if(testo == true)
        {
            return cena + cena * 0.1;
        }
        if(testo == false)
        {
            return cena + cena * 0.3;
        }
    }
    friend ostream & operator << (ostream & out , FoldedPizza & p)
    {
        out << p.ime << ": " << p.sostojki << ", ";
        if(p.testo == true)
        {
            out<<"wf - ";
        }
        if (p.testo == false)
        {
            out<<"nwf - ";
        }
        out<<p.price()<<endl;
        return out;
    }
   /* bool operator < (FoldedPizza & p)
    {
        return this->price() < p.price();
    }*/
};
void expensivePizza (Pizza ** pizzas , int n)
{
    int maxInd = 0;
    double maxCena = 0.0;
    for(int i = 0; i < n; i++)
    {
        if(pizzas[i]->price() > maxCena)
        {
            maxCena = pizzas[i]->price();
            maxInd = i;
        }
    }
    FlatPizza * p1 = dynamic_cast<FlatPizza *>(pizzas[maxInd]);
    if(p1)
    {
        cout<<*p1;
    }
    FoldedPizza * p2 = dynamic_cast<FoldedPizza *>(pizzas[maxInd]);
    if(p2)
    {
        cout<<*p2;
    }

}
int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
