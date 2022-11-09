#include <iostream>
#include <vector>
using namespace std;

class PrimalityTest{
    virtual bool isPrime(vector<int>, int)=0;
};

class Fermat: public PrimalityTest{
    bool isPrime(vector<int>, int) override;
};

class MillerRabin: public PrimalityTest{
    bool isPrime(vector<int>,int) override;
};

class SolovayStrassen: public PrimalityTest{
    bool isPrime(vector<int>,int) override;
};


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

class ToomCook: public Mult{
    vector<int>multiply(vector<int>d1,vector<int>d2);
};

class Lint{
private:
    vector <int> digits;
    static Mult* multer;
    static PrimalityTest* tester;
    static Lint linGen(Lint x, Lint min, Lint max);
public:
    Lint();
    Lint(string val);
    Lint(vector<int> d);
    ~Lint();
    Lint& operator =(const Lint& other);
    bool operator ==(Lint other);
    bool operator !=(Lint other);
    bool operator >(Lint& other);
    bool operator <=(Lint& other);
    bool operator <(Lint& other);
    bool operator >=(Lint other);

    static void setMultMode(Mult *newMulter);
    static void setTestMode(PrimalityTest *newTester);

    Lint operator +(Lint other);
    Lint operator -(Lint other);
    Lint operator *(Lint other);
    void getInv();
    Lint operator /(Lint other);
    Lint operator %(Lint other);
    static Lint setRandLint(int n);
    static Lint genRandLint(Lint min, Lint max);
    Lint powMod(Lint pow, Lint mod);
    Lint gcd(Lint other);
    int jacobi(Lint other);

    bool isPrime(int iters=1);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

Mult* Lint::multer;
void Lint::setMultMode(Mult *newMulter){multer=newMulter;}
PrimalityTest* Lint::tester;
void Lint::setTestMode(PrimalityTest *newTester){tester=newTester;}
