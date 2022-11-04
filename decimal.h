#include <vector>
#include "vecArithmetic.h"
using namespace std;

class DecimalException: public exception{
public:
    const char* what() const throw();
};

class Decimal{
private:
    vector <int> digits;
    int exp;
public:
    Decimal()= default;
    Decimal(vector<int> d, int e=0);
    bool operator==(Decimal other);
    Decimal operator*(Decimal& other);
    Decimal inverse();
    Decimal operator/(Decimal other);
    vector<int> getDigits();
    Decimal round();
    friend ostream& operator<<(ostream &out, Decimal num);
};


