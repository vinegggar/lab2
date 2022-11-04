#include <iostream>
#include "longint.h"
#include "vecArithmetic.h"
using namespace std;


int main() {
    Lint A("3457874784")
    , C("256789987"), B, E("4");
    Lint::setMultMode(new NaiveMult);
    cout<<"Naive: "<<(A-C)*E;
    Lint::setMultMode(new Karatsuba);
    cout<<"Karatsuba: "<<(A-C)*E;
    Lint::setMultMode(new SchonhageStrassen);
    cout<<"Schonhage-Strassen: "<<(A-C)*E;
    Lint::setMultMode(new ToomCook);
    cout<<"Toom-Cook: "<<(A-C)*E;
    cout<<A/C;
    C.get_inv();
    return 0;
}
