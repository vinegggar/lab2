#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("169169")
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
    cout <<endl<< B;
    return 0;
}
