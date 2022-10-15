#include <vector>
using namespace std;
class Lint{
private:
    vector <int> digits;
    string val;
public:
    Lint()=default;
    Lint(string val);
};

ostream& operator<<(ostream &out, Lint num);
istream& operator>>(istream& in, Lint& num);