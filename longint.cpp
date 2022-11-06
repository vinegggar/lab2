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
    bool operator==(Lint& other);
    bool operator !=(Lint other);
    bool operator>(Lint& other);
    bool operator <=(Lint& other);
    bool operator >=(Lint other);
    bool operator<(Lint& other);

    static void setMultMode(Mult *newMulter);
    static void setTestMode(PrimalityTest *newTester);

    Lint operator+(Lint& other);
    Lint operator-(Lint other);
    Lint operator *(Lint other);
    void get_inv();
    Lint operator /(Lint other);
    Lint operator %(Lint other);
    static Lint generate_random(Lint max);
    Lint powmod(Lint pow, Lint mod);

    bool primeCheck(int iters=1);

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
bool Lint:: operator==(Lint& other) {trim(digits);trim(other.digits);return digits==other.digits;}

bool Lint::operator!=(Lint other){return !(*this==other);}

bool Lint::operator >(Lint &other) {return digits>other.digits;}

bool Lint::operator<=(Lint &other) {return !(*this>other);}

bool Lint:: operator<(Lint &other) {return other>*this;}

bool Lint:: operator>=(Lint other) {return !(*this<other);}

/*
 * arithmetic operators
 */

Lint Lint::operator+(Lint& other){
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

void Lint::get_inv() {
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
    return *this - (other*(*this/other));
}


Lint Lint:: powmod(Lint pow, Lint mod) {
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

/*
 * random number generator
 */
Lint Lint:: generate_random(Lint max) {
    srand(time(nullptr));
    Lint res;
    int len = rand()%max.digits.size()+1;
    if (len==1)res.digits.push_back(rand()%7+3);//to guarantee that number is more than 2;
    else if (len!=max.digits.size()){
        for(int i=0;i<len-1;++i) res.digits.push_back(rand() % 10);
        res.digits.push_back(rand()%9+1);
    }
    else if (len==max.digits.size()){
        res.digits.push_back(rand()%10);
        for(int i=1;i<len-1;++i){
            if (res.digits[i-1]>max.digits[i-1]) res.digits.push_back(max.digits[i]!=0?rand()%max.digits[i]:0);
            else res.digits.push_back(rand()%10);
        }
        res.digits.push_back(rand()%(max.digits.back()+1));
    }
    return res;
}

/*
 * primality test
 */
bool Lint::primeCheck(int iters) {
    return tester->isPrime(digits,iters);
}

bool Fermat::isPrime(vector<int> d, int iters) {
    if (d==vector<int>{1}) return false;
    else if (d==vector<int>{2}) return true;
    for(int i=0;i<iters;++i) {
        Lint rd = Lint::generate_random(Lint(d)-Lint("1"));
        auto pm = rd.powmod(Lint(d) - Lint("1"), Lint(d));
        if (pm != Lint("1")) return false;
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
    for(int i=0;i<iters;++i){
        Lint rd = Lint::generate_random(d_1);
        Lint x = rd.powmod(Lint(k),Lint(d));
        if (x==one||x==d_1) continue;
        for(int j=1;j<s;++j){
            x = (x*x)%Lint(d);
            if (sgn==-1) {x = Lint(d)-x;sgn=1;}//that's an analogue of taking a module of negative number
            if (x==one) return false;
            if (x==d_1) break;
        }
        if (x!=d_1) return false;
    }
    return true;
}

bool SolovayStrassen::isPrime(vector<int> d, int iters) {
    return false;
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
