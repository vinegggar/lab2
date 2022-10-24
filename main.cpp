#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("49988556"), C("9565587"), B;
    cin>>B;
    Lint::setMultMode(new NaiveMult);
    cout<<A*C;
    cout<<(A-C)*B;
    Lint::setMultMode(new Karatsuba);
    cout<<"Karatsuba"<<endl;
    cout<<A*C;
    cout<<(A-C)*B;
    return 0;
}
