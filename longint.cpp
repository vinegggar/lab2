#include <iostream>
#include <vector>
#include "vecArithmetic.h"
#include "decimal.h"

using namespace std;

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
public:
    Lint()= default;
    Lint(string val){
        for (int i=int(val.size())-1; i>=0;--i){
            digits.push_back(val[i]-'0');
        }
    }

    Lint& operator =(const Lint& other);
    bool operator==(Lint& other);
    bool operator !=(Lint other);
    bool operator>(Lint& other);
    bool operator <=(Lint& other);
    bool operator >=(Lint other);
    bool operator<(Lint& other);

    static void setMultMode(Mult *newMulter);

    Lint operator+(Lint& other);
    Lint operator-(Lint other);
    Lint operator *(Lint other);
    void get_inv();
    Lint operator /(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

//implement assignment operator for Lint
    Lint &Lint::operator=(const Lint &other) {
        digits = other.digits;
        return *this;
    }

/*
 * comparison operators}
 */
bool Lint:: operator==(Lint& other) {trim(digits);trim(other.digits);return digits==other.digits;}

bool Lint::operator!=(Lint other){return !(operator==(other));}
bool Lint::operator >(Lint &other) {
    bool res;
    trim(digits);trim(other.digits);
    if (digits.size()!=other.digits.size()){
        res = digits.size() > other.digits.size();
    }
    for (int i=int(digits.size())-1;i>=0;--i){
        if (digits[i] > other.digits[i]){
            res = true; break;
        }
        res = false;
    }
    return res;
}

bool Lint::operator<=(Lint &other) {return not(operator>(other));}

bool Lint:: operator>=(Lint other) {return (operator>(other) or operator==(other));}

bool Lint:: operator<(Lint &other) {return not(operator>=(other));}

/*
 * arithmetic operators
 */

Lint Lint::operator+(Lint& other){
    Lint res;
    res.digits = digits+other.digits;
    carry_res(res.digits);
    return res;
}

Lint Lint::operator-(Lint other) {
    Lint res;
    if (operator>=(other)) {
        res.digits = digits-other.digits;
        carry_res(res.digits);
        return res;
    }
    return {};
}

Lint Lint::operator*(Lint other){
    Lint res;
    res.digits = multer->multiply(digits, other.digits);
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

