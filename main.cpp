#include <iostream>
#include "longint.h"
#include "vecArithmetic.h"
using namespace std;


int main() {
    Lint A("1691691691")
    , C("13"), B, E("4");
    Lint::setMultMode(new NaiveMult());
    cout<< "Naive: " << A * C << endl;
    Lint::setMultMode(new Karatsuba());
    cout<< "Karatsuba: " << A * C << endl;
    Lint::setMultMode(new SchonhageStrassen());
    cout<< "Schonhage-Strassen: " << A * C << endl;
    Lint::setMultMode(new ToomCook());
    cout<< "Toom-Cook: " << A * C << endl;

    cout<< "Inverse: ";
    C.get_inv();
    B = A / C;
    cout<<endl;
    Lint D = A%C;
    cout << "A/C = " << B << endl;
    cout << "A%C = " << D << endl;

    Lint::setTestMode(new Fermat());
    cout << "Fermat: " << A.primeCheck();
    return 0;
}
