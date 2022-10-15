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

    Lint operator+(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

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
