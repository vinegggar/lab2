#include <iostream>
#include <vector>
using namespace std;

class Lint{
private:
    vector <int> digits;
public:
    Lint()= default;
    Lint(string number){
        for (int i=number.size()-1; i>=0;--i)
            digits.push_back(number[i]-'0');
    }

    friend ostream& operator<<(ostream &out, Lint num);
};

ostream& operator<<(ostream &out, Lint num){
    for (int i=num.digits.size()-1;i>=0;--i){
        out <<num.digits[i];}
    out<<endl;
    return out;
}

int main() {
    Lint A("45666"), B;

    cout << A;
    return 0;
}
