#include<iostream>
#include<cstring>
using namespace std;
class ExistingGame {
private:
    char msg[50];
public:
    ExistingGame(const char * msg) {
        strcpy(this->msg, msg);
    }
    void message() {
        cout<<msg;
    }
};
class Game { //Потребно е да се имплементира класа за компјутерска игра (Game),
protected:// што содржи информации за:
    char * ime; //име на играта (низа од макс. 100 знаци)
    double cena; //цена на играта (децимален број)
    bool sale; //дали е играта купена на распродажба (bool променлива).
public:
    Game() {
        this->ime = new char[1];
        strcpy(this->ime, "");
        this->cena = 0.0;
        this->sale = true;
    } // DEFAULTEN
    Game(char * ime, double cena, bool sale) {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sale = sale;
    }//konstruktor so argumenti
    Game(const Game &copy) {
        this->ime = new char[strlen(copy.ime)+1];
        strcpy(this->ime, copy.ime);
        this->cena = copy.cena;
        this->sale = copy.sale;
    }//copy konstruktor
    friend ostream &operator<<(ostream &o, Game &g) { //За класите Game и SubscriptionGame
        o<<"Game: "<<g.ime<<", regular price: $"<<g.cena;
        if(g.getsale() == true)
            o<<", bought on sale";
        return o;
    }//да се преоптоварат операторите за печатење (<< )
    friend istream &operator>>(istream &i, Game &g) { //и читање (>>).
        i.get();
        i.getline(g.ime,100);
        i>>g.cena>>g.sale;
        return i;
    }
    bool operator == (const Game &g) { //Да се дефинира и операторот ==
        if(strcmp(this->ime, g.ime) == 0)
            return true;
        else return false;
    } //кој ќе споредува игри според нивното име.
    double getcena() {
        return cena;
    }
    bool getsale() {
        return sale;
    }
    virtual double calc() {
        double a = 0.0;
        if(this->sale) { //Доколку играта е купена на распродажба, цената на
            a = cena * 0.3; //играта е 30% од стандарната цена.
       return a;
        }
        else return cena;
    }
};
class SubscriptionGame : public Game { //Од класата Game да се изведе класа SubscriptionGame,
private://што дополнително ќе чува:
    double nadomestok; //месечен надоместок за играње (децимален број).
    int mesec; //датум кога играта е купена (месец и
    int godina; //година како позитивни цели броеви)
public:
    SubscriptionGame() {
        this->nadomestok = 0.0;
        this->mesec = 1;
        this->godina = 1;
    } //defaulten
    SubscriptionGame(char * ime, double cena, bool sale, double nadomestok, int mesec, int godina) : Game(ime, cena, sale) {
        this->nadomestok = nadomestok;
        this->mesec = mesec;
        this->godina = godina;
    }//so argumenti
    SubscriptionGame(const SubscriptionGame &copy) : Game(copy) {
        this->nadomestok = copy.nadomestok;
        this->mesec = copy.mesec;
        this->godina = copy.godina;
    }//copy konstruktor
    friend ostream &operator<<(ostream &o,  SubscriptionGame &sg)  {
        o<<"Game: "<<sg.ime<<", regular price: $"<<sg.cena;
        if(sg.getsale() == true)
            o<<", bought on sale";
        o<<", monthly fee: $" <<sg.nadomestok<<", purchased: "<<sg.mesec<<"-"<<sg.godina<<endl;
        return o;
    } //monthlyfee:10, purchased: 1-2017
    friend istream &operator>>(istream &i, SubscriptionGame &sg) {
        i.get();
        i.getline(sg.ime,100);
        i>>sg.cena>>sg.sale>>sg.nadomestok>>sg.mesec>>sg.godina;
        return i;
    }
    int getmesec() {
        return mesec;
    }
    double getnadomestok() {
        return nadomestok;
    }
    double calc() {
        return calcnadomestok();
    }
    int calcnadomestok() { // Доколку играта е од типот SubscriptionGame, потребно е да се вкалкулира
        double tmp =  Game::calc();
                int m = 0;
                if(this->godina < 2018)
                    m = (12 - this->mesec) + (2017 - this->godina) * 12 + 5;
                else m = 5 - this->mesec;
                tmp = tmp + m * nadomestok;
                return tmp;
    }
        //и сумата потрошена за месечниот надоместок (број_на_изминати_месеци x цена_на_месечен
        //_надоместок) без да се земе
      //  во предвид моменталниот месец (мај 2018).
};
class User { //Да се дефинира класа за корисник (User)
private://во која се чуваат:
    char username[100];//кориснично име на корисникот (низа од макс. 100 знаци)
    Game ** niza; //колекција од игри кои се купени од корисникот (динамички алоцирана низа).
    int broj;
public:
    User() {
        strcpy(this->username, "");
    }
    User(char * username) {
        strcpy(this->username, username);
        this->niza = new Game * [1];
        this->broj = 0;
    }
    User(const User &copy) {
        strcpy(this->username, copy.username);
        this->niza = new Game * [copy.broj];
        for(int i=0; i<copy.broj; i++)
            this->niza[i] = copy.niza[i];
    }
    User &operator+=(Game &g) { //Да се преоптовари операторот +=
        int flag = 0;
        for(int i=0; i<broj; i++)
            if(*(niza[i]) == g)
                flag=1;
        if(flag==0) {
            Game ** tmp = new Game * [broj+1];
            for(int i=0; i<broj; i++)
                tmp[i] = niza[i];
            SubscriptionGame * sg = dynamic_cast<SubscriptionGame *>(&g);
            if(sg)
                tmp[this->broj++] = new SubscriptionGame(*sg);
            else
                tmp[this->broj++] = new Game(g);
            //prepisano od nikola poso wtf
            delete [] niza;
            niza = tmp;
        }
        if(flag==1)
            throw ExistingGame("The game is already in the collection\n");
        return *this;
    }//кој ќе овозможи додавање на нова игра во колекцијата на игри.
    double total_spent() { //Да се креира и метода total_spent() во класата User
        double total = 0.0; //која ќе пресметува колку пари корисникот потрошил за својата колекција од игри.
        for(int i=0; i<broj; i++){
            total = total + niza[i]->calc();
        }
        return total;
    }
    // Доколку играта е од типот SubscriptionGame, потребно е да се вкалкулира и
    //    сумата потрошена за месечниот надоместок (број_на_изминати_месеци x
    // цена_на_месечен_надоместок) без да се земе
    //  во предвид моменталниот месец (мај 2018).
    friend ostream &operator<<(ostream &o, User &u) { //Да се преоптовари и оператоторот за печатење
        o<<endl;
        o<<"User: "<<u.username<<endl;//на корисникот, која печати информации во
        for(int i=0; i<u.broj; i++) { //сл. формат
            o<<"- ";
            SubscriptionGame * p = dynamic_cast<SubscriptionGame*>(u.niza[i]);
            if(p)
                o<<*p<<endl;
            else
                o<<*u.niza[i]<<endl;
        }
        return o;
    }
};
int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1) {
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    } else if (test_case_num == 2) {
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    } else if (test_case_num == 3) {
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    } else if (test_case_num == 4) {
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    } else if (test_case_num == 5) {
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i) {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                } else if (game_type == 2) {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }
                u+=(*g);
            }
        } catch(ExistingGame &ex) {
            ex.message();
        }
        cout<<u;
    } else if (test_case_num == 6) {
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            } catch(ExistingGame &ex) {
                ex.message();
            }
        }

        cout<<u;
    } else if (test_case_num == 7) {
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i) {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1) {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            } else if (game_type == 2) {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
