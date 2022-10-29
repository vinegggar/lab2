#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("18779777239"), C("75771"), B;
    cin>>B;
    Lint::setMultMode(new NaiveMult);
    cout<<A*C;
    cout<<(A-C)*B;
    Lint::setMultMode(new Karatsuba);
    cout<<"Karatsuba"<<endl;
    cout<<A*C;
    cout<<(A-C)*B;
    Lint::setMultMode(new SchonhageStrassen);
    cout<<"Schonhage-Strassen"<<endl;
    cout<<A*C;
    cout<<(A-C)*B;
    return 0;
}
