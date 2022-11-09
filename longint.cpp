#include <iostream>
#include <vector>
#include "vecArithmetic.h"
#include "decimal.h"

using namespace std;

class PrimalityTest{
public:
    virtual bool isPrime(vector<int>, int)=0;
};

class Fermat: public PrimalityTest{
    bool isPrime(vector<int>, int) override;
};

class MillerRabin: public PrimalityTest{
    bool isPrime(vector<int>, int) override;
};

class SolovayStrassen: public PrimalityTest{
    bool isPrime(vector<int>,int) override;
};


class Mult{
public:
    virtual vector<int> multiply(vector<int>, vector<int>)=0;
};

class NaiveMult: public Mult{
public:
    vector<int> multiply(vector<int>d1, vector<int>d2) override;
};

class Karatsuba: public Mult{
public:
    vector<int>multiply(vector<int>d1, vector<int>d2) override;
};

class SchonhageStrassen: public Mult{
public:
    vector<int>multiply(vector<int>d1, vector<int>d2) override;
};

class ToomCook: public Mult{
public:
    vector<int>multiply(vector<int>d1, vector<int>d2) override;
};


vector <int> NaiveMult:: multiply(vector<int>d1,vector<int>d2){
    return d1*d2;
}

vector<int> Karatsuba::multiply(vector<int> d1, vector<int> d2) {
    return karatsuba_mul(d1,d2);
}

vector<int> SchonhageStrassen::multiply(vector<int> d1, vector<int> d2) {
    return fft_mul(d1,d2);
}

vector<int> ToomCook::multiply(vector<int> d1, vector<int> d2) {
    return toom_cook_mul(d1,d2);
}

class Lint{
private:
    vector <int> digits;
    static Mult* multer;
    static PrimalityTest* tester;
    static Lint linGen(Lint x, Lint min, Lint max);
public:
    Lint()= default;
    Lint(string val){
        for (int i=int(val.size())-1; i>=0;--i){
            digits.push_back(val[i]-'0');
        }
    }
    Lint(vector<int> d){
        digits=d;
    }
    ~Lint(){digits.clear();}

    Lint& operator =(const Lint& other);
    bool operator==(Lint other);
    bool operator !=(Lint other);
    bool operator>(Lint& other);
    bool operator <=(Lint& other);
    bool operator >=(Lint other);
    bool operator<(Lint& other);

    static void setMultMode(Mult *newMulter);
    static void setTestMode(PrimalityTest *newTester);

    Lint operator+(Lint other);
    Lint operator-(Lint other);
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

/*
 * assignment operator
 */
    Lint &Lint::operator=(const Lint &other) {
        digits = other.digits;
        return *this;
    }


/*
 * comparison operators
 */
bool Lint:: operator==(Lint other) {trim(digits);trim(other.digits);return digits==other.digits;}

bool Lint::operator!=(Lint other){return !(*this==other);}

bool Lint::operator >(Lint &other) {return digits>other.digits;}

bool Lint::operator<=(Lint &other) {return !(*this>other);}

bool Lint:: operator<(Lint &other) {return other>*this;}

bool Lint:: operator>=(Lint other) {return !(*this<other);}

/*
 * arithmetic operators
 */

Lint Lint::operator+(Lint other){
    Lint res;
    res.digits = digits+other.digits;
    carry_res(res.digits);
    return res;
}

int sgn = 1;
Lint Lint::operator-(Lint other) {
    Lint res;
    if (operator>=(other)) {
        res.digits = digits-other.digits;
        carry_res(res.digits);
        return res;
    }
    sgn = -1;
    return other-*this;
}

Lint Lint::operator*(Lint other){
    Lint res;
    res.digits = multer->multiply(digits,other.digits);
    carry_res(res.digits);
    trim(res.digits);
    return res;
}

void Lint::getInv() {
    cout<<Decimal(digits).inverse();
}

Lint Lint::operator/(Lint other) {
    Lint res;
    res.digits = (Decimal(digits)/Decimal(other.digits)).getDigits();
    return res;
}

Lint Lint::operator%(Lint other) {
    Lint res;
    if (other.digits==vector<int>{1} or digits==other.digits)return Lint("0");
    if (*this<other) return *this;
    res = *this - (other*(*this/other));
    if (sgn == -1){
        return other-res;
    }
    return res;
}


Lint Lint:: powMod(Lint pow, Lint mod) {
    Lint res("1");
    Lint base = *this;
    vector<int> e = to_binary(pow.digits);
    for (int i = 0; i<e.size(); ++i){
        if (e[i]==1){
            res = (res*base)%mod;
        }
        base = (base*base)%mod;
    }
    return res;
}
Lint Lint:: gcd(Lint other){
    Lint res = *this;
    while (other != Lint("0")){
        res = res%other;
        if (res == Lint("0")) return other;
        other = other%res;
    }
    return res;
}
/*
 * random number generator
 */
Lint x_prev;

Lint Lint::setRandLint(int n) {
    vector<int> num = {n};
    x_prev = Lint(num);
    return x_prev;
}

Lint Lint:: linGen(Lint x,Lint min, Lint max) {
    Lint a("37"), c("71");
    return (a*x+c)%(max-min+Lint("1"))+min;
}

Lint Lint:: genRandLint(Lint min, Lint max){
    x_prev = linGen(x_prev,min,max);
    return x_prev;
}

/*
 * primality test
 */
bool Lint::isPrime(int iters) {
    return tester->isPrime(digits,iters);
}


bool Fermat::isPrime(vector<int> d, int iters) {
    if (d==vector<int>{1}) return false;
    else if (d==vector<int>{2}) return true;
    x_prev = Lint::setRandLint(time(nullptr)%107);
    for(int i=0;i<iters;++i) {
        Lint rand = Lint::genRandLint(Lint("2"),Lint(d)-Lint("1"));
        Lint randPowMod = rand.powMod(Lint(d) - Lint("1"), Lint(d));
        if (randPowMod != Lint("1")) return false;
    }
    return true;
}

bool MillerRabin::isPrime(vector<int> d, int iters) {
    if (d==vector<int>{1}) return false;
    else if (d==vector<int>{2}||d==vector<int>{3}) return true;
    int s = factorize(d)[0][0];
    vector<int> k = factorize(d)[1];
    Lint one = Lint("1");
    Lint d_1 = Lint(d)-one;
    x_prev = Lint::setRandLint(time(nullptr)%107);
    for(int i=0;i<iters;++i){
        Lint rand = Lint::genRandLint(Lint("2"),d_1);
        Lint x = rand.powMod(Lint(k),Lint(d));
        if (x==one||x==d_1) continue;
        for(int j=1;j<s;++j){
            x = (x*x)%Lint(d);
            if (x==one) return false;
            if (x==d_1) break;
        }
        if (x!=d_1) return false;
    }
    return true;
}

int Lint::jacobi(Lint other) {
    if (other.digits[0]%2==0){
        throw invalid_argument("second argument must be odd");
    }
    Lint a = *this;
    Lint b = other;
    a = a % b;
    int t = 1;
    Lint r;
    while (a!=Lint("0")){
        while (a.digits[0]%2==0){
            a = a/Lint("2");
            r = b%Lint("8");
            if (r==Lint("3")||r==Lint("5")) t = -t;
        }
        r = b;
        b = a;
        a = r;
        if (a%Lint("4")==Lint("3") && b%Lint("4")==Lint("3")) t = -t;
        a = a%b;
    }
    if (b==Lint("1")) return t;
    else return 0;
}

bool SolovayStrassen::isPrime(vector<int> d, int iters) {
    if (d == vector<int>{2}) return true;
    if (d[0]%2==0) return false;
    x_prev = Lint::setRandLint(abs(time(nullptr)%107));
    for (int i=0;i<iters;++i){
        Lint rand = Lint::genRandLint(Lint("2"),Lint(d)-Lint("1"));

        if (rand.gcd(Lint(d))!=Lint("1")) return false;

        Lint j = rand.powMod((Lint(d)-Lint("1"))/Lint("2"),Lint(d));
        int jacobi = rand.jacobi(Lint(d));

        if (jacobi == 1){
            if (sgn == -1){
                if (j!=Lint(d)-Lint("1")) return false;
            }
            else if (j!=Lint("1")) return false;
        }
        else if (j!=Lint(d)-Lint("1")) return false;
    }
    return true;
}

/*
 * i/o stream operators
 */
ostream& operator<<(ostream &out, Lint num){
    trim(num.digits);
    for(int i=int(num.digits.size())-1;i>=0;--i){
        out<<num.digits[i];
    }
    out<<endl;
    return out;
}

istream& operator>>(istream& in, Lint& num){
    string input;
    in >> input;
    num = Lint(input);
    return in;
}
