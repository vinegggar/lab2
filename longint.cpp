#include <iostream>
#include <vector>

using namespace std;
class Lint{
private:
    vector <int> digits;
    string val;
public:
    Lint()= default;
    Lint(string val){
        for (int i=int(val.size())-1; i>=0;--i)
            digits.push_back(val[i]-'0');
    }
    bool operator==(Lint other);
    bool operator !=(Lint other);
    bool operator>(Lint other);
    bool operator <=(Lint other);
    bool operator >=(Lint other);
    bool operator<(Lint other);

    Lint operator+(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

/*
 * comparison operators
 */
bool Lint:: operator==(Lint other) {return digits == other.digits;}

bool Lint::operator!=(Lint other){return !(operator==(other));}
bool Lint::operator >(Lint other) {
    bool res;
    if (digits.size()!=other.digits.size()){
        res = digits.size()>other.digits.size()?true:false;
    }
    for (int i=int(digits.size())-1;i>=0;--i){
        if (digits[i] > other.digits[i]){
            res = true; break;
        }
        res = false;
    }
    return res;
}

bool Lint::operator<=(Lint other) {return not(operator>(other));}

bool Lint:: operator>=(Lint other) {return (operator>(other) or operator==(other));}

bool Lint:: operator<(Lint other) {return not(operator>=(other));}

/*
 * arithmetic operators
 */
Lint Lint::operator+(Lint other){
    Lint sum;
    int carry = 0;
    int max_size = int(max(digits.size(), other.digits.size()));
    for (int i=0;i< max_size;++i){
        int d = 0;

        if (i<digits.size()) d += digits[i];
        if (i<other.digits.size()) d+=other.digits[i];

        sum.digits.push_back((d+carry)%10);
        carry = (d+carry)/10;
    }
    if(carry) sum.digits.push_back(carry);
    return sum;
}

/*
 * i/o stream operators
 */
ostream& operator<<(ostream &out, Lint num){
    for (int i=int(num.digits.size())-1;i>=0;--i){
        out <<num.digits[i];}
    out<<endl;
    return out;
}

istream& operator>>(istream& in, Lint& num){
    string input;
    in >> input;
    num = Lint(input);
    return in;
}
