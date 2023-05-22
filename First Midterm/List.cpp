#include <iostream>
#include <cstring>
using namespace std;
class List
{
    int * broevi;
    int brBroevi;
    void copy(const List & lc)
    {
        this->brBroevi = lc.brBroevi;
        for(int i = 0; i < brBroevi; i++)
        {
            this->broevi[i] = lc.broevi[i];
        }
    }
public:
    List(int * broevi , int brBroevi)
    {
        this->brBroevi = brBroevi;
        for(int i = 0; i < brBroevi; i++)
        {
            this->broevi[i] = broevi[i];
        }
    }
    List(const List & lc)
    {
        copy(lc);
    }
    List & operator = (const List & lc)
    {
        if(this != &lc)
        {
            delete [] broevi;
            copy(lc);
        }
        return * this;
    }
    ~List()
    {
        delete [] broevi;
    }
    int sum()
    {
        int sum = 0;
        for(int i = 0; i < brBroevi; i++)
        {
            sum += broevi[i];
        }
        return sum;
    }
    double average()
    {
        return (sum*1.0)/brBroevi;
    }
    void pecati()
    {
        cout<<brBroevi<<": "<<broevi<<" sum: "<<sum()<<" average: "<<average()<<endl;
    }
};
