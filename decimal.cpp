#include <vector>
#include "vecArithmetic.h"
#include <iostream>
using namespace std;

class DecimalException: public exception{
public:
    const char* what() const throw(){
        return "Division by zero";
    }
};

class Decimal{
private:
    vector <int> digits;
    int exp;
public:
    Decimal()= default;
    Decimal(vector<int> d, int e=0){
        digits=d;
        exp=e;
    }
    bool operator==(Decimal other);
    Decimal operator*(Decimal& other);
    Decimal inverse();
    Decimal operator/(Decimal other);
    vector<int> getDigits();
    Decimal round();
    friend ostream& operator<<(ostream &out, Decimal num);
};

ostream& operator<<(ostream &out, Decimal num) {
    for (int i = num.digits.size() - 1; i >= num.digits.size()-6; --i) {
        out << num.digits[i];
    }
    out << "e" << num.exp+int(num.digits.size())-6;
    return out;
}

bool Decimal::operator==(Decimal other) {
    return digits==other.digits && exp==other.exp;
}

Decimal Decimal:: operator*(Decimal& other){
    Decimal res;
    res.digits = fft_mul(digits,other.digits);
    carry_res(res.digits);
    trim(res.digits);
    res.exp = exp+other.exp;
    return res;
}

Decimal Decimal:: inverse(){
    if (digits.size()==1 && digits[0]==0){
        throw DecimalException();
    }
    Decimal guess({1},-digits.size());
    for(int i=0;i<8;++i){
        guess.digits = guess.digits*(add_zeroes({2},-guess.exp)-digits*guess.digits);
        carry_res(guess.digits);
        trim(guess.digits);
        for(int &el:guess.digits){
            if (el<0){
                el+=10;
            }
        }
        guess.exp = guess.exp*2;
    }
    return guess;
}

vector<int> Decimal::getDigits() {
    return digits;
}

Decimal Decimal:: round(){
    if (digits.size()<=-exp) {
        int s = digits.size();
        if (digits[s-1]==9 and digits[s-2]==9) return Decimal({1}, 0);
        else return Decimal({0},0);
    }
    for(int i=0;i<digits.size()+exp;++i){
        if (digits[i]>=5) digits[i+1]+=1;
    }
    carry_res(digits);
    while(exp<0){
        digits.erase(digits.begin());
        exp++;
    }
    return *this;
}

Decimal Decimal:: operator/(Decimal other){
    Decimal res;
    res.digits = fft_mul(digits,other.inverse().digits);
    carry_res(res.digits);
    trim(res.digits);
    res.exp = exp+other.inverse().exp;
    return res.round();
}
