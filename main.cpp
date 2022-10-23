#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("1385148"), B, C("879899");
    cin>>B;
    Lint::setMultMode(new NaiveMult);
    cout<<(A-C)*B;
    return 0;
}
