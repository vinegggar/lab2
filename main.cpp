#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("6779"), C("71898"), B;
//    cin>>B;
    Lint::setMultMode(new NaiveMult);
    cout<<"Naive: "<<A*C;
    Lint::setMultMode(new Karatsuba);
    cout<<"Karatsuba: "<<A*C;
    Lint::setMultMode(new SchonhageStrassen);
    cout<<"Schonhage-Strassen: "<<A*C;
    Lint::setMultMode(new ToomCook);
    cout<<"Toom-Cook: "<<A*C;
    return 0;
}
