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
    ~Decimal(){
        digits.clear();
    }
    bool operator==(Decimal other);

    Decimal operator*(Decimal other);
    Decimal inverse();
    Decimal operator/(Decimal other);

    vector<int> getDigits();
    Decimal floor();

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


Decimal Decimal:: operator*(Decimal other){
    Decimal res;
    res.digits = fft_mul(digits,other.digits);
    carry_res(res.digits);
    trim(res.digits);
    res.exp = exp+other.exp;
    return res;
}

Decimal Decimal:: inverse(){
    if (digits==vector<int>(1)){
        throw DecimalException();
    }
    Decimal guess({1},-digits.size());
    for(int i=0;i<12;++i){
        guess.digits = guess.digits*(add_zeroes({2},-guess.exp)- digits*guess.digits);
        carry_res(guess.digits);
        trim(guess.digits);
        guess.exp = guess.exp*2;

        while(guess.digits.size()>128){//optimization because length of number is growing exponentially
            guess.digits.erase(guess.digits.begin());
            guess.exp++;
        }
    }
    return guess;
}

vector<int> Decimal::getDigits() {
    return digits;
}

Decimal Decimal:: floor(){
    carry_res(digits);
    Decimal res;
    vector<int> decimal;
    for(int i=-exp-1;i>=-exp-12;--i){
        decimal.push_back(digits[i]);
    }
    while (exp < 0) {
        digits.erase(digits.begin());
        exp++;
    }
    res.digits = decimal==vector<int>(12,9)? digits+vector<int>{1}: digits;
    carry_res(res.digits);
    trim(res.digits);
    res.exp = exp;
    return res;
}


Decimal Decimal:: operator/(Decimal other){
    Decimal res;
    if (other==Decimal({1}))return *this;
    if(other.digits>digits) return Decimal({0});
    else if(digits==other.digits){return Decimal({1});}
    else {
        res.digits = digits*other.inverse().digits;
        carry_res(res.digits);
        trim(res.digits);
        res.exp = exp + other.inverse().exp;
        return res.floor();
    }
}
