#include <iostream>
#include <vector>
using namespace std;
class Lint{
private:
    vector <int> digits;
    string val;
public:
    Lint();
    Lint(string val);
    Lint operator +(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};