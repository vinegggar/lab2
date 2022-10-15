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

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

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
