#include <iostream>
#include <cstring>
using namespace std;
class Book
{
protected:
    char isbn [20];
    char naslov [50];
    char avtor [30];
    double osnovnaCena;
public:
    Book(const char * isbn = "" , const char * naslov = "" , const char * avtor = "" , double osnovnaCena = 0.0)
    {
        strcpy(this->isbn,isbn);
        strcpy(this->naslov,naslov);
        strcpy(this->avtor,avtor);
        this->osnovnaCena = osnovnaCena;
    }
    virtual double bookPrice()
    {
        return osnovnaCena;
    }
    friend ostream & operator << (ostream & out , Book & f)
    {
        out << f.isbn << ": " << f.naslov << ", " << f.avtor << " " << f.bookPrice() << endl;
        return out;
    }
    bool operator > (Book & b)
    {
        return this->bookPrice() > b.bookPrice();
    }
    void setISBN (char * _isbn)
    {
        strcpy(isbn,_isbn);
    }
};
class OnlineBook : public Book
{
private:
    char * url;
    int golemina;
public:
    OnlineBook(const char * isbn = "" , const char * naslov = "" ,const char * avtor = "" , double osnovnaCena = 0.0 , char * url = NULL , int golemina = 0) : Book(isbn,naslov,avtor,osnovnaCena)
    {
        this->url = new char [strlen(url)+1];
        strcpy(this->url,url);
        this->golemina = golemina;
    }
    double bookPrice()
    {
        if(golemina > 20)
        {
            return osnovnaCena + osnovnaCena * 0.2;
        }
        else
        {
            return osnovnaCena;
        }
    }
    bool operator > (OnlineBook & o)
    {
        return this->bookPrice() > o.bookPrice();
    }
    friend ostream & operator << (ostream & out , OnlineBook & f)
    {
        out << f.isbn << ": " << f.naslov << ", " << f.avtor << " " << f.bookPrice() << endl;
        return out;
    }
};
class PrintBook : public Book
{
private:
    double masa;
    bool daliZaliha;
public:
    PrintBook(const char * isbn = "" , const char * naslov = "" , const char * avtor = "" , double osnovnaCena = 0.0 , double masa = 0.0 , bool daliZaliha = false) : Book(isbn,naslov,avtor,osnovnaCena)
    {
        this->masa = masa;
        this->daliZaliha = daliZaliha;
    }
    double bookPrice()
    {
        if(masa > 0.7)
        {
            return osnovnaCena + osnovnaCena * 0.15;
        }
        else
        {
            return osnovnaCena;
        }
    }
    bool operator > (PrintBook & p)
    {
        return this->bookPrice() > p.bookPrice();
    }
    friend ostream & operator << (ostream & out , PrintBook & f)
    {
        out << f.isbn << ": " << f.naslov << ", " << f.avtor << " " << f.bookPrice() << endl;
        return out;
    }
};
void mostExpensiveBook (Book ** books , int n)
{
    int countOnlineBooks = 0 , countPrintedBooks = 0 , maxIndeks = 0;
    double maxPrice = 0.0;
    for(int i = 0; i < n; i++)
    {
        OnlineBook * ob = dynamic_cast<OnlineBook *>(books[i]);
        if(ob)
        {
            countOnlineBooks++;
        }
        PrintBook * pb = dynamic_cast<PrintBook *>(books[i]);
        if(pb)
        {
            countPrintedBooks++;
        }
        if(books[i]->bookPrice() > maxPrice)
        {
            maxPrice = books[i]->bookPrice();
            maxIndeks = i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<countOnlineBooks<<endl;
    cout<<"Total number of print books: "<<countPrintedBooks<<endl;
    cout<<"The most expensive book is: "<<endl<<*books[maxIndeks];
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
