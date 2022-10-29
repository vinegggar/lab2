#include <iostream>
#include <vector>
#include "vecArithmetic.h"

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


vector <int> NaiveMult:: multiply(vector<int>d1,vector<int>d2){
    return naive_multiplication(d1,d2);
}

vector<int> Karatsuba::multiply(vector<int> d1, vector<int> d2) {
    return karatsuba_mul(d1,d2);
}

vector<int> SchonhageStrassen::multiply(vector<int> d1, vector<int> d2) {
    return fft_mul(d1,d2);
}


class Lint{
private:
    vector <int> digits;
    string val;
    static Mult* multer;
public:
    Lint()= default;
    Lint(string val){
        for (int i=int(val.size())-1; i>=0;--i){
            digits.push_back(val[i]-'0');
        }
    }

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

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

/*
 * comparison operators
 */
bool Lint:: operator==(Lint& other) {return digits == other.digits;}

bool Lint::operator!=(Lint other){return !(operator==(other));}
bool Lint::operator >(Lint &other) {
    bool res;
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
    res.digits = sum(digits, other.digits);
    carry_res(res.digits);
    return res;
}

Lint Lint::operator-(Lint other) {
    if (operator>=(other)){
    for (int & digit : other.digits){
        digit *= -1;
    }
    return operator+(other);
    }
    return {};
}

Lint Lint::operator*(Lint other){
    Lint res;
    res.digits = multer->multiply(digits, other.digits);
    carry_res(res.digits);
    return res;
}

/*
 * i/o stream operators
 */
ostream& operator<<(ostream &out, Lint num){
    int i;
    for (i=0;i<num.digits.size();++i){
        if(num.digits[num.digits.size()-1-i]!=0)break;
    }
    if (i==num.digits.size())out<<"0";
    for (int j=int(num.digits.size())-1-i;j>=0;--j){
        out <<num.digits[j];}
    out<<endl;
    return out;
}

istream& operator>>(istream& in, Lint& num){
    string input;
    in >> input;
    num = Lint(input);
    return in;
}

