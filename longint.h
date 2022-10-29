#include <iostream>
#include <vector>
using namespace std;


class Mult{
    virtual vector<int> multiply(vector<int>, vector<int>)=0;
};

class NaiveMult: public Mult{
    vector<int> multiply(vector<int>d1, vector<int>d2);
};

class Karatsuba: public Mult{
    vector<int>multiply(vector<int>d1,vector<int>d2);
};

class SchonhageStrassen: public Mult{
    vector<int>multiply(vector<int>d1,vector<int>d2);
};

class Lint{
private:
    vector <int> digits;
    string val;
    static Mult* multer;
public:
    Lint();
    Lint(string val);

    bool operator ==(Lint& other);
    bool operator !=(Lint other);
    bool operator >(Lint& other);
    bool operator <=(Lint& other);
    bool operator >=(Lint other);
    bool operator <(Lint& other);

    static void setMultMode(Mult *newMulter);
    Lint operator +(Lint &other);
    Lint operator -(Lint other);
    Lint operator *(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

Mult* Lint::multer;
void Lint::setMultMode(Mult *newMulter){multer=newMulter;}